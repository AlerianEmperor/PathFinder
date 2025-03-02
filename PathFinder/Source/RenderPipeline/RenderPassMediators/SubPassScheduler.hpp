#pragma once

#include "RenderPassUtilityProvider.hpp"
#include "PipelineResourceStorage.hpp"

#include <Foundation/Name.hpp>

namespace PathFinder
{

    template <class ContentMediator>
    class RenderPassContainer;

    template <class ContentMediator>
    class RenderSubPass;

    template <class ContentMediator>
    class SubPassScheduler
    {
    public:
        SubPassScheduler(RenderPassContainer<ContentMediator>* passContainer, const PipelineResourceStorage* resourceStorage, const RenderPassUtilityProvider* utilityProvider);

        void AddRenderSubPass(RenderSubPass<ContentMediator>* pass);
        void SetContent(const ContentMediator* content);

        const HAL::TextureProperties& GetTextureProperties(Foundation::Name textureName) const;
        const HAL::BufferProperties& GetBufferProperties(Foundation::Name bufferName) const;

    private:
        const PipelineResourceStorage* mResourceStorage;
        const RenderPassUtilityProvider* mUtilityProvider;
        const ContentMediator* mContent = nullptr;
        RenderPassContainer<ContentMediator>* mPassContainer;

    public:
        inline const RenderSurfaceDescription& GetDefaultRenderSurfaceDesc() const { return mUtilityProvider->DefaultRenderSurfaceDescription; }
        inline auto FrameNumber() const { return mUtilityProvider->FrameNumber; }
        inline const ContentMediator* Content() const { return mContent; }
    };

}

#include "RenderPassContainer.hpp"
#include "SubPassScheduler.inl"