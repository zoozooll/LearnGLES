//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_SCENEHELPER_H
#define LEARNGLES_SCENEHELPER_H

#include "Scene.h"
#include <string>
#include <memory>
#include <cstring>

// Basic
#include "basic/BasicGlesScene.h"
#include "basic/DepthTestingScene.h"
#include "basic/StencilTestingScene.h"
#include "basic/BlendingScene.h"
#include "basic/CubemapScene.h"
#include "basic/GeometryShaderScene.h"
#include "basic/TesselationShaderScene.h"
#include "basic/ComputeShaderScene.h"
#include "basic/InstanceScene.h"
#include "basic/AsteroidScene.h"
#include "basic/MsaaScene.h"
#include "basic/ModelScene.h"
#include "basic/SkeletalAnimationScene.h"
#include "basic/DebuggingScene.h"
#include "basic/TextRenderingScene.h"
#include "basic/FrustumCullingScene.h"

// Lighting
#include "lighting/BasicLightingScene.h"
#include "lighting/LightCasterScene.h"
#include "lighting/PhongVsBlinnScene.h"
#include "lighting/GammaCorrectionScene.h"
#include "lighting/MultiLightsScene.h"
#include "lighting/ShadowScene.h"
#include "lighting/HdrScene.h"
#include "lighting/BloomScene.h"
#include "lighting/SsaoScene.h"
#include "lighting/AreaLightsScene.h"
#include "lighting/PhysicallyBasedBloomScene.h"

// PBR
#include "pbr/NormalMappingScene.h"
#include "pbr/ParallaxMappingScene.h"
#include "pbr/PbrScene.h"
#include "pbr/PbrTextureScene.h"
#include "pbr/TheoryScene.h"
#include "pbr/IblScene.h"

// Advanced
#include "advanced/OitScene.h"
#include "advanced/SceneScene.h"
#include "advanced/CsmScene.h"
#include "advanced/DsaScene.h"


inline std::unique_ptr<Scene> GenSceneByName(const std::string& tutorial) {
    if (tutorial == "basic_gles") {
        return std::make_unique<BasicGlesScene>();
    } else if (tutorial == "depth_testing") {
        return std::make_unique<DepthTestingScene>();
    } else if (tutorial == "stencil_testing") {
        return std::make_unique<StencilTestingScene>();
    } else if (tutorial == "blending") {
        return std::make_unique<BlendingScene>();
    } else if (tutorial == "cubemap") {
        return std::make_unique<CubemapScene>();
    } else if (tutorial == "geometry_shader") {
        return std::make_unique<GeometryShaderScene>();
    } else if (tutorial == "tesselation_shader") {
        return std::make_unique<TesselationShaderScene>();
    } else if (tutorial == "compute_shader") {
        return std::make_unique<ComputeShaderScene>();
    } else if (tutorial == "instance") {
        return std::make_unique<InstanceScene>();
    } else if (tutorial == "asteroid") {
        return std::make_unique<AsteroidScene>();
    } else if (tutorial == "msaa") {
        return std::make_unique<MsaaScene>();
    } else if (tutorial == "model") {
        return std::make_unique<ModelScene>();
    } else if (tutorial == "skeletal_animation") {
        return std::make_unique<SkeletalAnimationScene>();
    } else if (tutorial == "debugging") {
        return std::make_unique<DebuggingScene>();
    } else if (tutorial == "text_rendering") {
        return std::make_unique<TextRenderingScene>();
    } else if (tutorial == "frustum_culling") {
        return std::make_unique<FrustumCullingScene>();
    } else if (tutorial == "basic_lighting") {
        return std::make_unique<BasicLightingScene>();
    } else if (tutorial == "light_caster") {
        return std::make_unique<LightCasterScene>();
    } else if (tutorial == "phong_vs_blinn") {
        return std::make_unique<PhongVsBlinnScene>();
    } else if (tutorial == "gamma_correction") {
        return std::make_unique<GammaCorrectionScene>();
    } else if (tutorial == "multi_lights") {
        return std::make_unique<MultiLightsScene>();
    } else if (tutorial == "shadow") {
        return std::make_unique<ShadowScene>();
    } else if (tutorial == "hdr") {
        return std::make_unique<HdrScene>();
    } else if (tutorial == "bloom") {
        return std::make_unique<BloomScene>();
    } else if (tutorial == "ssao") {
        return std::make_unique<SsaoScene>();
    } else if (tutorial == "area_lights") {
        return std::make_unique<AreaLightsScene>();
    } else if (tutorial == "physically_based_bloom") {
        return std::make_unique<PhysicallyBasedBloomScene>();
    } else if (tutorial == "normal_mapping") {
        return std::make_unique<NormalMappingScene>();
    } else if (tutorial == "parallax_mapping") {
        return std::make_unique<ParallaxMappingScene>();
    } else if (tutorial == "pbr") {
        return std::make_unique<PbrScene>();
    } else if (tutorial == "pbr_texture") {
        return std::make_unique<PbrTextureScene>();
    } else if (tutorial == "theory") {
        return std::make_unique<TheoryScene>();
    } else if (tutorial == "ibl") {
        return std::make_unique<IblScene>();
    } else if (tutorial == "oit") {
        return std::make_unique<OitScene>();
    } else if (tutorial == "scene") {
        return std::make_unique<SceneScene>();
    } else if (tutorial == "csm") {
        return std::make_unique<CsmScene>();
    } else if (tutorial == "dsa") {
        return std::make_unique<DsaScene>();
    }
    return nullptr;
}

#endif //LEARNGLES_SCENEHELPER_H
