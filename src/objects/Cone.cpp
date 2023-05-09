/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Cone
*/

#include "objects/Cone.hpp"
#include "transformations/TransformationFactory.hpp"

Cone::Cone(Vec3 pos, Vec3 dir, float height, float slope,
sf::Color color, sf::Color emmsionColor, float intensity) :
AObject(pos, color, emmsionColor, intensity)
{
    _dir = dir;
    _height = height;
    _slope = slope;
}

bool Cone::intersect(const Ray &ray, Vec3 &intersection) const
{
    const Ray r = transformRay(ray);
    const Vec3  pos = r.getOrigin(),
                dir = r.getDir();
    float coeffs[3] = {
            POW2(dir.x) - _slope * POW2(dir.y) + POW2(dir.z),
            2 * pos.x * dir.x - 2 * _slope * pos.y * dir.y + 2 * pos.z * dir.z,
            POW2(pos.x) - _slope * POW2(pos.y) + POW2(pos.z)
    };
    auto sols = Math::solveQuadratic(coeffs);
    if (sols.size() == 1) sols.push_back(sols[0]);
    if (sols.empty() || (sols[0] < 0 && sols[1] < 0))
        return false;
    float t1 = sols[0], t2 = sols[1];
    if (_height < INF) {
        Vec3 inter1 = pos + dir * t1;
        Vec3 inter2 = pos + dir * t2;
        if ((inter1.y <= 0 || inter1.y > _height) && (inter2.y <= 0 || inter2.y > _height))
            return false;
        if (inter1.y <= 0 || inter1.y > _height) {
            intersection = inter2;
        } else if (inter2.y <= 0 || inter2.y > _height) {
            intersection = inter1;
        } else // If both are in the cone
            intersection = pos + dir * (t1 < t2 ? t1 : t2);
    } else
        intersection = pos + dir * (t1 < 0 ? t1 : t2);
    intersection = transformPosInverse(intersection);
    return true;
}

Vec3 Cone::getNormal(const Vec3 &inter, unused const Ray &ray) const
{
    // Equation of a cone is x^2 + y^2 = z^2 * slope
    // Or x^2 + y^2 - z^2 * slope = 0
    // So the normal at any point (x,y,z) is given by (2x, 2y, -2z * slope)
    Vec3 localInter = transformPos(inter);
    return Math::normalize(transformDirInverse({
            2 * localInter.x,
            2 * localInter.y,
            -2 * localInter.z * _slope
    }));
}

void Cone::setHeight(const float &height)
{
    _height = height;
}

void Cone::setSlope(const float &slope)
{
    if (_slope <= 0)
        throw InvalidParameterValueException("slope");
    _slope = slope;
}
