/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TcpListener
*/

#include "network/TcpListener.hpp"
#include <sys/socket.h>
#include <cstring>
#include <stdexcept>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

void Network::TcpListener::listen(unsigned short port)
{
    // Check if we are already listening
    if (_listening)
        throw std::runtime_error("Listener is already listening. Use close() first.");

    // Socket
    _listening = false;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    int optval = 1;
    setsockopt(_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    if (_socket == -1)
        throw std::runtime_error("Failed to create socket. Reason: " + std::string(strerror(errno)));

    // Bind & Listen
    sockaddr_in address = {0, 0, 0, 0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (::bind(_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
        throw std::runtime_error("Failed to bind socket. Reason: " + std::string(strerror(errno)));
    if (::listen(_socket, 3) < 0)
        throw std::runtime_error("Failed to listen on socket. Reason: " + std::string(strerror(errno)));
    std::cout << "Listening on port " << port << std::endl;
    _listening = true;
}

void Network::TcpListener::close()
{
    if (!_listening)
        return;
    ::close(_socket);
    _listening = false;
}

void Network::TcpListener::accept(Network::TcpSocket &socket)
{
    if (!_listening)
        throw std::runtime_error("Listener is not listening. Use listen() first.");

    // Accept client, getting the socket and connection data
    sockaddr_in address = {0, 0, 0, 0};
    socklen_t addressSize = sizeof(address);
    int clientSocket = ::accept(_socket, (struct sockaddr *)&address, &addressSize);
    if (clientSocket < 0)
        throw std::runtime_error("Failed to accept client. Reason: " + std::string(strerror(errno)));

    // Set the socket using private constructor
    ::close(socket._socket);
    socket._socket = clientSocket;
    socket._remoteAddress = std::string(inet_ntoa(address.sin_addr));
    socket._remotePort = ntohs(address.sin_port);
    socket._connected = true;
}

Network::TcpListener::~TcpListener()
{
    close();
}
