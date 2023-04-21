/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** AObjectBuilder
*/

#ifndef EPITECH_RAYTRACER_AOBJECTBUILDER_HPP
#define EPITECH_RAYTRACER_AOBJECTBUILDER_HPP
#include <memory>
#include "objects/Object.hpp"
#include "ABuilder.hpp"
#include "libconfig.h++"

template <typename T>
class AObjectBuilder: public ABuilder<T> {
    typedef libconfig::Setting::Type Type;

    public:
        explicit AObjectBuilder(const libconfig::Setting &settings):
                ABuilder<T>(settings)
        {
            // Objects
            this->_objSetters.at("type") =            {Type::TypeString,  nullptr,                                                                     false};
            this->_objSetters.at("position") =        {Type::TypeGroup,   reinterpret_cast<ABuilder<T>::ObjSetterFunc>(&Object::setPosition),          false};
            this->_objSetters.at("color") =           {Type::TypeGroup,   reinterpret_cast<ABuilder<T>::ObjSetterFunc>(&Object::setEmissionColor),     true};
            this->_objSetters.at("transparency") =    {Type::TypeFloat,   reinterpret_cast<ABuilder<T>::ObjSetterFunc>(&Object::setTransparency),      true};
            this->_objSetters.at("reflection") =      {Type::TypeBoolean, reinterpret_cast<ABuilder<T>::ObjSetterFunc>(&Object::setReflectivity),      true};
            this->_objSetters.at("transformations") = {Type::TypeList,    reinterpret_cast<ABuilder<T>::ObjSetterFunc>(&Object::setTransformations),   true};

            // Groups
            this->_objGroupSetters.at("position") =   static_cast<ABuilder<T>::BuilderSetterFunc>(&AObjectBuilder::setPosition);
            this->_objGroupSetters.at("color") =      static_cast<ABuilder<T>::BuilderSetterFunc>(&AObjectBuilder::setColor);

            // Lists
            this->_objListSetters.at("transformations") = static_cast<ABuilder<T>::BuilderSetterFunc>(&AObjectBuilder::setTransformations);
        }
        ~AObjectBuilder() override = default;

    protected:
        void setPosition(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {

            if (!setting.exists("x") || !setting.exists("y") || !setting.exists("z"))
                throw MissingParameterException(argName + " (x, y, z)");

            sf::Vector3f pos = {
                    setting["x"],
                    setting["y"],
                    setting["z"]
            };
            setParameter(obj, argName, pos);
        }

        void setColor(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {
            // Check presence
            if (!setting.exists("r") || !setting.exists("g") || !setting.exists("b"))
                throw MissingParameterException(argName + " (r, g, b)");
            int r = setting["r"],
                    g = setting["g"],
                    b = setting["b"];

            // Check value
            if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
                throw InvalidParameterValueException(argName + " (r, g, b) must be between 0 and 255");

            // Set values
            sf::Color color = {
                    static_cast<sf::Uint8>(r),
                    static_cast<sf::Uint8>(g),
                    static_cast<sf::Uint8>(b)
            };
            setParameter(obj, argName, color);
        }

        void setTransformations(T &obj, const std::string &argName, const libconfig::Setting &setting)
        {
            TransformationFactory transformationFactory;

            setGroupList(obj, argName, setting, transformationFactory);
        }
};

#endif //EPITECH_RAYTRACER_AOBJECTBUILDER_HPP
