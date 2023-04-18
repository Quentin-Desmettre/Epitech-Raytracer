/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include "Renderer.hpp"
#include "objects/Sphere.hpp"
#include "objects/Triangle.hpp"

int main(void)
{
    Renderer r;
    Scene pool;

    srand(time(NULL));
    // pool.addObject(new Sphere(sf::Vector3f(0.5, 0, 10), sf::Color(255, 64, 64)));
    pool.addObject(new Sphere(sf::Vector3f(-2, -0.1, 10), sf::Color(64, 255, 64), 0.5));
    pool.addObject(new Sphere(sf::Vector3f(-0.8, -2, 10), sf::Color(64, 64, 255), 0.3));
    // pool.addObject(new Sphere(sf::Vector3f(-1, 18, 20), sf::Color(255, 64, 255), 20));
    pool.addObject(new Sphere(sf::Vector3f(1, -0.5, 10.5), sf::Color(255, 64, 64), 0.5, sf::Color::Black, 5.0f));
    pool.addObject(new Triangle(sf::Vector3f(-1, 0, 10), sf::Vector3f(-1, 1, 10), sf::Vector3f(0, 0, 10), sf::Color(64, 255, 64)));
    r.setCamera(sf::Vector3f(0, 0, 0), sf::Vector3f(0, 0, 0.5));
    r.run(&pool);
    return 0;
}
