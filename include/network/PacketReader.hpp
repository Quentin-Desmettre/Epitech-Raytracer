/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Encoder
*/

#ifndef EPITECH_RAYTRACER_PACKETREADER_HPP
#define EPITECH_RAYTRACER_PACKETREADER_HPP
#include "network/Packet.hpp"
#include "scene/Scene.hpp"

namespace Network {
    class PacketReader {
    public:
        explicit PacketReader(const Network::Packet &packet);

        // Primitives
        template <typename T>
        PacketReader &operator>>(T &value) {
            auto *bytes = reinterpret_cast<std::byte *>(&value);
            for (std::size_t i = 0; i < sizeof(T); i++)
                *this >> bytes[i];
            return *this;
        }

        // Misc
        PacketReader &operator>>(std::byte &byte);
        PacketReader &operator>>(std::vector<std::byte> &bytes);
        PacketReader &operator>>(std::string &string);
        PacketReader &operator>>(sf::VertexArray &vertexArray);
        PacketReader &operator>>(sf::Vertex &vertex);


    private:
        const Network::Packet &_packet;
        std::size_t _offset = 0;
    };
} // Clustering

#endif //EPITECH_RAYTRACER_PACKETREADER_HPP
