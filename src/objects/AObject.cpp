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
    if (refractiveIndex < 0)
        throw InvalidParameterValueException("Refractive index must be >= 0");
    _refractiveIndex = refractiveIndex;
}

void AObject::setColor(const sf::Color &color)
{
    _color = Vec3(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}

void AObject::setPosition(const Vec3 &pos)
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
    return {transformPos(ray.getOrigin()), transformDir(ray.getDir())};
}

Vec3 AObject::transformPos(const Vec3 &pos) const
{
    Vec3 newOrigin;
    newOrigin.x = _inverseTransformations[0] * pos.x + _inverseTransformations[1] * pos.y + _inverseTransformations[2] * pos.z + _inverseTransformations[3];
    newOrigin.y = _inverseTransformations[4] * pos.x + _inverseTransformations[5] * pos.y + _inverseTransformations[6] * pos.z + _inverseTransformations[7];
    newOrigin.z = _inverseTransformations[8] * pos.x + _inverseTransformations[9] * pos.y + _inverseTransformations[10] * pos.z + _inverseTransformations[11];
    return newOrigin;
}

Vec3 AObject::transformDir(const Vec3 &dir) const
{
    Vec3 newDir;
    newDir.x = _inverseTransformations[0] * dir.x + _inverseTransformations[1] * dir.y + _inverseTransformations[2] * dir.z;
    newDir.y = _inverseTransformations[4] * dir.x + _inverseTransformations[5] * dir.y + _inverseTransformations[6] * dir.z;
    newDir.z = _inverseTransformations[8] * dir.x + _inverseTransformations[9] * dir.y + _inverseTransformations[10] * dir.z;
    return newDir;
}

Vec3 AObject::transformDirInverse(const Vec3 &dir) const
{
    Vec3 newDir;
    newDir.x = _transformationsMatrix[0] * dir.x + _transformationsMatrix[1] * dir.y + _transformationsMatrix[2] * dir.z;
    newDir.y = _transformationsMatrix[4] * dir.x + _transformationsMatrix[5] * dir.y + _transformationsMatrix[6] * dir.z;
    newDir.z = _transformationsMatrix[8] * dir.x + _transformationsMatrix[9] * dir.y + _transformationsMatrix[10] * dir.z;
    return newDir;
}

Vec3 AObject::transformPosInverse(const Vec3 &pos) const
{
    Vec3 newOrigin;
    newOrigin.x = _transformationsMatrix[0] * pos.x + _transformationsMatrix[1] * pos.y + _transformationsMatrix[2] * pos.z + _transformationsMatrix[3];
    newOrigin.y = _transformationsMatrix[4] * pos.x + _transformationsMatrix[5] * pos.y + _transformationsMatrix[6] * pos.z + _transformationsMatrix[7];
    newOrigin.z = _transformationsMatrix[8] * pos.x + _transformationsMatrix[9] * pos.y + _transformationsMatrix[10] * pos.z + _transformationsMatrix[11];
    return newOrigin;
}
