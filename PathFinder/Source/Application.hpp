#pragma once

#include <Scene/Scene.hpp>
#include <Scene/CameraInteractor.hpp>
#include <UI/UIManager.hpp>
#include <UI/UIEntryPoint.hpp>
#include <RenderPipeline/RenderEngine.hpp>
#include <RenderPipeline/RenderSettings.hpp>
#include <RenderPipeline/RenderPassContentMediator.hpp>
#include <IO/Input.hpp>
#include <IO/CommandLineParser.hpp>
#include <IO/InputHandlerWindows.hpp>
#include <Utility/DisplaySettingsController.hpp>

#include "RenderPipeline/RenderPasses/GBufferRenderPass.hpp"
#include "RenderPipeline/RenderPasses/BackBufferOutputPass.hpp"
#include "RenderPipeline/RenderPasses/RngSeedGenerationRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DeferredLightingRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DeferredShadowsRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserPreBlurRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserMipGenerationRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserReprojectionRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserGradientSamplesGenerationRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserGradientConstructionRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserGradientFilteringRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserHistoryFixRenderPass.hpp"
#include "RenderPipeline/RenderPasses/TAARenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserPostBlurRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DenoiserMainRenderPass.hpp"
#include "RenderPipeline/RenderPasses/SMAAEdgeDetectionRenderPass.hpp"
#include "RenderPipeline/RenderPasses/SMAABlendingWeightCalculationRenderPass.hpp"
#include "RenderPipeline/RenderPasses/SMAANeighborhoodBlendingRenderPass.hpp"
#include "RenderPipeline/RenderPasses/ToneMappingRenderPass.hpp"
#include "RenderPipeline/RenderPasses/DisplacementDistanceMapRenderPass.hpp"
#include "RenderPipeline/RenderPasses/UIRenderPass.hpp"
#include "RenderPipeline/RenderPasses/CommonSetupRenderPass.hpp"
#include "RenderPipeline/RenderPasses/BloomBlurRenderPass.hpp"
#include "RenderPipeline/RenderPasses/BloomCompositionRenderPass.hpp"
#include "RenderPipeline/RenderPasses/GeometryPickingRenderPass.hpp"
#include "RenderPipeline/RenderPasses/GIRayTracingRenderPass.hpp"
#include "RenderPipeline/RenderPasses/GIProbeUpdateRenderPass.hpp"
#include "RenderPipeline/RenderPasses/GIDebugRenderPass.hpp"
#include "RenderPipeline/RenderPasses/SkyGenerationRenderPass.hpp"
#include "RenderPipeline/GlobalRootConstants.hpp"
#include "RenderPipeline/PerFrameRootConstants.hpp"
#include "RenderPipeline/RenderPassContentMediator.hpp"

#include <Scene/ThirdPartySceneLoader.hpp>
#include <Scene/MaterialLoader.hpp>
#include <choreograph/Choreograph.h>

namespace PathFinder
{
   
    class Application
    {
    public:
        Application(int argc, char** argv);

        void RunMessageLoop();

    private:
        void CreateEngineWindow();
        void DestroyEngineWindow();
        void InjectRenderPasses();
        void PerformPreRenderActions();
        void PerformPostRenderActions();
        void LoadSpheres();
        void LoadSponza();

        HWND mWindowHandle;
        WNDCLASSEX mWindowClass;

        std::unique_ptr<CommandLineParser> mCmdLineParser;
        std::unique_ptr<RenderEngine<RenderPassContentMediator>> mRenderEngine;
        std::unique_ptr<Scene> mScene;
        std::unique_ptr<Input> mInput;
        std::unique_ptr<RenderSettingsController> mSettingsController;
        std::unique_ptr<InputHandlerWindows> mWindowsInputHandler;
        std::unique_ptr<UIManager> mUIManager;
        std::unique_ptr<UIEntryPoint> mUIEntryPoint;
        std::unique_ptr<UIDependencies> mUIDependencies;
        std::unique_ptr<CameraInteractor> mCameraInteractor;
        std::unique_ptr<DisplaySettingsController> mDisplaySettingsController;
        std::unique_ptr<RenderPassContentMediator> mContentMediator;

        CommonSetupRenderPass mCommonSetupPass;
        GBufferRenderPass mGBufferPass;
        RngSeedGenerationRenderPass mRgnSeedGenerationPass;
        DeferredLightingRenderPass mDeferredLightingPass;
        DeferredShadowsRenderPass mDeferredShadowsPass;
        DenoiserPreBlurRenderPass mDenoiserPreBlurPass;
        DenoiserMipGenerationRenderPass mDenoiserMipGenerationPass;
        DenoiserReprojectionRenderPass mReprojectionPass;
        DenoiserGradientConstructionRenderPass mDenoiserGradientConstructionPass;
        DenoiserGradientFilteringRenderPass mDenoiserGradientFilteringPass;
        DenoiserGradientSamplesGenerationRenderPass mDenoiserForwardProjectionPass;
        DenoiserHistoryFixRenderPass mDenoiserHistoryFixPass;
        TAARenderPass mTAARenderPass;
        DenoiserPostBlurRenderPass mDenoiserPostBlurPass;
        DenoiserMainRenderPass mDenoiserMainPass;
        BloomBlurRenderPass mBloomBlurPass;
        BloomCompositionRenderPass mBloomCompositionPass;
        ToneMappingRenderPass mToneMappingPass;
        SMAAEdgeDetectionRenderPass mSMAAEdgeDetectionPass;
        SMAABlendingWeightCalculationRenderPass mSMAABlendingWeightCalculationPass;
        SMAANeighborhoodBlendingRenderPass mSMAANeighborhoodBlendingPass;
        BackBufferOutputPass mBackBufferOutputPass;
        UIRenderPass mUIPass;
        GeometryPickingRenderPass mGeometryPickingPass;
        GIRayTracingRenderPass mGIRayTracingPass;
        GIProbeUpdateRenderPass mGIProbeUpdatePass;
        GIDebugRenderPass mGIDebugPass;
        SkyGenerationRenderPass mSkyGenerationPass;

        GlobalRootConstants mGlobalConstants;
        PerFrameRootConstants mPerFrameConstants;

        // Temporary to load demo scene
        std::unique_ptr<MaterialLoader> mMaterialLoader;
        choreograph::Timeline mAnimationTimeline;
    };

}
