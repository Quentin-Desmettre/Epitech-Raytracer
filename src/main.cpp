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

void addSolarSystem(Renderer &r, Scene &scene)
{
    scene.clear();

    Sphere *Sun = new Sphere(sf::Vector3f(-120, 0, 0), sf::Color(255, 64, 64), 100, sf::Color(255, 255, 255), 5.0f);
    scene.addObject(Sun);

    Sphere *Mercure = new Sphere(sf::Vector3f(-4.95, 0, 0), sf::Color(140, 92, 42), 0.2);
    scene.addObject(Mercure);

    Sphere *Venus = new Sphere(sf::Vector3f(-0.95, 0, 0), sf::Color(201, 115, 30), 1);
    scene.addObject(Venus);

    Sphere *Earth = new Sphere(sf::Vector3f(2.25, 0, 0), sf::Color(83, 206, 203), 0.5);
    scene.addObject(Earth);

    Sphere *Mars = new Sphere(sf::Vector3f(8.45, 0, 0), sf::Color(197, 55, 3), 0.25);
    scene.addObject(Mars);

    Sphere *Jupiter = new Sphere(sf::Vector3f(10.55, 0, 0), sf::Color(232, 166, 88), 5);
    scene.addObject(Jupiter);

    Sphere *Saturn = new Sphere(sf::Vector3f(25.55, 0, 0), sf::Color(240, 196, 126), 4.7);
    scene.addObject(Saturn);

    Sphere *Uranus = new Sphere(sf::Vector3f(36.55, 0, 0), sf::Color(144, 219, 221), 2.05);
    scene.addObject(Uranus);

    Sphere *Neptune = new Sphere(sf::Vector3f(45.55, 0, 0), sf::Color(100, 182, 233), 1.95);
    scene.addObject(Neptune);

    r.setCamera(sf::Vector3f(13, -15, -80), sf::Vector3f(0, 0.25, 0));
}

void addObjects(Renderer &r, Scene &scene)
{
    Sphere *sphere1 = new Sphere(sf::Vector3f(-1.5, -0.5, 10), sf::Color(64, 255, 64), 1);
    scene.addObject(sphere1);

    Sphere *sphere2 = new Sphere(sf::Vector3f(-0.5, -2, 10), sf::Color(64, 64, 255), 0.3);
    scene.addObject(sphere2);

    Sphere *sphere3 = new Sphere(sf::Vector3f(1, 0, 10), sf::Color(255, 64, 64), 0.5, sf::Color(255, 255, 255), 5.0f);
    scene.addObject(sphere3);

    Plane *plane = new Plane(sf::Vector3f(-10, 0.5, 0), sf::Vector3f(10, 0.5, 20), sf::Color(64, 64, 255));
    plane->setReflectivity(0.8);
    scene.addObject(plane);

    r.setCamera(sf::Vector3f(-1, -2, 0), sf::Vector3f(0, 0.25, 0.5));
}

int main(void)
{
    Renderer r;
    Scene scene;

    srand(time(NULL));
    addObjects(r, scene);
    // addSolarSystem(r, scene);
    // r.smoothImage(false);
    r.run(&scene);
    return 0;
}
