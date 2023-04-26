/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** AFactory
*/

#ifndef EPITECH_RAYTRACER_AFACTORY_HPP
#define EPITECH_RAYTRACER_AFACTORY_HPP
#include "IFactory.hpp"
#include "ABuilder.hpp"

template <typename T>
class AFactory: public IFactory<T> {
    public:
        virtual ~AFactory() = default;
        std::shared_ptr<T> create(const std::string &type, const libconfig::Setting &settings) override {
            if (_builders.find(type) == _builders.end())
                throw InvalidParameterNameException(type);
            auto *builder = static_cast<IBuilder<T> *>(_builders[type].get());
            return builder->build(settings);
        }

    protected:
        std::map<std::string, std::shared_ptr<void>> _builders;
};


#endif //EPITECH_RAYTRACER_AFACTORY_HPP
