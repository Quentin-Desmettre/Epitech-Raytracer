/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Encoder
*/

#include "network/PacketReader.hpp"
#include <cstring>

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
    std::size_t size = 0;
    *this >> size;

    string.resize(size);
    std::memcpy(string.data(), _packet.getData().data() + _offset, size);
    _offset += size;
    return *this;
}

Network::PacketReader &Network::PacketReader::readPointArray(PointArray &array, sf::Vector2u start)
{
    std::size_t size = 0;

    *this >> size;
    std::memcpy(array.getPixels() + (start.x * array.getSizeVector().y + start.y) * 3,
                _packet.getData().data() + _offset,
                size);
    return *this;
}
