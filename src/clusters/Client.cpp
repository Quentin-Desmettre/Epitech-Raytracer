/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Client
*/

#include "clusters/Client.hpp"
#include "Encoder.hpp"

const std::map<std::byte, void (Raytracer::Clustering::Client::*)(Network::Packet &, Network::TcpSocket &)> Raytracer::Clustering::Client::_handlers = {
    {std::byte{Raytracer::Clustering::UPDATE_SCENE},    &Raytracer::Clustering::Client::handleUpdateScene},
    {std::byte{Raytracer::Clustering::RENDER},          &Raytracer::Clustering::Client::handleRender}
};

Raytracer::Clustering::Client::Client(unsigned short port)
{
    _listener.listen(port);
}

void Raytracer::Clustering::Client::run()
{
    Network::TcpSocket socket;

    _listener.accept(socket);
    // Wait for request, handle it, then wait again
    while (true) {
        Network::Packet message = socket.receive();
        std::byte type = message.getData()[0];
        if (_handlers.find(type) != _handlers.end())
            (this->*_handlers.at(type))(message, socket);
        else
            std::cerr << "Unknown message type: " << static_cast<int>(type) << std::endl;
    }
}

void Raytracer::Clustering::Client::handleUpdateScene(Network::Packet &data, Network::TcpSocket &socket)
{
    auto [scene, startPoint, endPoint] = Encoder::decodeScene(data.getData());

    _scene = scene;
    _renderers.setRange(startPoint, endPoint);
}

void Raytracer::Clustering::Client::handleRender(Network::Packet &data, Network::TcpSocket &socket)
{
    _renderers.render(_scene);
    sf::VertexArray vertexArray = _renderers.getVertexArray();
    socket.send(Encoder::encodeVertexArray(vertexArray, std::byte{RENDER_DONE}).getData());
}
