# ft_p

Implementation of a simple client and server in C for file transfering (FTP). The communication between them is done in TCP/IP(v4).
The server can support up to 10 clients.

The client cat send the following commands to the server:

- pwd - list the path of the current working directory of the server

- ls - list the content of the current working directory of the server

- put _file_ - send a file to the server

- get _file_ - receive a file from the server

- cd - change the current working directory of the server

- quit - close the connection

-------------------

Usage:

-> make

-> ./serveur port

-> ./client ip port
