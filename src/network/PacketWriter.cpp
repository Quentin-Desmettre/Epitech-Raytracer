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
    const std::size_t arraySizeInBytes = array.getSize() * sizeof(float);
    const auto *pixels = reinterpret_cast<const std::byte *>(array.getPixels());
    auto &vecData = _packet.getData();

    *this << arraySizeInBytes;
    _packet.resize(vecData.size() + arraySizeInBytes);
    const std::size_t offset = vecData.size() - arraySizeInBytes;
    for (std::size_t i = 0; i < arraySizeInBytes; i++)
        vecData[offset + i] = pixels[i];
    return *this;
}
