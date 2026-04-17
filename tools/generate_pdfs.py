#!/usr/bin/env python3
from __future__ import annotations

import math
import re
from pathlib import Path
from typing import Iterable, List, Tuple

from pygments import lex
from pygments.lexers import CLexer
from pygments.token import Token
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4, landscape
from reportlab.pdfbase.pdfmetrics import stringWidth
from reportlab.pdfgen import canvas

ROOT = Path(__file__).resolve().parents[1]
PDF_DIR = ROOT / "pdfs"

TXT_PAGE = landscape(A4)
CODE_PAGE = A4

MARGIN = 36
BOTTOM_MARGIN = 30
TITLE_GAP = 14

CODE_FONT = "Courier"
TXT_FONT = "Courier"
TITLE_FONT = "Helvetica-Bold"

# High-contrast palette inspired by dark-theme syntax colors, adapted for white paper.
PALETTE = {
    "default": colors.HexColor("#1F2328"),
    "keyword": colors.HexColor("#7A2EAE"),
    "type": colors.HexColor("#005CC5"),
    "function": colors.HexColor("#0B5CAD"),
    "string": colors.HexColor("#AF3A1A"),
    "number": colors.HexColor("#0D7A5F"),
    "comment": colors.HexColor("#6A737D"),
    "preproc": colors.HexColor("#B36A00"),
    "operator": colors.HexColor("#374151"),
}


def list_project_files(pattern: str) -> List[Path]:
    return sorted(path for path in ROOT.glob(pattern) if path.is_file() and path.parent == ROOT)


def normalize_lines(text: str) -> List[str]:
    return text.replace("\r\n", "\n").replace("\r", "\n").split("\n")


def fit_font_size(lines: Iterable[str], width: float, height: float, start: int, end: int, line_factor: float = 1.25) -> float:
    lines = list(lines)
    for size in range(start, end - 1, -1):
        max_width = max((stringWidth(line, CODE_FONT, size) for line in lines), default=0)
        line_height = size * line_factor
        max_lines = math.floor(height / line_height)
        if max_width <= width and len(lines) <= max_lines:
            return float(size)
    return float(end)


def remove_42_header(content: str) -> str:
    stripped = content.lstrip()
    if not stripped.startswith("/*"):
        return content

    start_offset = len(content) - len(stripped)
    end_idx = stripped.find("*/")
    if end_idx == -1:
        return content

    header_block = stripped[: end_idx + 2]
    marker = header_block.lower()
    looks_like_header = any(k in marker for k in ("created:", "updated:", "by:", "42"))

    if not looks_like_header:
        return content

    remainder = stripped[end_idx + 2 :]
    return remainder.lstrip("\n")


def draw_preformatted_text_pdf(src: Path, dst: Path) -> None:
    c = canvas.Canvas(str(dst), pagesize=TXT_PAGE)
    page_w, page_h = TXT_PAGE

    file_name = src.stem.upper()
    title_size = 16
    c.setFillColor(PALETTE["default"])
    c.setFont(TITLE_FONT, title_size)
    c.drawString(MARGIN, page_h - MARGIN, file_name)

    text = src.read_text(encoding="utf-8", errors="replace")
    lines = [line.expandtabs(4) for line in normalize_lines(text)]

    content_top = page_h - MARGIN - title_size - TITLE_GAP
    content_height = content_top - BOTTOM_MARGIN
    content_width = page_w - (2 * MARGIN)

    font_size = fit_font_size(lines, content_width, content_height, start=11, end=6)
    line_h = font_size * 1.22

    # Count total pages
    total_pages = 1
    y_test = content_height
    for _ in lines:
        y_test -= line_h
        if y_test < BOTTOM_MARGIN + 25:
            total_pages += 1
            y_test = page_h - MARGIN - 30 - BOTTOM_MARGIN

    y = content_top
    current_page = 1
    c.setFont(TXT_FONT, font_size)
    c.setFillColor(PALETTE["default"])

    for line in lines:
        if y - line_h < BOTTOM_MARGIN + 25:
            # Draw footer before new page
            c.setFont("Helvetica", 9)
            c.setFillColor(PALETTE["default"])
            page_text = f"{src.stem} ({current_page}/{total_pages})"
            c.drawRightString(page_w - MARGIN, BOTTOM_MARGIN - 10, page_text)
            
            c.showPage()
            current_page += 1
            y = page_h - MARGIN - 30
            c.setFont(TXT_FONT, font_size)
            c.setFillColor(PALETTE["default"])
        
        c.drawString(MARGIN, y, line)
        y -= line_h

    # Final page footer
    c.setFont("Helvetica", 9)
    c.setFillColor(PALETTE["default"])
    page_text = f"{src.stem} ({current_page}/{total_pages})"
    c.drawRightString(page_w - MARGIN, BOTTOM_MARGIN - 10, page_text)

    c.save()


