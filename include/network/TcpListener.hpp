/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TcpListener
*/

#ifndef EPITECH_RAYTRACER_TCPLISTENER_HPP
#define EPITECH_RAYTRACER_TCPLISTENER_HPP
#include "TcpSocket.hpp"

namespace Network {
    class TcpListener {
    public:
        TcpListener() = default;

        /**
         * @brief Destroy the TcpListener object, and close the listener.
         */
        ~TcpListener();

        int bytesAvailable() const {
            return Network::bytesAvailable(_socket);
        }

        /**
         * @brief Start listening for incoming connections. Listens on all interfaces.
         * @param port The port to listen on.
         * @throws std::runtime_error If the listener cannot listen on the specified port.
         */
        void listen(unsigned short port);

        /**
         * @brief Closes the listener.
         *
         * @note This method is called upon destruction of the listener.
         * @note It is your responsibility to close the accepted sockets, or to call their destructor.
         */
        void close();

        /**
         * @brief Waits until a client connects to the listener.
         *
         * @throws std::runtime_error If the listener is not listening, or if the client cannot be accepted.
         * @param socket The socket to accept the client into.
         */
        void accept(TcpSocket &socket);

    private:
        int _socket = -1;
        bool _listening = false;
    };
} // Network


#endif //EPITECH_RAYTRACER_TCPLISTENER_HPP
