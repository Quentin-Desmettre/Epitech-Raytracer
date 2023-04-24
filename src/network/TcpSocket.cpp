/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TcpSocket
*/

#include "network/TcpSocket.hpp"
#include <sys/socket.h>
#include <cstring>
#include <stdexcept>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>
#include <sys/ioctl.h>
#include <iostream>

Network::TcpSocket::TcpSocket()
{
    _connected = false;
    _socket = -1;
    _remotePort = 0;
}

void Network::TcpSocket::connect(const std::string &address, unsigned short port)
{
    if (_connected)
        throw std::runtime_error("Socket is already connected. Use disconnect() first.");

    // Socket
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
        throw std::runtime_error("Failed to create socket. Reason: " + std::string(strerror(errno)));

    // Setup connection
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    std::cout << address << std::endl;
    addr.sin_addr.s_addr = inet_addr(address.c_str());
    addr.sin_port = htons(port);

    // Connect
    if (::connect(_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Failed to connect to server. Reason: " + std::string(strerror(errno)));
    _connected = true;
    _remoteAddress = address;
    _remotePort = port;
}

Network::TcpSocket::TcpSocket(const std::string &address, unsigned short port, int socket)
{
    std::cout <<" === nik ===" << std::endl;
    int val = 0;
    std::cout << ioctl(socket, FIONREAD, &val) << std::endl;
    std::cout << "val: " << val << std::endl;
    std::cout << "errno: " << strerror(errno) << std::endl;
    std::cout << "=================" << std::endl;
    _connected = true;
    _socket = socket;
    std::cout <<" === ta race ===" << std::endl;
    val = 0;
    std::cout << ioctl(socket, FIONREAD, &val) << std::endl;
    std::cout << "val: " << val << std::endl;
    std::cout << "errno: " << strerror(errno) << std::endl;
    std::cout << "=================" << std::endl;
}

Network::TcpSocket::~TcpSocket()
{
    disconnect();
}

void Network::TcpSocket::disconnect()
{
    if (!_connected)
        return;
    ::close(_socket);
    _connected = false;
}

void Network::TcpSocket::send(const Packet &data)
{
    if (!_connected)
        throw std::runtime_error("Socket is not connected. Use connect() first.");

    // Send size
    std::size_t size = data.getSize();
    if (!send(&size, sizeof(size)))
        throw std::runtime_error("Failed to send data. Reason: " + std::string(strerror(errno)));
    // Send data
    if (!send(data.getData().data(), data.getSize()))
        throw std::runtime_error("Failed to send data. Reason: " + std::string(strerror(errno)));
}

bool Network::TcpSocket::send(const void *data, std::size_t size) const
{
    // Get infos
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    getpeername(_socket, (struct sockaddr *)&addr, &len);
    std::cout << "Sending " << size << " bytes to " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << std::endl;
    std::size_t sent = 0;
    while (sent < size) {
        ssize_t res = write(_socket, static_cast<const char *>(data) + sent, size - sent);
        if (res < 0)
            return false;
        sent += res;
    }
    std::cout << "sent " << size << " bytes" << std::endl;
    return true;
}

Network::Packet Network::TcpSocket::receive()
{
    if (!_connected)
        throw std::runtime_error("Socket is not connected. Use connect() first.");

    // Get size
    std::cout << "Waiting for data" << std::endl;
    waitForData(sizeof(std::size_t));
    std::size_t size = 0;
    if (!receive(static_cast<void *>(&size), sizeof(std::size_t)))
        throw std::runtime_error("Failed to receive data. Reason: " + std::string(strerror(errno)));

    std::cout << "Received size: " << size << std::endl;
    std::cout << "Waiting for data" << std::endl;
    // Get data
    waitForData(size);
    std::vector<std::byte> data(size);
    if (!receive(static_cast<void *>(data.data()), size))
        throw std::runtime_error("Failed to receive data. Reason: " + std::string(strerror(errno)));
    return {data};
}

bool Network::TcpSocket::receive(void *data, std::size_t size) const
{
    std::size_t received = 0;

    while (received < size) {
        ssize_t res = read(_socket, static_cast<char *>(data) + received, size - received);
        if (res < 0)
            return false;
        received += res;
    }
    return true;
}

void Network::TcpSocket::waitForData(std::size_t size) const
{
    while (true) {
        int bytes = bytesAvailable(_socket);
        if (bytes < 0)
            throw std::runtime_error("Failed to get bytes available. Reason: " + std::string(strerror(errno)));
        std::cout << "Bytes available on fd " << _socket << ": " << bytes << std::endl;
        if (static_cast<std::size_t>(bytes) >= size)
            return;
        // Wait 1ms
        usleep(100000);
    }
}

std::string Network::TcpSocket::getRemoteAddress() const
{
    if (!_connected)
        throw std::runtime_error("Socket is not connected. Use connect() first.");
    return _remoteAddress;
}

unsigned short Network::TcpSocket::getRemotePort() const
{
    if (!_connected)
        throw std::runtime_error("Socket is not connected. Use connect() first.");
    return _remotePort;
}

void Network::TcpSocket::checkDisconnect()
{
    if (!_connected)
        return;
    fd_set set;
    FD_ZERO(&set);
    FD_SET(_socket, &set);
    if (select(_socket + 1, &set, nullptr, nullptr, nullptr) < 0)
        throw std::runtime_error("Failed to check disconnect. Reason: " + std::string(strerror(errno)));
    if (bytesAvailable(_socket) == 0) {
        disconnect();
        throw std::runtime_error("Disconnected from server.");
    }
}

// Functions
bool Network::isIpPortValid(const std::string &ipPort)
{
    // Split ip and port
    std::size_t pos = ipPort.find(':');
    if (pos == std::string::npos)
        return false;
    std::string ip = ipPort.substr(0, pos);
    std::string port = ipPort.substr(pos + 1);
    if (ip.empty() || port.empty())
        return false;

    // Check port
    if (!std::ranges::all_of(port, [](char c) { return std::isdigit(c); })
    || std::stoi(port) < 0 || std::stoi(port) > 65535)
        return false;

    // Check ip
    if (inet_aton(ip.c_str(), nullptr) == 0)
        return false;
    return true;
}

int Network::bytesAvailable(int socket)
{
    int bytes = 0;
    std::cout << "ioctl: " << ioctl(socket, FIONREAD, &bytes) << "// " << strerror(errno) << std::endl;
    return bytes;
}