def token_color(ttype) -> colors.Color:
    if ttype in Token.Comment:
        return PALETTE["comment"]
    if ttype in Token.Keyword:
        return PALETTE["keyword"]
    if ttype in Token.Keyword.Type:
        return PALETTE["type"]
    if ttype in Token.Name.Function:
        return PALETTE["function"]
    if ttype in Token.Literal.String:
        return PALETTE["string"]
    if ttype in Token.Literal.Number:
        return PALETTE["number"]
    if ttype in Token.Comment.Preproc or ttype in Token.Comment.PreprocFile:
        return PALETTE["preproc"]
    if ttype in Token.Operator:
        return PALETTE["operator"]
    return PALETTE["default"]


def lex_line(line: str) -> List[Tuple[str, colors.Color]]:
    parts: List[Tuple[str, colors.Color]] = []
    for ttype, value in lex(line, CLexer()):
        if not value:
            continue
        if value.endswith("\n"):
            value = value[:-1]
        if value:
            parts.append((value, token_color(ttype)))
    if not parts:
        parts.append(("", PALETTE["default"]))
    return parts


def choose_code_font_size(lines: List[str], width: float, height: float) -> float:
    return fit_font_size(lines, width, height, start=10, end=6)


def draw_code_title(c: canvas.Canvas, page_h: float, name: str, continuation: bool = False) -> float:
    c.setFillColor(PALETTE["default"])
    if not continuation:
        c.setFont(TITLE_FONT, 14)
        c.drawString(MARGIN, page_h - MARGIN, name.upper())
        return page_h - MARGIN - 14 - TITLE_GAP
    else:
        return page_h - MARGIN - 30


def draw_functions_pdf(files: List[Path], dst: Path) -> None:
    c = canvas.Canvas(str(dst), pagesize=CODE_PAGE)
    page_w, page_h = CODE_PAGE
    content_width = page_w - (2 * MARGIN)

    first_file = True
    for file_path in files:
        if not first_file:
            c.showPage()
        first_file = False

        raw = file_path.read_text(encoding="utf-8", errors="replace")
        body = remove_42_header(raw)
        lines = [line.expandtabs(4) for line in normalize_lines(body)]

        file_name = file_path.name

        # Determine font size based on first page layout
        first_page_top = page_h - MARGIN - 14 - TITLE_GAP
        content_height_available = first_page_top - BOTTOM_MARGIN
        font_size = choose_code_font_size(lines, content_width, content_height_available)
        line_h = font_size * 1.23

        # Count total pages using smart page break logic
        total_pages = 1
        y = content_height_available
        for _ in lines:
            y -= line_h
            if y < BOTTOM_MARGIN + 25:
                total_pages += 1
                y = page_h - MARGIN - 30 - BOTTOM_MARGIN

        # Draw the file
        current_page = 1
        c.setFillColor(PALETTE["default"])
        c.setFont(TITLE_FONT, 14)
        c.drawString(MARGIN, page_h - MARGIN, file_name.upper())

        y = page_h - MARGIN - 14 - TITLE_GAP
        c.setFont(CODE_FONT, font_size)

        for line in lines:
            # Smart page break: if line won't fit with footer space, start new page
            if y - line_h < BOTTOM_MARGIN + 25:
                # Draw footer before new page
                c.setFont("Helvetica", 9)
                c.setFillColor(PALETTE["default"])
                page_text = f"{file_name} ({current_page}/{total_pages})"
                c.drawRightString(page_w - MARGIN, BOTTOM_MARGIN - 10, page_text)

                c.showPage()
                current_page += 1
                y = page_h - MARGIN - 30
                c.setFont(CODE_FONT, font_size)

            x = MARGIN
            for chunk, color in lex_line(line):
                c.setFillColor(color)
                c.drawString(x, y, chunk)
                x += stringWidth(chunk, CODE_FONT, font_size)
            y -= line_h

        # Final page footer
        c.setFont("Helvetica", 9)
        c.setFillColor(PALETTE["default"])
        page_text = f"{file_name} ({current_page}/{total_pages})"
        c.drawRightString(page_w - MARGIN, BOTTOM_MARGIN - 10, page_text)

    c.save()


def main() -> None:
    PDF_DIR.mkdir(parents=True, exist_ok=True)

    txt_files = list_project_files("*.txt")
    c_h_files = sorted(
        [
            path
            for path in ROOT.glob("*")
            if path.is_file() and path.suffix in {".c", ".h"}
        ]
    )

    for txt in txt_files:
        draw_preformatted_text_pdf(txt, PDF_DIR / f"{txt.stem}.pdf")

    draw_functions_pdf(c_h_files, PDF_DIR / "functions.pdf")

    print(f"Generated {len(txt_files)} text PDFs + functions.pdf in {PDF_DIR}")


if __name__ == "__main__":
    main()
