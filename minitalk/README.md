
```markdown
![Rating](/_assets/images/header.png)

# MINITALK [subject](es.minitalk.pdf)

## Project Index
- [SERVER](#SERVER)
- [CLIENT](#CLIENT)
- [SERVER BONUS](#SERVER_BONUS)
- [CLIENT BONUS](#CLIENT_BONUS)
- [Bit Manipulation Operators](#Bit_Manipulation_Operators)
- [Extra Info](#Extra_Info)

## Description
Create a client/server service where clients can send text messages to the server using UNIX system signals SIGUSR1 and SIGUSR2. This means clients and server will be processes that send signals to each other. The server will run first. To send the text, we need to go character by character converting to binary, associating 0 and 1 with SIGUSR1 and SIGUSR2 signals.

In C, SIGUSR1 and SIGUSR2 signals are user-defined signals used for inter-process communication. These signals do not have default behavior associated with them and are available for programmers to use according to their needs.

## Allowed Functions

- [ft_printf](#ft_printf)
- [write](#write)
- [signal](#signal)
- [sigemptyset](#sigemptyset)
- [sigaddset](#sigaddset)
- [sigaction](#sigaction)
- [kill](#kill)
- [getpid](#getpid)
- [malloc](#malloc)
- [free](#free)
- [pause](#pause)
- [sleep](#sleep)
- [usleep](#usleep)
- [exit](#exit)

### ft_printf

For writing text to the screen.

### write

**Description:** Writes data from a buffer to a file descriptor.

**Prototype:** size_t write(int fd, const void *buf, size_t count);

**Usage:** Used to write data to a file or file descriptor. It's a low-level system call that provides direct interface with the operating system, unlike high-level functions like fprintf or fwrite in standard C libraries. Commonly used in Unix and Unix-like operating systems.

### signal

**Description:** Sets a handler routine for a specific signal.

**Prototype:** void (*signal(int signum, void (*handler)(int)))(int);

**Usage:** Defines how the program should behave when it receives a particular signal (e.g., SIGINT, SIGTERM).

### sigemptyset

**Description:** Initializes an empty signal set.

**Prototype:** int sigemptyset(sigset_t *set);

**Usage:** Prepares a signal set to contain no signals, useful before adding specific signals.

### sigaddset

**Description:** Adds a specific signal to a signal set.

**Prototype:** int sigaddset(sigset_t *set, int signum);

**Usage:** Modifies a signal set to include a specific signal.

### sigaction

**Description:** Changes the action to take when a specific signal is received.

**Prototype:** int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

**Usage:** Allows more detailed control over signal manipulation than signal.

### kill

**Description:** Sends a signal to a process or group of processes.

**Prototype:** int kill(pid_t pid, int sig);

**Usage:** Can be used to terminate processes, interrupt them, or send any other signal.

### getpid

**Description:** Returns the process ID of the calling process.

**Prototype:** pid_t getpid(void);

**Usage:** Get the unique identifier of the current process.

### malloc

**Description:** Allocates a block of memory of specified size.

**Prototype:** void *malloc(size_t size);

**Usage:** Reserves dynamic memory in the heap.

### free

**Description:** Frees a block of memory previously allocated by malloc, calloc, or realloc.

**Prototype:** void free(void *ptr);

**Usage:** Returns the allocated memory to the system.

### pause

**Description:** Causes the current process to wait until a signal is received.

**Prototype:** int pause(void);

**Usage:** Suspends program execution until a signal is received.

### sleep

**Description:** Suspends process execution for a specified number of seconds.

**Prototype:** unsigned int sleep(unsigned int seconds);

**Usage:** Pauses program execution for a determined time.

### usleep

**Description:** Suspends process execution for a specified number of microseconds.

**Prototype:** int usleep(useconds_t usec);

**Usage:** Similar to sleep, but with greater time precision.

### exit

**Description:** Terminates process execution and returns a status value to the operating system.

**Prototype:** void exit(int status);

**Usage:** Ends the program in a controlled manner, allowing resource release and returning an exit code.

## Additional Restrictions:

- You can use one global variable per program (one for client and one for server), but you must justify its use.

There are two structures per process where pending and blocked signals are stored. With 32-bit numbers, up to 32 signals can be managed.

### Bonus
- The server confirms each received signal by sending a signal back to the client.
- Supports Unicode characters.

<br>

## Bit Manipulation Operators

### Operator | (Bitwise OR) (server)

**Description:** Performs a bitwise OR operation between two numbers.

**Operation:** Compares each corresponding bit of the operands. If at least one of the bits is 1, the resulting bit will be 1; otherwise, it will be 0.

**Typical Use:** Used to set specific bits in a value.

### Operator << (Left Shift) (server)

**Description:** Shifts the bits of a number to the left by a specified number of positions.

**Operation:** Each left shift is equivalent to multiplying the number by 2. Bits shifted to the left leave the number and zeros are inserted from the right.

**Typical Use:** Used for fast multiplication operations by powers of two or for manipulating specific bits in binary values.

### Operator & (Bitwise AND) (client)

**Description:** Compares each bit of the operands. If both bits are 1, the resulting bit is 1. If either bit is 0, the resulting bit is 0.

### Operator >> (Right Shift) (client)

**Description:** Shifts the bits of the operand to the right by n positions. Bits shifted out of the number are discarded. If it's a signed integer, the sign bit may be replicated to fill the new bits on the left (arithmetic shift) or they may be filled with zeros (logical shift, typically used for unsigned integers).

<br>

## SERVER

### set_signals
``` c
void	set_signals(void)
```
Set the signals and associate SIGUSR1 and SIGUSR2 with the function that will handle the signal.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

### receive_msg
``` c
void	receive_msg(int sig_usr, siginfo_t *info, void *na)
```
Function that handles signals and "translates" them into characters to be displayed.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

### main
``` c
int	main(void)
```
Displays the process PID and waits to receive signals.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

## CLIENT

### ft_send_char
``` c
static void	ft_send_char(int pid, unsigned char c)
```
"Translates" a character to "binary" by making each signal correspond to SIGUSR1 or SIGUSR2.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

### ft_send_msg
``` c
static void	ft_send_msg(int pid, const char *str)
```
Simply handles passing the characters of a text to the function that sends them (ft_send_char).
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

### main
``` c
int	main(int argc, char *argv[])
```
Shows help if the executable was used incorrectly, and if everything is correct, sends the text.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

## BONUS

>Similar to the non-bonus version. The only difference is that the server must send a signal back confirming it has received it.

## SERVER BONUS

### receive_msg
``` c
void	receive_msg(int sig_usr, siginfo_t *info, void *na)
```
Send confirmation to the client.

``` c
	if (sig_usr == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (sig_usr == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
```
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

## CLIENT BONUS

### confirm_handler
``` c
static void	ft_confirm(int sig_usr)
```
Confirm that the signal has arrived and display a message.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

### main
``` c
int	main(int argc, char *argv[])
```
Sets the signal handler for arrival confirmation.
<div style='text-align: right;'>

[UP &#11014;](#minitalk-subject)
</div>

## Differences between signal and sigaction

### signal

**Prototype:** void (*signal(int signum, void (*handler)(int)))(int);

**Description:** Sets a handler routine for a specific signal.

**Usage:** A simpler and more direct way to associate a handler with a signal.

**Limitations:**

Less predictable behavior: Depending on the implementation, the action for a signal may be reset to default behavior after the signal is handled.

Limited control: Does not offer the ability to specify more details about how signals should be handled.

Compatibility: Less portable as some implementations may vary in behavior between different Unix and Unix-like systems.

### sigaction

**Prototype:** int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

**Description:** Allows setting a handler routine for a specific signal with more control and flexibility.

**Usage:** A more robust and controlled way to handle signals, recommended for serious applications.

**Advantages:**

Handler persistence: The handler set with sigaction is not automatically reset to default value after handling a signal, unless explicitly indicated.

More options: Allows specifying additional options, such as masking other signals while handling a specific signal and other advanced configurations.

Portability: More consistent and portable between different Unix and Unix-like systems.

>For applications requiring detailed and reliable signal handling, sigaction is the recommended option.

## Extra Info

### struct sigaction

	The struct sigaction structure is used in the sigaction function to specify how signals should be handled in a C program. It provides detailed control over signal behavior.

**Fields of struct sigaction**

sa_handler:

	Pointer to a function that handles the signal, or one of the constants:
		SIG_DFL: Uses the default behavior for the signal.
		SIG_IGN: Ignores the signal.
	Example: sa.sa_handler = handler;

sa_sigaction:

	Pointer to an extended signal handler function that provides additional information about the received signal. Used when SA_SIGINFO is set in sa_flags.
	Example: sa.sa_sigaction = extended_handler;

sa_mask:

	Set of signals that should be blocked (masked) during the execution of the signal handler to avoid interruptions by those signals.
	Example: sigemptyset(&sa.sa_mask);

sa_flags:

	Options that modify the behavior of the signal handler. Some of the most common options are:
		SA_RESTART: Causes certain system calls that are interrupted by this signal to be automatically restarted.
		SA_SIGINFO: Uses sa_sigaction instead of sa_handler to provide additional information about the signal.
	Example: sa.sa_flags = SA_RESTART;

sa_restorer:

	Obsolete field and generally not used in modern implementations. Ignored on most platforms.

---

Issues: When a client terminates before the entire text is sent, the server side starts corrupting the text because it no longer knows which position it's at in the character's bit string. This could be solved by storing the state in a static variable as a structure, for each different client PID.
The problem also appears when sending messages simultaneously from different clients.

To display the complete text once fully received, memory would need to be allocated for that text, but the server doesn't know the length. So the length could be sent before the text from the client, but then we couldn't know if it meets the condition of 1 second per 100 letters, since it would have to wait for everything to be sent (imagine 1 million characters)

[$${\color{red}BACK}$$](../../README.md)
```
