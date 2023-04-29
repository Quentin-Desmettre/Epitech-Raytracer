/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Ray
*/

#include "render/Ray.hpp"

void Ray::reflect(Vec3 normal, const IObject *obj)
{
    // Get the material properties of the object
    bool reflectivity = obj->getReflectivity();
    bool transparency = obj->getTransparency();
    float refractiveIndex = obj->getRefractiveIndex();
    float roughness = obj->getRoughness();

    // Calculate the refractive index of the medium the ray is currently in
    float currentRefractiveIndex = 1.0f;
    if (Math::dot(_dir, normal) > 0.0f) {
        currentRefractiveIndex = refractiveIndex;
        normal = -normal;
    }

    // Calculate the reflected direction of the ray
    Vec3 reflectionDirection = _dir - 2.0f * Math::dot(_dir, normal) * normal;

    // Calculate the refracted direction of the ray (if applicable)
    Vec3 refractionDirection = Vec3(0.0f, 0.0f, 0.0f);
    if (transparency) {
        float cosI = -Math::dot(normal, _dir);
        float sinT2 = currentRefractiveIndex * currentRefractiveIndex * (1.0f - cosI * cosI) / (refractiveIndex * refractiveIndex);
        if (sinT2 <= 1.0f) {
            float cosT = sqrtf(1.0f - sinT2);
            refractionDirection = (currentRefractiveIndex / refractiveIndex) * _dir + ((currentRefractiveIndex / refractiveIndex) * cosI - cosT) * normal;
            float reflectionAmount = 0.5f * (1.0f + fabsf(Math::dot(_dir, normal))) * 0.0f;
            _dir = Math::normalize(reflectionAmount * reflectionDirection + (1.0f - reflectionAmount) * refractionDirection);
            return;
        }
    }

    // Calculate the final direction of the ray based on the material properties
    Vec3 tmp = Math::randomDir();
    if (reflectivity) {
        // Use a perturbed reflection direction for rough surfaces
        Vec3 perturbedReflectionDirection = Math::normalize(reflectionDirection + roughness * tmp);
        _dir = perturbedReflectionDirection;
    } else {
        _dir = tmp * Math::sign(Math::dot(normal, tmp));
    }
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

// void Ray::reflect(Vec3 normal, float reflectivity, float transparency, float refraction)
// {
//     float cosi = Math::dot(_dir, normal);
//     float etai = 1.0f; // refractive index of air
//     float etat = refraction;
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
