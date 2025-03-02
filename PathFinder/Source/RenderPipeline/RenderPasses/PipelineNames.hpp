#pragma once

#include <Foundation/Name.hpp>

#include <array>

namespace PathFinder
{

    template <size_t Count>
    using NameArray = std::array<Foundation::Name, Count>;

    namespace ResourceNames
    {
        inline Foundation::Name JumpFloodingConesIndirection0{ "Resource_JumpFloodingConesIndirection0" };
        inline Foundation::Name JumpFloodingConesIndirection1{ "Resource_JumpFloodingConesIndirection1" };
        inline Foundation::Name JumpFloodingCones0{ "Resource_JumpFloodingConesBuffer0" };
        inline Foundation::Name JumpFloodingCones1{ "Resource_JumpFloodingConesBuffer1" };
        inline Foundation::Name UAVCounterBuffer{ "Resource_UAVCounterBuffer" };

        // Normal GBuffer Textures
        inline NameArray<2> GBufferAlbedoMetalness{ "Resource_GBuffer_Albedo_Metalness[0]", "Resource_GBuffer_Albedo_Metalness[1]" };
        inline NameArray<2> GBufferNormalRoughness{ "Resource_GBuffer_Normal_Roughness[0]", "Resource_GBuffer_Normal_Roughness[1]" };
        inline Foundation::Name GBufferMotionVector{ "Resource_GBuffer_Motion_Vector" };
        inline Foundation::Name GBufferTypeAndMaterialIndex{ "Resource_GBuffer_Type_And_Material_Index" };
        inline Foundation::Name GBufferDepthStencil{ "Resource_GBuffer_Depth_Stencil" };
        inline NameArray<2> GBufferViewDepth{ "Resource_GBuffer_View_Depth[0]", "Resource_GBuffer_View_Depth[1]" };

        // Patched for denoiser gradient detection
        inline Foundation::Name GBufferAlbedoMetalnessPatched{ "Resource_GBuffer_Albedo_Metalness_Patched" };
        inline Foundation::Name GBufferNormalRoughnessPatched{ "Resource_GBuffer_Normal_Roughness_Patched" };
        inline Foundation::Name GBufferViewDepthPatched{ "Resource_GBuffer_View_Depth_Patched" };

        inline Foundation::Name ShadingAnalyticOutput{ "Resource_Shading_Analytic_Output" };

