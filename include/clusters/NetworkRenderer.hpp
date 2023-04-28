/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Server
*/

#ifndef EPITECH_RAYTRACER_NETWORKRENDERER_HPP
#define EPITECH_RAYTRACER_NETWORKRENDERER_HPP
#include "render/IRenderer.hpp"
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

    class NetworkRenderer: public IRenderer {
    public:
        explicit NetworkRenderer(const std::string &ipPort);

        /**
         * @brief Sends the RENDER request to the cluster, and wait until a response is received
         * @param scene
         */
        void render(const Scene &scene, PointArray &array, sf::Time *time) override;

        /**
         * @brief Sends the request to update the range of the renderer.
         * @see IRenderer::setRange()
         */
        void setRange(sf::Vector2u start, sf::Vector2u end) override;

        /**
         * @brief Get the range of the renderer.
         * @see IRenderer::getRange()
         */
        std::pair<sf::Vector2u, sf::Vector2u> getRange() const override;

        /**
         * @brief Get the number of threads of the cluster.
         * @see IRenderer::getThreadsCount()
         */
        int getThreadsCount() const override;

    private:
        int _nbThreads;
        Network::TcpSocket _socket;
        PointArray *_array;
        const Scene *_scene = nullptr;
        sf::Vector2u _start, _end;
        sf::Clock _clock;
    };
} // Raytracer

#endif //EPITECH_RAYTRACER_NETWORKRENDERER_HPP
