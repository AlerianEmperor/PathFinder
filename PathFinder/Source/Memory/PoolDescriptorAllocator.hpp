#pragma once

#include "Pool.hpp"
#include "Ring.hpp"

#include "../HardwareAbstractionLayer/DescriptorHeap.hpp"
#include "../HardwareAbstractionLayer/Buffer.hpp"
#include "../HardwareAbstractionLayer/Texture.hpp"

#include <memory>
#include <functional>
#include <list>

namespace Memory
{
   
    class PoolDescriptorAllocator
    {
    public:
        PoolDescriptorAllocator(const HAL::Device* device, uint8_t simultaneousFramesInFlight);

        template <class DescriptorT>
        using DescriptorPtr = std::unique_ptr<DescriptorT, std::function<void(DescriptorT*)>>;

        using RTDescriptorPtr = DescriptorPtr<HAL::RTDescriptor>;
        using DSDescriptorPtr = DescriptorPtr<HAL::DSDescriptor>;
        using SRDescriptorPtr = DescriptorPtr<HAL::SRDescriptor>;
        using UADescriptorPtr = DescriptorPtr<HAL::UADescriptor>;
        using CBDescriptorPtr = DescriptorPtr<HAL::CBDescriptor>;

        RTDescriptorPtr AllocateRTDescriptor(const HAL::Texture* texture, std::optional<HAL::ColorFormat> shaderVisibleFormat = std::nullopt);
        DSDescriptorPtr AllocateDSDescriptor(const HAL::Texture* texture);
        SRDescriptorPtr AllocateSRDescriptor(const HAL::Texture* texture, std::optional<HAL::ColorFormat> shaderVisibleFormat = std::nullopt);
        UADescriptorPtr AllocateUADescriptor(const HAL::Texture* texture, std::optional<HAL::ColorFormat> shaderVisibleFormat = std::nullopt);

        SRDescriptorPtr AllocateSRDescriptor(const HAL::Buffer* buffer, uint64_t stride);
        UADescriptorPtr AllocateUADescriptor(const HAL::Buffer* buffer, uint64_t stride);
        CBDescriptorPtr AllocateCBDescriptor(const HAL::Buffer* buffer, uint64_t stride);
        
    private:
        template <class DescriptorT>
        struct Allocation
        {
            DescriptorT Descriptor;
            Pool<>::SlotType Slot;

            Allocation(const DescriptorT& descriptor, const Pool<>::SlotType& slot)
                : Descriptor{ descriptor }, Slot{ slot } {}
        };

        void ValidateRTFormatsCompatibility(HAL::ResourceFormat::FormatVariant textureFormat, std::optional<HAL::ColorFormat> shaderVisibleFormat);
        void ValidateSRUAFormatsCompatibility(HAL::ResourceFormat::FormatVariant textureFormat, std::optional<HAL::ColorFormat> shaderVisibleFormat);

        uint64_t mDescriptorRangeCapacity = 5000;

        HAL::CBSRUADescriptorHeap mCBSRUADescriptorHeap;
        HAL::RTDescriptorHeap mRTDescriptorHeap;
        HAL::DSDescriptorHeap mDSDescriptorHeap;

        Ring mRingFrameTracker;

        Pool<> mRTPool;
        Pool<> mDSPool;
        Pool<> mSRPool;
        Pool<> mUAPool;
        Pool<> mCBPool;

        std::list<Allocation<HAL::RTDescriptor>> mAllocatedRTDescriptors;
        std::list<Allocation<HAL::DSDescriptor>> mAllocatedDSDescriptors;
        std::list<Allocation<HAL::SRDescriptor>> mAllocatedSRDescriptors;
        std::list<Allocation<HAL::UADescriptor>> mAllocatedUADescriptors;
        std::list<Allocation<HAL::CBDescriptor>> mAllocatedCBDescriptors;

        //std::vector<std::vector>
    };

}
