/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Object
*/

#pragma once

#include "ITransformation.hpp"
#include "lights/ObjectLight.hpp"
#include "Exceptions.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

class Ray;

class IObject {
    public:
        virtual ~IObject() = default;

        // Getters
        virtual Vec3 getPos() const = 0;
        virtual Vec3 getColor() const = 0;
        virtual Vec3 getEmissionColor() const = 0;
        virtual float getEmissionIntensity() const = 0;
        virtual bool isReflective() const = 0;
        virtual bool isTransparent() const = 0;
        virtual float getRoughness() const = 0;
        virtual float getRefractiveIndex() const = 0;
        virtual const ObjectLight &getLight() const = 0;

        // Setters
        virtual void setPos(Vec3 pos) = 0;
        virtual void setReflectivity(const bool &reflectivity) = 0;
        virtual void setTransparency(const bool &transparency) = 0;
        virtual void setRoughness(const float &roughness) = 0;
        virtual void setRefractiveIndex(const float &refractiveIndex) = 0;
        virtual void setColor(const sf::Color &color) = 0;
        virtual void setPosition(const sf::Vector3f &pos) = 0;
        virtual void setEmissionColor(const sf::Color &color) = 0;
        virtual void setEmissionIntensity(const float &intensity) = 0;
        virtual void setTransformations(const std::vector<std::shared_ptr<ITransformation>> &transformations) = 0;

        // Methods
        virtual bool intersect(const Ray &ray) const = 0;
        virtual Vec3 getIntersection(const Ray &ray) const = 0;
        virtual Vec3 getNormal(const Vec3 &inter, const Ray &ray) const = 0;

    protected:
        Vec3 _pos;
        Vec3 _color;
        ObjectLight _light;
        float _roughness;
        bool _reflectivity;
        bool _transparency;
        float _refractiveIndex;
    private:
};

/**
 * @brief Abstract class for all objects
 *
 * This class implements setters/getters from IObject, but left abstract the methods
 * - intersect
 * - getIntersection
 * - getNormal
 */
class AObject : public IObject {
    public:
        explicit AObject(Vec3 pos = Vec3(0, 0, 0), sf::Color color = sf::Color::Red,
        sf::Color emmsionColor = sf::Color::Transparent, float intensity = 1.0f);
        ~AObject() override = default;

        // Operators
        virtual bool operator==(const AObject &obj) const;
        virtual bool operator!=(const AObject &obj) const;

        // Getters
        Vec3 getPos() const override;
        Vec3 getColor() const override;
        Vec3 getEmissionColor() const override;
        float getEmissionIntensity() const override;
        bool isReflective() const override;
        bool isTransparent() const override;
        float getRoughness() const override;
        float getRefractiveIndex() const override;
        const ObjectLight &getLight() const override;

        // Setters
        void setPos(Vec3 pos) override;
        void setReflectivity(const bool &reflectivity) override;
        void setTransparency(const bool &transparency) override;
        void setRoughness(const float &roughness) override;
        void setRefractiveIndex(const float &refractiveIndex) override;
        void setColor(const sf::Color &color) override;
        void setPosition(const sf::Vector3f &pos) override;
        void setEmissionColor(const sf::Color &color) override;
        void setEmissionIntensity(const float &intensity) override;
        void setTransformations(const std::vector<std::shared_ptr<ITransformation>> &transformations);

    protected:
        std::vector<std::shared_ptr<ITransformation>> _transformations;
};
