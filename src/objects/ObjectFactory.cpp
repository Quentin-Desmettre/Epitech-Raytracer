/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** ObjectFactory
*/

#include "objects/ObjectFactory.hpp"
#include "Exceptions.hpp"
#include "objects/Sphere.hpp"
#include "objects/builders/SphereBuilder.hpp"
#include "objects/builders/PlaneBuilder.hpp"
#include "objects/builders/CylinderBuilder.hpp"
#include "objects/builders/ConeBuilder.hpp"
#include "objects/builders/TorusBuilder.hpp"
#include "objects/builders/TriangleBuilder.hpp"
#include "objects/builders/TanglecubeBuilder.hpp"
#include "objects/builders/ObjBuilder.hpp"
#include "objects/builders/QuadBuilder.hpp"

ObjectFactory::ObjectFactory(Scene &scene)
{
    this->_builders["sphere"] =     std::make_shared<SphereBuilder>();
    this->_builders["plane"] =      std::make_shared<PlaneBuilder>();
    this->_builders["cylinder"] =   std::make_shared<CylinderBuilder>();
    this->_builders["cone"] =       std::make_shared<ConeBuilder>();
    this->_builders["torus"] =      std::make_shared<TorusBuilder>();
    this->_builders["triangle"] =   std::make_shared<TriangleBuilder>();
    this->_builders["tanglecube"] = std::make_shared<TanglecubeBuilder>();
    this->_builders["obj"] =        std::make_shared<ObjBuilder>(scene);
    this->_builders["quad"] =       std::make_shared<QuadBuilder>();
}
