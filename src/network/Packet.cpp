/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Packet
*/

#include "network/Packet.hpp"

Network::Packet::Packet(const std::vector<std::byte> &data)
    : _data(data)
{
}

std::size_t Network::Packet::getSize() const
{
    return _data.size();
}

void Network::Packet::append(const std::vector<std::byte> &data)
{
    _data.insert(_data.end(), data.begin(), data.end());
}

void Network::Packet::append(const std::byte *data, std::size_t size)
{
    _data.reserve(_data.size() + size);
    for (std::size_t i = 0; i < size; ++i)
        _data.push_back(data[i]);
}
