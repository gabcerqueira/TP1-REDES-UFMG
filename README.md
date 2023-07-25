# TP1-REDES-UFMG

Practical task 1 aimed to implement a simple file transfer system between a server and a client using sockets in C.

Challenges
During the implementation of the task, several challenges arose, including:

Understanding the socket structure in C, which required knowledge of data structures, functions, and system calls related to sockets. Concepts like socket creation, address binding, connection listening, establishment and termination of connections, data sending and receiving were crucial.
Properly establishing and disconnecting connections involved configuring socket parameters like protocol family (IPv4 or IPv6), socket, and port. Handling potential errors and exceptions during the connection process was necessary.
Maintaining both server and client active was essential for the file transfer system. The implementation required loops and waiting mechanisms to keep the server waiting for client connections and the client ready to send and receive data.
Difficulties
The main difficulties encountered during the system implementation were file manipulation, understanding socket programming, and managing strings in C for message formatting and processing on both communication sides.

Solution
Infrastructure
To address the infrastructure, a function called "usage" was defined to verify the input parameters following the pattern:
IPv4:
Terminal 1: ./server v4 51511
Terminal 2: ./client 127.0.0.1 51511
IPv6:
Terminal 1: ./server v6 51511
Terminal 2: ./client ::1 51511
Examples of connections were also shown.
In the client part, input parameter correctness was verified. The "storage" structure stored network address information, and the "addrparse" function filled the structure based on the input parameters. Then, the "socket" function created a new socket of type SOCK_STREAM, using the TCP protocol, and associated it with the specified address domain "storage.ss_family," whether IPv4 or IPv6. The "connect" function established the connection with the retrieved network address. Finally, the "run" function was called to establish the client's logic with the server.
On the server-side, storing network information and creating the socket were similar to the client's logic. The "bind" function associated the "serversock" socket with the retrieved network address. The "listen" function was called to start listening for connections, and an infinite loop was defined to accept client connections. The "accept" function accepted a new connection, and the connected client's information (client sock, client address) was stored. Then, the "exec" function was executed, containing the logic of communication with the client. When the mentioned loop ended, the connection was closed using the "close" function, terminating the connection between both sides.

To modularize supporting infrastructure functions, "common.h" and "common.c" files were used. For supporting file transfer system logic functions, "handlers.c" and "handlers.h" files were utilized. To handle sending responses to the client and receiving responses from the client, the "sendResponse" and "receiveResponse" functions were respectively used, executing the "send" and "recv" functions.

Execution Flow
The system works as follows:

Communication between the client and server is established using the following commands:
IPv4:
Terminal 1: ./server v4 51511
Terminal 2: ./client 127.0.0.1 51511
IPv6:
Terminal 1: ./server v6 51511
Terminal 2: ./client ::1 51511
The client selects a file using the "select file [filename]" command. Validations are performed to check if the specified file exists and has a valid format (.c, .txt, .cpp, .py, .java, .tex). If the validations pass, the file is selected.
With the selected file, the client can send it to the server using the "send file" command. At this stage, it checks if a file is selected, and if so, it sends the file, and the server responds by validating the reception.
The server processes the received message, retrieving the file's name and content and checking if the file exists in the "serverFiles" directory. If it does, it performs the overwrite; otherwise, the file is saved normally.
The user can terminate the connection with the server using the "exit" command, finalizing the connection.
