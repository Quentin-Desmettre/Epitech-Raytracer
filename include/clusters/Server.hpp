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
            // Requests
            UPDATE_SCENE,
            UPDATE_RANGE,
            RENDER,
            GET_THREAD_COUNT,

            // Answers
            UPDATE_SCENE_DONE,
            UPDATE_RANGE_DONE,
            RENDER_DONE,
            THREAD_COUNT,
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
            explicit Server(const std::vector<std::string> &clusters, sf::Vector2u start, sf::Vector2u end);

            /**
             * @brief Render the scene
             *
             * This method will send the render request to the clusters, and wait until each one of them has finished.
             * Once the clusters have finished, the method will update the vertex array with the result of the clusters.
             * @param scene The scene to render. This object must never be destroyed.
             */
            void render(const Scene &scene) override;
            sf::VertexArray getVertexArray() const override;

            void setRange(sf::Vector2u start, sf::Vector2u end) override;

            int getThreadsCount() const override;

        private:
            class NetworkRenderer: public IRenderer {
            public:
                explicit NetworkRenderer(const std::string &ipPort);

                /**
                 * @brief Sends the RENDER request to the cluster.
                 * @param scene
                 */
                void render(const Scene &scene) override;

                /**
                 * @brief Fetch the answer from the cluster.
                 */
                void fetchAnswer();

                /**
                 * @see IRenderer::getVertexArray()
                 */
                sf::VertexArray getVertexArray() const override;

                /**
                 * @brief Sends the request to update the range of the renderer.
                 * @see IRenderer::setRange()
                 */
                void setRange(sf::Vector2u start, sf::Vector2u end) override;

                /**
                 * @brief Get the number of threads of the cluster.
                 * @see IRenderer::getThreadsCount()
                 */
                int getThreadsCount() const override;

            private:
                int _nbThreads;
                Network::TcpSocket _socket;
                sf::VertexArray _vertexArray;
                const Scene *_scene = nullptr;
                sf::Vector2u _start, _end;
            };

            std::vector<std::unique_ptr<IRenderer>> _renderers;
            sf::Vector2u _start, _end;
            sf::VertexArray _vertexArray;

            void internalSetRange(sf::Vector2u start, sf::Vector2u end);
        };
    } // Raytracer

#endif //EPITECH_RAYTRACER_SERVER_HPP
