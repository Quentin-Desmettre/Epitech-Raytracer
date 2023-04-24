/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Encoder
*/

#include "network/PacketReader.hpp"

Network::PacketReader::PacketReader(const Network::Packet &packet)
    : _packet(packet)
{
}

Network::PacketReader &Network::PacketReader::operator>>(std::byte &byte)
{
    byte = _packet.getData()[_offset];
    _offset += 1;
    return *this;
}

Network::PacketReader &Network::PacketReader::operator>>(std::vector<std::byte> &bytes)
{
    unsigned int size = 0;
    *this >> size;
    bytes.resize(size);
    for (unsigned int i = 0; i < size; i++)
        *this >> bytes[i];
    return *this;
}

Network::PacketReader &Network::PacketReader::operator>>(std::string &string)
{
    unsigned int size = 0;
    *this >> size;
    string.resize(size);
    for (unsigned int i = 0; i < size; i++)
        *this >> string[i];
    return *this;
}

Network::PacketReader &Network::PacketReader::operator>>(sf::VertexArray &vertexArray)
{
    unsigned int size = 0;
    *this >> size;
    vertexArray.resize(size);
    for (unsigned int i = 0; i < size; i++)
        *this >> vertexArray[i];
    return *this;
}

Network::PacketReader &Network::PacketReader::operator>>(sf::Vertex &vertex)
{
    *this >> vertex.position.x;
    *this >> vertex.position.y;
    *this >> vertex.color.r;
    *this >> vertex.color.g;
    *this >> vertex.color.b;
    *this >> vertex.color.a;
    *this >> vertex.texCoords.x;
    *this >> vertex.texCoords.y;
    return *this;
}
