//
// Created by zoozo on 7/18/2023.
//

#ifndef LEARNGLES_SCENEHELPER_H
#define LEARNGLES_SCENEHELPER_H

#include "Scene.h"
#include <cstring>

#include "1_getting_started/HelloWindowScene.h"
#include "1_getting_started/HelloWindowClearScene.h"
#include "1_getting_started/HelloTriangleScene.h"
#include "1_getting_started/HelloTriangleIndexedScene.h"
#include "1_getting_started/HelloTriangleExercise1Scene.h"
#include "1_getting_started/HelloTriangleExercise2Scene.h"
#include "1_getting_started/HelloTriangleExercise3Scene.h"
#include "1_getting_started/ShadersUniformScene.h"
#include "1_getting_started/ShadersInterpolationScene.h"
#include "1_getting_started/ShadersClassScene.h"
#include "1_getting_started/ShadersExercise1Scene.h"
#include "1_getting_started/ShadersExercise2Scene.h"
#include "1_getting_started/ShadersExercise3Scene.h"
#include "1_getting_started/TexturesScene.h"
#include "1_getting_started/TextureCombinedScene.h"
#include "1_getting_started/TransformationsScene.h"
#include "1_getting_started/TextureExercise1Scene.h"
#include "1_getting_started/TextureExercise2Scene.h"
#include "1_getting_started/TextureExercise3Scene.h"
#include "1_getting_started/TextureExercise4Scene.h"
#include "1_getting_started/TransformationsExercise1Scene.h"
#include "1_getting_started/TransformationsExercise2Scene.h"
#include "1_getting_started/CoordinateSystemScene.h"
#include "1_getting_started/CoordinateSystemDepthScene.h"
#include "1_getting_started/CoordinateSystemMultipleScene.h"
#include "1_getting_started/CoordinateSystemExercise1Scene.h"
#include "1_getting_started/CameraScene.h"
#include "1_getting_started/FocalLengthAndFOVScene.h"
#include "3_model_loading/ModelLoadingScene.h"
#include "5_advanced_lighting/AdvancedLightingScene.h"
#include "2_lighting/ColorScene.h"
#include "2_lighting/BasicLightingDiffuseScene.h"
#include "2_lighting/BasicLightingSpecularScene.h"
#include "2_lighting/MaterialScene.h"
#include "2_lighting/MaterialExercise1Scene.h"
#include "2_lighting/LightingMapsDiffuseMapScene.h"
#include "2_lighting/LightingMapsSpecularMapScene.h"
#include "2_lighting/LightingMapsExercise3Scene.h"
#include "2_lighting/LightingMapsExercise4Scene.h"
#include "2_lighting/LightingCastersDirectionalScene.h"
#include "2_lighting/LightingCastersPointScene.h"
#include "2_lighting/LightingCastersSpotScene.h"
#include "2_lighting/LightingCastersSpotSoftScene.h"
#include "2_lighting/MultipleLightsScene.h"
#include "4_advanced_opengl/DepthTestingScene.h"
#include "4_advanced_opengl/DepthTestingViewScene.h"
#include "4_advanced_opengl/StencilTestingScene.h"
#include "4_advanced_opengl/BlenderSortScene.h"
#include "4_advanced_opengl/BlendingDiscardScene.h"
#include "4_advanced_opengl/FrameBuffersScene.h"
#include "4_advanced_opengl/FramebuffersExercise1Scene.h"
#include "4_advanced_opengl/FramebuffersMultiTexturesScene.h"
#include "4_advanced_opengl/CubemapSkyboxScene.h"
#include "4_advanced_opengl/CubemapsEnvironmentMappingScene.h"
#include "4_advanced_opengl/AdvancedGlslUboScene.h"
#include "4_advanced_opengl/FaceCullingScene.h"
#include "4_advanced_opengl/GeometryShaderHousesScene.h"
#include "4_advanced_opengl/GeometryShaderExplodingScene.h"
#include "4_advanced_opengl/GeometryShaderNormalsScene.h"
#include "4_advanced_opengl/InstancingQuadsScene.h"
#include "4_advanced_opengl/AsteroidsScene.h"
#include "4_advanced_opengl/AsteroidInstancedScene.h"
#include "4_advanced_opengl/AntiAliasingOffscreenScene.h"
#include "4_advanced_opengl/AntiAliasingMsaaScene.h"
#include "5_advanced_lighting/GammaCorrectionScene.h"
#include "5_advanced_lighting/ShadowMappingDepthScene.h"
#include "5_advanced_lighting/ShadowMappingBaseScene.h"
#include "5_advanced_lighting/ShadowMappingScene.h"
#include "5_advanced_lighting/PointShadowsScene.h"
#include "5_advanced_lighting/PointShadowSoftScene.h"
#include "5_advanced_lighting/CsmScene.h"
#include "5_advanced_lighting/NormalMappingScene.h"
#include "5_advanced_lighting/ParallaxMappingScene.h"
#include "5_advanced_lighting/SteepParallaxMappingScene.h"
#include "5_advanced_lighting/ParallaxOcclusionMappingScene.h"
#include "5_advanced_lighting/HdrScene.h"
#include "5_advanced_lighting/BloomScene.h"
#include "5_advanced_lighting/DeferredShadingScene.h"
#include "5_advanced_lighting/DeferredShadingVolumesScene.h"
#include "5_advanced_lighting/SsaoScene.h"
#include "6_pbr/LightingScene.h"
#include "6_pbr/LightingTexturedScene.h"
#include "6_pbr/IblIrradianceConversionScene.h"
#include "6_pbr/IblIrradianceScene.h"
#include "6_pbr/IblSpecularScene.h"
#include "6_pbr/IblSpecularTexturedScene.h"
#include "7_in_practice/DebuggingScene.h"
#include "7_in_practice/TextRenderingScene.h"
#include "7_in_practice/Game2dScene.h"
#include "8_guest/OitScene.h"
#include "8_guest/SkeletalAnimationScene.h"
#include "8_guest/SceneExercise.h"
#include "8_guest/GuestCsmScene.h"
#include "8_guest/TessellationScene.h"
#include "8_guest/DsaScene.h"
#include "8_guest/ComputeshaderHelloworld.h"
#include "8_guest/PhysicallyBasedBloomScene.h"
#include "1_getting_started/CameraExercise1Scene.h"
#include "1_getting_started/CameraExercise2Scene.h"
#include "1_getting_started/CameraCircleScene.h"
#include "1_getting_started/CoordinateSystemExercise2Scene.h"
#include "1_getting_started/CoordinateSystemExercise3Scene.h"
#include "1_getting_started/CoordinateSystemExercise4Scene.h"

