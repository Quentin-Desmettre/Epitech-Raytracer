/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TransformationFactory
*/

#ifndef EPITECH_RAYTRACER_TRANSFORMATIONFACTORY_HPP
#define EPITECH_RAYTRACER_TRANSFORMATIONFACTORY_HPP
#include "AFactory.hpp"
#include "ITransformation.hpp"
#include "objects/Object.hpp"

typedef std::shared_ptr<ITransformation> SharedITransformation;

class TransformationFactory: public IFactory<ITransformation> {
public:
    /**
     * @brief Construct a new Transformation Factory object.
     *
     * This class should be instantiated once per object.
     * @param obj The object to which the transformations will be applied.
     */
    explicit TransformationFactory(Object &obj);
    SharedITransformation create(const std::string &type, const libconfig::Setting &settings) override;

private:
    typedef SharedITransformation (TransformationFactory::*Builder)(const libconfig::Setting &);

    SharedITransformation buildTranslate(const libconfig::Setting &settings);
    SharedITransformation buildRotate(const libconfig::Setting &settings);
    SharedITransformation buildScale(const libconfig::Setting &settings);
    SharedITransformation buildMatrix(const libconfig::Setting &settings);

    Object &_obj;
    const static std::map<std::string, Builder> _builders;
};

#endif //EPITECH_RAYTRACER_TRANSFORMATIONFACTORY_HPP
