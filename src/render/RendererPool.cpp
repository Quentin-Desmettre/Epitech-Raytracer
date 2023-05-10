/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** RendererPool
*/

#include "render/RendererPool.hpp"
#include <thread>
#include "Print.hpp"

Raytracer::RendererPool::RendererPool(sf::Vector2u start, sf::Vector2u end, bool updateRangeOnRender)
{
    _start = start;
    _end = end;
    _updateRangeOnRender = updateRangeOnRender;
}

void Raytracer::RendererPool::addRenderer(std::unique_ptr<IRenderer> &&renderer)
{
    IRenderer *ptr = renderer.release();
    _renderers.emplace_back(ptr);
}

void Raytracer::RendererPool::setRange(sf::Vector2u start, sf::Vector2u end)
{
    internalSetRange(start, end);
}

void Raytracer::RendererPool::setRange()
{
    internalSetRange(_start, _end);
}

void Raytracer::RendererPool::internalSetRange(sf::Vector2u start, sf::Vector2u end)
{
    _start = start;
    _end = end;
    auto ranges = splitRange(start, end, _renderers);
    for (auto &renderer : _renderers) {
        renderer->setRange(ranges[renderer.get()].first,
                           ranges[renderer.get()].second);
    }
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

void Raytracer::RendererPool::render(const Scene &scene, PointArray &array, sf::Time *timeTaken)
{
    // Launch renderers
    // They will automatically fill the PointArray with their results
    sf::Clock clock;
    std::vector<std::thread> threads;
    std::vector<sf::Time> times;

    threads.reserve(_renderers.size());
    times.resize(_renderers.size());
    for (std::size_t i = 0; i < _renderers.size(); ++i)
        threads.emplace_back(&IRenderer::render, _renderers[i].get(), std::ref(scene), std::ref(array), &times[i]);

    // Wait for renderers to finish
    for (auto &thread : threads)
        thread.join();

    // Compute total time
    *timeTaken = clock.getElapsedTime();
    Raytracer::cout << "Time taken: " << timeTaken->asSeconds() << std::endl;

    return;
    if (!_updateRangeOnRender)
        return;

    for (size_t i = 0; i < _renderers.size(); i++)
        Raytracer::cout << "Time taken by renderer " << i << ": " << times[i].asSeconds() << std::endl;

    // Split range, according to time taken by each renderer, using the formula:
    /*
     * WidthToUse = W/T * Wa / (Sum(Wk/Tk), k=1..n)
     *
     * Where:
     *  W: Width currently used
     *  T: Time taken to render W
     *  Wa: Total width
     *  Wk: Width used by renderer k
     *  Tk: Time taken by renderer k
     *  n: Number of renderers
     *
     *  Because:
     *      Sum(Wk/Tk) computes the total power of all renderers
     *      Then, Wa/Sum(Wk/Tk) computes the average time needed to render the scene
     *      Finally, W/T * Wa/Sum(Wk/Tk) computes the width to use for each renderer
     */

    sf::Clock cl;
    // Compute total work power, in terms of pixels per second
    float totalPower = 0;
    for (std::size_t i = 0; i < _renderers.size(); i++) {
        auto [start, end] = _renderers[i]->getRange();
        totalPower += (end.x - start.x) / times[i].asSeconds();
    }

    // Compute average time per pixel
    float averageTime = (_end.x - _start.x) / totalPower;

    // Compute and set range for each renderer
    sf::Vector2u start = _start;
    sf::Vector2u end = {_start.x, _end.y};
    for (std::size_t i = 0; i < _renderers.size() - 1; i++) {
        auto [r_start, r_end] = _renderers[i]->getRange();
        const unsigned int width = r_end.x - r_start.x;
        end.x = start.x + width / times[i].asSeconds() * averageTime;
        _renderers[i]->setRange(start, end);
        Raytracer::cout << "Range of " << i << ": " << start.x << ";" << start.y << " -> " << end.x << ";" << end.y << std::endl;
        start.x = end.x;
    }
    Raytracer::cout << "Range of " << _renderers.size() - 1 << ": " << start.x << ";" << start.y << " -> " << _end.x << ";" << _end.y << std::endl;
    _renderers.back()->setRange(start, _end);
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

std::pair<sf::Vector2u, sf::Vector2u> Raytracer::RendererPool::getRange() const
{
    return std::make_pair(_start, _end);
}

void Raytracer::RendererPool::reset()
{
    for (auto &renderer : _renderers)
        reset(renderer);
}

void Raytracer::RendererPool::reset(const std::unique_ptr<IRenderer> &renderer)
{
    renderer->reset();
    for (auto &child : renderer->getSubRenderers())
        reset(child);
}

const std::vector<std::unique_ptr<Raytracer::IRenderer>> &Raytracer::RendererPool::getSubRenderers()
{
    return _renderers;
}
