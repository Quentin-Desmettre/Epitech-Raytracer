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
    pool.addObject(new Sphere(sf::Vector3f(1.5, -1, 15), sf::Color(255, 64, 64)));
    pool.addObject(new Sphere(sf::Vector3f(-1.5, 0, 10), sf::Color(64, 255, 64)));
    pool.addObject(new Sphere(sf::Vector3f(-1, 18, 20), sf::Color(255, 64, 255), 20));
    pool.addObject(new Sphere(sf::Vector3f(10, -2, 6), sf::Color(255, 64, 64), 5, sf::Color::White, 5.0f));
    r.setCamera(sf::Vector3f(0, 0, 0), sf::Vector3f(0, 0, 0.5));
    r.run(pool);
    return 0;
}
