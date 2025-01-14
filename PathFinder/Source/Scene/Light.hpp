#pragma once

#include <Foundation/Color.hpp>
#include <glm/mat4x4.hpp>

#include "VertexStorageLocation.hpp"

namespace PathFinder 
{
    using Lumen = float;
    using Nit = float;
    using Kelvin = float;
    using Candela = float;

    // Maximum spectral luminous efficacy of radiation for photoscopic vision
    // and its value is based on the definition of candela[Wikb] which is the SI unit for luminous intensity measurement. 
    // Its definition is: one candela is the luminous intensity, in a given direction, of a source
    // that emits monochromatic radiation at a frequency of 540THz(i.e a wavelength of 555nm) and whose
    // radiant intensity in that direction is 1 / 683 watts per steradian., meaning that Km = 683.
    inline static const float StandardLuminousEfficacy = 683;

    class Light
    {
    public:
        virtual ~Light() = 0;

        void SetColor(const Foundation::Color& color);
        void SetColorTemperature(Kelvin temperature);

        /// Sets Luminous Power a.k.a Luminous Flux.
        /// Measure of the perceived power of light.
        void SetLuminousPower(Lumen luminousPower);
        void SetPosition(const glm::vec3& position);

        void SetIndexInGPUTable(uint32_t index);
        void SetVertexStorageLocation(const VertexStorageLocation& location);

        void UpdatePreviousFrameValues();
        virtual void ConstructModelMatrix() = 0;

    protected:
        void SetArea(float area);

        glm::vec3 mPosition;
        glm::vec3 mPreviousPosition;
        glm::mat4 mModelMatrix;
        uint32_t mIndexInGPUTable = 0;

    private:
        Lumen mLuminousPower = 0.0;
        Nit mLuminance = 0.0;
        Nit mPreviousLuminance = 0.0;
        Foundation::Color mColor = Foundation::Color::White();
        float mArea = 0.0;
        float mPreviousArea = 0.0;
        VertexStorageLocation mVertexStorageLocation;

    public:
        inline const glm::vec3& GetPosition() const { return mPosition; }
        inline const glm::vec3& GetPreviousPosition() const { return mPreviousPosition; }
        inline float GetArea() const { return mArea; }
        inline float GetPreviousArea() const { return mPreviousArea; }
        inline Lumen GetLuminousPower() const { return mLuminousPower; }
        inline Nit GetLuminance() const { return mLuminance; }
        inline Nit GetPreviousLuminance() const { return mPreviousLuminance; }
        inline const Foundation::Color& GetColor() const { return mColor; }
        inline const glm::mat4& GetModelMatrix() const { return mModelMatrix; }
        inline auto GetIndexInGPUTable() const { return mIndexInGPUTable; }
        inline const VertexStorageLocation& GetLocationInVertexStorage() const { return mVertexStorageLocation; }
    };

}
