#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <chrono>

#include <HardwareAbstractionLayer/Device.hpp>
#include <HardwareAbstractionLayer/SwapChain.hpp>
#include <HardwareAbstractionLayer/DisplayAdapterFetcher.hpp>

#include <Scene/Scene.hpp>
#include <Foundation/Event.hpp>
#include <IO/CommandLineParser.hpp>
#include <Utility/AftermathCrashTracker.hpp>

#include <Memory/SegregatedPoolsResourceAllocator.hpp>
#include <Memory/PoolDescriptorAllocator.hpp>
#include <Memory/ResourceStateTracker.hpp>
#include <Memory/GPUResourceProducer.hpp>
#include <Memory/CopyRequestManager.hpp>

#include "RenderPassMediators/ResourceScheduler.hpp"
#include "RenderPassMediators/RootConstantsUpdater.hpp"
#include "RenderPassMediators/PipelineStateCreator.hpp"
#include "RenderPassMediators/RootSignatureCreator.hpp"
#include "RenderPassMediators/CommandRecorder.hpp"
#include "RenderPassMediators/SubPassScheduler.hpp"
#include "RenderPassMediators/SamplerCreator.hpp"
#include "RenderPassMediators/RenderPassUtilityProvider.hpp"

#include "PipelineResourceStorage.hpp"
#include "RenderDevice.hpp"
#include "ShaderManager.hpp"
#include "PipelineStateManager.hpp"
#include "RenderContext.hpp"
#include "RenderPassGraph.hpp"
#include "BottomRTAS.hpp"
#include "TopRTAS.hpp"
#include "GPUProfiler.hpp"
#include "GPUDataInspector.hpp"
#include "FrameFence.hpp"
#include "PipelineSettings.hpp"

namespace PathFinder
{
    template <class ContentMediator>
    class RenderPass;

    template <class ContentMediator>
    class RenderEngine
    {
    public:
        using Event = Foundation::Event<RenderEngine<ContentMediator>, std::string, void()>;

        RenderEngine(HWND windowHandle, const CommandLineParser& commandLineParser);

        void AddRenderPass(RenderPass<ContentMediator>* pass);

        void Render();
        void FlushAllQueuedFrames();

        void AddBottomRayTracingAccelerationStructure(const BottomRTAS* bottomRTAS);
        void AddTopRayTracingAccelerationStructure(const TopRTAS* topRTAS);

        void SetContentMediator(ContentMediator* mediator);

        template <class Constants>
        void SetGlobalRootConstants(const Constants& constants);

        template <class Constants>
        void SetFrameRootConstants(const Constants& constants);

    private:
        void NotifyStartFrame(uint64_t newFrameNumber);
        void NotifyEndFrame(uint64_t completedFrameNumber);
        void MoveToNextFrame();
        void PerformPreRenderUploads();
        void BuildAccelerationStructures();
        void RecordCommandLists();
        void ScheduleFrame();
        void UpdateBackBuffers();

        RenderPassGraph mRenderPassGraph;

        uint8_t mCurrentBackBufferIndex = 0;
        uint8_t mSimultaneousFramesInFlight = 2;
        uint64_t mFrameNumber = 0;
        std::chrono::time_point<std::chrono::steady_clock> mFrameStartTimestamp;
        std::chrono::microseconds mFrameDuration = std::chrono::microseconds::zero();

        RenderSurfaceDescription mRenderSurfaceDescription;
        HAL::DisplayAdapterFetcher mAdapterFetcher;

        std::unique_ptr<HAL::Device> mDevice;

        std::unique_ptr<Memory::SegregatedPoolsResourceAllocator> mResourceAllocator;
        std::unique_ptr<Memory::PoolCommandListAllocator> mCommandListAllocator;
        std::unique_ptr<Memory::PoolDescriptorAllocator> mDescriptorAllocator;
        std::unique_ptr<Memory::ResourceStateTracker> mResourceStateTracker;
        std::unique_ptr<Memory::CopyRequestManager> mCopyRequestManager;
        std::unique_ptr<Memory::GPUResourceProducer> mResourceProducer;

        std::unique_ptr<AftermathCrashTracker> mAftermathCrashTracker;
        std::unique_ptr<RenderPassUtilityProvider> mPassUtilityProvider;
        std::unique_ptr<PipelineResourceStorage> mPipelineResourceStorage;
        std::unique_ptr<ResourceScheduler<ContentMediator>> mResourceScheduler;
        std::unique_ptr<SamplerCreator> mSamplerCreator;
        std::unique_ptr<SubPassScheduler<ContentMediator>> mSubPassScheduler;
        std::unique_ptr<ShaderManager> mShaderManager;
        std::unique_ptr<PipelineStateManager> mPipelineStateManager;
        std::unique_ptr<PipelineStateCreator> mPipelineStateCreator;
        std::unique_ptr<RootSignatureCreator> mRootSignatureCreator;
        std::unique_ptr<RenderDevice> mRenderDevice;
        std::unique_ptr<RenderPassContainer<ContentMediator>> mRenderPassContainer;
        std::unique_ptr<GPUProfiler> mGPUProfiler;
        std::unique_ptr<GPUDataInspector> mGPUDataInspector;

        std::unique_ptr<HAL::SwapChain> mSwapChain;
        std::unique_ptr<FrameFence> mFrameFence;

        HAL::DisplayAdapter* mSelectedAdapter = nullptr;
        ContentMediator* mContentMediator = nullptr;
        PipelineSettings mPipelineSettings;

        Event mPreRenderEvent;
        Event mPostRenderEvent;

        std::vector<const TopRTAS*> mTopRTASes;
        std::vector<const BottomRTAS*> mBottomRTASes;
        std::vector<Memory::GPUResourceProducer::TexturePtr> mBackBuffers;

    public:
        inline PipelineResourceStorage* ResourceStorage() { return mPipelineResourceStorage.get(); }
        inline const RenderSurfaceDescription& RenderSurface() const { return mRenderSurfaceDescription; }
        inline Memory::GPUResourceProducer* ResourceProducer() { return mResourceProducer.get(); }
        inline const RenderDevice* RendererDevice() const { return mRenderDevice.get(); }
        inline const GPUDataInspector* GPUInspector() const { return mGPUDataInspector.get(); }
        inline const RenderPassGraph* RenderGraph() const { return &mRenderPassGraph; }
        inline HAL::Device* Device() { return mDevice.get(); }
        inline HAL::SwapChain* SwapChain() { return mSwapChain.get(); }
        inline HAL::DisplayAdapter* SelectedAdapter() { return mSelectedAdapter; }
        inline Event& PreRenderEvent() { return mPreRenderEvent; }
        inline Event& PostRenderEvent() { return mPostRenderEvent; }
        inline uint64_t FrameDurationUS() const { return mFrameDuration.count(); }
        inline uint64_t FrameNumber() const { return mFrameNumber; }
        inline PipelineSettings& Settings() { return mPipelineSettings; }
    };

}

#include "RenderEngine.inl"
