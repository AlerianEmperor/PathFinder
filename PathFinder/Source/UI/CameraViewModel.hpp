#pragma once

#include "ViewModel.hpp"

#include <Scene/Camera.hpp>

namespace PathFinder
{
   
    class CameraViewModel : public ViewModel
    {
    public:
        void Import() override;
        void Export() override;

        float FOVH = 0.0;
        FStop LenseAperture;
        ISO FilmSpeed;
        float ShutterTime;
        glm::mat4 View;
        glm::mat4 Projection;

    private:
        Camera* mCamera = nullptr;

    public:
        const glm::vec3& CameraPosition() const { return mCamera->GetPosition(); }
        const glm::vec3& CameraDirection() const { return mCamera->GetFront(); }
    };

}
