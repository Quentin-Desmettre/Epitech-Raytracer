/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** AObject
*/

#include "objects/Object.hpp"

AObject::AObject(Vec3 pos, sf::Color color, sf::Color emmsionColor, float intensity)
{
    _pos = pos;
    _reflectivity = false;
    _transparency = false;
    _refractiveIndex = 1.0f;
    _roughness = 1.0f;
    _light.setIntensity(intensity);
    AObject::setColor(color);
    AObject::setEmissionColor(emmsionColor);
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
    _light.setIntensity(intensity);
}

void AObject::setTransformations(const std::vector<std::shared_ptr<ITransformation>> &transformations)
{
    _transformations = transformations;
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
