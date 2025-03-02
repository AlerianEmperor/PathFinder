#pragma once

#include "Triangle3D.hpp"

#include <glm/vec3.hpp>

namespace Geometry
{

    struct Sphere
    {
        glm::vec3 Center;
        float Radius = 0.0;

        Sphere(const glm::vec3 &c, float r);

        bool contains(const glm::vec3 &point) const;
        bool contains(const Triangle3D &triangle) const;
    };

}