inline std::unique_ptr<Scene> GenSceneByName(const char *tutorial) {
    if (!strcmp(tutorial, "hello_window")) {
        return std::unique_ptr<Scene>(new HelloWindowScene);
    } else if (!strcmp(tutorial, "hello_window_clear")) {
        return std::unique_ptr<Scene>(new HelloWindowClearScene);
    } else if (!strcmp(tutorial, "hello_triangle")) {
        return std::unique_ptr<Scene>(new HelloTriangleScene);
    } else if (!strcmp(tutorial, "hello_triangle_indexed")) {
        return std::unique_ptr<Scene>(new HelloTriangleIndexedScene);
    } else if (!strcmp(tutorial, "hello_triangle_exercise1")) {
        return std::unique_ptr<Scene>(new HelloTriangleExercise1Scene);
    } else if (!strcmp(tutorial, "hello_triangle_exercise2")) {
        return std::unique_ptr<Scene>(new HelloTriangleExercise2Scene);
    } else if (!strcmp(tutorial, "hello_triangle_exercise3")) {
        return std::unique_ptr<Scene>(new HelloTriangleExercise3Scene);
    } else if (!strcmp(tutorial, "shaders_uniform")) {
        return std::unique_ptr<Scene>(new ShadersUniformScene);
    } else if (!strcmp(tutorial, "shaders_interpolation")) {
        return std::unique_ptr<Scene>(new ShadersInterpolationScene);
    } else if (!strcmp(tutorial, "shaders_class")) {
        return std::unique_ptr<Scene>(new ShadersClassScene);
    } else if (!strcmp(tutorial, "shaders_exercise1")) {
        return std::unique_ptr<Scene>(new ShadersExercise1Scene);
    } else if (!strcmp(tutorial, "shaders_exercise2")) {
         return std::unique_ptr<Scene>(new ShadersExercise2Scene);
    } else if (!strcmp(tutorial, "shaders_exercise3")) {
         return std::unique_ptr<Scene>(new ShadersExercise3Scene);
    } else if (!strcmp(tutorial, "textures")) {
        return std::unique_ptr<Scene>(new TexturesScene);
    } else if (!strcmp(tutorial, "texture_combined")) {
        return std::unique_ptr<Scene>(new TextureCombinedScene);
    } else if (!strcmp(tutorial, "transformations")) {
        return std::unique_ptr<Scene>(new TransformationsScene);
    } else if (!strcmp(tutorial, "texture_exercise1")) {
        return std::unique_ptr<Scene>(new TextureExercise1Scene);
    } else if (!strcmp(tutorial, "texture_exercise2")) {
        return std::unique_ptr<Scene>(new TextureExercise2Scene);
    } else if (!strcmp(tutorial, "texture_exercise3")) {
        return std::unique_ptr<Scene>(new TextureExercise3Scene);
    } else if (!strcmp(tutorial, "texture_exercise4")) {
        return std::unique_ptr<Scene>(new TextureExercise4Scene);
    } else if (!strcmp(tutorial, "transformations_exercise1")) {
        return std::unique_ptr<Scene>(new TransformationsExercise1Scene);
    } else if (!strcmp(tutorial, "transformations_exercise2")) {
        return std::unique_ptr<Scene>(new TransformationsExercise2Scene);
    } else if (!strcmp(tutorial, "coordinate_systems")) {
        return std::unique_ptr<Scene>(new CoordinateSystemScene);
    } else if (!strcmp(tutorial, "coordinate_systems_depth")) {
        return std::unique_ptr<Scene>(new CoordinateSystemDepthScene);
    } else if (!strcmp(tutorial, "coordinate_systems_multiple")) {
        return std::unique_ptr<Scene>(new CoordinateSystemMultipleScene);
    } else if (!strcmp(tutorial, "coordinate_systems_exercise")) {
        return std::unique_ptr<Scene>(new CoordinateSystemExercise1Scene);
    } else if (!strcmp(tutorial, "coordinate_systems_exercise2")) {
        return std::unique_ptr<Scene>(new CoordinateSystemExercise2Scene);
    } else if (!strcmp(tutorial, "coordinate_systems_exercise3")) {
        return std::unique_ptr<Scene>(new CoordinateSystemExercise3Scene);
    } else if (!strcmp(tutorial, "coordinate_systems_exercise4")) {
        return std::unique_ptr<Scene>(new CoordinateSystemExercise4Scene);
    } else if (!strcmp(tutorial, "Focal Length and FOV")) {
        return std::unique_ptr<Scene>(new FocalLengthAndFOVScene());
    } else if (!strcmp(tutorial, "camera_circle")) {
        return std::unique_ptr<Scene>(new CameraCircleScene);
    } else if (!strcmp(tutorial, "camera_class")) {
        return std::unique_ptr<Scene>(new CameraScene);
    } else if (!strcmp(tutorial, "camera_exercise1")) {
        return std::unique_ptr<Scene>(new CameraExercise1Scene);
    } else if (!strcmp(tutorial, "camera_exercise2")) {
        return std::unique_ptr<Scene>(new CameraExercise2Scene);
    } else if (!strcmp(tutorial, "model_loading")) {
        return std::unique_ptr<Scene>(new ModelLoadingScene);
    } else if (!strcmp(tutorial, "advanced_lighting")) {
        return std::unique_ptr<Scene>(new AdvancedLightingScene);
    } else if (!strcmp(tutorial, "colors" )) {
        return std::unique_ptr<Scene>(new ColorScene);
    } else if (!strcmp(tutorial, "basic_lighting_diffuse" )) {
        return std::unique_ptr<Scene>(new BasicLightingDiffuseScene);
    } else if (!strcmp(tutorial, "basic_lighting_specular" )) {
        return std::unique_ptr<Scene>(new BasicLightingSpecularScene);
    } else if (!strcmp(tutorial, "materials" )) {
        return std::unique_ptr<Scene>(new MaterialScene);
    } else if (!strcmp(tutorial, "materials_exercise1" )) {
        return std::unique_ptr<Scene>(new MaterialExercise1Scene);
    } else if (!strcmp(tutorial, "lighting_maps_diffuse_map" )) {
        return std::unique_ptr<Scene>(new LightingMapsDiffuseMapScene);
    } else if (!strcmp(tutorial, "lighting_maps_specular_map")) {
        return std::unique_ptr<Scene>(new LightingMapsSpecularMapScene);
    } else if (!strcmp(tutorial, "lighting_maps_exercise3" )) {
        return std::unique_ptr<Scene>(new LightingMapsExercise3Scene);
    } else if (!strcmp(tutorial, "lighting_maps_exercise4" )) {
        return std::unique_ptr<Scene>(new LightingMapsExercise4Scene);
    } else if (!strcmp(tutorial, "light_casters_directional" )) {
        return std::unique_ptr<Scene>(new LightingCastersDirectionalScene);
    } else if (!strcmp(tutorial, "light_casters_point" )) {
        return std::unique_ptr<Scene>(new LightingCastersPointScene);
    } else if (!strcmp(tutorial, "light_casters_spot" )) {
        return std::unique_ptr<Scene>(new LightingCastersSpotScene);
    } else if (!strcmp(tutorial, "light_casters_spot_soft" )) {
        return std::unique_ptr<Scene>(new LightingCastersSpotSoftScene);
    } else if (!strcmp(tutorial, "multiple_lights" )) {
        return std::unique_ptr<Scene>(new MultipleLightsScene);
    } else if (!strcmp(tutorial, "depth_testing")) {
        return std::unique_ptr<Scene>(new DepthTestingScene());
    } else if (!strcmp(tutorial, "depth_testing_view")) {
        return std::unique_ptr<Scene>(new DepthTestingViewScene());
    } else if (!strcmp(tutorial, "stencil_testing")) {
        return std::unique_ptr<Scene>(new StencilTestingScene());
    } else if (!strcmp(tutorial, "blending_discard")) {
        return std::unique_ptr<Scene>(new BlendingDiscardScene());
    } else if (!strcmp(tutorial, "blending_sort")) {
        return std::unique_ptr<Scene>(new BlenderSortScene());
    } else if (!strcmp(tutorial, "face_culling_exercise1")) {
        return std::unique_ptr<Scene>(new FaceCullingScene);
    } else if (!strcmp(tutorial, "framebuffers")) {
        return std::unique_ptr<Scene>(new FrameBuffersScene);
    } else if (!strcmp(tutorial, "framebuffers_exercise1")) {
        return std::unique_ptr<Scene>(new FramebuffersExercise1Scene);
    } else if (!strcmp(tutorial, "framebuffers_multi_textures")) {
        return std::unique_ptr<Scene>(new FramebuffersMultiTexturesScene);
    } else if (!strcmp(tutorial, "cubemap_skybox")) {
        return std::unique_ptr<Scene>(new CubemapSkyboxScene);
    } else if (!strcmp(tutorial, "cubemap_environment_mapping" )) {
        return std::unique_ptr<Scene>(new CubemapsEnvironmentMappingScene);
    } else if (!strcmp(tutorial, "advanced_glsl_ubo")) {
        return std::unique_ptr<Scene>(new AdvancedGlslUboScene);
    } else if (!strcmp(tutorial, "geometry_shader_houses")) {
        return std::unique_ptr<Scene>(new GeometryShaderHousesScene);
    } else if (!strcmp(tutorial, "geometry_shader_exploding" )) {
        return std::unique_ptr<Scene>(new GeometryShaderExplodingScene);
    } else if (!strcmp(tutorial, "geometry_shader_normals")) {
        return std::unique_ptr<Scene>(new GeometryShaderNormalsScene);
    } else if (!strcmp(tutorial, "instancing_quads")) {
        return std::unique_ptr<Scene>(new InstancingQuadsScene);
    } else if (!strcmp(tutorial, "asteroids")) {
        return std::unique_ptr<Scene>(new AsteroidsScene);
    } else if (!strcmp(tutorial, "asteroids_instanced")) {
        return std::unique_ptr<Scene>(new AsteroidInstancedScene);
    } else if (!strcmp(tutorial, "anti_aliasing_msaa")) {
        return std::unique_ptr<Scene>(new AntiAliasingMsaaScene);
    } else if (!strcmp(tutorial, "anti_aliasing_offscreen")) {
        return std::unique_ptr<Scene>(new AntiAliasingOffscreenScene);
    } else if (!strcmp(tutorial, "advanced_lighting")) {
        return std::unique_ptr<Scene>(new AdvancedLightingScene);
    } else if (!strcmp(tutorial, "gamma_correction")) {
        return std::unique_ptr<Scene>(new GammaCorrectionScene);
    } else if (!strcmp(tutorial, "shadow_mapping_depth")) {
        return std::unique_ptr<Scene>(new ShadowMappingDepthScene);
    } else if (!strcmp(tutorial, "shadow_mapping_base")) {
        return std::unique_ptr<Scene>(new ShadowMappingBaseScene);
    } else if (!strcmp(tutorial, "shadow_mapping")) {
        return std::unique_ptr<Scene>(new ShadowMappingScene);
    } else if (!strcmp(tutorial, "shadow_mapping_exercise1")) {
        return std::unique_ptr<Scene>(new ShadowMappingScene);
    } else if (!strcmp(tutorial, "point_shadows")) {
        return std::unique_ptr<Scene>(new PointShadowsScene);
    } else if (!strcmp(tutorial, "point_shadow_soft")) {
        return std::unique_ptr<Scene>(new PointShadowSoftScene);
    } else if (!strcmp(tutorial, "csm")) {
        return std::unique_ptr<Scene>(new CsmScene);
    } else if (!strcmp(tutorial, "normal_mapping")) {
        return std::unique_ptr<Scene>(new NormalMappingScene);
    } else if (!strcmp(tutorial, "parallax_mapping")) {
        return std::unique_ptr<Scene>(new ParallaxMappingScene);
    } else if (!strcmp(tutorial, "steep_parallax_mapping")) {
        return std::unique_ptr<Scene>(new SteepParallaxMappingScene);
    } else if (!strcmp(tutorial, "parallax_occlusion_mapping")) {
        return std::unique_ptr<Scene>(new ParallaxOcclusionMappingScene);
    } else if (!strcmp(tutorial, "hdr")) {
        return std::unique_ptr<Scene>(new HdrScene);
    } else if (!strcmp(tutorial, "bloom")) {
        return std::unique_ptr<Scene>(new BloomScene);
    } else if (!strcmp(tutorial, "deferred_shading")) {
        return std::unique_ptr<Scene>(new DeferredShadingScene);
    } else if (!strcmp(tutorial, "deferred_shading_volumes")) {
        return std::unique_ptr<Scene>(new DeferredShadingVolumesScene);
    } else if (!strcmp(tutorial, "ssao")) {
        return std::unique_ptr<Scene>(new SsaoScene);
    } else if (!strcmp(tutorial, "lighting" )) {
        return std::unique_ptr<Scene>(new LightingScene);
    } else if (!strcmp(tutorial, "lighting_textured" )) {
        return std::unique_ptr<Scene>(new LightingTexturedScene);
    } else if (!strcmp(tutorial, "ibl_irradiance_conversion" )) {
        return std::unique_ptr<Scene>(new IblIrradianceConversionScene);
    } else if (!strcmp(tutorial, "ibl_irradiance" )) {
        return std::unique_ptr<Scene>(new IblIrradianceScene);
    } else if (!strcmp(tutorial, "ibl_specular" )) {
        return std::unique_ptr<Scene>(new IblSpecularScene);
    } else if (!strcmp(tutorial, "ibl_specular_textured" )) {
        return std::unique_ptr<Scene>(new IblSpecularTexturedScene);
    } else if (!strcmp(tutorial, "debugging" )) {
        return std::unique_ptr<Scene>(new DebuggingScene);
    } else if (!strcmp(tutorial, "text_rendering" )) {
        return std::unique_ptr<Scene>(new TextRenderingScene);
    } else if (!strcmp(tutorial, "2d_game" )) {
        return std::unique_ptr<Scene>(new Game2dScene);
    } else if (!strcmp(tutorial, "oit" )) {
        return std::unique_ptr<Scene>(new OitScene);
    } else if (!strcmp(tutorial, "skeletal_animation" )) {
        return std::unique_ptr<Scene>(new SkeletalAnimationScene);
    } else if (!strcmp(tutorial, "scene" )) {
        return std::unique_ptr<Scene>(new SceneExercise);
    } else if (!strcmp(tutorial, "csm" )) {
        return std::unique_ptr<Scene>(new CsmScene);
    } else if (!strcmp(tutorial, "tessellation" )) {
        return std::unique_ptr<Scene>(new TessellationScene);
    } else if (!strcmp(tutorial, "dsa" )) {
        return std::unique_ptr<Scene>(new DsaScene);
    } else if (!strcmp(tutorial, "computeshader_helloworld" )) {
        return std::unique_ptr<Scene>(new ComputeshaderHelloworld);
    } else if (!strcmp(tutorial, "physically_based_bloom")) {
        return std::unique_ptr<Scene>(new PhysicallyBasedBloomScene);
    }
    return nullptr;
}

#endif //LEARNGLES_SCENEHELPER_H
