/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ScenBuilderException
*/

#include "Exceptions.hpp"

AException::~AException() = default;

MissingParameterException::MissingParameterException(const std::string &param)
        : AException("Missing parameter: " + param) {}

InvalidParameterNameException::InvalidParameterNameException(const std::string &param)
        : AException("Invalid parameter name: " + param) {}

InvalidParameterValueException::InvalidParameterValueException(const std::string &param)
        : AException("Invalid parameter value: " + param) {}

UnsupportedParameterTypeException::UnsupportedParameterTypeException(const std::string &param)
        : AException("Unsuported parameter type: " + param) {}

InvalidArgumentsException::InvalidArgumentsException(const std::string &param)
        : AException("Invalid arguments: " + param) {}
