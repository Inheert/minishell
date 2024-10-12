# Minishell

Minishell is a simple shell implementation written in C. It supports basic shell functionalities including command execution, signal handling, and built-in commands.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Features


- Command execution
- Signal handling
- Built-in commands (cd, echo, env, exit, export, pwd, unset)
- Support for heredoc
- Environment variable management

## Installation

To install and build Minishell, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/minishell.git
    cd minishell
    ```

2. Build the project using `make`:
    ```sh
    make
    ```

## Usage

To start the shell, run the following command after building the project:
```sh
./minishell
```

## Project structure


### Key Files and Directories

- [**includes/minishell.h**](/includes/minishell.h): Header file containing function prototypes and type definitions.
- [**src/main.c**](/src/main.c): Entry point of the application.
- [**src/exec/**](/src/exec/): Contains the implementation of command execution.
- [**src/parsing/**](/src/parsing/): Contains the lexer and tokenizer implementations.
- [**src/signals/**](src/signals/): Contains signal handling implementations.
- [**src/utils/**](src/utils/): Utility functions and helper modules.
- [**Makefile**](/Makefile): Build script for compiling the project.