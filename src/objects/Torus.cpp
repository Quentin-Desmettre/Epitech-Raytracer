/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Torus
*/

#include "objects/Torus.hpp"
#include "Exceptions.hpp"

void Torus::setRadius(const float &radius)
{
    if (radius <= 0)
        throw InvalidParameterValueException("radius must be positive");
    _radius = radius;
}

void Torus::setThickness(const float &thickness)
{
    if (thickness <= 0)
        throw InvalidParameterValueException("thickness must be positive");
    _thickness = thickness;
}

bool Torus::intersect(unused const Ray &ray, unused Vec3 &intersection) const
{
    Ray r = transformRay(ray);
    float
        x = r.getOrigin().x,
        y = r.getOrigin().y,
        z = r.getOrigin().z,
        dx = r.getDir().x,
        dy = r.getDir().y,
        dz = r.getDir().z;
    float sum_d_sqrd = dx * dx + dy * dy + dz * dz;
    float e = x * x + y * y + z * z - _radius * _radius - _thickness * _thickness;
    float f = x * dx + y * dy + z * dz;
    float four_a_sqrd = 4.0f * _radius * _radius;

    float coeffs[5] = {
            sum_d_sqrd * sum_d_sqrd,
            4.0f * sum_d_sqrd * f,
            2.0f * sum_d_sqrd * e + 4.0f * f * f + four_a_sqrd * dy * dy,
            4.0f * f * e + 2.0f * four_a_sqrd * y * dy,
            e * e - four_a_sqrd * (_thickness * _thickness - y * y)
    };

    auto solutions = Math::solveQuartic(coeffs);
    if (solutions.empty())
        return false;
    float t = INFINITY;
    bool found = false;
    for (auto solution : solutions) {
        if (solution > 0 && solution < t) {
            t = solution;
            found = true;
        }
    }
    if (!found)
        return false;
    intersection = _transformationsMatrix * (r.getOrigin() + r.getDir() * t);
    return true;
}

Vec3 Torus::getNormal(const Vec3 &inter, unused const Ray &ray) const
{
    // Put intersection in local space
    Vec3 intersection = _inverseTransformations * inter;
    float param_squared = _radius * _radius + _thickness * _thickness;

    float
        x = intersection.x,
        y = intersection.y,
        z = intersection.z;
    float sum_squared = x * x + y * y + z * z;

    return Math::normalize({
           4.0f * x * (sum_squared - param_squared),
           4.0f * y * (sum_squared - param_squared + 2.0f * _radius * _radius),
           4.0f * z * (sum_squared - param_squared)
   });
}
