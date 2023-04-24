/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TcpSocket
*/

#ifndef EPITECH_RAYTRACER_TCPSOCKET_HPP
#define EPITECH_RAYTRACER_TCPSOCKET_HPP
#include <string>
#include "network/Packet.hpp"

namespace Network {
    bool isIpPortValid(const std::string &ipPort);
    int bytesAvailable(int socket);

    class TcpSocket {
    public:
        friend class TcpListener;
        TcpSocket();
        ~TcpSocket();

        /**
         * @brief Connects to a remote host.
         *
         * If the socket is already connected, it will be disconnected first.
         *
         * @throws std::runtime_error If the socket cannot connect to the remote host.
         * @param address The address of the remote host.
         * @param port The port of the remote host.
         */
        void connect(const std::string &address, unsigned short port);

        /**
         * @brief Disconnects the socket.
         * @note This method is called upon destruction of the socket, and when the server disconnects.
         * @note Calling it on a not-connected socket will do nothing.
         */
        void disconnect();

        /**
         * @brief Sends data to the remote host.
         *
         * @param data The packet to send
         * @throws std::runtime_error If the data cannot be sent.
         */
        void send(const Packet &data);

        /**
         * @brief Receives data from the remote host.
         *
         * @note This method will block until all the data is received.
         * @throws std::runtime_error If the data cannot be received.
         * @return Packet The packet received
         */
        Packet receive();

        /**
         * @brief Gets the address of the remote host.
         *
         * @return std::string The address of the remote host.
         */
        std::string getRemoteAddress() const;

        /**
         * @brief Gets the port of the remote host.
         *
         * @return unsigned short The port of the remote host.
         */
        unsigned short getRemotePort() const;

        void checkDisconnect();
    private:
        bool send(const void *data, std::size_t size) const;
        bool receive(void *data, std::size_t size) const;

        void waitForData(std::size_t size) const;

        TcpSocket(const std::string &address, unsigned short port, int socket);

        int _socket;
        bool _connected;
        std::string _remoteAddress;
        unsigned short _remotePort;
    };

} // Network

#endif //EPITECH_RAYTRACER_TCPSOCKET_HPP
