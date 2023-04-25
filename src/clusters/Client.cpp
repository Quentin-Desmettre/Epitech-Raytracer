/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Client
*/

#include "clusters/Client.hpp"
#include "network/PacketReader.hpp"
#include "network/PacketWriter.hpp"
#include "scene/SceneBuilder.hpp"
#include "LocalRenderer.hpp"
#include <fstream>
#include <thread>

const std::map<std::byte, void (Raytracer::Clustering::Client::*)(Network::Packet &, Network::TcpSocket &)> Raytracer::Clustering::Client::_handlers = {
    {std::byte{Raytracer::Clustering::UPDATE_SCENE},    &Raytracer::Clustering::Client::handleUpdateScene},
    {std::byte{Raytracer::Clustering::UPDATE_RANGE},     &Raytracer::Clustering::Client::handleUpdateRange},
    {std::byte{Raytracer::Clustering::RENDER},          &Raytracer::Clustering::Client::handleRender},
    {std::byte{Raytracer::Clustering::GET_THREAD_COUNT},  &Raytracer::Clustering::Client::handleGetThreadCount},
};

Raytracer::Clustering::Client::Client(unsigned short port)
{
    _listener.listen(port);
}

void Raytracer::Clustering::Client::run()
{
    Network::TcpSocket socket;

    std::cout << "Waiting for connection..." << std::endl;
    _listener.accept(socket);
    // Wait for request, handle it, then wait again
    std::cout << "waiting for request..." << std::endl;
    usleep(1000000);
    _startPoint = {0, 0};
    _endPoint = {1, 1};
    buildRendererPool();
    while (true) {
        Network::Packet message = socket.receive();
        std::byte type = message.getData()[0];
        std::cout << "received request: " << static_cast<int>(type) << std::endl;
        if (_handlers.find(type) != _handlers.end())
            (this->*_handlers.at(type))(message, socket);
        else
            std::cerr << "Unknown message type: " << static_cast<int>(type) << std::endl;
    }
}

void Raytracer::Clustering::Client::handleUpdateScene(Network::Packet &data, Network::TcpSocket &socket)
{
    Network::PacketReader reader(data);
    std::string sceneConfig;
    std::byte header;
    reader >> header >> sceneConfig >> _startPoint.x >> _startPoint.y >> _endPoint.x >> _endPoint.y;

    // Write the scene to a file
    std::ofstream file("scene.config");
    file << sceneConfig;
    file.close();

    // Build the scene
    SceneBuilder builder{"scene.config"};
    _scene = builder.build();
    _renderers->setRange(_startPoint, _endPoint);

    // Inform that the update is done
    Network::Packet packet({std::byte(UPDATE_SCENE_DONE)});
    socket.send(packet);
}

void Raytracer::Clustering::Client::handleRender(Network::Packet &, Network::TcpSocket &socket)
{
    _renderers->render(*_scene);
    sf::VertexArray vertexArray = _renderers->getVertexArray();
    sf::Clock clock;
    Network::Packet packet;
    Network::PacketWriter writer(packet);

    writer << std::byte(RENDER_DONE) << vertexArray;
    socket.send(packet);
    std::cout << "Sent vertex array in " << clock.getElapsedTime().asMilliseconds() << "ms" << std::endl;
}

void Raytracer::Clustering::Client::handleUpdateRange(Network::Packet &data, Network::TcpSocket &socket)
{
    // Rebuild the renderer pool
    Network::PacketReader reader(data);
    std::byte header;
    reader >> header >> _startPoint.x >> _startPoint.y >> _endPoint.x >> _endPoint.y;

    _renderers->setRange(_startPoint, _endPoint);

    // Inform that the update is done
    Network::Packet packet({std::byte(UPDATE_RANGE_DONE)});
    socket.send(packet);
}

void Raytracer::Clustering::Client::handleGetThreadCount(Network::Packet &, Network::TcpSocket &socket)
{
    Network::Packet packet;
    Network::PacketWriter writer(packet);

    writer << std::byte(THREAD_COUNT) << _renderers->getThreadsCount();
    socket.send(packet);
}

void Raytracer::Clustering::Client::buildRendererPool()
{
    _renderers = std::make_unique<RendererPool>(_startPoint, _endPoint);
    for (unsigned i = 0; i < std::thread::hardware_concurrency(); i++)
        _renderers->addRenderer(std::make_unique<LocalRenderer>(sf::Vector2u(0, 0), sf::Vector2u(1, 1)));
    _renderers->setRange();
}
