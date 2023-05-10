
##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC = \
	./src/network/PacketReader.cpp \
	./src/network/TcpListener.cpp \
	./src/network/TcpSocket.cpp \
	./src/network/PacketWriter.cpp \
	./src/network/Packet.cpp \
	./src/clusters/NetworkRenderer.cpp \
	./src/clusters/Client.cpp \
	./src/scene/Scene.cpp \
	./src/scene/SceneBuilder.cpp \
	./src/render/Camera.cpp \
	./src/render/LocalRenderer.cpp \
	./src/render/PointArray.cpp \
	./src/render/Drawer.cpp \
	./src/render/RendererPool.cpp \
	./src/render/Ray.cpp \
	./src/Exceptions.cpp \
	./src/lights/LightPoint.cpp \
	./src/lights/builders/LightPointBuilder.cpp \
	./src/lights/ObjectLight.cpp \
	./src/lights/DirectionalLight.cpp \
	./src/lights/builders/DirectionalLightBuilder.cpp \
	./src/lights/LightFactory.cpp \
	./src/transformations/TransformationFactory.cpp \
	./src/transformations/Transformation.cpp \
	./src/objects/Sphere.cpp \
	./src/objects/Obj.cpp \
	./src/objects/Quad.cpp \
	./src/objects/Torus.cpp \
	./src/objects/Cone.cpp \
	./src/objects/Cylinder.cpp \
	./src/objects/Triangle.cpp \
	./src/objects/ObjectFactory.cpp \
	./src/objects/AObject.cpp \
	./src/objects/Tanglecube.cpp \
	./src/objects/Plane.cpp \
	./src/objects/builders/SphereBuilder.cpp \
	./src/objects/builders/CylinderBuilder.cpp \
	./src/objects/builders/ConeBuilder.cpp \
	./src/objects/builders/ObjBuilder.cpp \
	./src/objects/builders/TorusBuilder.cpp \
	./src/objects/builders/TanglecubeBuilder.cpp \
	./src/objects/builders/TriangleBuilder.cpp \
	./src/objects/builders/PlaneBuilder.cpp \
	./src/objects/builders/QuadBuilder.cpp \
	./src/utils/Math.cpp \
	./src/utils/Matrix.cpp \
	./src/Raytracer.cpp \
	./src/main.cpp \
	./src/Print.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

NAME = raytracer

CXXFLAGS = -Wall -Wextra -I ./include -std=c++20 -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -O3

all: $(NAME)

$(NAME):   $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

debug: CXXFLAGS += -g -DDEBUG
debug: all

rebug: CXXFLAGS += -g -DDEBUG
rebug: re

run: all
	./$(NAME)

rrun: re
	./$(NAME)

tests_run:
	cd tests && make && ./tests

clean:
	rm -f $(OBJ)
	find . -name "vgcore.*" -delete || true
	find . -name "*~" -delete || true
	find . -name "\#*" -delete || true

fclean:    clean
	rm -f $(NAME)

re:        fclean all
