![Rating](/assets/images/header.png)

# PHILOSOPHERS

## Description
In this project, you will learn the basic principles of threading a process.
You will learn how to create threads and discover mutexes.

> Classic version

	The dining philosophers problem is a classic concurrent programming problem that illustrates synchronization issues, where five philosophers alternate between thinking and eating, but can only eat if they have access to two forks (one to their left and one to their right). This creates potential race conditions, deadlock, and starvation if concurrent access to shared resources (the forks) is not handled correctly.

> Project version
- One or more philosophers sit at a round table.
- In the center of the table is a large bowl of spaghetti.
- When a philosopher finishes eating, they will put the forks back on the table and immediately start sleeping. Once they wake up, they will start thinking again.
- The simulation stops when a philosopher dies of starvation.
- There are also forks on the table, as many forks as philosophers.
- All philosophers need to eat and should never starve.
- Philosophers don't know if another philosopher is going to die.
- If there is only one philosopher, there will only be one fork on the table.

## Allowed Functions
| Function | Description |
| ------- | ----------- |
| memset | Fills a block of memory with a specific value |
| printf | Prints formatted text to standard output |
| malloc | Dynamically allocates a block of memory in the heap |
| free | Frees a block of memory previously allocated with malloc |
| write | Writes data from a buffer to a file descriptor |
| usleep | Suspends program execution for a time in microseconds |
| gettimeofday | Gets the current system time in seconds and microseconds |
| pthread_create | Creates a new execution thread |
| pthread_detach | Detaches a thread, allowing it to automatically release its resources when finished |
| pthread_join | Waits for a thread to finish execution and collects its return value |
| pthread_mutex_init | Initializes a mutex for thread synchronization |
| pthread_mutex_destroy | Destroys a mutex, releasing associated resources |
| pthread_mutex_lock | Locks a mutex, preventing other threads from acquiring it |
| pthread_mutex_unlock | Unlocks a mutex, allowing other threads to acquire it |

* USING LIBFT IS NOT ALLOWED

## Restrictions
- Global variables are prohibited.
- Philosophers can only eat, think, or sleep.
- While eating, they cannot think or sleep;
- While thinking, they cannot sleep or eat;
- While sleeping, they cannot eat or think.
- Philosophers must take the right fork and the left fork, one in each hand.
- Philosophers do not speak to each other.
- All must avoid dying.
- The printed state must not be broken or altered by the state of other philosophers.
- You cannot have more than 10ms between a philosopher's death and when you print their death.
- Your program must not have any data races.
- To prevent philosophers from duplicating forks, you must protect the fork states with a mutex for each one.
- Mandatory part directory: philo/
- Bonus part directory: philo_bonus/

> Any philosopher state change must have the following format:
- (current time in milliseconds) (philosopher number) has taken a fork
- (current time in milliseconds) (philosopher number) is eating
- (current time in milliseconds) (philosopher number) is sleeping
- (current time in milliseconds) (philosopher number) is thinking
- (current time in milliseconds) (philosopher number) died

## Program Arguments
| Position | Name |
| -------- | ------ |
| 1 | number_of_philosophers | is the number of philosophers, but also the number of forks |
| 2 | time_to_die (in milliseconds) if a philosopher does not start eating within time_to_die milliseconds from the start of their last meal or from the beginning of the simulation, they will die |
| 3 | time_to_eat (in milliseconds) is the time a philosopher has to eat. During this time, they will have the forks occupied |
| 4 | time_to_sleep (in milliseconds) is the time a philosopher has to sleep |
| 5 | number_of_times_each_philosopher_must_eat (optional argument) if all philosophers eat at least number_of_times_each_philosopher_must_eat times, the simulation will stop. If not specified, the simulation will stop with the death of a philosopher |

- Each philosopher must be a thread.
- Each philosopher will be assigned a number from 1 to number_of_philosophers.
- Philosopher number 1 will sit next to philosopher number number_of_philosophers.
- Any other philosopher number N will sit between philosopher number N - 1 and philosopher number N + 1.

## When is it acceptable for a philosopher to die?
- When there is only 1; Dies because there is only one fork, so they cannot eat.
- When the number of philosophers is even:
	- If the time until they need to eat is less than the time it takes to eat plus the time to sleep. Dies because there is not enough time to complete the cycle.
	- If the time it takes to eat is greater than half the time until they need to eat again. Dies while eating because there is not enough time to finish.
