/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Triangle
*/

#include "objects/Triangle.hpp"

Triangle::Triangle(sf::Vector3f point1, sf::Vector3f point2, sf::Vector3f point3,
sf::Color color, sf::Color emmsionColor, float intensity) :
Object(point1, color, emmsionColor, intensity)
{
    _points[0] = point1;
    _points[1] = point2;
    _points[2] = point3;
}

bool Triangle::intersect(Ray *ray)
{
    sf::Vector3f origin = ray->getOrigin();
    sf::Vector3f dir = ray->getDir();
    sf::Vector3f edge1 = _points[1] - _points[0];
    sf::Vector3f edge2 = _points[2] - _points[0];
    sf::Vector3f pvec = Math::cross(dir, edge2);
    float det = Math::dot(edge1, pvec);

    if (det < 0.0001f)
        return false;
    sf::Vector3f tvec = origin - _points[0];
    float u = Math::dot(tvec, pvec);
    if (u < 0.0f || u > det)
        return false;
    sf::Vector3f qvec = Math::cross(tvec, edge1);
    float v = Math::dot(dir, qvec);
    if (v < 0.0f || u + v > det)
        return false;
    float t = Math::dot(edge2, qvec) / det;
    if (t < 0.0f)
        return false;
    _lastRay = ray;
    return true;
}

sf::Vector3f Triangle::getIntersection(Ray *ray)
{
    if (ray != _lastRay)
        intersect(ray);
    return ray->getOrigin() + ray->getDir() * 0.1f;
}

sf::Vector3f Triangle::getNormal(sf::Vector3f inter)
{
    sf::Vector3f edge1 = _points[1] - _points[0];
    sf::Vector3f edge2 = _points[2] - _points[0];
    return Math::normalize(Math::cross(edge1, edge2));
}
