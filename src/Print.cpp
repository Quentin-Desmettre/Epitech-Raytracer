/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Print
*/

#include "Print.hpp"

Raytracer::AnonymousCout Raytracer::cout;

Raytracer::AnonymousCout &operator<<(Raytracer::AnonymousCout &c, std::ostream& (*f)(std::ostream&))
{
    static_cast<void>(f);
    static_cast<void>(c);
#ifdef DEBUG
    std::cout << f;
#endif
    return c;
}
