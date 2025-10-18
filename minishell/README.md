# Minishell Project Summary

## Project Overview
Minishell is a project that requires creating a simple Unix shell, similar to bash. The goal is to develop a command-line interpreter that can execute commands, manage processes, handle input/output redirections, and implement built-in shell functionalities. This project provides deep understanding of process management, file descriptors, and shell internals.

## Key Features & Requirements

### Core Functionality
- **Command prompt display** showing input waiting for new commands
- **Working history system** for command recall
- **Executable search and execution** using PATH variable or relative/absolute paths
- **Signal handling** with limited global variable usage (only for signal reception indication)
- **Quoting mechanisms**:
  - Single quotes (') prevent interpretation of all metacharacters
  - Double quotes (") prevent interpretation except for $ (dollar sign)

### Redirections Implementation
- **Input redirection**: `<` redirects input
- **Output redirection**: `>` redirects output
- **Heredoc**: `<<` reads input until delimiter appears
- **Append mode**: `>>` redirects output in append mode

### Advanced Features
- **Pipes implementation** (`|`) connecting command outputs to subsequent command inputs
- **Environment variable expansion** (`$` followed by characters) expanding to their values
- **Exit status expansion** (`$?`) showing the most recent command's exit status
- **Signal management**:
  - `ctrl-C` prints new prompt on a new line
  - `ctrl-D` exits the shell
  - `ctrl-\` does nothing

### Built-in Commands
- `echo` with `-n` option
- `cd` with relative or absolute paths
- `pwd` without options
- `export` without options
- `unset` without options
- `env` without options or arguments
- `exit` without options

### Technical Constraints
- **Single global variable** allowed only for signal reception indication
- **No interpretation** of unclosed quotes or unspecified special characters (`\`, `;`)
- **Memory management**: No memory leaks except for readline function inherent leaks
- **Bash compatibility**: Use bash as reference for ambiguous cases

## Authorized Functions
The project permits these key function groups:

### Readline & History Functions
- `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`

### Process Management
- `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `execve`, `kill`, `exit`

### File Operations
- `open`, `close`, `read`, `write`, `access`, `dup`, `dup2`, `pipe`, `unlink`
- `stat`, `lstat`, `fstat`, `opendir`, `readdir`, `closedir`

### System Information
- `getcwd`, `chdir`, `getenv`, `isatty`, `ttyname`, `ttyslot`

### Signal Handling
- `signal`, `sigaction`

### Error Handling
- `perror`, `strerror`

### Terminal Operations
- `ioctl`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

### Memory Management
- `malloc`, `free`

### Output
- `printf`

## Bonus Features
- **Logical operators**: `&&` (AND), `||` (OR) with parentheses for priority
- **Wildcards**: `*` wildcard functionality for current directory

## Evaluation Criteria
- Mandatory part must be **perfect** for bonus evaluation
- No unexpected crashes (segmentation faults, bus errors, double free)
- Proper memory management with no memory leaks (except readline)
- Norm compliance for all code
- Makefile requirements: $(NAME), all, clean, fclean, re rules
- libft integration if used

This project emphasizes robust process management, proper signal handling, accurate command parsing, and efficient memory management while replicating core shell functionalities found in modern Unix systems.
