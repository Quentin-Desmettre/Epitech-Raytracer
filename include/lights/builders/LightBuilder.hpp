/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** LightBuilder
*/

#pragma once

#include <memory>
#include "ABuilder.hpp"
#include "lights/ILight.hpp"
#include "Exceptions.hpp"
#include "libconfig.h++"

/**
 * @brief Generic builder for every lights
 * @tparam T Type of the light to build
 */
template <class T>
class LightBuilder: public ABuilder<T> {
    public:
        explicit LightBuilder():
                ABuilder<T>()
        {
            // Lights
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
            this->_objSetters.push_back({"type",                {Type::TypeString,  nullptr,                                                    false}});
            this->_objSetters.push_back({"color",               {Type::TypeGroup,   reinterpret_cast<LightSetterFunc>(&ILight::setColor),       true}});
            this->_objSetters.push_back({"intensity",           {Type::TypeFloat,   reinterpret_cast<LightSetterFunc>(&ILight::setIntensity),   true}});

            // Groups
            this->_objGroupSetters.push_back({"color",      static_cast<ABuilder<T>::BuilderSetterFunc>(&LightBuilder::setColor)});
#pragma GCC diagnostic pop

        }
        ~LightBuilder() override = default;

    protected:
        typedef libconfig::Setting::Type Type;
        typedef void (ILight::*LightSetterFunc)();

        void setPosition(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {
            if (!setting.exists("x") || !setting.exists("y") || !setting.exists("z"))
                throw MissingParameterException(argName + " (x, y, z)");

            sf::Vector3f pos = {
                    ABuilder<T>::getFloat(setting["x"]),
                    ABuilder<T>::getFloat(setting["y"]),
                    ABuilder<T>::getFloat(setting["z"])
            };
            ABuilder<T>::setParameter(obj, argName, pos);
        }

        sf::Color getColor(const libconfig::Setting &setting)
        {
            // Check presence
            if (!setting.exists("r") || !setting.exists("g") || !setting.exists("b"))
                throw MissingParameterException("color (r, g, b)");
            int r = setting["r"],
                g = setting["g"],
                b = setting["b"];

            // Check value
            if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
                throw InvalidParameterValueException("color (r, g, b) must be between 0 and 255");

            // Set values
            return sf::Color(
                    static_cast<sf::Uint8>(r),
                    static_cast<sf::Uint8>(g),
                    static_cast<sf::Uint8>(b)
            );
        }

        void setColor(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {
            ABuilder<T>::setParameter(obj, argName, getColor(setting));
        }

        void setIntensity(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {
            ABuilder<T>::setParameter(obj, argName, ABuilder<T>::getFloat(setting));
        }
};
