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
    Vec3 randDir = Math::randomDir();

    if (hitAngle > 0.0f) {
        airRefractiveIndex = refractiveIndex;
        normal = -normal;
        hitAngle = -hitAngle;
    }

    if (obj->isTransparent()) {
        float cosI = -hitAngle;
        float sinT2 = airRefractiveIndex * airRefractiveIndex * (1.0f - cosI * cosI) / (refractiveIndex * refractiveIndex);
        if (sinT2 <= 1.0f) {
            float cosT = sqrtf(1.0f - sinT2);
            Vec3 refractionDirection = (airRefractiveIndex / refractiveIndex) * _dir + ((airRefractiveIndex / refractiveIndex) * cosI - cosT) * normal;
            _dir = Math::normalize(refractionDirection + roughness * randDir);;
        }
    } else if (obj->isReflective()) {
        Vec3 reflectionDirection = _dir - 2.0f * hitAngle * normal;
        _dir = Math::normalize(Math::lerp(reflectionDirection, randDir, roughness));
    } else
        _dir = randDir * Math::sign(Math::dot(normal, randDir));
}
