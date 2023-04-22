##
## EPITECH PROJECT, 2023
## helloworld
## File description:
## Makefile
##

SRC = 	src/main.cpp 				\
		src/Renderer/Core.cpp		\
		src/Renderer/Lights.cpp		\
		src/Scene.cpp 				\
		src/Camera.cpp 				\
		src/LightPoint.cpp 			\
		src/utils/Math.cpp			\
		src/utils/Matrix.cpp		\
		src/objects/Sphere.cpp 		\
		src/objects/Triangle.cpp 	\
		src/objects/Square.cpp 		\
		src/objects/Plane.cpp 		\
		src/objects/Cone.cpp 		\

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = raytracer

CXXFLAGS = -Wall -Wextra -I ./include -std=c++20 -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -O3

all: $(NAME)

$(NAME):   $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

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
