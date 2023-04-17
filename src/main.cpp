/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include <stdio.h>
#include "Renderer.hpp"
#include "ObjectPool.hpp"

int main(void)
{
    Renderer r;
    ObjectPool pool;

    srand(time(NULL));
    pool.addObject(new Sphere(sf::Vector3f(0.5, 0, 10), sf::Color(255, 64, 64)));
    pool.addObject(new Sphere(sf::Vector3f(-0.8, 0, 10), sf::Color(64, 255, 64), 0.3));
    pool.addObject(new Sphere(sf::Vector3f(-1, 18, 20), sf::Color(255, 64, 255), 20));
    pool.addObject(new Sphere(sf::Vector3f(2.5, 0, 10), sf::Color(255, 64, 64), 0.5, sf::Color::White, 25.0f));
    r.setCamera(sf::Vector3f(0, 0, 0), sf::Vector3f(0, 0, 0.5));
    r.run(pool);
    return 0;
}
