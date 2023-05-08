/*
** EPITECH PROJECT, 2023
** Epitech-Raytracer
** File description:
** Math
*/

#include "utils/Math.hpp"

Vec3 Math::normalize(const Vec3 &vec)
{
    float len = length(vec);

    if (len == 0)
        return VEC3_ZERO;
    return {vec.x / len, vec.y / len, vec.z / len};
}

float Math::dot(const Vec3 &vec1, const Vec3 &vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float Math::randomf(const float min, const float max)
{
    thread_local std::normal_distribution<float> distribution(min, max);

    return distribution(generator);
}

int Math::random(int min, int max)
{
    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}

Vec3 Math::randomDir(const Vec3 &normal)
{
    int maxIterations = 100;
    Vec3 dir = {randomf(-1, 1), randomf(-1, 1), randomf(-1, 1)};

    while (dot(dir, normal) < 0 && maxIterations-- > 0)
        dir = {randomf(-1, 1), randomf(-1, 1), randomf(-1, 1)};
    return normalize(dir);
}

float Math::sign(const float val)
{
    return (0 < val) - (val < 0);
}

Vec3 Math::cross(const Vec3 &vec1, const Vec3 &vec2)
{
    return {vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x};
}

Vec3 Math::lerp(const Vec3 &vec1, const Vec3 &vec2, const float t)
{
    return vec1 + t * (vec2 - vec1);
}

float Math::length(const Vec3 &vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

bool Math::sameSign(const Vec3 &a, const Vec3 &b)
{
    return (a.x * b.x >= 0) && (a.y * b.y >= 0) && (a.z * b.z >= 0);
}

Vec3 Math::proj(const Vec3 &vec1, const Vec3 &vec2)
{
    return dot(vec1, vec2) / dot(vec2, vec2) * vec2;
}

Vec3 Math::refract(const Vec3 &incident, const Vec3 &normal, float n1, float n2)
{
    float cosi = dot(incident, normal);
    float etai = n1;
    float etat = n2;
    Vec3 n = normal;

    if (cosi < 0)
        cosi = -cosi;
    else {
        std::swap(etai, etat);
        n = -n;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0)
        return VEC3_ZERO;
    return eta * incident + (eta * cosi - sqrtf(k)) * n;
}

float Math::fresnel(float cosi, float etai, float etat)
{
    float r0 = powf((etai - etat) / (etai + etat), 2.0f);
    float x = 1.0f - (cosi < 0 ? -cosi : cosi);
    float fresnel = r0 + (1.0f - r0) * powf(x, 5.0f);
    return fresnel;
}

bool Math::isPowerOfTwo(int n)
{
    return (ceil(log2(n)) == floor(log2(n)));
}

float Math::toRad(float deg)
{
    return deg * M_PIf / 180.0f;
}

float Math::toDeg(float rad)
{
    return rad * 180.0f / M_PIf;
}

std::vector<float> Math::solveLinear(const float coeffs[2]) {
    std::vector<float> res;
    if (coeffs[0] == 0)
        return res;
    return {-coeffs[1] / coeffs[0]};
}

std::vector<float> Math::solveQuadratic(const float coeffs[3])
{
    if (coeffs[0] == 0)
        return solveLinear(coeffs + 1);

    std::vector<float> res;
    float a = coeffs[0];
    float b = coeffs[1];
    float c = coeffs[2];

    float delta = b * b - 4 * a * c;
    if (delta < 0)
        return {};
    if (delta == 0)
        return {-b / (2 * a)};
    float u = std::sqrt(delta);
    return {
            (-b + u) / (2 * a),
            (-b - u) / (2 * a)
    };
}

std::vector<float> Math::solveCubic(const float coeffs[4])
{
    if (coeffs[0] == 0)
        return solveQuadratic(coeffs + 1);

    std::vector<float> res;
    res.reserve(3);
    float a = coeffs[0];
    float b = coeffs[1];
    float c = coeffs[2];
    float d = coeffs[3];

    float A = b / a;
    float B = c / a;
    float C = d / a;

    float sq_A = A * A;
    float p = 1.0f / 3 * (-1.0f / 3 * sq_A + B);
    float q = 1.0f / 2 * (2.0f / 27 * A * sq_A - 1.0f / 3 * A * B + C);

    float cb_p = p * p * p;
    float D = q * q + cb_p;

    if (D == 0) {
        if (q == 0)
            res.push_back(0);
        else {
            float u = std::cbrt(-q);
            res.push_back(2 * u);
            res.push_back(-u);
        }
    } else if (D < 0) {
        float phi = 1.0f / 3 * std::acos(-q / std::sqrt(-cb_p));
        float t = 2 * std::sqrt(-p);
        res.push_back(t * std::cos(phi));
        res.push_back(-t * std::cos(phi + M_PIf / 3));
        res.push_back(-t * std::cos(phi - M_PIf / 3));
    } else {
        float sqrt_D = std::sqrt(D);
        float u = std::cbrt(sqrt_D - q);
        float v = -std::cbrt(sqrt_D + q);
        res.push_back(u + v);
    }

    float sub = 1.0f / 3 * A;
    for (float& r : res)
        r -= sub;
    return res;
}

std::vector<float> Math::solveQuartic(const float coeffs[5])
{
    if (coeffs[0] == 0)
        return solveCubic(coeffs + 1);

    std::vector<float> res;
    float a = coeffs[0];
    float b = coeffs[1];
    float c = coeffs[2];
    float d = coeffs[3];
    float e = coeffs[4];

    float A = b / a;
    float B = c / a;
    float C = d / a;
    float D = e / a;

    float sq_A = A * A;
    float p = -3.0f / 8 * sq_A + B;
    float q = 1.0f / 8 * sq_A * A - 1.0f / 2 * A * B + C;
    float r = -3.0f / 256 * sq_A * sq_A + 1.0f / 16 * sq_A * B - 1.0f / 4 * A * C + D;

    if (r == 0) { // Same as a cubic equation
        float newCoeffs[4] = {1, 0, p, q};
        auto tmp = solveCubic(newCoeffs);
        res.insert(res.end(), tmp.begin(), tmp.end());
    } else {

        // First, solve a cubic
        float newCoeffs[4] = {
                1,
                -1.0f / 2 * p,
                -r,
                1.0f / 2 * r * p - 1.0f / 8 * q * q
        };
        auto tmp = solveCubic(newCoeffs); // The final solution vector

        // Then, use on of these solutions to build two quadratic equations
        float z = tmp[0];

        float u = z * z - r;
        float v = 2 * z - p;

        if (u == 0)
            u = 0;
        else if (u > 0)
            u = std::sqrt(u);
        else
            return {};

        if (v == 0)
            v = 0;
        else if (v > 0)
            v = std::sqrt(v);
        else
            return {};

        // Solve them, and add their result to our solution vector
        // First quadratic equation
        newCoeffs[0] = 1;
        newCoeffs[1] = q < 0 ? -v : v;
        newCoeffs[2] = z - u;
        res = solveQuadratic(newCoeffs);

        // Second quadratic equation
        newCoeffs[0] = 1;
        newCoeffs[1] = q < 0 ? v : -v;
        newCoeffs[2] = z + u;
        auto newSols = solveQuadratic(newCoeffs);
        res.insert(res.end(), newSols.begin(), newSols.end());
    }

    // Resubstitute
    float sub = 1.0f / 4 * A;
    for (float &tmp: res)
        tmp -= sub;
    return res;
}
