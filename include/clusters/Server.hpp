/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Server
*/

#ifndef EPITECH_RAYTRACER_SERVER_HPP
#define EPITECH_RAYTRACER_SERVER_HPP
#include "IRenderer.hpp"
#include "network/TcpSocket.hpp"

namespace Raytracer::Clustering {
        enum PacketType {
            UPDATE_SCENE,
            RENDER,
        };
        /**
         * @brief Server class
         *
         * This class handles the communication with the clusters
         */
        class Server: public IRenderer {
        public:
            /**
             * @brief Construct a new Server object.
             *
             * It will initialize the connections with the clusters.         *
             * @param clusters The list of clusters to connect to.
             */
            explicit Server(const std::vector<std::string> &clusters, unsigned xStart, unsigned xEnd, unsigned yStart, unsigned yEnd);

            /**
             * @brief Render the scene
             *
             * This method will send the render request to the clusters, and wait until each one of them has finished.
             * Once the clusters have finished, the method will update the vertex array with the result of the clusters.
             * @param scene The scene to render. This object must never be destroyed.
             */
            void render(const Scene &scene) override;
            sf::VertexArray getVertexArray() const override;

        private:
            std::vector<std::string> _clusters;
            std::vector<Network::TcpSocket> _sockets;
            unsigned _xStart, _xEnd, _yStart, _yEnd;

            sf::VertexArray _vertexArray;
            const Scene *_scene;
            std::vector<std::byte> _encodedScene;

            /**
             * @brief Encode the scene
             *
             * This method will encode the scene into a buffer that can be sent to the clusters.
             */
            void encodeScene();
            void updateVertexArrays(const std::vector<Network::Packet> &packets);
            void appendToVertexArray(const std::vector<std::byte> &data);
        };
    } // Raytracer

#endif //EPITECH_RAYTRACER_SERVER_HPP
