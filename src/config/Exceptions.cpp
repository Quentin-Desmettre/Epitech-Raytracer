/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ScenBuilderException
*/

#include "SceneBuilderException.hpp"

AException::~AException() = default;

SceneBuilder::MissingParameterException::MissingParameterException(const std::string &param)
        : AException("Missing parameter: " + param) {}

SceneBuilder::InvalidParameterNameException::InvalidParameterNameException(const std::string &param)
        : AException("Invalid parameter name: " + param) {}

SceneBuilder::InvalidParameterValueException::InvalidParameterValueException(const std::string &param)
        : AException("Invalid parameter value: " + param) {}

SceneBuilder::UnsupportedParameterTypeException::UnsupportedParameterTypeException(const std::string &param)
        : AException("Unsuported parameter type: " + param) {}

SceneBuilder::InvalidArgumentsException::InvalidArgumentsException(const std::string &param)
        : AException("Invalid arguments: " + param) {}
