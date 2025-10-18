![Rating](/assets/images/header.png)

# LIBFT

>[!NOTE]
>THE LIBRARY HAS BEEN MODIFIED BY ADDING NEW FUNCTIONS AND MODIFYING SOME EXISTING FUNCTIONS, SO IT WOULD NOT PASS THE MOULINETTE. TO SEE THE ORIGINAL FUNCTIONS I SUBMITTED ON THE PLATFORM, SEE [ORIGINAL LIBFT](./../../libft_original/)

<table align="center">
<caption>Table of Contents</caption>
<tbody>
<tr><td align="center"><b>

[LIBFT](#LIBFT)</b></td>
    <td align="center"><b>
[ADDITIONAL](#ADDITIONAL)</td>
    <td align="center"><b>
[BONUS](#BONUS)</td>
    <td align="center"><b>
[UTILS](#UTILS)</td></tr>
<tr><td>

0. [ft_isalpha](#ft_isalpha)
1. [ft_isdigit](#ft_isdigit)
1. [ft_isalnum](#ft_isalnum)
1. [ft_isascii](#ft_isascii)
1. [ft_isprint](#ft_isprint)
1. [ft_strlen](#ft_strlen)
1. [ft_memset](#ft_memset)
1. [ft_bzero](#ft_bzero)
1. [ft_memcpy](#ft_memcpy)
1. [ft_memmove](#ft_memmove)
1. [ft_strlcpy](#ft_strlcpy)
1. [ft_strlcat](#ft_strlcat)
1. [ft_toupper](#ft_toupper)
1. [ft_tolower](#ft_tolower)
1. [ft_strchr](#ft_strchr)
1. [ft_strrchr](#ft_strrchr)
1. [ft_strncmp](#ft_strncmp)
1. [ft_memchr](#ft_memchr)
1. [ft_memcmp](#ft_memcmp)
1. [ft_strnstr](#ft_strnstr)
1. [ft_atoi](#ft_atoi)
1. [ft_calloc](#ft_calloc)
1. [ft_strdup](#ft_strdup)
</td><td>

23. [ft_substr](#ft_substr)
1. [ft_strjoin](#ft_strjoin)
1. [ft_strtrim](#ft_strtrim)
1. [ft_split](#ft_split)
1. [ft_itoa](#ft_itoa)
1. [ft_strmapi](#ft_strmapi)
1. [ft_striteri](#ft_striteri)
1. [ft_putchar_fd](#ft_putchar_fd)
1. [ft_putstr_fd](#ft_putstr_fd)
1. [ft_putendl_fd](#ft_putendl_fd)
1. [ft_putnbr_fd](#ft_putnbr_fd)
</td><td>

34. [ft_lstnew](#ft_lstnew)
1. [ft_lstadd_front](#ft_lstadd_front)
1. [ft_lstsize](#ft_lstsize)
1. [ft_lstlast](#ft_lstlast)
1. [ft_lstadd_back](#ft_lstadd_back)
1. [ft_lstdelone](#ft_lstdelone)
1. [ft_lstclear](#ft_lstclear)
1. [ft_lstiter](#ft_lstiter)
1. [ft_lstmap](#ft_lstmap)
</td><td>

43. [ft_freeptr](#ft_freeptr)
1. [ft_isspace](#ft_isspace)
1. [ft_nbrlen](#ft_nbrlen)
1. [ft_isinset](#ft_isinset)
1. [ft_putnbr_base](#ft_putnbr_base)
1. [ft_printf](#ft_printf)
1. [get_next_line](#get_next_line)

</td></tr>
</tbody>
</table>

- [References](#References)
- [Glossary](#Glossary)

## LIBFT

### Execution

	cd libft
	make libft

### ft_isalpha
``` c
#include <ctype.h>
int isalpha(int c);

	The ft_isalpha function takes a character as input and determines whether it is an alphabetic character or not. An alphabetic character is defined as a letter of the English alphabet, either uppercase (A-Z) or lowercase (a-z). The function performs a comparison to check if the ASCII value of the given character falls within the range of uppercase letters (65 to 90) or lowercase letters (97 to 122). If the character is within any of these ranges, it returns a value of 1024 (which can be any non-zero value), indicating that the character is an alphabetic character. Otherwise, it returns 0, indicating that the character is not alphabetic.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isdigit
``` c
#include <ctype.h>
int isdigit(int c);

	The ft_isdigit function takes a character as input and determines whether it is a digit or not. A digit is defined as a numerical character from 0 to 9. The function performs a comparison to check if the ASCII value of the character is within the range of digits (48 to 57). If the character is within this range, it returns a non-zero value, indicating that the character is a digit. Otherwise, it returns 0, indicating that the character is not a digit.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isalnum
``` c
#include <ctype.h>
int isalnum(int c);

	The ft_isalnum function takes a character as input and determines whether it is an alphabetic character or a digit. An alphabetic character is defined as a letter of the English alphabet, either uppercase (A-Z) or lowercase (a-z). A digit is defined as a numerical character from 0 to 9. The function performs a series of comparisons to check if the ASCII value of the given character falls within the range of uppercase letters (65 to 90), lowercase letters (97 to 122), or digits (48 to 57). If the character is within any of these ranges, it returns 8, indicating that it is an alphabetic character or a digit. Otherwise, it returns 0, indicating that the character is neither an alphabetic character nor a digit.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isascii
``` c
#include <ctype.h>
int isascii(int c);

	The ft_isascii function takes a character as input and determines whether it is within the ASCII range or not. The ASCII range includes characters with ASCII values from 0 to 127. The function performs a comparison to check if the ASCII value of the given character is within this range. If the character is within the ASCII range, it returns 1, indicating that the character is valid. Otherwise, it returns 0, indicating that the character is outside the ASCII range.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isprint
``` c
#include <ctype.h>
int isprint(int c);

	The ft_isprint function takes a character as input and determines whether it is a printable character or not. A character is considered printable if its ASCII value is greater than 31 (decimal) and less than 127 (decimal). Characters in this range correspond to printable characters in the ASCII table, including alphabets (A-Z, a-z), digits (0-9), punctuation marks, and special symbols. The function performs a simple comparison to check if the ASCII value of the given character falls within the specified range. If so, it returns a value of 16384 (which can be any non-zero value), indicating that the character is printable. Otherwise, it returns 0, indicating that the character is not printable.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strlen
``` c
#include <string.h>
size_t strlen(const char *s);

	The ft_strlen function takes a pointer to a null-terminated string as input and calculates its length. It initializes a variable 'i' to 0 and then enters a loop that continues until it encounters a null terminator character ('\0'). In each iteration, it checks the value at the memory location pointed to by the pointer 'str' plus the offset 'i'. If the value is not a null terminator, it increments 'i' by 1. This process continues until the null terminator is found, indicating the end of the string. Finally, it returns the value of 'i', which represents the length of the string.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memset
``` c
#include <string.h>
void *memset(void str, int c, size_t n);

	The ft_memset function takes three parameters: str, c, and n. It starts by assigning the value of str to a variable str_ptr to keep track of the original pointer. It enters a loop that iterates n times, decrementing n in each iteration. The purpose of this loop is to fill each byte of the memory block with the value c. Inside the loop, it casts the str pointer to an unsigned char pointer to ensure correct byte-by-byte assignment. It assigns the value of c to the current byte by dereferencing the pointer. Then, it increments the str pointer to move to the next byte. After filling all bytes, it returns the original str_ptr, which now points to the memory block after being filled with the specified value. This function is commonly used to initialize memory or set memory regions to a specific value, such as setting a character array to null terminators or setting an integer array to zeros.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_bzero
``` c
#include <string.h>
void bzero(void str, size_t n);

	The ft_bzero function takes a pointer to a memory block and the number of bytes to zero out. It treats the memory block as an array of unsigned characters (bytes) and iterates through each byte of the block. In each iteration, it assigns the value 0 to the current byte by dereferencing the pointer 's' and casting it to an unsigned char pointer. Then, it increments the pointer 's' to point to the next byte. This process continues until 'n' becomes zero, at which point the entire memory block has been zeroed out. The function directly modifies the memory, zeroing out the specified number of bytes starting from the given memory address.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memcpy
``` c
#include <string.h>
void *memcpy(void *dst, const void *src, size_t n);

	The ft_memcpy function takes a pointer to the destination memory block (dest), a pointer to the source memory block (src), and the number of bytes to copy (n). It starts by assigning the value of 'dest' to 'dest_ptr' to not lose track of the original destination pointer. Then, it checks if the 'dest' and 'src' pointers are not NULL. If either of them is NULL, it returns the 'dest' pointer as it indicates an invalid operation. Otherwise, it enters a loop that iterates 'n' times, copying each byte from the source to the destination. The function casts the "dest" and "src" pointers to char pointers to ensure byte copying. It dereferences the pointers, assigns the value in 'src' to 'dest', and then increments the 'dest' and 'src' pointers to move to the next byte. This process continues until 'n' becomes zero, indicating that the necessary number of bytes has been copied. Finally, it returns the 'dest_ptr' pointer, which points to the start of the destination memory block.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memmove
``` c
#include <string.h>
void *memmove(void *dst, const void *src, size_t n);

	The ft_memmove function takes a pointer to the destination memory block (dest), a pointer to the source memory block (src), and the number of bytes to copy (n). It starts by assigning the value of 'dest' to 'dest_ptr' to keep track of the original destination pointer. Then, it checks if the 'dest' and 'src' pointers are not NULL. If either of them is NULL, it returns the 'dest' pointer as it indicates an invalid operation. It checks if the 'dest' and 'src' pointers are equal. If they are equal, it indicates that the memory regions overlap, so no copying is necessary. In this case, it returns the 'dest' pointer without modifying the memory. If the destination pointer is greater than the source pointer, it means the memory regions do not overlap, and it can safely perform a forward copy. It enters a loop that iterates 'n' times, copying each byte from the source to the destination. The function uses pointer arithmetic and type casting to access and copy the bytes. It dereferences the 'dest' and 'src' pointers, assigns the value in 'src' to 'dest', and then increments both 'dest' and 'src' pointers to move to the next byte. This process continues until 'n' becomes zero, indicating that the necessary number of bytes has been copied. If the destination pointer is less than the source pointer, it means the memory regions overlap, and it needs to perform a backward copy to avoid data corruption. It enters a loop that iterates 'n' times, starting from

	If both are equal, it means they are overlapped and nothing needs to be done.
if dst > src it means the regions are not overlapped and can be copied.
If dst < src it means they are overlapped and it needs to reverse to avoid corruption.
YES, it can overlap.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strlcpy
``` c
#include <string.h>
size_t strlcpy(char *dst, const char *src, size_t size);

	The ft_strlcpy function takes a pointer to the destination string (dest), a pointer to the source string (src), and the size limit of the destination buffer (n). It initializes a variable 'i' to 0 to track the length of the source string. Then, it enters a loop that iterates until it reaches the end of the source string, identified by a null terminator character ('\0'). In each iteration, it increments 'i' by 1 to count the length of the source string.

	After counting the length, it checks if the size limit 'n' is zero. If 'n' is zero, it means there is no space in the destination buffer, so the function returns the length of the source string.

	Otherwise, it enters another loop that copies characters from the source string to the destination buffer. It decrements 'n' to account for the space occupied by the null terminator character. It also checks if the current character of the source string is not a null terminator ('\0') to continue copying. Inside the loop, it assigns the value in 'src' to 'dest' and increments the 'dest' and 'src' pointers to move to the next character. This process continues until 'n' becomes zero or the null terminator is reached. Finally, it adds a null terminator character at the end of the destination buffer to ensure proper termination, and returns the length of the source string.

Note: The function assumes that the destination buffer has enough space to hold at least 'n' characters plus the null terminator. Otherwise, it may cause a buffer overflow.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strlcat
``` c
#include <string.h>
size_t strlcat(char *dst, const char *src, size_t size);

Non-standard function
More efficient and secure than strlcat

	The ft_strlcat function takes a pointer to the destination string (dest), a pointer to the source string (src), and the size limit of the destination buffer (n). It starts by declaring the variables 'dest_len', 'total_len', and 's'. It checks if the 'dest' or 'src' pointer is NULL and the size limit 'n' is zero. If both conditions are true, it returns 0 to indicate an invalid operation. It assigns the 'src' pointer to 's' to keep track of the original source pointer. It initializes 'dest_len' to 0 to count the length of the destination string. It enters a loop that iterates until it reaches the end of the destination string or the size limit 'n'. In each iteration, it increments 'dest_len' by 1 and checks if the current character of the destination string is not a null terminator ('\0'). It also checks if 'dest_len' is less than 'n' to ensure it stays within the limit. After counting the length of the destination string, it checks if 'dest_len' is less than 'n'. If true, it means there is still space in the destination buffer to add characters from the source string. It calculates the "total_len" by adding the length of the destination string (dest_len) and the length of the source string (str_len(s)). If 'dest_len' is already equal to or greater than 'n', it means the destination buffer is already full, so it directly returns 'n' plus the length of the source string (str_len(s)). It enters another loop that copies n characters from the source string to the destination buffer. It checks if the current character of the source string is not a null terminator ('\0') and if there is still space in the destination buffer ('dest_len + 1 < n'). Inside the loop, it assigns the value in 's' to 'dest' and increments the 'dest' and 's' pointers to move to the next character. It also increments 'dest_len' to track the length of the concatenated string. This process continues until the end of the source string or until no space is left in the destination buffer. Finally, it adds a null terminator character at the end of the destination buffer to ensure proper termination, and returns the 'total_len' value, which represents the total length of the concatenated string.

Note: The function assumes that the destination buffer has enough space to hold at least 'n' characters plus the null terminator. Otherwise, it may cause a buffer overflow.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_toupper
``` c
#include <ctype.h>
int toupper(int c);

	The ft_toupper function takes an input character 'c'.

	It checks if 'c' is in the range of lowercase letters, which corresponds to ASCII values from 97 to 122. If 'c' is a lowercase letter, it subtracts 32 from its ASCII value to convert it to the corresponding uppercase letter. If 'c' is a lowercase letter, it subtracts 32 from its ASCII value to convert it to the corresponding uppercase letter. This conversion is possible because the ASCII values of uppercase and lowercase letters have a difference of 32. Finally, it returns the converted uppercase letter if 'c' was a lowercase letter, or the input character itself if 'c' was not a lowercase letter.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_tolower
``` c
#include <ctype.h>
int tolower(int c);

	The ft_tolower function takes an input character 'c'.

	It checks if 'c' is in the range of uppercase letters, which corresponds to ASCII values from 65 to 90. If 'c' is an uppercase letter, it adds 32 to its ASCII value to convert it to the corresponding lowercase letter. If 'c' is an uppercase letter, it adds 32 to its ASCII value to convert it to the corresponding lowercase letter. This conversion is possible because the ASCII values of uppercase and lowercase letters have a difference of 32. Finally, it returns the converted lowercase letter if 'c' was an uppercase letter, or the input character itself if 'c' was not an uppercase letter.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strchr
``` c
#include <string.h>
char *strchr(const char *s, int c);

	The ft_strchr function takes a pointer to the input string 'str' and an integer 'c' representing a character. It enters a loop that iterates until it reaches the end of the string, identified by a null terminator character ('\0'). In each iteration, it checks if the current character of the string is equal to the searched character 'c'. If a match is found, it returns a pointer to that character in the string. If no match is found until the end of the string, it checks if the last character is equal to 'c'. This check is necessary because the loop exits before checking the last character. If the last character matches 'c', it returns a pointer to that character. If no match is found, it means the character 'c' is not present in the string, so it returns NULL.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strrchr
``` c
#include <string.h>
char *strrchr(const char *s, int c);

	The ft_strrchr function takes a pointer to the input string 'str' and an integer 'c' representing a character. It declares a pointer 'aux' and initializes it to NULL. It enters a loop that iterates until it reaches the end of the string, identified by a null terminator character ('\0'). In each iteration, it checks if the current character of the string is equal to the searched character 'c'. If a match is found, it updates the 'aux' pointer to point to that character in the string. This way, 'aux' keeps track of the last occurrence of the character. After the loop, it checks if the last character is equal to 'c'. If the last character matches 'c', it returns a pointer to that character. If the last character is not equal to 'c', it means the character 'c' is not present in the string, so it returns the 'aux' pointer. The 'aux' pointer would be NULL if no occurrence of 'c' was found during the loop, indicating that 'c' is not present in the string.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strncmp
``` c
#include <string.h>
int strncmp(const char *s1, const char *s2, size_t n);

	The ft_strncmp function takes three parameters: s1, s2, and n. First, it checks if n is zero. If true, it means no characters should be compared, so it returns 0 to indicate equality. The function enters a loop that iterates until it reaches the end of s1 or s2, or until n becomes 1. In each iteration, it compares the characters of s1 with those of s2. In each iteration, it compares the characters at the current positions of s1 and s2. If the characters are equal and n is greater than 1, it means a potential match has been found, so it increments s1, s2, and decrements n to move to the next character. The function continues comparing characters until a difference is found or n becomes 1. Once the loop ends, it means the end of s1 or s2 has been reached, or n has become 1. If the strings are equal, it returns 0. If s1 is less than s2, it means s1 is lexicographically smaller, so it returns a negative value. If s1 is greater than s2, it means s1 is lexicographically greater, so it returns a positive value. By converting the characters to unsigned char, the function ensures correct character comparison without sign extension issues. This function can be used to compare strings in lexicographical order up to a specified length.

Returns:
*. 0    if s1 = s2
*. > 0  if s1 > s2
* < 0   if s2 > s1
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memchr
``` c
#include <string.h>
void *memchr(const void *s, int c, size_t n);

	The ft_memchr function takes a pointer to the memory block 'str', an integer 'c' representing a character, and a size_t 'n' specifying the number of bytes to search within the memory block. It enters a loop that iterates 'n' times, decrementing 'n' in each iteration. In each iteration, it checks if the current byte of the memory block, accessed by casting 'str' to an unsigned char pointer, is equal to the character 'c' being searched for. If a match is found, it returns a pointer to that byte in the memory block. If no match is found by the end of the loop, it means the character 'c' is not present in the memory block, so it returns NULL.

	Unlike strchr, memchr does not stop even if it finds the end of string "\0"
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_memcmp
``` c
#include <string.h>
int memcmp(const void *s1, const void *s2, size_t n);

	The ft_memcmp function takes two pointers, s1 and s2, which point to the memory areas to compare, and the number of bytes to compare, n. It enters a loop that iterates n times, decrementing n in each iteration. The purpose of this loop is to compare each byte in the memory areas until n becomes zero. Inside the loop, it checks if the value at the current byte of s1 is different from the value at the current byte of s2. If a difference is found, it returns the difference between the two bytes. Since the return type is int, the difference is calculated by subtracting the value of the current byte of s2 from the value of the current byte of s1. By casting the pointers to unsigned char, the function ensures byte-by-byte comparison without sign extension issues. After comparing each byte, if no differences are found, it means the memory areas are equal, so it returns 0. This function can be used to compare arrays, strings, or any other generic memory areas.
	Compare even if it encounters '\0'
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strnstr
``` c
#include <string.h>
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)

	The ft_strnstr function takes three parameters: haystack, needle, and n. It starts by checking if haystack is NULL and n is zero. If both conditions are true, it returns NULL to indicate an invalid operation. Then, it checks if needle is an empty string ('\0'). If true, it means an empty string is always considered to be at the beginning of the haystack, so it returns a pointer to the haystack. The function enters a loop that iterates until it reaches the end of the haystack string or until n becomes zero. In each iteration, it initializes a variable j to 0 to keep track of the current position in the needle string. Then, it compares the characters at the current positions of the haystack and needle. If the characters are equal and the character in needle is not a null terminator, it means a potential match has been found, so it increments j and checks if j is less than or equal to n to ensure it stays within the search limit. It also checks if the next character in needle is a null terminator. If true, it means the entire needle has been found in the haystack, so it returns a pointer to the current position in the haystack. If no match is found, it increments the haystack to move to the next character and continues searching. Once the loop ends, it means the end of the haystack has been reached or n is zero. In either case, it means the substring was not found, so it returns NULL to indicate the absence of the substring.

Note: The function searches for a substring within the first 'n' characters of the haystack string. If 'n' is greater than the length of the haystack, it will search the entire haystack string.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_atoi
``` c
#include <stdlib.h>
int atoi(const char *nptr);

	The ft_atoi function scans the input string and converts it to an integer. It skips any whitespace characters by advancing the pointer. If a plus (+) or minus (-) sign is encountered, it determines the sign of the number and advances the pointer. Then, it processes each digit and calculates the corresponding integer value. It performs checks to avoid overflow by comparing the current value with the previous value multiplied by the sign. If overflow occurs, it returns 0 if the sign is positive or -1 if negative. Finally, it returns the resulting integer value.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_calloc
``` c
#include <stdlib.h>
void *calloc(size_t nmemb, size_t size);

	The ft_calloc function takes two parameters: count and n. First, it performs a check to ensure that the product of count and n does not overflow the size_t type. If the check fails, it returns NULL to indicate an error. Then, it calls the malloc function to allocate memory for count * n bytes. If memory allocation fails, malloc returns NULL, and ft_calloc also returns NULL to indicate an error. If memory allocation is successful, it performs additional checks to handle the case where n is zero. If n is zero, it means the size of each element is zero, so ft_calloc directly returns the allocated memory without initializing it. Otherwise, it calls the s_zero function to initialize the allocated memory block to all zeros. The s_zero function is defined as a static function in the code and zeros out each byte of the memory block. Finally, ft_calloc returns the pointer to the allocated and initialized memory block. This function is useful when you need to allocate memory for an array and initialize it to a specific value, such as zeroing out a buffer or allocating memory for an array of structures.

	The allocated memory is set to "\0". Cleans unlike malloc
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strdup
``` c
#include <string.h>
char *strdup(const char *s);

	The ft_strdup function takes a single parameter: src, which is a pointer to the source string. It starts by calling the str_new function to allocate memory for the duplicated string. The str_new function is responsible for memory allocation and is defined as a static function. If memory allocation fails, str_new returns NULL, and ft_strdup also returns NULL to indicate an error. If memory allocation is successful, ft_strdup assigns the returned pointer to the variable dest. Then, ft_strdup enters a loop that iterates until it reaches the end of the source string by checking if the current character is not a null terminator. In each iteration, it assigns the value of the current character in src to the memory location pointed to by dest and increments both pointers to move to the next character. After copying all characters, it adds a null terminator at the end of the duplicated string to ensure proper termination. Finally, ft_strdup returns the start pointer, which points to the beginning of the duplicated string. The function is useful when you need to create an independent copy of a string, allowing modifications to the duplicated string without affecting the original.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## ADDITIONAL

### ft_substr
``` c
char	*ft_substr(char const *s, unsigned int start, size_t len);

	The ft_substr function takes three parameters: s, start, and len. First, it checks that s is not NULL. If s is NULL, it returns NULL to indicate an error. Then, it checks if the start index is greater than the length of the source string. If true, it means the start index is beyond the end of the source string, so it sets len to 0 to create an empty substring. Otherwise, it checks if the specified length exceeds the remaining characters in the source string after the start index. If true, it adjusts len to be equal to the number of characters remaining in the source string after the start index. The next step is to call the str_new function to allocate memory for the substring. The str_new function is defined as static in the code and is responsible for allocating the memory. If memory allocation fails, str_new returns NULL, and ft_substr also returns NULL to indicate an error. If memory allocation is successful or if len is zero, ft_substr assigns the returned pointer to the variable str and increments the s pointer by the start index to position it at the beginning of the desired substring. It also assigns the str pointer to the variable str_ptr to keep track of the start of the substring. Then, it adds a null terminator at the end of the substring to ensure proper termination. Finally, ft_substr enters a loop that copies characters from the source string to the substring. It checks if len is not zero and if the current character in s is not a null terminator. Inside the loop, it assigns the value of the current character in s to the memory location pointed to by str and increments both pointers to move to the next character. It also decrements len to keep track of the remaining characters to copy. This process continues until len becomes zero or a null terminator is encountered. Once the loop ends, ft_substr returns the str_ptr pointer, which points to the beginning of the allocated substring. The function is useful when you need to extract a portion of a string to create a new string.
```

### ft_strjoin
``` c
char	*ft_strjoin(char const *s1, char const *s2);

	The ft_strjoin function takes two parameters: s1 and s2. First, it checks if s1 or s2 is NULL. If true, it means one of the strings is missing, and the function returns NULL to indicate an error. Then, it calls the str_new function to allocate memory for the concatenated string. The str_new function is defined as static in the code and is responsible for allocating the memory. If memory allocation fails, str_new returns NULL, and ft_strjoin also returns NULL to indicate an error. If memory allocation is successful, ft_strjoin assigns the returned pointer to the variable str and increments the str_ptr variable to track the start of the concatenated string. Then, it enters a loop that copies characters from s1 into the new string until a null terminator is encountered in s1. Inside the loop, it assigns the value of the current character in s1 to the memory location pointed to by str and increments both pointers to move to the next character. The loop continues until the end of s1. After copying s1, ft_strjoin enters another loop to copy characters from s2 into the new string. It performs the same character copying process as in the previous loop. Once the end of s2 is reached, it adds a null terminator at the end of the concatenated string to ensure proper termination. Finally, ft_strjoin returns the str_ptr pointer, which points to the beginning of the concatenated string. The function is useful when you need to combine two strings into a new string.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strtrim
``` c
char	*ft_strtrim(char const *s1, char const *set);

	The ft_strtrim function takes two parameters: s1 and set. First, it checks if s1 or set is NULL. If true, it means one of the strings is missing, and the function returns NULL to indicate an error. Then, it initializes the variable start to 0 and enters a loop to find the index of the first non-matching character in s1 by iterating over it. Inside the loop, it uses the char_check function to determine if the current character of s1 matches any character in the set. If there is a match, it increments the start variable to move to the next character. Once the loop ends, the start variable represents the index of the first non-matching character or the end of the string if all characters match the set. Similarly, it initializes the variable end to the length of s1 and enters a loop to find the index of the last non-matching character in s1 by iterating over it in reverse. Inside the loop, it uses the char_check function to determine if the current character of s1 matches any character in the set. If it matches, it decrements the end variable to move to the previous character. Once the loop ends, the end variable represents the index of the last non-matching character plus one. Then, the ft_strtrim function calls the str_new function to allocate memory for the trimmed string. The str_new function is defined as static in the code and is responsible for allocating the memory. If memory allocation fails, str_new returns NULL, and ft_strtrim also returns NULL to indicate an error. If memory allocation is successful, ft_strtrim assigns the returned pointer to the variable str and increments the str_ptr variable to track the start of the trimmed string. Then, it enters a loop to copy the characters from s1 to the new string, starting from the start index and ending at the end index. Inside the loop, it assigns the value of the current character in s1 to the memory location pointed to by str and increments both pointers to move to the next character. The loop continues until the end index is reached. Once the loop ends, it adds a null terminator at the end of the trimmed string to ensure proper termination. Finally, ft_strtrim returns the str_ptr pointer, which points to the beginning of the trimmed string. The function is useful when you need to remove leading and trailing characters from a string.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_split
``` c
char	**ft_split(char const *s, char c);

	The ft_split function takes two parameters: s and c. First, it checks if s is NULL. If true, it returns NULL to indicate an error. Then, it calls the str_new function to allocate memory for the array of strings. The str_new function is defined as static in the code and is responsible for allocating the memory. If memory allocation fails, str_new returns NULL, and ft_split also returns NULL to indicate an error. If memory allocation is successful, ft_split assigns the returned pointer to the variable str and increments the str_ptr variable to track the start of the array. Then, it initializes the variable i to 0 to keep track of the current position in the array. It enters a loop that iterates until it reaches the end of the input string s. Inside the loop, it checks if the current character of s is not equal to the delimiter c. If true, it means a new word has been found. It initializes the variable j to 0 to keep track of the length of the current word. Then, it enters another loop to calculate the length of the current word by incrementing j until it encounters the delimiter c or the end of the string. After calculating the length, it calls the str_new function again to allocate memory for the current word. If memory allocation fails, it calls the free_str function to free the previously allocated memory and returns NULL to indicate an error. If memory allocation is successful, it assigns the returned pointer to the current position in the array and increments the array pointer. Then, it copies the characters of the current word from s to the allocated memory using the strncpy function. It adds a null terminator at the end of the word to ensure proper termination. Finally, it increments the s pointer by j to skip the copied word and continues the loop. Once the loop ends, it adds a NULL pointer at the end of the array to mark the end of the array of strings. Finally, ft_split returns the str_ptr pointer, which points to the beginning of the array of strings. The function is useful when you need to split a string into an array of substrings based on a delimiter character.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_itoa
``` c
char	*ft_itoa(int n);

	The ft_itoa function takes a single parameter: n, which is the integer to convert. First, it initializes the variable len to 0 to keep track of the length of the resulting string. Then, it checks if n is negative. If true, it increments len by 1 to account for the minus sign. It also converts n to a positive value by multiplying it by -1. If n is zero, it sets len to 1 because the string representation of zero is "0". Otherwise, it enters a loop to calculate the length of the integer by repeatedly dividing n by 10 until it becomes zero. In each iteration, it increments len by 1. After calculating the length, it calls the str_new function to allocate memory for the string. The str_new function is defined as static in the code and is responsible for allocating the memory. If memory allocation fails, str_new returns NULL, and ft_itoa also returns NULL to indicate an error. If memory allocation is successful, ft_itoa assigns the returned pointer to the variable str and sets the variable str_ptr to point to the start of the string. Then, it checks if the original n was negative. If true, it assigns a minus sign to the first character of the string and increments the str pointer. It also sets the variable nbr to the absolute value of n. Then, it enters a loop to convert each digit of the integer to a character. It starts from the last digit and moves towards the first. In each iteration, it calculates the current digit by taking the remainder of nbr divided by 10. It converts the digit to a character by adding the ASCII value of '0'. It assigns the character to the current position in the string and decrements the str pointer to move to the previous position. It also divides nbr by 10 to remove the last digit. The loop continues until nbr becomes zero. Once the loop ends, ft_itoa returns the str_ptr pointer, which points to the beginning of the string representation of the integer. The function is useful when you need to convert an integer to a string.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_strmapi
``` c
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

	The ft_strmapi function takes two parameters: s, which is the input string, and f, which is a function pointer. First, it checks if s or f is NULL. If true, it returns NULL to indicate an error. Then, it calls the str_new function to allocate memory for the new string. The str_new function is defined as static in the code and is responsible for allocating the memory. If memory allocation fails, str_new returns NULL, and ft_strmapi also returns NULL to indicate an error. If memory allocation is successful, ft_strmapi assigns the returned pointer to the variable str and increments the str_ptr variable to track the start of the new string. Then, it initializes the variable i to 0 to keep track of the current index in the string. It enters a loop that iterates until it reaches the end of the input string s. Inside the loop, it applies the function f to the current character of s and the current index i. The result of the function call is assigned to the current position in the new string. Then, it increments the str pointer and the index i to move to the next character. The loop continues until the end of the string is reached. Once the loop ends, it adds a null terminator at the end of the new string to ensure proper termination. Finally, ft_strmapi returns the str_ptr pointer, which points to the beginning of the new string. The function is useful when you need to apply a function to each character of a string and create a new string with the results.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_striteri
``` c
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

	The ft_striteri function takes two parameters: s, which is the input string, and f, which is a function pointer. First, it checks if s or f is NULL. If true, it returns without performing any operations. Then, it initializes the variable i to 0 to keep track of the current index in the string. It enters a loop that iterates until it reaches the end of the input string s. Inside the loop, it applies the function f to the current index i and a pointer to the current character of s. The function f can modify the character in place since it receives a pointer to it. Then, it increments the index i to move to the next character. The loop continues until the end of the string is reached. The function does not return any value as it operates directly on the input string. The function is useful when you need to apply a function to each character of a string and modify the string in place.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putchar_fd
``` c
void	ft_putchar_fd(char c, int fd);

	The ft_putchar_fd function takes two parameters: c, which is the character to write, and fd, which is the file descriptor. It uses the write system call to write the character c to the specified file descriptor. The write function is called with the parameters fd (file descriptor), a pointer to the character c, and the size 1 (indicating one byte to write). The function does not return any value. It is useful when you need to output a single character to a specific file descriptor, such as standard output (fd = 1) or standard error (fd = 2).
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putstr_fd
``` c
void	ft_putstr_fd(char *s, int fd);

	The ft_putstr_fd function takes two parameters: s, which is the string to write, and fd, which is the file descriptor. First, it checks if s is NULL. If true, it returns without performing any operations. Then, it uses the write system call to write the entire string s to the specified file descriptor. The write function is called with the parameters fd (file descriptor), the string s, and the length of the string calculated by ft_strlen(s). The function does not return any value. It is useful when you need to output a string to a specific file descriptor, such as standard output (fd = 1) or standard error (fd = 2).
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putendl_fd
``` c
void	ft_putendl_fd(char *s, int fd);

	The ft_putendl_fd function takes two parameters: s, which is the string to write, and fd, which is the file descriptor. First, it checks if s is NULL. If true, it returns without performing any operations. Then, it uses the write system call to write the entire string s to the specified file descriptor, followed by a newline character. The write function is called twice: first to write the string s with the length calculated by ft_strlen(s), and then to write the newline character '\n' with a length of 1. The function does not return any value. It is useful when you need to output a string followed by a newline to a specific file descriptor, such as standard output (fd = 1) or standard error (fd = 2).
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putnbr_fd
``` c
void	ft_putnbr_fd(int n, int fd);

	The ft_putnbr_fd function takes two parameters: n, which is the integer to write, and fd, which is the file descriptor. First, it checks if n is the smallest possible integer value (-2147483648). If true, it writes the string "-2147483648" to the file descriptor and returns. If n is negative, it writes a minus sign '-' to the file descriptor and converts n to a positive value by multiplying it by -1. Then, if n is greater than or equal to 10, it recursively calls ft_putnbr_fd with n divided by 10 to write the higher digits first. After the recursive call, it writes the last digit of n by converting it to a character. The last digit is calculated as n % 10, and then the ASCII value of '0' is added to convert it to a character. The character is written to the file descriptor using the write system call. The function does not return any value. It is useful when you need to output an integer to a specific file descriptor, such as standard output (fd = 1) or standard error (fd = 2).
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## BONUS

### ft_lstnew
``` c
t_list	*ft_lstnew(void *content);

	The ft_lstnew function takes a single parameter: content, which is a pointer to the data to be stored in the new node. First, it calls the malloc function to allocate memory for the new node. The size of the allocation is sizeof(t_list), which is the size of the structure. If memory allocation fails, malloc returns NULL, and ft_lstnew also returns NULL to indicate an error. If memory allocation is successful, it assigns the content pointer to the content member of the new node. Then, it sets the next pointer of the new node to NULL, indicating that it is the last node in the list. Finally, it returns a pointer to the newly created node. The function is useful when you need to create a new node for a linked list.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstadd_front
``` c
void	ft_lstadd_front(t_list **lst, t_list *new);

	The ft_lstadd_front function takes two parameters: lst, which is a pointer to the pointer of the first node in the list, and new, which is a pointer to the new node to be added. First, it checks if lst or new is NULL. If true, it returns without performing any operations. Then, it sets the next pointer of the new node to point to the current first node of the list. This links the new node to the existing list. After that, it updates the pointer to the first node of the list to point to the new node. This makes the new node the new first node of the list. The function does not return any value. It is useful when you need to add a new node at the beginning of a linked list.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstsize
``` c
int	ft_lstsize(t_list *lst);

	The ft_lstsize function takes a single parameter: lst, which is a pointer to the first node of the list. First, it initializes the variable i to 0 to keep track of the number of nodes. Then, it enters a loop that iterates through the list until it reaches the end. In each iteration, it increments the counter i by 1 to count the current node. It then moves to the next node by updating the lst pointer to point to the next node in the list. The loop continues until lst becomes NULL, indicating the end of the list. Once the loop ends, it returns the value of i, which represents the total number of nodes in the list. The function is useful when you need to determine the size of a linked list.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstlast
``` c
t_list	*ft_lstlast(t_list *lst);

	The ft_lstlast function takes a single parameter: lst, which is a pointer to the first node of the list. First, it checks if lst is NULL. If true, it returns NULL to indicate an empty list. Then, it enters a loop that iterates through the list until it reaches the last node. In each iteration, it checks if the next pointer of the current node is NULL. If true, it means the current node is the last node, so it returns a pointer to that node. If the next pointer is not NULL, it updates the lst pointer to point to the next node and continues the loop. The loop continues until the last node is found. The function is useful when you need to find the last node in a linked list.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstadd_back
``` c
void	ft_lstadd_back(t_list **lst, t_list *new);

	The ft_lstadd_back function takes two parameters: lst, which is a pointer to the pointer of the first node in the list, and new, which is a pointer to the new node to be added. First, it checks if lst or new is NULL. If true, it returns without performing any operations. Then, it checks if the list is empty by verifying if the pointer to the first node (*lst) is NULL. If true, it sets the pointer to the first node to point to the new node, making the new node the first and only node in the list. If the list is not empty, it calls the ft_lstlast function to find the last node in the list. The ft_lstlast function returns a pointer to the last node. Then, it sets the next pointer of the last node to point to the new node, effectively adding the new node at the end of the list. The function does not return any value. It is useful when you need to add a new node at the end of a linked list.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstdelone
``` c
void	ft_lstdelone(t_list *lst, void (*del)(void *));

	The ft_lstdelone function takes two parameters: lst, which is a pointer to the node to be deleted, and del, which is a function pointer to the function that will free the content of the node. First, it checks if lst or del is NULL. If true, it returns without performing any operations. Then, it calls the del function with the content of the node as an argument to free the memory allocated for the content. After that, it calls the free function to free the memory allocated for the node itself. The function does not return any value. It is useful when you need to delete a single node from a linked list and properly free its memory.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstclear
``` c
void	ft_lstclear(t_list **lst, void (*del)(void *));

	The ft_lstclear function takes two parameters: lst, which is a pointer to the pointer of the first node in the list, and del, which is a function pointer to the function that will free the content of each node. First, it checks if lst or del is NULL. If true, it returns without performing any operations. Then, it enters a loop that iterates through the list until all nodes are deleted. In each iteration, it assigns the next pointer of the current node to a temporary variable next to keep track of the next node. Then, it calls the ft_lstdelone function to delete the current node and free its memory. The ft_lstdelone function uses the del function to free the content of the node. After deleting the current node, it updates the current node pointer to point to the next node stored in the temporary variable. The loop continues until all nodes are deleted and the list becomes empty. Finally, it sets the pointer to the first node (*lst) to NULL to indicate that the list is now empty. The function does not return any value. It is useful when you need to delete all nodes in a linked list and properly free their memory.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstiter
``` c
void	ft_lstiter(t_list *lst, void (*f)(void *));

	The ft_lstiter function takes two parameters: lst, which is a pointer to the first node of the list, and f, which is a function pointer to the function that will be applied to the content of each node. First, it checks if lst or f is NULL. If true, it returns without performing any operations. Then, it enters a loop that iterates through the list until all nodes have been processed. In each iteration, it calls the function f with the content of the current node as an argument. This allows the function f to perform some operation on the content of the node. After applying the function to the current node, it moves to the next node by updating the lst pointer to point to the next node in the list. The loop continues until all nodes have been processed. The function does not return any value. It is useful when you need to apply a function to the content of each node in a linked list.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_lstmap
``` c
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

	The ft_lstmap function takes three parameters: lst, which is a pointer to the first node of the list, f, which is a function pointer to the function that will be applied to the content of each node, and del, which is a function pointer to the function that will free the content of a node in case of an error. First, it checks if lst, f, or del is NULL. If true, it returns NULL to indicate an error. Then, it initializes a pointer new_list to NULL to represent the new list. It enters a loop that iterates through the original list until all nodes have been processed. In each iteration, it applies the function f to the content of the current node to create new content for the new node. It then calls the ft_lstnew function to create a new node with the new content. If memory allocation fails during the creation of the new node, it calls the ft_lstclear function to delete all nodes in the new list and free their memory using the del function. It then returns NULL to indicate an error. If the new node is successfully created, it calls the ft_lstadd_back function to add the new node to the end of the new list. This ensures that the order of nodes in the new list matches the order in the original list. After processing all nodes, it returns a pointer to the first node of the new list. The function is useful when you need to create a new list by applying a function to the content of each node in the original list.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## UTILS

### ft_freeptr
``` c
void	ft_freeptr(void **ptr);

	The ft_freeptr function takes a single parameter: ptr, which is a pointer to the pointer of the memory to be freed. First, it checks if ptr is NULL or if the pointer it points to is NULL. If true, it returns without performing any operations. Then, it calls the free function to free the memory pointed to by the pointer. After freeing the memory, it sets the pointer to NULL to avoid dangling pointers. The function does not return any value. It is useful when you need to safely free a pointer and set it to NULL to prevent accidental use after freeing.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isspace
``` c
int	ft_isspace(int c);

	The ft_isspace function takes a single parameter: c, which is the character to check. It checks if the character c is a whitespace character. The whitespace characters include space (' '), form feed ('\f'), newline ('\n'), carriage return ('\r'), horizontal tab ('\t'), and vertical tab ('\v'). The function returns a non-zero value if c is a whitespace character, and 0 otherwise. It is useful when you need to check if a character is a whitespace character.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_nbrlen
``` c
int	ft_nbrlen(int n);

	The ft_nbrlen function takes a single parameter: n, which is the integer to measure. First, it initializes the variable len to 0 to keep track of the length. Then, it checks if n is negative. If true, it increments len by 1 to account for the minus sign. It also converts n to a positive value by multiplying it by -1. If n is zero, it sets len to 1 because the string representation of zero is "0". Otherwise, it enters a loop to calculate the length of the integer by repeatedly dividing n by 10 until it becomes zero. In each iteration, it increments len by 1. Finally, it returns the value of len, which represents the number of digits in the integer plus the sign if negative. The function is useful when you need to determine the length of the string representation of an integer.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_isinset
``` c
int	ft_isinset(int c, const char *set);

	The ft_isinset function takes two parameters: c, which is the character to check, and set, which is a string containing a set of characters. It enters a loop that iterates through each character in the set until the end of the set is reached. In each iteration, it checks if the current character in the set matches the character c. If a match is found, it returns 1 to indicate that the character is in the set. If no match is found after checking all characters in the set, it returns 0 to indicate that the character is not in the set. The function is useful when you need to check if a character is present in a given set of characters.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_putnbr_base
``` c
void	ft_putnbr_base(int nbr, char *base);

	The ft_putnbr_base function takes two parameters: nbr, which is the integer to convert, and base, which is a string representing the base to use for the conversion. First, it checks if the base is valid by calling the is_valid_base function. If the base is not valid, it returns without performing any operations. Then, it checks if nbr is negative. If true, it writes a minus sign '-' to the standard output and converts nbr to a positive value by multiplying it by -1. Then, it calls the print_base function to recursively print the number in the specified base. The print_base function takes the number and the base as parameters. If the number is greater than or equal to the length of the base, it recursively calls itself with the number divided by the base length to print the higher digits first. Then, it prints the digit corresponding to the remainder of the number divided by the base length by indexing into the base string. The function does not return any value. It is useful when you need to output an integer in a specified base, such as binary, octal, or hexadecimal.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### ft_printf
``` c
int	ft_printf(const char *format, ...);

	The ft_printf function takes a format string and a variable number of arguments. It processes the format string and writes the formatted output to the standard output. The function supports the following format specifiers: %c (character), %s (string), %p (pointer), %d (decimal integer), %i (integer), %u (unsigned decimal integer), %x (hexadecimal integer in lowercase), %X (hexadecimal integer in uppercase), and %% (percent sign). The function returns the number of characters written, or a negative value if an error occurs.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

### get_next_line
``` c
char	*get_next_line(int fd);

	The get_next_line function reads a line from a file descriptor. It takes a file descriptor as a parameter and returns a string containing the next line from the file. The function uses a static buffer to store the remaining data from previous reads. It reads the file in chunks until it finds a newline character or reaches the end of the file. The function returns the line read, including the newline character if present, or NULL if an error occurs or the end of file is reached.
```
<div style='text-align: right;'>

[UP &#11014;](#libft)
</div>

## References

- [42 Docs](https://cdn.intra.42.fr/pdf/pdf/960/en.subject.pdf)
- [Tutorial](https://www.youtube.com/playlist?list=PLVeeVcDE3acqQYv5YZWqjaq2XMQi3zrVh)
- [Manual](https://www.man7.org/linux/man-pages/man3/string.3.html)
- [C Library](https://www.tutorialspoint.com/c_standard_library/ctype_h.htm)

## Glossary

- **ASCII**: American Standard Code for Information Interchange, a character encoding standard.
- **Buffer**: A temporary storage area in memory used to hold data while it is being processed.
- **File Descriptor**: An integer that uniquely identifies an open file in a computer's operating system.
- **Linked List**: A data structure consisting of a sequence of nodes, where each node contains data and a reference to the next node.
- **Memory Allocation**: The process of assigning memory space for variables and data structures during program execution.
- **Null Terminator**: A special character ('\0') used to mark the end of a string in C.
- **Pointer**: A variable that stores the memory address of another variable.
- **String**: A sequence of characters terminated by a null terminator.

[ $${\color{red}BACK}$$ ](../../README.md)
