#pragma once

#include "ViewController.hpp"
#include "LuminanceMeterViewController.hpp"
#include "RenderGraphViewController.hpp"
#include "ProfilerViewController.hpp"
#include "RenderPipelineViewController.hpp"
#include "GPUDataInspectorViewController.hpp"
#include "TextureViewerViewController.hpp"

namespace PathFinder
{
   
    class MainMenuViewController : public ViewController
    {
    public:
        void Draw() override;

    private:
        void DrawFileMenu();
        void DrawWindowMenu();

        std::shared_ptr<LuminanceMeterViewController> mLuminanceMeterVC;
        std::shared_ptr<RenderGraphViewController> mRenderGraphVC;
        std::shared_ptr<ProfilerViewController> mProfilerVC;
        std::shared_ptr<RenderPipelineViewController> mRenderPipelineVC;
        std::shared_ptr<GPUDataInspectorViewController> mGPUDataInspectorVC;
        std::shared_ptr<TextureViewerViewController> mTextureViewerVC;
    };

}
