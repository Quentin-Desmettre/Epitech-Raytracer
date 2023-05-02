/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** PacketWriter
*/

#ifndef EPITECH_RAYTRACER_PACKETWRITER_HPP
#define EPITECH_RAYTRACER_PACKETWRITER_HPP
#include "network/Packet.hpp"
#include "render/PointArray.hpp"
#include <string>

namespace Network {
    class PacketWriter {
    public:
        explicit PacketWriter(Network::Packet &packet);

        template <typename T>
        PacketWriter &operator<<(const T &value) {
            const auto *bytes = reinterpret_cast<const std::byte *>(&value);
            for (std::size_t i = 0; i < sizeof(T); i++)
                *this << bytes[i];
            return *this;
        }

        PacketWriter &operator<<(std::byte byte);
        PacketWriter &operator<<(const PointArray &array);
        PacketWriter &operator<<(const std::vector<std::byte> &bytes);
        PacketWriter &operator<<(const std::string &string);

    private:
        Network::Packet &_packet;
    };
} // Clustering

#endif //EPITECH_RAYTRACER_PACKETWRITER_HPP
