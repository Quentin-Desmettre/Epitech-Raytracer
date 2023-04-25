/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjectBuilder
*/

#ifndef EPITECH_RAYTRACER_OBJECTBUILDER_HPP
#define EPITECH_RAYTRACER_OBJECTBUILDER_HPP
#include <memory>
#include "objects/Sphere.hpp"
#include "ABuilder.hpp"
#include "libconfig.h++"
#include "transformations/TransformationFactory.hpp"
#include "Exceptions.hpp"

/**
 * @brief Generic builder for every objects
 * @tparam T Type of the object to build
 */
template <class T>
class ObjectBuilder: public ABuilder<T> {
    public:
        explicit ObjectBuilder():
                ABuilder<T>()
        {
            // Objects
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
            this->_objSetters.push_back({"type",                {Type::TypeString,  nullptr,                                                        false}});
            this->_objSetters.push_back({"position",            {Type::TypeGroup,   reinterpret_cast<ObjSetterFunc>(&IObject::setPosition),          false}});
            this->_objSetters.push_back({"color",               {Type::TypeGroup,   reinterpret_cast<ObjSetterFunc>(&IObject::setColor),             true}});
            this->_objSetters.push_back({"transparency",        {Type::TypeFloat,   reinterpret_cast<ObjSetterFunc>(&IObject::setTransparency),      true}});
            this->_objSetters.push_back({"reflection",          {Type::TypeFloat,   reinterpret_cast<ObjSetterFunc>(&IObject::setReflectivity),      true}});
            this->_objSetters.push_back({"transformations",     {Type::TypeList,    reinterpret_cast<ObjSetterFunc>(&IObject::setTransformations),   true}});
            this->_objSetters.push_back({"emission-color",      {Type::TypeGroup,   reinterpret_cast<ObjSetterFunc>(&IObject::setEmissionColor),     true}});
            this->_objSetters.push_back({"emission-intensity",  {Type::TypeFloat,   reinterpret_cast<ObjSetterFunc>(&IObject::setEmissionIntensity), true}});

            // Groups
            this->_objGroupSetters.push_back({"position",   static_cast<ABuilder<T>::BuilderSetterFunc>(&ObjectBuilder::setPosition)});
            this->_objGroupSetters.push_back({"color",      static_cast<ABuilder<T>::BuilderSetterFunc>(&ObjectBuilder::setColor)});
            this->_objGroupSetters.push_back({"emission-color", static_cast<ABuilder<T>::BuilderSetterFunc>(&ObjectBuilder::setEmissionColor)});

            // Lists
            // transformations MUST BE AFTER POSITION
            this->_objListSetters.push_back({"transformations", static_cast<ABuilder<T>::BuilderSetterFunc>(&ObjectBuilder::setTransformations)});
#pragma GCC diagnostic pop

        }
        ~ObjectBuilder() override = default;

    protected:
        typedef libconfig::Setting::Type Type;
        typedef void (IObject::*ObjSetterFunc)();


    void setPosition(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {
            if (!setting.exists("x") || !setting.exists("y") || !setting.exists("z"))
                throw MissingParameterException(argName + " (x, y, z)");

            sf::Vector3f pos = {
                    ABuilder<T>::getFloat(setting["x"]),
                    ABuilder<T>::getFloat(setting["y"]),
                    ABuilder<T>::getFloat(setting["z"])
            };
            std::cout << "pos: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
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

        void setEmissionColor(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {
            ABuilder<T>::setParameter(obj, argName, getColor(setting));
        }

        void setTransformations(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {
            TransformationFactory transformationFactory(obj);

            ABuilder<T>::setGroupList(obj, argName, setting, &transformationFactory);
        }
};

#endif //EPITECH_RAYTRACER_OBJECTBUILDER_HPP
