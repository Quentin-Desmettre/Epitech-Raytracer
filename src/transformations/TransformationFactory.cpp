/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TransformationFactory
*/

#include "transformations/TransformationFactory.hpp"
#include "transformations/Transformation.hpp"
#include "objects/builders/ObjectBuilder.hpp"
#include "objects/Triangle.hpp"
#define getFloat ABuilder<Transformation>::getFloat

const std::map<std::string, TransformationFactory::Builder> TransformationFactory::_builders = {
    {"translate",   &TransformationFactory::buildTranslate},
    {"rotate",      &TransformationFactory::buildRotate},
    {"scale",       &TransformationFactory::buildScale},
    {"matrix",      &TransformationFactory::buildMatrix}
};

TransformationFactory::TransformationFactory(IObject &obj):
    _obj(obj)
{
}

SharedITransformation TransformationFactory::create(const std::string &type, const libconfig::Setting &settings)
{
    auto it = _builders.find(type);
    if (it == _builders.end())
        throw UnsupportedParameterTypeException(type);
    return (this->*it->second)(settings);
}

SharedITransformation TransformationFactory::buildTranslate(const libconfig::Setting &settings)
{
    // Check presence
    if (!settings.exists("x") || !settings.exists("y") || !settings.exists("z"))
        throw MissingParameterException("(x, y, z)");

    // Check type
    std::vector<libconfig::Setting::Type> possibleTypes = {
        libconfig::Setting::Type::TypeFloat,
        libconfig::Setting::Type::TypeInt,
        libconfig::Setting::Type::TypeInt64
    };
    if (std::find(possibleTypes.begin(), possibleTypes.end(), settings.lookup("x").getType()) == possibleTypes.end() ||
        std::find(possibleTypes.begin(), possibleTypes.end(), settings.lookup("y").getType()) == possibleTypes.end() ||
        std::find(possibleTypes.begin(), possibleTypes.end(), settings.lookup("z").getType()) == possibleTypes.end())
        throw InvalidParameterValueException("translate");

    auto translate = std::make_shared<Transformation>("translate");

    translate->setMatrices({Mat4::translate3D(
        sf::Vector3f{
              getFloat(settings["x"]),
              getFloat(settings["y"]),
              getFloat(settings["z"])
      }
    )});
    return translate;
}

SharedITransformation TransformationFactory::buildRotate(const libconfig::Setting &settings)
{
    // Check presence
    if (!settings.exists("around") || !settings.exists("axis") || !settings.exists("angle"))
        throw MissingParameterException("(around, axis, angle)");

    // Check type
    std::vector<libconfig::Setting::Type> possibleTypes = {
        libconfig::Setting::Type::TypeFloat,
        libconfig::Setting::Type::TypeInt,
        libconfig::Setting::Type::TypeInt64
    };
    if (settings.lookup("around").getType() != libconfig::Setting::Type::TypeString ||
        settings.lookup("axis").getType() != libconfig::Setting::Type::TypeString ||
        std::find(possibleTypes.begin(), possibleTypes.end(), settings.lookup("angle").getType()) == possibleTypes.end())
        throw InvalidParameterValueException("rotate");

    // Check values
    std::vector<std::string> possibleAxisValues = {"x", "y", "z"};
    std::vector<std::string> possibleAroundValues = {"origin", "center"};
    if (std::find(possibleAxisValues.begin(), possibleAxisValues.end(), static_cast<std::string>(settings["axis"])) == possibleAxisValues.end() ||
        std::find(possibleAroundValues.begin(), possibleAroundValues.end(), static_cast<std::string>(settings["around"])) == possibleAroundValues.end())
        throw InvalidParameterValueException("rotate");

    auto rotate = std::make_shared<Transformation>("rotate");
    char axis = static_cast<std::string>(settings["axis"])[0];

    // If the rotation is around the origin, simply return a basic rotation matrix
    if (static_cast<std::string>(settings["around"]) == "origin") {
        rotate->setMatrices({Mat4::rotate3D(
            axis,
            Math::toRad(getFloat(settings["angle"]))
        )});
        return rotate;
    }

    // If the rotation is around the center of the object, we need to translate it to the origin, rotate it, then translate it back
    // To do so, we create 3 matrices
    // 1. Translate the object to the origin
    Mat4 translateToOrigin = Mat4::translate3D(
        sf::Vector3f{
                -_obj.getPos().x,
                -_obj.getPos().y,
                -_obj.getPos().z
        }
    );

    // 2. Rotate the object
    Mat4 rotateAroundCenter = Mat4::rotate3D(
        axis,
        Math::toRad(getFloat(settings["angle"]))
    );

    // 3. Translate the object back to its original position
    Mat4 translateBack = Mat4::translate3D(
        sf::Vector3f{
                _obj.getPos().x,
                _obj.getPos().y,
                _obj.getPos().z
        }
    );

    // Then set theses 3 matrices
    rotate->setMatrices({translateToOrigin, rotateAroundCenter, translateBack});
    return rotate;
}

SharedITransformation TransformationFactory::buildScale(
        const libconfig::Setting &settings)
{
    // Check presence
    if (!settings.exists("x") || !settings.exists("y") || !settings.exists("z"))
        throw MissingParameterException("(x, y, z)");

    // Check type
    std::vector<libconfig::Setting::Type> possibleTypes = {
        libconfig::Setting::Type::TypeFloat,
        libconfig::Setting::Type::TypeInt,
        libconfig::Setting::Type::TypeInt64
    };
    if (std::find(possibleTypes.begin(), possibleTypes.end(), settings.lookup("x").getType()) == possibleTypes.end() ||
        std::find(possibleTypes.begin(), possibleTypes.end(), settings.lookup("y").getType()) == possibleTypes.end() ||
        std::find(possibleTypes.begin(), possibleTypes.end(), settings.lookup("z").getType()) == possibleTypes.end())
        throw InvalidParameterValueException("scale");

    auto scale = std::make_shared<Transformation>("scale");
    scale->setMatrices({Mat4::scale3D(
        sf::Vector3f{
              getFloat(settings["x"]),
              getFloat(settings["y"]),
              getFloat(settings["z"])
      }
    )});
    return scale;
}

SharedITransformation TransformationFactory::buildMatrix(
        const libconfig::Setting &settings)
{
    // Check presence
    if (!settings.exists("matrix"))
        throw MissingParameterException("matrix");

    // Check length
    if (settings["matrix"].getLength() != 16)
        throw InvalidParameterValueException("matrix");

    // Fill matrix
    Mat4 matrix;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix(i, j) = getFloat(settings["matrix"][i * 4 + j]);
    auto matrixTransformation = std::make_shared<Transformation>("matrix");
    matrixTransformation->setMatrices({matrix});
    return matrixTransformation;
}
