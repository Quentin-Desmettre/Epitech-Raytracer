/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Triangle
*/

#include "objects/Triangle.hpp"

Triangle::Triangle(Vec3 point1, Vec3 point2, Vec3 point3,
sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(point1, color, emmsionColor, intensity)
{
    _points[0] = point1;
    _points[1] = point2;
    _points[2] = point3;
}

bool Triangle::intersect(const Ray &ray, Vec3 &intersection) const
{
    Vec3 origin = ray.getOrigin();
    Vec3 dir = ray.getDir();
    Vec3 edge1 = _points[1] - _points[0];
    Vec3 edge2 = _points[2] - _points[0];
    Vec3 pvec = Math::cross(dir, edge2);
    float det = Math::dot(edge1, pvec);

    if (det < 0.0001f)
        return false;
    Vec3 tvec = origin - _points[0];
    float u = Math::dot(tvec, pvec);
    if (u < 0.0f || u > det)
        return false;
    Vec3 qvec = Math::cross(tvec, edge1);
    float v = Math::dot(dir, qvec);
    if (v < 0.0f || u + v > det)
        return false;
    float t = Math::dot(edge2, qvec) / det;
    if (t < 0.0f)
        return false;
    intersection = origin + dir * t;
    return true;
}

Vec3 Triangle::getNormal(unused const Vec3 &inter, unused const Ray &ray) const
{
    Vec3 edge1 = _points[1] - _points[0];
    Vec3 edge2 = _points[2] - _points[0];
    return Math::normalize(Math::cross(edge1, edge2));
}
