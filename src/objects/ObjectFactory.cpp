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

ObjectFactory::ObjectFactory()
{
    this->_builders["sphere"] =     reinterpret_cast<IBuilder<Object> *>(new SphereBuilder());
    this->_builders["plane"] =      reinterpret_cast<IBuilder<Object> *>(new PlaneBuilder());
    this->_builders["cylinder"] =   reinterpret_cast<IBuilder<Object> *>(new CylinderBuilder());
    this->_builders["cone"] =       reinterpret_cast<IBuilder<Object> *>(new ConeBuilder());
    this->_builders["torus"] =      reinterpret_cast<IBuilder<Object> *>(new TorusBuilder());
    this->_builders["triangle"] =   reinterpret_cast<IBuilder<Object> *>(new TriangleBuilder());
    this->_builders["tanglecube"] = reinterpret_cast<IBuilder<Object> *>(new TanglecubeBuilder());
    this->_builders["obj"] =        reinterpret_cast<IBuilder<Object> *>(new ObjBuilder());
}
