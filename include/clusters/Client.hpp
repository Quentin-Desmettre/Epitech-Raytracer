/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Client
*/

#ifndef EPITECH_RAYTRACER_CLIENT_HPP
#define EPITECH_RAYTRACER_CLIENT_HPP
#include "network/TcpListener.hpp"
#include "RendererPool.hpp"
#include "clusters/Server.hpp"
#include <map>

namespace Raytracer::Clustering {
    class Client {
    public:
        Client(unsigned short port);
        ~Client() = default;

        void run();

    private:
        void handleUpdateScene(Network::Packet &data, Network::TcpSocket &socket);
        void handleRender(Network::Packet &data, Network::TcpSocket &socket);
        Network::TcpListener _listener;
        RendererPool _renderers;
        Scene _scene;

        const static std::map<std::byte, void (Client::*)(Network::Packet &, Network::TcpSocket &)> _handlers;
    };
}

#endif //EPITECH_RAYTRACER_CLIENT_HPP
