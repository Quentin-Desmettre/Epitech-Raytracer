
##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC = \
	./src/main.cpp \
	./src/Camera.cpp \
	./src/Drawer.cpp \
	./src/AObject.cpp \
	./src/Raytracer.cpp \
	./src/Exceptions.cpp \
	./src/LightPoint.cpp \
	./src/utils/Math.cpp \
	./src/scene/Scene.cpp \
	./src/objects/Obj.cpp \
	./src/objects/Cone.cpp \
	./src/utils/Matrix.cpp \
	./src/RendererPool.cpp \
	./src/Renderer/Core.cpp \
	./src/objects/Torus.cpp \
	./src/objects/Plane.cpp \
	./src/LocalRenderer.cpp \
	./src/network/Packet.cpp \
	./src/objects/Sphere.cpp \
	./src/objects/Square.cpp \
	./src/Renderer/Lights.cpp \
	./src/clusters/Server.cpp \
	./src/clusters/Client.cpp \
	./src/objects/Cylinder.cpp \
	./src/objects/Triangle.cpp \
	./src/network/TcpSocket.cpp \
	./src/scene/SceneBuilder.cpp \
	./src/objects/Tanglecube.cpp \
	./src/network/TcpListener.cpp \
	./src/network/PacketReader.cpp \
	./src/network/PacketWriter.cpp \
	./src/objects/ObjectFactory.cpp \
	./src/objects/builders/ObjBuilder.cpp \
	./src/objects/builders/ConeBuilder.cpp \
	./src/objects/builders/TorusBuilder.cpp \
	./src/objects/builders/PlaneBuilder.cpp \
	./src/transformations/Transformation.cpp \
	./src/objects/builders/SphereBuilder.cpp \
	./src/objects/builders/CylinderBuilder.cpp \
	./src/objects/builders/TriangleBuilder.cpp \
	./src/objects/builders/TanglecubeBuilder.cpp \
	./src/transformations/TransformationFactory.cpp \

OBJ = $(SRC:.cpp=.o)

CXX = g++

NAME = raytracer

CXXFLAGS = -Wall -Wextra -I ./include -std=c++20 -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -O3 -g

all: $(NAME)

$(NAME):   $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

debug: CXXFLAGS += -g
debug: re

run: all
	./$(NAME)

rrun: re
	./$(NAME)

tests_run:
	cd tests && make && ./tests

clean:
	rm -f $(OBJ)
	find . -name "vgcore.*" -delete
	find . -name "*~" -delete
	find . -name "\#*" -delete

fclean:    clean
	rm -f $(NAME)

re:        fclean all
