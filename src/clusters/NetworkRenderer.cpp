/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Server
*/

#include "clusters/Server.hpp"
#include "RendererPool.hpp"
#include "network/PacketReader.hpp"
#include "network/PacketWriter.hpp"
#include <thread>

Raytracer::Clustering::Server::Server(const std::vector<std::string> &clusters, sf::Vector2u start, sf::Vector2u end)
{
    // Connect to clusters
    for (const auto &cluster : clusters)
        _renderers.push_back(std::make_unique<NetworkRenderer>(cluster));
    internalSetRange(start, end);
}

void Raytracer::Clustering::Server::render(const Scene &scene, PointArray &array)
{
    // Render
    for (auto &renderer : _renderers)
        renderer->render(scene, array);
    std::cout << "Fetching answers..." << std::endl;
    for (auto &renderer : _renderers)
        dynamic_cast<NetworkRenderer *>(renderer.get())->fetchAnswer();
    std::cout << "Done" << std::endl;
}

int Raytracer::Clustering::Server::getThreadsCount() const
{
    int count = 0;

    for (const auto &renderer : _renderers)
        count += renderer->getThreadsCount();
    return count;
}

void Raytracer::Clustering::Server::setRange(sf::Vector2u start, sf::Vector2u end)
{
    internalSetRange(start, end);
}

void Raytracer::Clustering::Server::internalSetRange(sf::Vector2u start, sf::Vector2u end)
{
    _start = start;
    _end = end;

    std::cout << "setting range to " << start.x << " " << start.y << " " << end.x << " " << end.y << std::endl;
    auto ranges = RendererPool::splitRange(start, end, _renderers);
    for (auto &renderer : _renderers)
        renderer->setRange(ranges[renderer.get()].first, ranges[renderer.get()].second);
}

//==============================================================================
// NetworkRenderer
//==============================================================================
Raytracer::Clustering::Server::NetworkRenderer::NetworkRenderer(const std::string &ipPort)
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

void Raytracer::Clustering::Server::NetworkRenderer::render(const Scene &scene, PointArray &array)
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

    _clock.restart();
    // Render
    _array = &array;
    packet = Network::Packet({std::byte(RENDER)});
    _socket.send(packet);
}
#include <cstring>
#include <fstream>
void Raytracer::Clustering::Server::NetworkRenderer::fetchAnswer()
{
    std::cout << "fetching answer" << std::endl;
    Network::Packet packet = _socket.receive();
    std::cout << "starting the reader" << std::endl;
    Network::PacketReader reader(packet);
    std::byte type;
    reader >> type;
    std::cout << "reading..." << std::endl;
    std::size_t size = 0;
    reader >> size;

    sf::Clock clock;
    std::cout << "packet size: " << packet.getData().size() << std::endl;
    std::ofstream file("test.ppm", std::ios::binary | std::ios::out | std::ios::trunc);
    file.write((const char *)packet.getData().data() + 9, size);
    file.close();
    std::memcpy(_array->getPixels() + _start.y * _array->getSizeVector().x * 3 + _start.x * 3, packet.getData().data() + 9, size);
//    auto *arr = new sf::Uint8[size * 3];
//    std::memcpy(arr, packet.getData().data() + 9, size * 3);
//    for (std::size_t i = 0; i < size; i++) {
//    }
//    for (int i = 0; i < size; i++)
//        std::cout << vertexArray[i].position.x << "; " << vertexArray[i].position.y << std::endl;
    std::cout << "Time to read array: " << clock.getElapsedTime().asMicroseconds() << std::endl;
    std::cout << "Fetched in " << _clock.getElapsedTime().asMilliseconds() << "ms" << std::endl;
}

void Raytracer::Clustering::Server::NetworkRenderer::setRange(sf::Vector2u start, sf::Vector2u end)
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

int Raytracer::Clustering::Server::NetworkRenderer::getThreadsCount() const
{
    return _nbThreads;
}
