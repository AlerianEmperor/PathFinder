#pragma once

#include "../HardwareAbstractionLayer/Device.hpp"
#include "../HardwareAbstractionLayer/CommandQueue.hpp"
#include "../HardwareAbstractionLayer/RingBufferResource.hpp"
#include "../HardwareAbstractionLayer/ResourceBarrier.hpp"

#include "../Scene/Vertices/Vertex1P1N1UV1T1BT.hpp"
#include "../Scene/Vertices/Vertex1P1N1UV.hpp"
#include "../Scene/Vertices/Vertex1P3.hpp"

#include "VertexStorageLocation.hpp"
#include "VertexLayouts.hpp"
#include "CopyDevice.hpp"

#include <vector>
#include <memory>
#include <tuple>

#include <imgui/imgui.h>

namespace PathFinder
{

    class UIGPUStorage
    {
    public:
        UIGPUStorage(const HAL::Device* device, uint8_t simulataneousFrameCount);

        void BeginFrame(uint64_t frameFenceValue);
        void EndFrame(uint64_t completedFrameFenceValue);

        void UploadUIVertices();

    private:
        uint32_t GetVertexBufferPerFrameCapacity(const ImDrawData* drawData) const;
        uint32_t GetIndexBufferPerFrameCapacity(const ImDrawData* drawData) const;

        uint8_t mFrameCount = 0;
        uint32_t mLastFenceValue = 0;
        uint32_t mCurrentFrameIndex = 0;
        const HAL::Device* mDevice = nullptr;
        std::unique_ptr<HAL::RingBufferResource<ImDrawVert>> mVertexBuffer;
        std::unique_ptr<HAL::RingBufferResource<ImDrawIdx>> mIndexBuffer;
    };

}