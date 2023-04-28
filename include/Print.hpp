/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Print
*/

#ifndef EPITECH_RAYTRACER_PRINT_HPP
#define EPITECH_RAYTRACER_PRINT_HPP
#include <iostream>

namespace Raytracer {
    class AnonymousCout {
    };

    extern AnonymousCout cout;
}

Raytracer::AnonymousCout &operator<<(Raytracer::AnonymousCout &c, std::ostream& (*f)(std::ostream&));

template <typename T>
Raytracer::AnonymousCout &operator<<(Raytracer::AnonymousCout &c, const T& x)
{
    static_cast<void>(x);
    static_cast<void>(c);
#ifdef DEBUG
    std::cout << x;
#endif
    return c;
}

#endif //EPITECH_RAYTRACER_PRINT_HPP
