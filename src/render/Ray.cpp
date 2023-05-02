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

    if (obj->getTransparency()) {
        float cosI = -hitAngle;
        float sinT2 = airRefractiveIndex * airRefractiveIndex * (1.0f - cosI * cosI) / (refractiveIndex * refractiveIndex);
        if (sinT2 <= 1.0f) {
            float cosT = sqrtf(1.0f - sinT2);
            Vec3 refractionDirection = (airRefractiveIndex / refractiveIndex) * _dir + ((airRefractiveIndex / refractiveIndex) * cosI - cosT) * normal;
            _dir = Math::normalize(refractionDirection + roughness * randDir);;
        }
    } else if (obj->getReflectivity()) {
        Vec3 reflectionDirection = _dir - 2.0f * hitAngle * normal;
        _dir = Math::normalize(reflectionDirection + roughness * randDir);
    } else
        _dir = randDir * Math::sign(Math::dot(normal, randDir));
}

// void Ray::reflect(Vec3 normal, const IObject *obj)
// {
//     // bool telling wether the object is transparent or not
//     bool isTransparent = obj->getTransparency();
//     // bool telling wether the object is reflective or not
//     bool isReflective = obj->getReflectivity();
//     // float representing the roughness of the object
//     float roughness = obj->getRoughness();
//     // float representing the refraction index of the object
//     float refraction = obj->getRefractiveIndex();
//     Vec3 tmp = Math::randomDir();

//     if (Math::dot(tmp, normal) < 0)
//         tmp = -tmp;
//     Vec3 specular = _dir - 2.0f * Math::dot(_dir, normal) * normal;
//     Vec3 diffuse = tmp * Math::sign(Math::dot(normal, tmp));
//     if (isReflective)
//         _dir = specular * (1.0f - roughness) + diffuse * roughness;
//     else
//         _dir = diffuse;
// }

// void Ray::reflect(Vec3 normal, const IObject *obj)
// {
//     float reflectivity = obj->getReflectivity();
//     float transparency = obj->getTransparency();
//     float cosi = Math::dot(_dir, normal);
//     float etai = 1.0f; // refractive index of air
//     float etat = obj->getRefractiveIndex();
//     if (cosi > 0) {
//         std::swap(etai, etat);
//         normal = -normal;
//     }

//     float sint = etai / etat * std::sqrt(std::max(0.0f, 1.0f - cosi * cosi));
//     float kr = Math::fresnel(cosi, etai, etat);
//     float kt = 1.0f - kr;

//     Vec3 specular = _dir - 2.0f * Math::dot(_dir, normal) * normal;
//     Vec3 diffuse = Math::randomDir();

//     if (sint >= 1.0f) { // total internal reflection
//         _dir = specular * reflectivity + diffuse * (1.0f - reflectivity);
//     } else {
//         Vec3 refracted = etai / etat * (_dir - normal * cosi) - normal * sint;
//         _dir = specular * kr * reflectivity + refracted * kt * transparency + diffuse * (1.0f - reflectivity - transparency);
//     }
// }
