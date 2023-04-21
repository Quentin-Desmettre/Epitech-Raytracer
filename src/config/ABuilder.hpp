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
#include "libconfig.h++"
#include "Exceptions.hpp"
#include "IFactory.hpp"

template <class T>
class ABuilder {
public:
    explicit ABuilder(const char *configPath)
            : _config(std::make_unique<libconfig::Config>()), _settings(nullptr)
    {
        _config->readFile(configPath);
        _settings = &_config->getRoot();
    }

    explicit ABuilder(const libconfig::Setting &settings)
            : _config(nullptr), _settings(&settings) {}

    virtual ~ABuilder() = default;

    /**
     * @brief Build an object of type T.
     * @return UniquePointer to an object of type T.
     */
    std::unique_ptr<T> build() {
        bool paramExists;
        std::unique_ptr<T> obj = std::make_unique<T>();

        for (auto &[argName, func]: _objSetters) {
            paramExists = _settings->exists(argName);
            if (!paramExists && !func.hasDefaultValue)
                throw MissingParameterException(argName);
            if (!paramExists)
                continue;
            setParameter(*obj, argName, _settings->lookup(argName));
        }
        return obj;
    }

protected:
    typedef void (ABuilder::*BuilderSetterFunc)(T &obj, const std::string &, const libconfig::Setting &);
    typedef void (T::*ObjSetterFunc)();

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
    std::map<std::string, ObjSetter> _objSetters;

    // Group setters
    std::map<std::string, BuilderSetterFunc> _objGroupSetters;

    // List setters
    std::map<std::string, BuilderSetterFunc> _objListSetters;

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
    const libconfig::Setting *_settings;
    std::unique_ptr<libconfig::Config> _config;

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
        if (_objSetters.find(param) == _objSetters.end())
            throw InvalidParameterNameException(param);
        auto func = reinterpret_cast<void (T::*)(const U&)>(_objSetters.at(param).setter);

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
        auto type = _objSetters.at(param).argType;

        switch (type) {
            case libconfig::Setting::TypeBoolean:
                setParameter<bool>(obj, param, setting);
                break;
            case libconfig::Setting::TypeInt:
            case libconfig::Setting::TypeInt64:
                setParameter<int>(obj, param, setting);
                break;
            case libconfig::Setting::TypeFloat:
                setParameter<float>(obj, param, setting);
                break;
            case libconfig::Setting::TypeString:
                setParameter<std::string>(obj, param, setting);
                break;
            case libconfig::Setting::TypeGroup:
                (this->*_objGroupSetters.at(param))(obj, param, setting);
                break;
            case libconfig::Setting::TypeList:
                (this->*_objListSetters.at(param))(obj, param, setting);
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
        std::vector<std::unique_ptr<U>> list;

        for (int i = 0; i < setting.getLength(); i++) {
            if (!setting[i].isGroup())
                throw InvalidParameterValueException("Invalid type for " + param);
            if (!setting[i].exists("type"))
                throw MissingParameterException("type");
            list.push_back(factory->create(setting[i].lookup("type")));
        }
        setParameter(obj, param, list);
    }
};

#endif //EPITECH_RAYTRACER_ABUILDER_HPP
