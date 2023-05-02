/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PacketWriter
*/

#include <SFML/Graphics.hpp>
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

Network::PacketWriter &Network::PacketWriter::operator<<(const PointArray &array)
{
    const std::size_t arraySize = array.getSize();
    const auto *pixels = array.getPixels();
    auto &vecData = _packet.getData();

    *this << arraySize;
    _packet.resize(vecData.size() + arraySize);
    const std::size_t offset = vecData.size() - arraySize;
    for (std::size_t i = 0; i < arraySize; i++)
        vecData[offset + i] = std::byte(pixels[i]);
    return *this;
}
