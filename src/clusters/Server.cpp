/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Server
*/

#include "clusters/Server.hpp"

Raytracer::Clustering::Server::Server(const std::vector<std::string> &clusters, unsigned xStart, unsigned xEnd, unsigned yStart, unsigned yEnd)
    : _clusters(clusters),
    _sockets(),
    _xStart(xStart), _xEnd(xEnd), _yStart(yStart), _yEnd(yEnd),
    _vertexArray(), _scene(nullptr), _encodedScene()
{
    // Connect to clusters
    int port;
    for (const auto &cluster : clusters) {
        port = std::stoi(cluster.substr(cluster.find(':') + 1));
        _sockets.emplace_back();
        _sockets.back().connect(cluster, port);
    }
}

void Raytracer::Clustering::Server::render(const Scene &scene)
{
    // Update scene if needed
    if (_scene != &scene) {
        _scene = &scene;
        encodeScene();

        // Divide range of pixels to render into columns, that have the same height
        std::vector<std::pair<sf::Vector2u, sf::Vector2u>> ranges;
        ranges.reserve(_sockets.size());
        unsigned width = (_xEnd - _xStart) / _sockets.size();
        unsigned xStart = _xStart;
        unsigned xEnd = _xStart + width;
        for (unsigned i = 0; i < _sockets.size() - 1; ++i) {
            ranges.emplace_back(sf::Vector2u(xStart, _yStart), sf::Vector2u(xStart + width, _yEnd));
            xStart += width;
            xEnd += width;
        }
        ranges.emplace_back(sf::Vector2u(xStart, _yStart), sf::Vector2u(_xEnd, _yEnd));

        // Tell clusters to update their scene
        Network::Packet packet({std::byte(UPDATE_SCENE)});
        packet.append(_encodedScene);
        for (int i = 0; i < _sockets.size(); ++i) {
            Network::Packet tmp = packet;
            tmp.append(ranges[i].first);
            tmp.append(ranges[i].second);
            _sockets[i].send(tmp);
        }
    }

    // Send render request to clusters
    Network::Packet packet({std::byte(RENDER)});
    for (auto &socket : _sockets)
        socket.send(packet);

    // Wait for clusters to finish
    std::vector<Network::Packet> answers;
    answers.reserve(_sockets.size());
    for (auto &socket : _sockets)
        answers.push_back(socket.receive());

    // Update vertex array
    updateVertexArrays(answers);
}

sf::VertexArray Raytracer::Clustering::Server::getVertexArray() const
{
    return _vertexArray;
}

void Raytracer::Clustering::Server::updateVertexArrays(const std::vector<Network::Packet> &packets)
{
    for (const auto &packet : packets)
        appendToVertexArray(packet.getData());
}

void Raytracer::Clustering::Server::encodeScene()
{
    // TODO
}

void Raytracer::Clustering::Server::appendToVertexArray(const std::vector<std::byte> &data)
{
    // TODO
}
