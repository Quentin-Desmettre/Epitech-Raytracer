/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Object
*/

#pragma once

#include "render/Ray.hpp"
#include "ITransformation.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

class IObject {
    public:
        virtual ~IObject() = default;

        // Getters
        virtual Vec3 getPos() const = 0;
        virtual Vec3 getColor() const = 0;
        virtual Vec3 getEmissionColor() const = 0;
        virtual float getEmissionIntensity() const = 0;
        virtual float getReflectivity() const = 0;
        virtual float getTransparency() const = 0;

        // Setters
        virtual void setPos(Vec3 pos) = 0;
        virtual void setReflectivity(float reflectivity) = 0;
        virtual void setTransparency(float transparency) = 0;
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
        Vec3 _emmsionColor;
        float _intensity = 1.0f;
        float _reflectivity = 0.0f;
        float _transparency = 0.0f;
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
        sf::Color emmsionColor = sf::Color::Transparent, float intensity = 1.0f, float reflectivity = 0.0f);
        ~AObject() override = default;

        // Operators
        virtual bool operator==(const AObject &obj) const;
        virtual bool operator!=(const AObject &obj) const;

        // Getters
        Vec3 getPos() const override;
        Vec3 getColor() const override;
        Vec3 getEmissionColor() const override;
        float getEmissionIntensity() const override;
        float getReflectivity() const override;
        float getTransparency() const override;

        // Setters
        void setPos(Vec3 pos) override;
        void setReflectivity(float reflectivity) override;
        void setTransparency(float transparency) override;
        void setColor(const sf::Color &color) override;
        void setPosition(const sf::Vector3f &pos) override;
        void setEmissionColor(const sf::Color &color) override;
        void setEmissionIntensity(const float &intensity) override;
        void setTransformations(const std::vector<std::shared_ptr<ITransformation>> &transformations);

    protected:
        std::vector<std::shared_ptr<ITransformation>> _transformations;
};
