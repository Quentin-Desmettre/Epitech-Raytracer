/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** AObject
*/

#include "objects/Object.hpp"

AObject::AObject(Vec3 pos, sf::Color color, sf::Color emmsionColor,
                 float intensity, float reflectivity)
{
    _pos = pos;
    _intensity = intensity;
    _reflectivity = reflectivity;
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

float AObject::getReflectivity() const
{
    return _reflectivity;
}

float AObject::getTransparency() const
{
    return _transparency;
}

void AObject::setPos(Vec3 pos)
{
    _pos = pos;
}

void AObject::setReflectivity(float reflectivity)
{
    _reflectivity = reflectivity;
}

void AObject::setTransparency(float transparency)
{
    _transparency = transparency;
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
