/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include "Renderer.hpp"
#include "objects/Sphere.hpp"
#include "objects/Triangle.hpp"
#include "objects/Plane.hpp"

int main(void)
{
    Renderer r;
    Scene pool;

    srand(time(NULL));
    // pool.addObject(new Sphere(sf::Vector3f(0.5, 0, 10), sf::Color(255, 64, 64)));
    pool.addObject(new Sphere(sf::Vector3f(-1.5, -0.5, 10), sf::Color(64, 255, 64), 1));
    pool.addObject(new Sphere(sf::Vector3f(-0.5, -2, 10), sf::Color(64, 64, 255), 0.3));
    // pool.addObject(new Sphere(sf::Vector3f(-1, 18, 20), sf::Color(255, 64, 255), 20));
    pool.addObject(new Sphere(sf::Vector3f(0.75, -0.5, 10.5), sf::Color(255, 64, 64), 0.5, sf::Color::White, 15.0f));
    // pool.addObject(new Triangle(sf::Vector3f(-1, 0, 10), sf::Vector3f(-1, 1, 10), sf::Vector3f(0, 0, 10), sf::Color(64, 255, 64)));
    pool.addObject(new Plane(sf::Vector3f(-10, 0.5, 0), sf::Vector3f(10, 0.5, 20), sf::Color(64, 64, 255)));
    pool.addLightPoint(lightPoint(sf::Vector3f(-3.75, -0.5, 7), sf::Color::Yellow, 1.0f));
    r.setCamera(sf::Vector3f(-1, -2, 0), sf::Vector3f(0, 0.25, 0.5));
    r.run(&pool);
    return 0;
}
