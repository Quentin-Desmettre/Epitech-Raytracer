/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** SceneBuilderException
*/

#ifndef EPITECH_RAYTRACER_SCENEBUILDEREXCEPTION_HPP
#define EPITECH_RAYTRACER_SCENEBUILDEREXCEPTION_HPP

#include <exception>
#include <string>

namespace SceneBuilder {
    class MissingParameterException;
    class InvalidParameterNameException;
    class InvalidParameterValueException;
    class UnsupportedParameterTypeException;
    class InvalidArgumentsException;
}

class AException : public std::exception {
    public:
        explicit AException(const std::string &msg) : _msg(msg) {};
        virtual ~AException() = 0;
        const char *what() const noexcept override { return _msg.c_str(); };
    private:
        std::string _msg;
};

class SceneBuilder::MissingParameterException : public AException {
    public:
        explicit MissingParameterException(const std::string &param);
};

class SceneBuilder::InvalidParameterNameException : public AException {
    public:
        explicit InvalidParameterNameException(const std::string &param);
};

class SceneBuilder::InvalidParameterValueException : public AException {
    public:
        explicit InvalidParameterValueException(const std::string &param);
};

class SceneBuilder::UnsupportedParameterTypeException : public AException {
    public:
        explicit UnsupportedParameterTypeException(const std::string &param);
};

class SceneBuilder::InvalidArgumentsException : public AException {
    public:
        explicit InvalidArgumentsException(const std::string &param);
};

#endif //EPITECH_RAYTRACER_SCENEBUILDEREXCEPTION_HPP
