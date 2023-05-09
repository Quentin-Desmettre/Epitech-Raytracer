/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Tanglecube
*/

#include "objects/Tanglecube.hpp"

bool Tanglecube::intersect(const Ray &ray, Vec3 &intersection) const
{
    // Put ray in local space
    Ray r = transformRay(ray);
    Vec3 rDir = r.getDir();
    Vec3 rOri = r.getOrigin();

    // Compute coefficients
    // Trust me for the equations bro
    float coeffs[5] = {
            POW4(rDir.x) + POW4(rDir.y) + POW4(rDir.z),
            4 * (POW3(rDir.x) * rOri.x + POW3(rDir.y) * rOri.y + POW3(rDir.z) * rOri.z),
            6 * (POW2(rDir.x) * POW2(rOri.x) + POW2(rDir.y) * POW2(rOri.y) + POW2(rDir.z) * POW2(rOri.z)) - 5 * (POW2(rDir.x) + POW2(rDir.y) + POW2(rDir.z)),
            4 * (POW3(rOri.x) * rDir.x + POW3(rOri.y) * rDir.y + POW3(rOri.z) * rDir.z) - 10 * (rOri.x * rDir.x + rOri.y * rDir.y + rOri.z * rDir.z),
            POW4(rOri.x) + POW4(rOri.y) + POW4(rOri.z) - 5 * (POW2(rOri.x) + POW2(rOri.y) + POW2(rOri.z)) + 11.8f
    };

    // Solve quartic equation
    auto sols = Math::solveQuartic(coeffs);
    if (sols.empty())
        return false;

    // Find the smallest positive solution
    float minT = std::numeric_limits<float>::max();
    for (auto t : sols) {
        if (t >= 0 && t < minT)
            minT = t;
    }
    if (minT == std::numeric_limits<float>::max())
        return false;

    // Compute intersection
    intersection = rOri + rDir * minT;
    intersection = transformPosInverse(intersection); // Put in world space
    return true;
}

Vec3 Tanglecube::getNormal(const Vec3 &inter, unused const Ray &ray) const
{
    // Put intersection in local coordinates
    Vec3 interLocal = transformPos(inter);

    return Math::normalize(transformDirInverse({
        4 * POW3(interLocal.x) - 2 * interLocal.x,
        4 * POW3(interLocal.y) - 2 * interLocal.y,
        4 * POW3(interLocal.z) - 2 * interLocal.z
    }));
}
