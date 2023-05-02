/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ABuilder
*/

#ifndef EPITECH_RAYTRACER_ABUILDER_HPP
#define EPITECH_RAYTRACER_ABUILDER_HPP

#include <memory>
#include <map>
#include <vector>
#include "libconfig.h++"
#include "Exceptions.hpp"
#include "IFactory.hpp"
#include "IBuilder.hpp"
#include <iostream>
#include "scene/Scene.hpp"

template <class T>
class ABuilder: IBuilder<T> {
public:
    virtual ~ABuilder() = default;

    /**
     * @brief Build an object of type T.
     * @return UniquePointer to an object of type T.
     */
    std::unique_ptr<T> build(const libconfig::Setting &settings) override {
        bool paramExists;
        std::unique_ptr<T> obj = std::make_unique<T>();

        for (auto &[argName, func]: _objSetters) {
            paramExists = settings.exists(argName);
            if (!paramExists && !func.hasDefaultValue)
                throw MissingParameterException(argName);
            if (!paramExists)
                continue;
            setParameter(*obj, argName, settings.lookup(argName));
        }
        return obj;
    }

    static float getFloat(const libconfig::Setting &setting)
    {
        typedef libconfig::Setting::Type Type;

        Type type = setting.getType();

        switch (type) {
            case Type::TypeFloat:
                return setting;
            case Type::TypeInt:
            case Type::TypeInt64:
                return static_cast<float>(static_cast<int>(setting));
            default:
                throw InvalidParameterValueException("float");
        }
    }


protected:
    typedef void (ABuilder::*BuilderSetterFunc)(T &obj, const std::string &, const libconfig::Setting &);
    typedef void (T::*SetterFunc)();

    /**
     * @brief Structure that holds information about a parameter.
     */
    struct ObjSetter {
        libconfig::Setting::Type argType;
        void (T::*setter)();
        bool hasDefaultValue;

        ObjSetter(libconfig::Setting::Type type, void (T::*setter)(), bool hasDefaultValue = false)
                : argType(type), setter(setter), hasDefaultValue(hasDefaultValue) {};
    };

    // Setters
    std::vector<std::pair<std::string, ObjSetter>> _objSetters;

    // Group setters
    std::vector<std::pair<std::string, BuilderSetterFunc>> _objGroupSetters;

    // List setters
    std::vector<std::pair<std::string, BuilderSetterFunc>> _objListSetters;

    // Conversion table for libconfig types
    std::map<libconfig::Setting::Type, std::string> _typeNames = {
            {libconfig::Setting::TypeNone,      "none"},
            {libconfig::Setting::TypeBoolean,   "boolean"},
            {libconfig::Setting::TypeInt,       "integer"},
            {libconfig::Setting::TypeInt64,     "integer"},
            {libconfig::Setting::TypeFloat,     "float"},
            {libconfig::Setting::TypeString,    "string"},
            {libconfig::Setting::TypeGroup,     "group"},
            {libconfig::Setting::TypeArray,     "array"},
            {libconfig::Setting::TypeList,      "list"}
    };

    /**
     * @brief Set a parameter of type U to the object.
     * @tparam U Type of the parameter.
     * @param obj Object to set the parameter to.
     * @param param Name of the parameter.
     * @param value Value of the parameter.
     */
    template <typename U>
    void setParameter(T &obj, const std::string &param, const U &value)
    {
        // Check presence
        std::size_t i;
        for (i = 0; i < _objSetters.size(); i++)
            if (_objSetters[i].first == param)
                break;
        if (i == _objSetters.size())
            throw InvalidParameterNameException(param);

        // Call
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
        auto func = reinterpret_cast<void (T::*)(const U&)>(_objSetters.at(indexOf(param, _objSetters)).second.setter);
#pragma GCC diagnostic pop

        if (!func)
            return;
        (obj.*func)(value);
    }

    /**
     * @brief Set a parameter of the object, casting it properly.
     * @param obj Object to set the parameter to.
     * @param param Name of the parameter.
     * @param setting Setting of the parameter.
     */
    void setParameter(T &obj, const std::string &param, const libconfig::Setting &setting) {
        auto type = _objSetters.at(indexOf(param, _objSetters)).second.argType;

        switch (type) {
            case libconfig::Setting::TypeBoolean:
                setParameter<bool>(obj, param, setting);
                break;
            case libconfig::Setting::TypeInt:
            case libconfig::Setting::TypeInt64:
                setParameter<int>(obj, param, setting);
                break;
            case libconfig::Setting::TypeFloat:
                setParameter<float>(obj, param, getFloat(setting));
                break;
            case libconfig::Setting::TypeString:
                setParameter<std::string>(obj, param, setting);
                break;
            case libconfig::Setting::TypeGroup:
                (this->*_objGroupSetters.at(indexOf(param, _objGroupSetters)).second)(obj, param, setting);
                break;
            case libconfig::Setting::TypeList:
                (this->*_objListSetters.at(indexOf(param, _objListSetters)).second)(obj, param, setting);
                break;
            default:
                throw UnsupportedParameterTypeException(_typeNames.at(type));
        }
    }

    /**
     * @brief Set a list of parameters of type U to the object.
     * @tparam U Type of the parameters.
     * @param obj Object to set the parameters to.
     * @param param Name of the parameter.
     * @param setting Setting of the parameter.
     * @param factory Factory to create the parameters.
     */
    template <class U>
    void setGroupList(T &obj, const std::string &param, const libconfig::Setting &setting, IFactory<U> *factory) {
        std::vector<std::shared_ptr<U>> list;

        for (int i = 0; i < setting.getLength(); i++) {
            if (!setting[i].isGroup())
                throw InvalidParameterValueException("Invalid type for " + param);
            if (!setting[i].exists("type"))
                throw MissingParameterException("type");
            list.push_back(factory->create(setting[i].lookup("type"), setting[i]));
        }
        setParameter(obj, param, list);
    }

    template <class U>
    std::size_t indexOf(const std::string &param, const std::vector<std::pair<std::string, U>> &_objs)
    {
        for (std::size_t i = 0; i < _objs.size(); i++) {
            if (_objs[i].first == param)
                return i;
        }
        throw InvalidParameterNameException(param);
    }
};

#endif //EPITECH_RAYTRACER_ABUILDER_HPP
