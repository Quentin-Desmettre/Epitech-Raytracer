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

void Raytracer::Clustering::Server::render(const Scene &scene)
{
    // Render
    for (auto &renderer : _renderers)
        renderer->render(scene);
    std::cout << "Fetching answers..." << std::endl;
    for (auto &renderer : _renderers)
        dynamic_cast<NetworkRenderer *>(renderer.get())->fetchAnswer();
    std::cout << "Done" << std::endl;

    std::cout << "Update vertex array" << std::endl;
    // Update vertex array
    sf::VertexArray arr;
    _vertexArray.clear();
    for (auto &renderer : _renderers) {
        arr = renderer->getVertexArray();
        for (std::size_t i = 0; i < arr.getVertexCount(); i++)
            _vertexArray.append(arr[i]);
    }
    std::cout << "Done" << std::endl;
}

sf::VertexArray Raytracer::Clustering::Server::getVertexArray() const
{
    return _vertexArray;
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

void Raytracer::Clustering::Server::NetworkRenderer::render(const Scene &scene)
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
    packet = Network::Packet({std::byte(RENDER)});
    _socket.send(packet);
}

void Raytracer::Clustering::Server::NetworkRenderer::fetchAnswer()
{
    std::cout << "fetching answer" << std::endl;
    Network::Packet packet = _socket.receive();
    std::cout << "starting the reader" << std::endl;
    Network::PacketReader reader(packet);
    std::byte type;

    std::cout << "reading..." << std::endl;
    reader >> type >> _vertexArray;
    std::cout << "Fetched!" << std::endl;
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

sf::VertexArray Raytracer::Clustering::Server::NetworkRenderer::getVertexArray() const
{
    return _vertexArray;
}
