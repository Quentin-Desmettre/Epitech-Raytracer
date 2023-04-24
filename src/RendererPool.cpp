/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** RendererPool
*/

#include "RendererPool.hpp"
#include <thread>

Raytracer::RendererPool::RendererPool(sf::Vector2u start, sf::Vector2u end)
{
    _vertexArray.setPrimitiveType(sf::Points);

    internalSetRange(start, end);
}

void Raytracer::RendererPool::addRenderer(std::unique_ptr<IRenderer> &&renderer)
{
    IRenderer *ptr = renderer.release();
    _renderers.emplace_back(ptr);
    setRange(_start, _end);
}

void Raytracer::RendererPool::setRange(sf::Vector2u start, sf::Vector2u end)
{
    internalSetRange(start, end);
}

void Raytracer::RendererPool::internalSetRange(sf::Vector2u start, sf::Vector2u end)
{
    _start = start;
    _end = end;
    auto ranges = splitRange(start, end, _renderers);
    for (auto &renderer : _renderers)
        renderer->setRange(ranges[renderer.get()].first, ranges[renderer.get()].second);
}

std::vector<std::pair<sf::Vector2u, sf::Vector2u>> Raytracer::RendererPool::splitRange(sf::Vector2u start, sf::Vector2u end, std::size_t count)
{
    std::vector<std::pair<sf::Vector2u, sf::Vector2u>> ranges;
    ranges.reserve(count);

    unsigned width = (end.x - start.x) / count;
    unsigned xStart = start.x;
    unsigned xEnd = start.x + width;
    for (unsigned i = 0; i < count - 1; ++i) {
        ranges.emplace_back(sf::Vector2u(xStart, start.y), sf::Vector2u(xStart + width, end.y));
        xStart += width;
        xEnd += width;
    }
    ranges.emplace_back(sf::Vector2u(xStart, start.y), sf::Vector2u(end.x, end.y));
    return ranges;
}

Raytracer::RendererPool::RendererRangeMap Raytracer::RendererPool::splitRange(sf::Vector2u start, sf::Vector2u end, const UniqueRendererVector &renderers)
{
    RendererRangeMap ranges;

    if (renderers.empty())
        return ranges;
    unsigned widthPerThread = (end.x - start.x) / getThreadsCount(renderers);
    unsigned xStart = start.x;
    unsigned xEnd = start.x + widthPerThread;

    for (unsigned i = 0; i < renderers.size() - 1; ++i) {
        int nbThreads = renderers[i]->getThreadsCount();

        ranges[renderers[i].get()] = std::make_pair(sf::Vector2u(xStart, start.y), sf::Vector2u(xStart + widthPerThread * nbThreads, end.y));
        xStart += widthPerThread * nbThreads;
        xEnd += widthPerThread * nbThreads;
    }
    ranges[renderers.back().get()] = std::make_pair(sf::Vector2u(xStart, start.y), sf::Vector2u(end.x, end.y));
    return ranges;
}

void Raytracer::RendererPool::render(const Scene &scene)
{
    // Launch renderers
    std::cout << "Rendering..." << std::endl;
    std::vector<std::thread> threads;
    threads.reserve(_renderers.size());
    for (auto &renderer: _renderers)
        threads.emplace_back(&IRenderer::render, renderer.get(), std::ref(scene));

    std::cout << "Rendering done" << std::endl;
    // Wait for renderers to finish
    for (auto &thread: threads)
        thread.join();

    std::cout << "Merging renderers..." << std::endl;
    // Merge renderers
    _vertexArray.clear();
    for (auto &renderer: _renderers) {
        auto vertexArray = renderer->getVertexArray();
        for (unsigned i = 0; i < vertexArray.getVertexCount(); ++i) {
            _vertexArray.append(vertexArray[i]);
        }
    }
}

sf::VertexArray Raytracer::RendererPool::getVertexArray() const
{
    return _vertexArray;
}

int Raytracer::RendererPool::getThreadsCount(const UniqueRendererVector &renderers)
{
    int count = 0;

    for (auto &renderer: renderers)
        count += renderer->getThreadsCount();
    return count;
}

int Raytracer::RendererPool::getThreadsCount() const
{
    return getThreadsCount(_renderers);
}