        inline Foundation::Name DeferredLightingRayPDFs{ "Resource_Deferred_Lighting_Ray_PDFs" };
        inline Foundation::Name DeferredLightingRayLightIntersectionPoints{ "Resource_Deferred_Lighting_Ray_Light_Intersection_Points" };
        inline Foundation::Name DeferredLightingRayLuminances{ "Resource_Deferred_Lighting_Ray_Luminances" };
        inline Foundation::Name StochasticUnshadowedShadingOutput{ "Resource_Shading_Stochastic_Unshadowed_Output" };
        inline NameArray<2> StochasticShadowedShadingOutput{ "Resource_Shading_Stochastic_Shadowed_Output[0]", "Resource_Shading_Stochastic_Shadowed_Output[1]" };
        inline Foundation::Name StochasticUnshadowedShadingPreBlurred{ "Resource_Shading_Stochastic_Unshadowed_Pre_Blurred" };
        inline Foundation::Name StochasticShadowedShadingPreBlurred{ "Resource_Shading_Stochastic_Shadowed_Pre_Blurred" };
        inline Foundation::Name StochasticUnshadowedShadingFixed{ "Resource_Shading_Stochastic_Unshadowed_Fixed" };
        inline Foundation::Name StochasticShadowedShadingFixed{ "Resource_Shading_Stochastic_Shadowed_Fixed" };
        inline Foundation::Name StochasticUnshadowedShadingReprojected{ "Resource_Shading_Stochastic_Unshadowed_Reprojected_History" };
        inline Foundation::Name StochasticShadowedShadingReprojected{ "Resource_Shading_Stochastic_Shadowed_Reprojected_History" };
        inline NameArray<2> StochasticUnshadowedShadingDenoised{ "Resource_Shading_Stochastic_Unshadowed_Denoised[0]", "Resource_Shading_Stochastic_Unshadowed_Denoised[1]" };
        inline NameArray<2> StochasticShadowedShadingDenoised{ "Resource_Shading_Stochastic_Shadowed_Denoised[0]", "Resource_Shading_Stochastic_Shadowed_Denoised[1]" };
        inline Foundation::Name StochasticUnshadowedShadingDenoisedStabilized{ "Resource_Shading_Stochastic_Unshadowed_Denoised_Stabilized" };
        inline Foundation::Name StochasticShadowedShadingDenoisedStabilized{ "Resource_Shading_Stochastic_Shadowed_Post_Blurred" };
        inline Foundation::Name StochasticUnshadowedShadingPostBlurred{ "Resource_Shading_Stochastic_Unshadowed_Post_Blurred" };
        inline Foundation::Name StochasticShadowedShadingPostBlurred{ "Resource_Shading_Stochastic_Shadowed_Post_Blurred" };
        inline Foundation::Name CombinedShading{ "Resource_Shading_Combined" };
        inline Foundation::Name CombinedShadingOversaturated{ "Resource_Shading_Combined_Oversaturated" };
        inline Foundation::Name DenoiserGradientSamples{ "Resource_Denoiser_Gradient_Samples" };
        inline Foundation::Name DenoiserGradient{ "Resource_Denoiser_Gradient" };
        inline Foundation::Name DenoiserSecondaryGradient{ "Resource_Denoiser_Secondary_Gradient" };
        inline Foundation::Name DenoiserGradientFiltered{ "Resource_Denoiser_Gradient_Filtered" };
        inline Foundation::Name DenoiserGradientFilteredIntermediate{ "Resource_Denoiser_Gradient_Filtered_Intermediate" };
        inline NameArray<2> RngSeeds{ "Resource_Stochastic_Rng_Seeds[0]", "Resource_Stochastic_Rng_Seeds[1]" };
        inline Foundation::Name RngSeedsCorrelated{ "Resource_Stochastic_Rng_Seeds_Correlated" };
        inline Foundation::Name DenoiserGradientSampleCandidates{ "Resource_Denoised_Gradient_Sample_Candidates" };
        inline NameArray<2> DenoiserGradientSamplePositions{ "Resource_Denoiser_Gradient_Sample_Positions[0]", "Resource_Denoiser_Gradient_Sample_Positions[1]" };
        inline Foundation::Name DenoisedPreBlurIntermediate{ "Resource_Denoised_Pre_Blur_Intermediate" };
        inline NameArray<2> ReprojectedFramesCount{ "Resource_Reprojected_Frames_Count[0]", "Resource_Reprojected_Frames_Count[1]" };
        // Patched during denoising if denoiser decides that additional history dropping conditions were met
        inline Foundation::Name ReprojectedFramesCountPatched{ "Resource_Reprojected_Frames_Count_Patched" };
        inline Foundation::Name DenoisedCombinedDirectShading{ "Resource_Denoised_Combined_Direct_Shading" };
        inline Foundation::Name DenoisedReprojectedTexelIndices{ "Resource_Denoised_Reprojected_Texel_Indices" };
        inline Foundation::Name BloomBlurIntermediate{ "Resource_Bloom_Blur_Intermediate" };
        inline Foundation::Name BloomBlurOutput{ "Resource_Bloom_Blur_Output" };
        inline Foundation::Name BloomCompositionOutput{ "Resource_Bloom_Composition_Output" };
        inline Foundation::Name SkyLuminance{ "Resource_Sky_Luminance" };
        inline Foundation::Name LuminanceHistogram{ "Resource_Luminance_Histogram" };
        inline Foundation::Name ToneMappingOutput{ "Resource_ToneMapping_Output" };
        inline Foundation::Name UIOutput{ "Resource_UI_Output" };
        inline NameArray<2> TAAOutput{ "Resource_TAA_Output[0]", "Resource_TAA_Output[1]" };

        inline Foundation::Name GIRayHitInfo{ "Resource_GI_Ray_Hit_Info" };
        inline NameArray<2> GIIlluminanceProbeAtlas{ "Resource_GI_Illuminance_Probe_Atlas[0]", "Resource_GI_Illuminance_Probe_Atlas[1]" };
        inline NameArray<2> GIDepthProbeAtlas{ "Resource_GI_Depth_Probe_Atlas[0]", "Resource_GI_Depth_Probe_Atlas[1]" };
        inline Foundation::Name GIDebugDepthStencil{ "Resource_GI_Debug_Depth_Stencil" };
        inline Foundation::Name GIDebugOutput{ "Resource_GI_Debug_Output" };

        inline Foundation::Name SMAADetectedEdges{ "Resource_SMAA_Detected_Edges" };
        inline Foundation::Name SMAABlendingWeights{ "Resource_SMAA_Blending_Weights" };
        inline Foundation::Name SMAAAntialiased{ "Resource_SMAA_Antialiased_Image" };

        inline Foundation::Name PickedGeometryInfo{ "Resource_Picked_Geometry_Info" };
    }

