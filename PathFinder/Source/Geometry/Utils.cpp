#include "Utils.hpp"

namespace Geometry
{

    float Snap(float value, float snap)
    {
        if (snap <= FLT_EPSILON)
            return value;

        float modulo = fmodf(value, snap);
        float moduloRatio = fabsf(modulo) / snap;
        float snapTension = 0.5;

        if (moduloRatio < snapTension)
        {
            return value - modulo;
        }
        else if (moduloRatio > (1.f - snapTension))
        {
            return value - modulo + snap * ((value < 0.f) ? -1.f : 1.f);
        }
        else
        {
            return value;
        }
    }

    glm::vec3 Snap(const glm::vec3& value, const glm::vec3& snap)
    {
        glm::vec3 result{};

        for (auto i = 0; i < 3; ++i)
            result[i] = Snap(value[i], snap[i]);

        return result;
    }

    glm::mat3 OrientationMatrix(const glm::vec3& direction)
    {
        glm::vec3 up = glm::abs(glm::dot(direction, glm::vec3{ 0.0, 1.0, 0.0 })) < 0.99 ?
            glm::vec3{ 0.0, 1.0, 0.0 } : glm::vec3{ 0.0, 0.0, 1.0 };

        glm::vec3 f(normalize(direction));
        glm::vec3 s(normalize(cross(up, f)));
        glm::vec3 u(cross(f, s));

        return glm::mat3{ s,u,f };
    }

    AABB GetCircumscribedAABBForSphere(const Sphere& sphere)
    {
        AABB aabb{ sphere.Center - sphere.Radius, sphere.Center + sphere.Radius };
        return aabb;
    }

    Sphere GetCircumscribedSphereForAABB(const AABB& aabb)
    {
        Sphere sphere{ (aabb.GetMin() + aabb.GetMax()) * 0.5f, glm::length(aabb.GetMax() - aabb.GetMin()) * 0.5f };
        return sphere;
    }

}
