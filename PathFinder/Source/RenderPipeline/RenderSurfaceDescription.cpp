#include "RenderSurfaceDescription.hpp"

namespace PathFinder
{

    RenderSurfaceDescription::RenderSurfaceDescription(const Geometry::Dimensions& dimensions, HAL::ColorFormat rtFormat, HAL::DepthStencilFormat dsFormat)
        : mDimensions(dimensions), mRTFormat(rtFormat), mDSFormat(dsFormat) {}

    glm::uvec2 RenderSurfaceDescription::DispatchDimensionsForGroupSize(uint32_t groupSizeX, uint32_t groupSizeY) const
    {
        float x = ceilf((float)mDimensions.Width / groupSizeX);
        float y = ceilf((float)mDimensions.Height / groupSizeY);
        return { x, y };
    }

}