    namespace PSONames
    {
        inline Foundation::Name DistanceMapHelperInitialization{ "PSO_DistanceMapHelperInitialization" };
        inline Foundation::Name DistanceMapHelperCompression{ "PSO_DistanceMapHelperCompression" };
        inline Foundation::Name DistanceMapGeneration{ "PSO_DistanceMapGeneration" };
        inline Foundation::Name Downsampling{ "PSO_AveragingDownsampling" };
        inline Foundation::Name SkyGeneration{ "PSO_SkyGeneration" };
        inline Foundation::Name DepthOnly{ "PSO_DepthOnly" };
        inline Foundation::Name GBufferMeshes{ "PSO_GBufferMeshes" };
        inline Foundation::Name GBufferLights{ "PSO_GBufferLights" };
        inline Foundation::Name DeferredLighting{ "PSO_Deferred_Lighting" };
        inline Foundation::Name DeferredShadows{ "PSO_Deferred_Shadows" };
        inline Foundation::Name GIRayTracing{ "PSO_GI_Ray_Tracing" };
        inline Foundation::Name GIProbeUpdate{ "PSO_GI_Probe_Update" };
        inline Foundation::Name GIProbeIndirectionTableUpdate{ "PSO_GI_Probe_Indirection_Table_Update" };
        inline Foundation::Name GIIlluminanceProbeCornerUpdate{ "PSO_GI_Illuminance_Probe_Corner_Update" };
        inline Foundation::Name GIDepthProbeCornerUpdate{ "PSO_GI_Depth_Probe_Corner_Update" };
        inline Foundation::Name GIIlluminanceProbeBorderUpdate{ "PSO_GI_Illuminance_Probe_Border_Update" };
        inline Foundation::Name GIDepthProbeBorderUpdate{ "PSO_GI_Depth_Probe_Border_Update" };
        inline Foundation::Name GIProbeDebug{ "PSO_GI_Probe_Debug" };
        inline Foundation::Name GIRaysDebug{ "PSO_GI_Rays_Debug" };
        inline Foundation::Name GeometryPicking{ "PSO_GeometryPicking" };
        inline Foundation::Name SeparableBlur{ "PSO_SeparableBlur" };
        inline Foundation::Name BloomBlur{ "PSO_BloomBlur" };
        inline Foundation::Name BloomComposition{ "PSO_BloomComposition" };
        inline Foundation::Name ToneMapping{ "PSO_ToneMapping" };
        inline Foundation::Name RngSeedGeneration{ "PSO_RngSeedGeneration" };
        inline Foundation::Name DenoiserGradientSamplesGeneration{ "PSO_DenoiserGradientSamplesGeneration" };
        inline Foundation::Name DenoiserReprojection{ "PSO_DenoiserReprojection" };
        inline Foundation::Name DenoiserHistoryFix{ "PSO_DenoiserHistoryFix" };
        inline Foundation::Name TAA{ "PSO_TAA" };
        inline Foundation::Name DenoiserPostBlur{ "PSO_DenoiserPostBlur" };
        inline Foundation::Name DenoiserGradientConstruction{ "PSO_DenoiserGradientConstruction" };
        inline Foundation::Name DenoiserGradientFiltering{ "PSO_DenoiserGradientFiltering" };
        inline Foundation::Name DenoiserMainPass{ "PSO_DenoiserMainPass" };
        inline Foundation::Name SMAAEdgeDetection{ "PSO_SMAAEdgeDetection" };
        inline Foundation::Name SMAABlendingWeightCalculation{ "PSO_SMAABlendingWeightCalculation" };
        inline Foundation::Name SMAANeighborhoodBlending{ "PSO_SMAANeighborhoodBlending" };
        inline Foundation::Name UI{ "PSO_UI" };
        inline Foundation::Name SDRBackBufferOutput{ "PSO_SDRBackBufferOutput" };
        inline Foundation::Name HDRBackBufferOutput{ "PSO_HDRBackBufferOutput" };
        inline Foundation::Name UAVClear{ "PSO_UAVClear" };
        inline Foundation::Name BoxBlur{ "PSO_BoxBlur" };
    }  
   
    namespace RootSignatureNames
    {
        inline Foundation::Name UAVClear{ "UAVClear_Root_Sig" };
        inline Foundation::Name GBufferMeshes{ "GBuffer_Meshes_Root_Sig" };
        inline Foundation::Name GBufferLights{ "GBuffer_Lights_Root_Sig" };
        inline Foundation::Name ShadingCommon{ "Shading_Common_Root_Sig" };
        inline Foundation::Name GIRayTracing{ "GI_Ray_Tracing_Root_Sig" };
        inline Foundation::Name ToneMapping{ "Tone_Mapping_Root_Sig" };
        inline Foundation::Name GeometryPicking{ "Geometry_Picking_Root_Sig" };
        inline Foundation::Name UI{ "UI_Root_Sig" };
        inline Foundation::Name DisplacementDistanceMapGeneration{ "Distance_Map_Generation_Root_Sig" };
    }

    namespace SamplerNames
    {
        inline Foundation::Name AnisotropicClamp{ "Sampler_Anisotropic_Clamp" };
        inline Foundation::Name AnisotropicWrap{ "Sampler_Anisotropic_Wrap" };
        inline Foundation::Name AnisotropicMirror{ "Sampler_Anisotropic_Mirror" };
        inline Foundation::Name LinearClamp{ "Sampler_Linear_Clamp" };
        inline Foundation::Name PointClamp{ "Sampler_Point_Clamp" };
        inline Foundation::Name Minimim{ "Sampler_Minimum" };
        inline Foundation::Name Maximum{ "Sampler_Maximum" };
    }

}
