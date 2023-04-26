/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Server
*/

#include "clusters/NetworkRenderer.hpp"
#include "render/RendererPool.hpp"
#include "network/PacketReader.hpp"
#include "network/PacketWriter.hpp"
#include <thread>

//==============================================================================
// NetworkRenderer
//==============================================================================
Raytracer::Clustering::NetworkRenderer::NetworkRenderer(const std::string &ipPort)
{
    // Connect
    _nbThreads = 0;
    int port = std::stoi(ipPort.substr(ipPort.find(':') + 1));
    _socket.connect(ipPort.substr(0, ipPort.find(':')), port);

    // Query thread count
    Network::Packet packet({std::byte(GET_THREAD_COUNT)});
    _socket.send(packet);
    packet = _socket.receive();
    Network::PacketReader reader(packet);
    std::byte header;
    reader >> header >> _nbThreads;

    std::cout << "Connected to " << ipPort << " with " << _nbThreads << " threads" << std::endl;
}

void Raytracer::Clustering::NetworkRenderer::render(const Scene &scene, PointArray &array)
{
    if (_scene != &scene) {// TODO: fix
        Network::Packet packet;
        // Encode scene
        Network::PacketWriter writer(packet);
        writer << std::byte(UPDATE_SCENE) << scene.getRawConfiguration();
        writer << _start.x << _start.y << _end.x << _end.y;
        _socket.send(packet);
        // Wait for answer
        packet = _socket.receive();
        _scene = &scene;
    }
    Network::Packet packet;

    // Render
    _clock.restart();
    packet = Network::Packet({std::byte(RENDER)});
    _socket.send(packet);

    // Fetch answer
    std::cout << "fetching answer" << std::endl;
    packet = _socket.receive();
    std::cout << "Time to receive render response: " << _clock.getElapsedTime().asMilliseconds() << "ms" << std::endl;
    _clock.restart();


    Network::PacketReader reader(packet);
    std::byte type;
    reader >> type;
    reader.readPointArray(array, _start);
    std::cout << "Fetched in " << _clock.getElapsedTime().asMilliseconds() << "ms" << std::endl;
}

void Raytracer::Clustering::NetworkRenderer::setRange(sf::Vector2u start, sf::Vector2u end)
{
    Network::Packet packet;
    Network::PacketWriter writer(packet);

    writer << std::byte(UPDATE_RANGE) << start.x << start.y << end.x << end.y;
    _socket.send(packet);

    // Wait for answer
    packet = _socket.receive();
    _start = start;
    _end = end;
}

int Raytracer::Clustering::NetworkRenderer::getThreadsCount() const
{
    return _nbThreads;
}
