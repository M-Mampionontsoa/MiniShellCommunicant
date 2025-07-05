# MiniShellCommunicant
This project try to imitate the terminal with some commands 


## Overview

Mini Shell Communicant is a C-based command-line application that provides a simple shell interface for managing environment variables, executing external commands, and enabling inter-process communication via named pipes. It also includes a background thread to monitor system resources such as memory and CPU usage in real-time.

The project consists of multiple C files, including a main program, a library of core functionalities, and two example programs (`ecrivain.c` and `lecteur.c`) demonstrating inter-process communication using named pipes.

## Features

- **Environment Variable Management**: View and modify environment variables dynamically.
- **External Command Execution**: Run standard Linux commands (e.g., `ls`, `date`) through a pipe-based mechanism.
- **Inter-Process Communication**: Execute two user-specified programs and enable communication between them using named pipes.
- **Resource Monitoring**: A background thread displays real-time memory and CPU usage every 10 seconds.
- **Interactive Menu**: A user-friendly menu to navigate the available functionalities.

## Project Structure

The project is organized into the following files:

- **main.c**: Entry point of the program. Initializes a background thread for resource monitoring and runs the main menu loop.
- **ProgrammePrincipal.h**: Header file declaring the core functions for the shell's operations.
- **ProgrammePrincipal.c**: Implementation of the core functionalities, including menu handling, environment variable management, command execution, and inter-process communication.
- **ecrivain.c**: A sample program (writer) that creates a named pipe and sends a message.
- **lecteur.c**: A sample program (reader) that reads a message from the named pipe created by `ecrivain.c`.

## Prerequisites

To compile and run this project, you need:

- A Linux-based operating system (e.g., Ubuntu).
- GCC compiler.
- POSIX thread library (`pthread`).
- Standard C libraries (`stdio.h`, `stdlib.h`, `unistd.h`, `sys/types.h`, `sys/wait.h`, `string.h`, `fcntl.h`).

## Compilation Instructions

1. Clone or download the project to your local machine.
2. Navigate to the project directory:

   ```bash
   cd mini-shell-communicant
   ```
3. Compile the main program:

   ```bash
   gcc -o mini_shell main.c ProgrammePrincipal.c -pthread
   ```
4. Compile the writer and reader programs for inter-process communication testing:

   ```bash
   gcc -o ecrivain ecrivain.c
   gcc -o lecteur lecteur.c
   ```
5. Ensure the compiled executables (`ecrivain` and `lecteur`) are in the same directory as `mini_shell` for the inter-process communication feature to work.

## Usage

1. Run the main program:

   ```bash
   ./mini_shell
   ```
2. The program displays an interactive menu with the following options:
   - **1. Environment Variable Management**:
     - View all environment variables at the current time.
     - Modify existing variables or add new ones (e.g., append to `PATH` or create a new variable).
   - **2. Execute External Command**:
     - Enter a Linux command (e.g., `ls`, `date`) to execute it via a pipe-based child process.
   - **3. Inter-Process Communication**:
     - Specify two executable programs (e.g., `./ecrivain` and `./lecteur`) to run them concurrently and enable communication via a named pipe.
   - **0. Exit**:
     - Terminate the program.
3. A background thread runs continuously, displaying memory usage (`free -m`) and CPU load (`/proc/loadavg`) every 10 seconds.

### Example Usage

- To view environment variables:
  - Select option `1` and then `1` again to list all variables.
- To add a new environment variable:
  - Select option `1`, then `2`, and then `1`. Enter the variable in the format `NAME=VALUE`.
- To run a command like `ls`:
  - Select option `2` and enter `ls` at the prompt.
- To test inter-process communication:
  - Ensure `ecrivain` and `lecteur` are compiled.
  - Select option `3` and enter `ecrivain lecteur` to run both programs.

## Inter-Process Communication Example

The `ecrivain.c` and `lecteur.c` programs demonstrate communication via a named pipe (`/tmp/mon_tube`):

- `ecrivain` creates a named pipe and writes a message ("Salut depuis l'écrivain!").
- `lecteur` reads the message from the pipe and displays it.
- To test manually:

  ```bash
  ./ecrivain &
  ./lecteur
  ```

## Notes

- The program assumes that the executables for inter-process communication (e.g., `ecrivain`, `lecteur`) are in the current directory.
- The resource monitoring thread runs indefinitely and outputs system stats every 10 seconds.
- Ensure proper permissions for creating named pipes (e.g., `/tmp/mon_tube`).
- The program uses `scanf` for input, so ensure inputs are correctly formatted to avoid unexpected behavior.
- Memory allocated in `varEvenGestion` (e.g., `newPath`) is not freed, which may cause memory leaks in long-running sessions. Consider adding `free` calls for production use.

## Limitations

- The inter-process communication feature requires precompiled executables in the current directory.
- The external command execution is limited to commands in `/usr/bin/`.
- Input validation is minimal; invalid inputs may cause unexpected behavior.
- The program does not handle signals or gracefully terminate the background thread on exit.

## Future Improvements

- Add robust input validation and error handling.
- Free allocated memory in `varEvenGestion` to prevent leaks.
- Enhance the inter-process communication to support dynamic pipe creation and more complex interactions.
- Allow users to specify the path for external commands beyond `/usr/bin/`.
- Implement signal handling to gracefully terminate the background thread.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

# Author:Mario MAMPIONONTSOA
