/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Ray
*/

#include "render/Ray.hpp"

void Ray::reflect(Vec3 normal, const IObject *obj)
{
    float refractiveIndex = obj->getRefractiveIndex();
    float roughness = obj->getRoughness();
    float hitAngle = Math::dot(_dir, normal);
    float airRefractiveIndex = 1.0f;
    Vec3 randDir = Math::randomDir(normal);

    if (hitAngle > 0.0f) {
        airRefractiveIndex = refractiveIndex;
        normal = -normal;
        hitAngle = -hitAngle;
    }

    if (obj->isTransparent()) {
        if (Math::randomf(0, 1) < Math::fresnel(hitAngle, airRefractiveIndex, refractiveIndex)) {
            Vec3 refractedDir = Math::refract(_dir, normal, airRefractiveIndex, refractiveIndex);
            _dir = Math::lerp(Math::normalize(refractedDir), randDir, roughness);
        } else {
            Vec3 reflectionDirection = _dir - 2.0f * hitAngle * normal;
            _dir = Math::lerp(reflectionDirection, randDir, roughness);
        }
    } else if (obj->isReflective()) {
        Vec3 reflectionDirection = _dir - 2.0f * hitAngle * normal;
        _dir = Math::lerp(reflectionDirection, randDir, roughness);
    } else
        _dir = randDir * Math::sign(Math::dot(normal, randDir));
    _dir = Math::normalize(_dir);
}
