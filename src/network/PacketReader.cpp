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

#include <cstring>

Network::PacketReader &Network::PacketReader::operator>>(std::string &string)
{
    std::size_t size = 0;
    *this >> size;

    char *data = new char[size];
    std::memcpy(data, _packet.getData().data() + _offset, size);
    string = std::string(data, size);
    _offset += size;
    delete[] data;
    return *this;
}

Network::PacketReader &Network::PacketReader::operator>>(sf::VertexArray &vertexArray)
{
    std::size_t size = 0;
    *this >> size;

    sf::Clock clock;
    vertexArray.resize(size);
    sf::Vertex *vertexArrayPtr = &vertexArray[0];
    std::memcpy(vertexArrayPtr, _packet.getData().data() + _offset, size * sizeof(sf::Vertex));
    std::cout << "Time to read array: " << clock.getElapsedTime().asMicroseconds() << std::endl;
    return *this;
}

Network::PacketReader &Network::PacketReader::operator>>(sf::Vertex &vertex)
{
    *this >> vertex.position.x >> vertex.position.y;
    *this >> vertex.color.r >> vertex.color.g >> vertex.color.b >> vertex.color.a;
    *this >> vertex.texCoords.x >> vertex.texCoords.y;
    return *this;
}
