# Webserve

A simple HTTP server implementation in C++ as part of the 42 Tokyo curriculum.

## Overview

This project implements a lightweight HTTP server from scratch using C++. It handles HTTP requests, serves static content, processes CGI scripts, and manages server configuration files.

## Features

- HTTP/1.1 protocol support
- Static file serving
- Custom error pages
- CGI script execution
- Multiple server configuration
- Connection handling with non-blocking I/O

## Project Structure

- `main.cpp`: Entry point for the server application
- `core/`: Core server components
  - `Server`: Main server implementation
  - `Request`: HTTP request parsing and handling
  - `Response`: HTTP response generation
  - `Router`: URL routing system
- `config/`: Configuration file parsing and management
- `cgi/`: Common Gateway Interface implementation
- `utils/`: Utility functions and classes
  - `Logger`: Logging system
  - `StringUtils`: String manipulation utilities
- `www/`: Web content directory
  - `index.html`: Default landing page
  - `error_pages/`: Custom error pages

## Building and Running

### Prerequisites

- C++ compiler with C++98 support
- Make

### Compilation

```bash
make
```