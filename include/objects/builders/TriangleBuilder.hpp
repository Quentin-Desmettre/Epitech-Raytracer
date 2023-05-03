/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** TriangleBuilder
*/

#ifndef EPITECH_RAYTRACER_TRIANGLEBUILDER_HPP
#define EPITECH_RAYTRACER_TRIANGLEBUILDER_HPP
#include "ObjectBuilder.hpp"
#include "objects/Triangle.hpp"

class TriangleBuilder: ObjectBuilder<Triangle> {
    public:
        explicit TriangleBuilder();

    private:
        template <std::size_t N>
        void setPoint(Triangle &obj, const std::string &param, const libconfig::Setting &setting) {

            if (!setting.exists("x") || !setting.exists("y") || !setting.exists("z"))
                throw MissingParameterException("Missing x, y or z for triangle point " + param);

            Vec3 point = {
                    getFloat(setting["x"]),
                    getFloat(setting["y"]),
                    getFloat(setting["z"])
            };
            setParameter(obj, param, point);
        }
};

#endif //EPITECH_RAYTRACER_TRIANGLEBUILDER_HPP
