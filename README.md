Lightweight HTTP Server for Educational Purposes

This project implements a basic HTTP server in C++ for educational purposes. It is designed to help users understand how web servers handle incoming requests and deliver responses.

Features:

Creates a TCP socket and binds it to a loopback address (localhost).
Listens for incoming connections.
Parses basic HTTP requests.
Reads requested files from the server's root directory.
Generates HTTP responses based on the request and file existence.

This is a basic server designed for learning and should not be used in a production environment. It lacks features and security measures required for real-world applications.

How to Use

Compile the source code using a C++ compiler.
Run the compiled executable.
The server will listen for connections on port specified in the configuration file (config.txt).
Use tools like curl or a web browser to send HTTP requests to http://localhost:<port>.
Configuration

The server reads configuration options from a file named config.txt. The configuration options include:

port: The port number on which the server listens for connections.
root: The directory from which the server serves static content.
index: The default file to serve when a directory is requested (e.g., index.html).
Learning Objectives

This project can be used to learn about:

Socket programming concepts (creating sockets, binding, listening, connecting).
HTTP request and response structure.
File I/O operations in C++.
Basic parsing of text data.
Further Enhancements

This is a basic implementation, and there are many ways to enhance it for educational purposes: