# TP1-REDES-UFMG

File Transfer System using C Sockets

This repository contains the source code for a simple file transfer system between a server and a client implemented in C, utilizing sockets.

Introduction

The goal of this project was to develop a file transfer system that allows seamless communication between a server and a client using C sockets.

Challenges

During the implementation of this project, several challenges were encountered, including:

Understanding C socket structures: A comprehensive understanding of data structures, functions, and system calls related to sockets was necessary. This included socket creation, address binding, connection listening, establishment, termination, and data sending/receiving.

Establishing and disconnecting connections: Configuring socket parameters such as protocol family (IPv4 or IPv6), socket, and port presented difficulties. Additionally, handling possible errors and exceptions during the connection process required careful consideration.

Keeping server and client active: Ensuring that both the server and the client remained active and ready to send/receive data was essential. This involved the development of loops and waiting mechanisms to handle client connections and communication effectively.

Solution

The file transfer system consists of both server and client components, each designed to facilitate seamless file exchange. The infrastructure, including connection handling, socket creation, and network communication, was meticulously developed. Furthermore, functions to support file manipulation, message formatting, and data exchange were implemented.

Usage

To run the file transfer system, follow these steps:

Clone this repository to your local machine.

Open two terminal windows.

In the first terminal, navigate to the repository's root directory and execute the following commands based on your preferred IP version:

IPv4:


./server v4 51511
IPv6:


./server v6 51511
In the second terminal, navigate to the repository's root directory and execute the following command based on your preferred IP version:

IPv4:


./client 127.0.0.1 51511
IPv6:

./client ::1 51511
Now, the server and client are connected, and you can perform various actions, such as selecting files to transfer, sending files, and receiving responses.
