*This project has been created as part of the 42 Curriculum by kramarat*

# Libft - Tu primera librería

## Description
The **Libft** project is the foundational step in the 42 curriculum, designed to help students 
understand the inner workings of the standard C library. 
The core objective is to move from high-level abstractions to native C code, effectively 
**"taking the training wheels off"** to master memory management,
pointer arithmetic, and data structures [1, 2].

By recreating essential functions from scratch, I have developed a deep understanding of the 
**"treasure map"** of memory addresses and the importance of memory integrity [3, 4]. 
This library serves as a personal toolkit for all my future C projects at 42.

## Instructions
The library is compiled into an archive file named `libft.a` using the provided **Makefile**.

### Compiling
To build the library, use the following commands:
*   `make`: Compiles the mandatory source files.
*   `make bonus`: Compiles the additional linked list functions.
*   `make clean`: Removes the object files.
*   `make fclean`: Removes the object files and the library file.
*   `make re`: Recompiles the entire library from scratch.

All files are compiled with the strict flags **`-Wall -Wextra -Werror`** 
	to ensure code quality and compliance [5].

## Resources
### References
*   **CS50x 2025 - Lecture 4 - Memory**: For foundational knowledge on pointers and hexadecimals [6].
*   **CS50x 2025 - Lecture 5 - Data Structures**: For implementing the "Bonus" linked list logic [2].
*   **Libft.pdf**: For project specifications and mandatory norms [7].

### Declaración de uso de IA
In accordance with the project requirements, I declare the following use of AI tools
(specifically NotebookLM) during development [8]:
*   **Debugging `ft_itoa`**: AI was used to identify logic errors 
	regarding integer overflows, specifically the "finite information" problem 
	of **`INT_MIN`** (-2147483648) [9, 10].
*   **Valgrind Optimization**: AI helped resolve **"conditional jump"** errors by suggesting 
	proper initialization techniques for heap memory, leading to the 
	**"Holy Grail"** of 0 errors from 0 contexts [4, 11].
*   **Logic Verification**: AI provided verification for edge cases in **`ft_calloc`**,
	ensuring that a call with zero parameters returns a unique, freeable pointer [12].

## Descripción detallada
The library consists of three main parts:
1.  **Libc Functions**: Re-implementations of standard functions like
	 `ft_strlen`, `ft_memset`, `ft_atoi`, `ft_calloc`, and `ft_strdup` [12].
2.  **Additional Functions**: Utility functions for string and memory manipulation, such as
	 `ft_substr`, `ft_strjoin`, `ft_split`, and `ft_itoa` [10, 13, 14].
3.  **Linked Lists (Bonus)**: Functions to manage a `t_list` structure, including
	`ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`, `ft_lstlast`, and `ft_lstclear` [15-17].
