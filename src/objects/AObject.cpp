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
    _intensity = intensity;
    _reflectivity = false;
    _transparency = false;
    _refractiveIndex = 1.0f;
    _roughness = 0.0f;
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
    return _emmsionColor;
}

float AObject::getEmissionIntensity() const
{
    return _intensity;
}

bool AObject::getReflectivity() const
{
    return _reflectivity;
}

bool AObject::getTransparency() const
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

void AObject::setPos(Vec3 pos)
{
    _pos = pos;
}

void AObject::setReflectivity(bool reflectivity)
{
    _reflectivity = reflectivity;
}

void AObject::setTransparency(bool transparency)
{
    _transparency = transparency;
}

void AObject::setRoughness(float roughness)
{
    _roughness = roughness;
}

void AObject::setRefractiveIndex(float refractiveIndex)
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
        _emmsionColor = Vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}

void AObject::setEmissionIntensity(const float &intensity)
{
    _intensity = intensity;
}

void AObject::setTransformations(const std::vector<std::shared_ptr<ITransformation>> &transformations)
{
    _transformations = transformations;
}

bool AObject::operator==(const AObject &obj) const
{
    return _pos == obj._pos && _color == obj._color && _emmsionColor == obj._emmsionColor &&
        _intensity == obj._intensity && _reflectivity == obj._reflectivity &&
        _transparency == obj._transparency;
}

bool AObject::operator!=(const AObject &obj) const
{
    return !(*this == obj);
}
