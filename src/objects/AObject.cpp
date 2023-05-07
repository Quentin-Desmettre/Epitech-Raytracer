/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** AObject
*/

#include "objects/Object.hpp"
#include "Exceptions.hpp"
#include "Raytracer.hpp"

AObject::AObject(Vec3 pos,
                 sf::Color color,
                 sf::Color emmsionColor,
                 float intensity,
                 bool reflective,
                 bool transparent,
                 float roughness
)
{
    AObject::setPos(pos);
    AObject::setColor(color);
    AObject::setEmissionColor(emmsionColor);
    AObject::setEmissionIntensity(intensity);
    AObject::setReflectivity(reflective);
    AObject::setTransparency(transparent);
    AObject::setRoughness(roughness);
    AObject::setRefractiveIndex(1.0f);
}

Vec3 AObject::getPos() const
{
    return _pos;
}

Vec3 AObject::getColor() const
{
    return _color;
}

Vec3 AObject::getEmissionColor() const
{
    return _light.getColor();
}

float AObject::getEmissionIntensity() const
{
    return _light.getIntensity();
}

bool AObject::isReflective() const
{
    return _reflectivity;
}

bool AObject::isTransparent() const
{
    return _transparency;
}

float AObject::getRoughness() const
{
    return _roughness;
}

float AObject::getRefractiveIndex() const
{
    return _refractiveIndex;
}

const ObjectLight &AObject::getLight() const
{
    return _light;
}

void AObject::setPos(Vec3 pos)
{
    _pos = pos;
}

void AObject::setReflectivity(const bool &reflectivity)
{
    _reflectivity = reflectivity;
}

void AObject::setTransparency(const bool &transparency)
{
    _transparency = transparency;
}

void AObject::setRoughness(const float &roughness)
{
    if (roughness < 0.0f || roughness > 1.0f)
        throw InvalidParameterValueException("Roughness must be between 0.0 and 1.0");
    _roughness = roughness;
}

void AObject::setRefractiveIndex(const float &refractiveIndex)
{
    _refractiveIndex = refractiveIndex;
}

void AObject::setColor(const sf::Color &color)
{
    _color = Vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}

void AObject::setPosition(const sf::Vector3f &pos)
{
    _pos = Vec3(pos.x, pos.y, pos.z);
}

void AObject::setEmissionColor(const sf::Color &color)
{
    if (color != sf::Color::Transparent)
        _light.setColor(color);
}

void AObject::setEmissionIntensity(const float &intensity)
{
    if (intensity < 0.0f)
        throw InvalidParameterValueException("Emission intensity must be >= 0");
    _light.setIntensity(intensity);
}

void AObject::addTransformations(const std::vector<std::shared_ptr<ITransformation>> &transformations)
{
    _transformations.insert(_transformations.end(), transformations.begin(), transformations.end());
}

bool AObject::operator==(const AObject &obj) const
{
    return _pos == obj._pos && _color == obj._color && _light.getColor() == obj._light.getColor() &&
        _light.getIntensity() == obj._light.getIntensity() && _reflectivity == obj._reflectivity &&
        _transparency == obj._transparency;
}

bool AObject::operator!=(const AObject &obj) const
{
    return !(*this == obj);
}

void AObject::computeTransformations()
{
    Mat4 inverse = Mat4::translate3D(_pos);

    for (auto &trans: _transformations) {
        for (auto &mat: trans->getMatrices())
            inverse *= mat;
    }
    _transformationsMatrix = inverse;
    _inverseTransformations = inverse.inverse();
}

Ray AObject::transformRay(const Ray &ray) const
{
    // Manually compute the new direction
    Vec3 newDir;
    newDir.x = _inverseTransformations(0, 0) * ray.getDir().x + _inverseTransformations(0, 1) * ray.getDir().y + _inverseTransformations(0, 2) * ray.getDir().z;
    newDir.y = _inverseTransformations(1, 0) * ray.getDir().x + _inverseTransformations(1, 1) * ray.getDir().y + _inverseTransformations(1, 2) * ray.getDir().z;
    newDir.z = _inverseTransformations(2, 0) * ray.getDir().x + _inverseTransformations(2, 1) * ray.getDir().y + _inverseTransformations(2, 2) * ray.getDir().z;

    // Manually compute the new origin
    Vec3 newOrigin;
    newOrigin.x = _inverseTransformations(0, 0) * ray.getOrigin().x + _inverseTransformations(0, 1) * ray.getOrigin().y + _inverseTransformations(0, 2) * ray.getOrigin().z + _inverseTransformations(0, 3);
    newOrigin.y = _inverseTransformations(1, 0) * ray.getOrigin().x + _inverseTransformations(1, 1) * ray.getOrigin().y + _inverseTransformations(1, 2) * ray.getOrigin().z + _inverseTransformations(1, 3);
    newOrigin.z = _inverseTransformations(2, 0) * ray.getOrigin().x + _inverseTransformations(2, 1) * ray.getOrigin().y + _inverseTransformations(2, 2) * ray.getOrigin().z + _inverseTransformations(2, 3);

    return {
        newOrigin,
        newDir
    };
}
