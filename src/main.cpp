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

void addSolarSystem(Scene &scene, Camera &camera)
{
    scene.clear();

    Sphere *Sun = new Sphere(Vec3(-120, 0, 0), sf::Color(255, 64, 64), 100, sf::Color(255, 255, 255), 5.0f);
    scene.addObject(Sun);

    Sphere *Mercure = new Sphere(Vec3(-4.95, 0, 0), sf::Color(140, 92, 42), 0.2);
    scene.addObject(Mercure);

    Sphere *Venus = new Sphere(Vec3(-0.95, 0, 0), sf::Color(201, 115, 30), 1);
    scene.addObject(Venus);

    Sphere *Earth = new Sphere(Vec3(2.25, 0, 0), sf::Color(83, 206, 203), 0.5);
    scene.addObject(Earth);

    Sphere *Mars = new Sphere(Vec3(8.45, 0, 0), sf::Color(197, 55, 3), 0.25);
    scene.addObject(Mars);

    Sphere *Jupiter = new Sphere(Vec3(10.55, 0, 0), sf::Color(232, 166, 88), 5);
    scene.addObject(Jupiter);

    Sphere *Saturn = new Sphere(Vec3(25.55, 0, 0), sf::Color(240, 196, 126), 4.7);
    scene.addObject(Saturn);

    Sphere *Uranus = new Sphere(Vec3(36.55, 0, 0), sf::Color(144, 219, 221), 2.05);
    scene.addObject(Uranus);

    Sphere *Neptune = new Sphere(Vec3(45.55, 0, 0), sf::Color(100, 182, 233), 1.95);
    scene.addObject(Neptune);


    camera.setPos(Vec3(13, -15, -80));
    camera.setRot(Vec3(0, 0.25, 0));
}

void addObjects(Scene &scene, Camera &camera)
{
    Sphere *sphere1 = new Sphere(Vec3(-1, -0.5, 10), sf::Color(64, 255, 64), 1);
    scene.addObject(sphere1);

    Sphere *sphere2 = new Sphere(Vec3(0, -2, 10), sf::Color(64, 64, 255), 0.3);
    scene.addObject(sphere2);

    Sphere *sphere3 = new Sphere(Vec3(1, 0, 10), sf::Color(255, 64, 64), 0.5, sf::Color(255, 255, 255), 5.0f);
    scene.addObject(sphere3);

    // LightPoint *light1 = new LightPoint(Vec3(1, 0, 10), sf::Color(255, 255, 255), 5.0f);
    // scene.addLightPoint(*light1);

    Plane *plane = new Plane(Vec3(-10, 0.5, 0), Vec3(10, 0.5, 20), sf::Color(64, 64, 255));
    plane->setReflectivity(1);
    scene.addObject(plane);

    camera.setPos(Vec3(0, -1, 6));
    camera.setRot(Vec3(0, 0, 0));
}

int main(void)
{
    Renderer r;
    Scene scene;
    Camera camera;

    srand(time(NULL));
    addObjects(scene, camera);
    // addSolarSystem(scene, camera);
    // r.smoothImage(false);
    r.useThreads(true);
    r.run(&scene, camera);
    return 0;
}
