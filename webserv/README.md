![Rating](/assets/images/header.png)

# Webserv Project Summary

## Project Overview
Webserv is a project that requires developing a custom HTTP server in C++98. The goal is to create a fully functional web server that can handle HTTP requests, serve static and dynamic content, manage client connections efficiently, and be configured through configuration files. This project provides deep understanding of HTTP protocol, network programming, and server architecture.

## Key Features & Requirements

### Core Server Functionality
- **HTTP/1.1 compliant server** implementation in C++98
- **Non-blocking I/O operations** using poll(), select(), kqueue(), or epoll()
- **Multiple port listening** capability
- **Client connection management** with proper disconnection handling
- **Configuration file** support for server customization
- **Compatibility with standard web browsers**

### HTTP Protocol Support
- **HTTP Methods**: GET, POST, DELETE (minimum requirement)
- **Accurate HTTP status codes** implementation
- **Default error pages** provision
- **Client request body size** limitations
- **Chunked transfer encoding** handling for CGI

### Static Content Serving
- **Fully static website** serving capability
- **Directory listing** configurable option
- **Default file** serving for directory requests
- **File upload** functionality support

### Dynamic Content Processing
- **CGI execution** support for server-side scripting (PHP, Python, etc.)
- **POST and GET method** support for CGI
- **File extension-based** CGI triggering
- **Proper PATH_INFO** handling for CGI scripts

### Configuration Capabilities
- **Port and host** configuration for multiple servers
- **Server names** virtual hosting support
- **Error page** customization
- **Route-based configuration** with:
  - Accepted HTTP methods per route
  - HTTP redirect rules
  - Directory/file root mapping
  - Directory listing enable/disable
  - File upload directory configuration

## Technical Requirements

### Programming Standards
- **C++98 compliance** with -std=c++98 flag
- **No external libraries** beyond standard system calls
- **Modern C++ features** preferred over C equivalents
- **Memory management** without crashes or leaks

### Performance & Reliability
- **Non-blocking architecture** at all times
- **Single poll() call** for all I/O operations
- **Stress test resilience** ensuring constant availability
- **Request timeout prevention** - no hanging requests

### System Call Usage
**Network Operations:**
- `socket`, `accept`, `listen`, `bind`, `connect`
- `send`, `recv`, `getsockname`, `setsockopt`
- `getaddrinfo`, `freeaddrinfo`
- `htonl`, `htons`, `ntohl`, `ntohs`

**I/O Multiplexing:**
- `select`, `poll`, `epoll_create`, `epoll_ctl`, `epoll_wait`
- `kqueue`, `kevent`
- `FD_SET`, `FD_CLR`, `FD_ISSET`, `FD_ZERO`

**File & Process Management:**
- `open`, `close`, `read`, `write`, `stat`, `access`
- `fork`, `execve`, `waitpid`, `kill`
- `opendir`, `readdir`, `closedir`
- `dup`, `dup2`, `pipe`, `fcntl` (macOS only with specific flags)

**Error Handling:**
- `errno`, `strerror`, `gai_strerror`

## Bonus Features
- **Cookies and session management**
- **Multiple CGI support**

## Evaluation Criteria
- **Configuration file** parsing and application
- **Browser compatibility** with standard web browsers
- **NGINX behavior alignment** for reference implementation
- **Error handling** robustness
- **Performance** under stress conditions
- **Code quality** and C++98 standards compliance

This project emphasizes understanding HTTP protocol internals, efficient I/O management, robust server architecture, and practical network programming skills while maintaining high performance and reliability standards comparable to production web servers.

[$${\color{red}BACK}$$](../../README.md)
