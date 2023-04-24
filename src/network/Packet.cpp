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

void Network::Packet::append(std::byte data)
{
    _data.push_back(data);
}

void Network::Packet::resize(std::size_t size)
{
    _data.resize(size);
}

std::vector<std::byte> Network::Packet::getData() const
{
    return _data;
}