- When the number of philosophers is odd:
	- If the time until they need to eat is less than the time it takes to eat plus the time to sleep. Dies because there is not enough time to complete the cycle.
	- If the time it takes to eat is greater than one third of the time until they need to eat again. Dies while eating because there is not enough time to finish.

## BONUS

### Description
Philosophers with processes and semaphores

The specific rules for the bonus part are:
- The forks are in the center of the table.
- The forks do not have memory states, but the number of available forks is represented by a semaphore.
- Each philosopher must be a process, and the main process must not be a philosopher.

### Allowed Functions
| Function | Description |
| ------- | ----------- |
| memset | Fills a block of memory with a specific value |
| printf | Prints formatted text to standard output |
| malloc | Dynamically allocates a block of memory in the heap |
| free | Frees a block of memory previously allocated with malloc |
| write | Writes data from a buffer to a file descriptor |
| fork | Creates a new process by duplicating the current process |
| kill | Sends a signal to a process to perform an action, such as terminating it |
| exit | Terminates the current process and returns a status code to the system |
| pthread_create | Creates a new execution thread in a multithreaded program |
| pthread_detach | Detaches a thread, allowing automatic release of its resources |
| pthread_join | Waits for a thread to finish and collects its return value |
| usleep | Suspends program execution for a time in microseconds |
| gettimeofday | Gets the current system time in seconds and microseconds |
| waitpid | Waits for a specific child process to finish and collects its exit status |
| sem_open | Opens or creates a POSIX semaphore |
| sem_close | Closes a POSIX semaphore |
| sem_post | Increments (releases) a semaphore's counter |
| sem_wait | Decrements (blocks) a semaphore's counter, waiting if necessary |
| sem_unlink | Removes a previously created POSIX semaphore |

## Glossary
- Threads: Lightweight units of execution within a process that share the same memory space and resources, allowing concurrent execution.
- Mutex: A synchronization mechanism used to prevent race conditions, allowing only one thread to access a shared resource at a time.
- Process: A running instance of a program, with its own memory space and resources independent of other processes.
- Inline: In C, the inline keyword is used to suggest to the compiler that a function should be inserted directly into the code instead of being called through the normal function call routine. This can improve performance by avoiding call overhead, but it's only a suggestion; the compiler may ignore it if deemed necessary.
- deadlock

## Includes
- limits.h: Defines constants that specify the limits of standard data types (e.g., INT_MAX, CHAR_MIN).
- memory.h: Declares functions for manipulating memory blocks, such as memcpy, memset and memmove.
- pthread.h: Provides interfaces for POSIX thread programming, including thread creation, synchronization, and management.
- stdio.h: Declares functions for standard input and output, such as printf, scanf, fopen, and fclose.
- stdlib.h: Defines functions for dynamic memory management, string conversion, and process execution, such as malloc, free, atoi, and exit.
- sys/time.h: Provides functions for obtaining and manipulating times and dates, such as gettimeofday and timercmp.
- unistd.h: Declares functions for basic system operations, such as read, write, fork, and sleep.
- sys/types.h: Defines data types used in system calls, such as pid_t, size_t, and off_t.
- sys/wait.h: Declares macros and functions for handling child process termination, such as wait, waitpid, and WIFEXITED.
- stdbool.h: Defines the boolean type bool and the values true and false to represent boolean logic in C.
- fcntl.h: Provides functions and macros for file and descriptor control, such as open, fcntl, and O_RDONLY.
- sys/stat.h: Declares functions and macros for handling file attributes, such as stat, chmod, and S_IRUSR.
- semaphore.h: Defines functions and types for POSIX semaphore-based synchronization, such as sem_init, sem_wait, and sem_post.
- signal.h: Declares functions and macros for signal handling, such as signal, kill, and raise.

[$${\color{red}BACK$$}$$](../../README.md)

With 200 philosophers I get delays greater than 10ms

## ERRORS
### FATAL: ThreadSanitizer: unexpected memory mapping 0x584eeef07000-0x584eeef0b000
- https://stackoverflow.com/questions/77850769/fatal-threadsanitizer-unexpected-memory-mapping-when-running-on-linux-kernels
- https://ziggit.dev/t/threadsanitizer-unexpected-memory-mapping-error/4930
- https://github.com/google/sanitizers/issues/1696

SOLUTION??SO
https://github.com/google/sanitizers/issues/1716
https://stackoverflow.com/questions/62001623/why-does-helgrind-show-lock-order-violated-error-message

