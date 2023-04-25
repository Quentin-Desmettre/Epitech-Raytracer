/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PacketWriter
*/

#include <SFML/Graphics.hpp>
#include <cstring>
#include "network/PacketWriter.hpp"

Network::PacketWriter::PacketWriter(Network::Packet &packet)
    : _packet(packet)
{
}

Network::PacketWriter &Network::PacketWriter::operator<<(std::byte byte)
{
    _packet.append(byte);
    return *this;
}

Network::PacketWriter &Network::PacketWriter::operator<<(const std::vector<std::byte> &bytes)
{
    _packet.resize(_packet.getSize() + sizeof(bytes.size()) + bytes.size());
    *this << bytes.size();
    for (auto &byte : bytes)
        *this << byte;
    return *this;
}

Network::PacketWriter &Network::PacketWriter::operator<<(const std::string &string)
{
    *this << string.size();
    for (auto &byte : string)
        *this << std::byte(byte);
    return *this;
}
#include <iostream>
Network::PacketWriter &Network::PacketWriter::operator<<(const sf::VertexArray &pointArray)
{
    const std::size_t count = pointArray.getVertexCount();

    sf::Clock clock;
    *this << count;
    _packet.getData().reserve(_packet.getSize() + count * sizeof(sf::Vertex));

//    std::memcpy(_packet.getData().data() + _packet.getSize() - 1, &pointArray[0], count * sizeof(sf::Vertex));
    for (std::size_t i = 0; i < count * sizeof(sf::Vertex); i++)
        _packet.getData().push_back(*(((std::byte *)&pointArray[0]) + i));
    std::cout << "time to write array: " << clock.getElapsedTime().asMicroseconds() << std::endl;
    return *this;
}

Network::PacketWriter &Network::PacketWriter::operator<<(const sf::Vertex &vertex)
{
    _packet.resize(_packet.getSize() + sizeof(sf::Vertex));
    std::memcpy(_packet.getData().data() + _packet.getSize() - 1 - sizeof(sf::Vertex), &vertex, sizeof(sf::Vertex));
    return *this;
}
