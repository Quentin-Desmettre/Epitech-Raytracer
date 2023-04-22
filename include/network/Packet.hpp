/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Packet
*/

#ifndef EPITECH_RAYTRACER_PACKET_HPP
#define EPITECH_RAYTRACER_PACKET_HPP
#include <vector>

namespace Network {
    class Packet {
    public:
        Packet(const std::vector<std::byte> &data = {});

        /**
         * @brief Gets the size of the packet.
         *
         * @return std::size_t The size of the packet.
         */
        std::size_t getSize() const;

        /**
         * @brief Gets the data of the packet.
         *
         * @return std::vector<std::byte> The data of the packet.
         */
        std::vector<std::byte> getData() const;

        /**
         * @brief Add data to the packet.
         * @param data The data to add.
         */
        template<class T>
        void append(const T &data) {
            append(reinterpret_cast<const std::byte *>(&data), sizeof(T));
        }

        /**
         * @brief Add data to the packet.
         * @param data The data to add.
         */
        void append(const std::vector<std::byte> &data);
        void append(const std::byte *data, std::size_t size);

    private:
        std::vector<std::byte> _data;
    };
} // Network

#endif //EPITECH_RAYTRACER_PACKET_HPP