To implement a mechanism that allows knowing how many child processes have finished correctly or prematurely, you can use the functions and macros provided by waitpid(), WIFEXITED(status), WEXITSTATUS(status), and kill().
Key concepts:

    waitpid(-1, &status, 0): Waits for any child process to finish and saves the exit status in status.
    WIFEXITED(status): Returns true if the child process terminated normally (i.e., called exit() or returned from main()).
    WEXITSTATUS(status): Returns the exit code of the child process if it terminated normally.
    kill(): Used to send a signal to a specific process. Can be used to terminate children prematurely, for example, with the SIGTERM or SIGKILL signal.

Proposed mechanism:

    The parent process will create multiple children (using fork()).
    Children will terminate normally (exit()) or prematurely (via kill() or signals).
    The parent monitors its children with waitpid(-1, &status, 0) and uses the WIFEXITED() and WEXITSTATUS() macros to count how many children terminated normally and how many terminated prematurely.

Implementation example:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    int num_children = 5;
    int children_completed_correctly = 0;
    int children_completed_prematurely = 0;

    pid_t pid;
    int i;

    // Create multiple child processes
    for (i = 0; i < num_children; i++) {
        pid = fork();

        if (pid == 0) {
            // Child code
            if (i % 2 == 0) {
                // Children with even indices terminate normally
                printf("Child %d: terminating normally.\n", getpid());
                exit(0);  // Exit code 0 indicates success
            } else {
                // Children with odd indices wait and are terminated by a signal
                printf("Child %d: waiting and terminated prematurely.\n", getpid());
                sleep(5);
                // The parent can kill this process after a certain time
            }
        } else if (pid < 0) {
            perror("Error during fork");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process: control child termination
    for (i = 0; i < num_children; i++) {
        int status;
        pid_t terminated_pid = waitpid(-1, &status, 0);  // Wait for any child

        if (terminated_pid == -1) {
            perror("Error in waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            // Child terminated normally with exit() or return
            printf("Parent: Child %d terminated correctly with exit code %d.\n", terminated_pid, WEXITSTATUS(status));
            children_completed_correctly++;
        } else if (WIFSIGNALED(status)) {
            // Child terminated prematurely due to a signal
            printf("Parent: Child %d was terminated prematurely by signal %d.\n", terminated_pid, WTERMSIG(status));
            children_completed_prematurely++;
        }
    }

    // The parent can terminate children that haven't finished prematurely
    for (i = 0; i < num_children; i++) {
        kill(0, SIGTERM);  // Terminates all children that haven't finished yet
    }

    printf("Summary: %d children terminated correctly.\n", children_completed_correctly);
    printf("Summary: %d children terminated prematurely.\n", children_completed_prematurely);

    return 0;
}
```

Code explanation:

    Create multiple children: The fork() loop creates num_children child processes. Each child has different behavior:
        If the child's index is even, the child process terminates normally with exit(0).
        If the index is odd, the child waits (using sleep()) and will be terminated prematurely by the parent after some time.

    Parent control:
        The parent process uses waitpid(-1, &status, 0) to wait for each child to finish.
        WIFEXITED(status): Checks if the child terminated normally. If so, the parent increments the children_completed_correctly counter.
        WIFSIGNALED(status): Checks if the child was terminated prematurely by a signal, in which case it increments the children_completed_prematurely counter.

    Using kill: After waiting for all children, the parent can use kill(0, SIGTERM) to terminate any child still running (in this case, the children that were waiting in sleep).

    Counters: At the end of the program, the parent prints the number of children that finished correctly or prematurely.

Important notes:

    waitpid(-1, &status, 0): -1 indicates that the parent will wait for any child to finish.
    WIFEXITED(status) and WEXITSTATUS(status): These macros check and get the exit code if the process terminated normally.
    WIFSIGNALED(status) and WTERMSIG(status): Check if the child was terminated by a signal and get the signal that caused its termination.

This mechanism allows you to count how many children terminated correctly and how many were terminated prematurely.

https://nafuka11.github.io/philosophers-visualizer/

### Testing
./philo 1 800 200 200. The philosopher should not eat and should die.
./philo 5 800 200 200. No philosopher should die.
./philo 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
./philo 4 410 200 200. No philosopher should die.
./philo 4 310 200 100. One philosopher should die.
With 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
./philo with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, and so forth.

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./philo 2 200 10 10 2
valgrind --tool=helgrind --track-fds=yes --history-level=approx  ./philo 2 200 10 10 2
valgrind --tool=drd ./philo 2 200 10 10 2
valgrind --tool=memcheck --leak-check=full ./philo 2 200 10 10 2

[$${\color{red}BACK}$$](../../README.md)
