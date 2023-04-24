/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PacketWriter
*/

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
    _packet.resize(_packet.getSize() + sizeof(string.size()) + string.size());
    *this << string.size();
    for (auto &byte : string)
        *this << std::byte(byte);
    return *this;
}

Network::PacketWriter &Network::PacketWriter::operator<<(const sf::VertexArray &vertexArray)
{
    const auto count = vertexArray.getVertexCount();
    std::size_t addedData = sizeof(count) + sizeof(vertexArray.getPrimitiveType()) + count * sizeof(sf::Vertex);

    _packet.resize(_packet.getSize() + addedData);
    *this << count;
    *this << vertexArray.getPrimitiveType();
    for (std::size_t i = 0; i < count; i++)
        *this << vertexArray[i];
    return *this;
}

Network::PacketWriter &Network::PacketWriter::operator<<(const sf::Vertex &vertex)
{
    *this << vertex.position.x;
    *this << vertex.position.y;
    *this << vertex.color.r;
    *this << vertex.color.g;
    *this << vertex.color.b;
    *this << vertex.color.a;
    *this << vertex.texCoords.x;
    *this << vertex.texCoords.y;
    return *this;
}
