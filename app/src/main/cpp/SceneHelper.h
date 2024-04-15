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

inline Scene* GenSceneByName(const char *tutorial) {
    if (!strcmp(tutorial, "hello_window")) {
        return new HelloWindowScene;
    } else if (!strcmp(tutorial, "hello_window_clear")) {
        return new HelloWindowClearScene;
    } else if (!strcmp(tutorial, "hello_triangle")) {
        return new HelloTriangleScene;
    } else if (!strcmp(tutorial, "hello_triangle_indexed")) {
        return new HelloTriangleIndexedScene;
    } else if (!strcmp(tutorial, "hello_triangle_exercise1")) {
        return new HelloTriangleExercise1Scene;
    } else if (!strcmp(tutorial, "hello_triangle_exercise2")) {
        return new HelloTriangleExercise2Scene;
    } else if (!strcmp(tutorial, "hello_triangle_exercise3")) {
        return new HelloTriangleExercise3Scene;
    } else if (!strcmp(tutorial, "shaders_uniform")) {
        return new ShadersUniformScene;
    } else if (!strcmp(tutorial, "shaders_interpolation")) {
        return new ShadersInterpolationScene;
    } else if (!strcmp(tutorial, "shaders_class")) {
        return new ShadersClassScene;
    } else if (!strcmp(tutorial, "shaders_exercise1")) {
        return new ShadersExercise1Scene;
    } else if (!strcmp(tutorial, "shaders_exercise2")) {
         return new ShadersExercise2Scene;
    } else if (!strcmp(tutorial, "shaders_exercise3")) {
         return new ShadersExercise3Scene;
    } else if (!strcmp(tutorial, "textures")) {
        return new TexturesScene;
    } else if (!strcmp(tutorial, "texture_combined")) {
        return new TextureCombinedScene;
    } else if (!strcmp(tutorial, "transformations")) {
        return new TransformationsScene;
    } else if (!strcmp(tutorial, "texture_exercise1")) {
        return new TextureExercise1Scene;
    } else if (!strcmp(tutorial, "texture_exercise2")) {
        return new TextureExercise2Scene;
    } else if (!strcmp(tutorial, "texture_exercise3")) {
        return new TextureExercise3Scene;
    } else if (!strcmp(tutorial, "texture_exercise4")) {
        return new TextureExercise4Scene;
    } else if (!strcmp(tutorial, "transformations_exercise1")) {
        return new TransformationsExercise1Scene;
    } else if (!strcmp(tutorial, "transformations_exercise2")) {
        return new TransformationsExercise2Scene;
    } else if (!strcmp(tutorial, "coordinate_systems")) {
        return new CoordinateSystemScene;
    } else if (!strcmp(tutorial, "coordinate_systems_depth")) {
        return new CoordinateSystemDepthScene;
    } else if (!strcmp(tutorial, "coordinate_systems_multiple")) {
        return new CoordinateSystemMultipleScene;
    } else if (!strcmp(tutorial, "coordinate_systems_exercise")) {
        return new CoordinateSystemExercise1Scene;
    } else if (!strcmp(tutorial, "coordinate_systems_exercise2")) {
        return new CoordinateSystemExercise2Scene;
    } else if (!strcmp(tutorial, "coordinate_systems_exercise3")) {
        return new CoordinateSystemExercise3Scene;
    } else if (!strcmp(tutorial, "coordinate_systems_exercise4")) {
        return new CoordinateSystemExercise4Scene;
    } else if (!strcmp(tutorial, "camera_circle")) {
        return new CameraCircleScene;
    } else if (!strcmp(tutorial, "camera_keyboard_dt")) {

    } else if (!strcmp(tutorial, "camera_mouse_zoom")) {

    } else if (!strcmp(tutorial, "camera_class")) {
        return new CameraScene;
    } else if (!strcmp(tutorial, "camera_exercise1")) {
        return new CameraExercise1Scene;
    } else if (!strcmp(tutorial, "camera_exercise2")) {
        return new CameraExercise2Scene;
    } else if (!strcmp(tutorial, "model_loading")) {
        return new ModelLoadingScene;
    } else if (!strcmp(tutorial, "advanced_lighting")) {
        return new AdvancedLightingScene;
    } else if (!strcmp(tutorial, "colors" )) {
        return new ColorScene;
    } else if (!strcmp(tutorial, "basic_lighting_diffuse" )) {
        return new BasicLightingDiffuseScene;
    } else if (!strcmp(tutorial, "basic_lighting_specular" )) {
        return new BasicLightingSpecularScene;
    } else if (!strcmp(tutorial, "materials" )) {
        return new MaterialScene;
    } else if (!strcmp(tutorial, "materials_exercise1" )) {
        return new MaterialExercise1Scene;
    } else if (!strcmp(tutorial, "lighting_maps_diffuse_map" )) {
        return new LightingMapsDiffuseMapScene;
    } else if (!strcmp(tutorial, "lighting_maps_specular_map")) {
        return new LightingMapsSpecularMapScene;
    } else if (!strcmp(tutorial, "lighting_maps_exercise3" )) {
        return new LightingMapsExercise3Scene;
    } else if (!strcmp(tutorial, "lighting_maps_exercise4" )) {
        return new LightingMapsExercise4Scene;
    } else if (!strcmp(tutorial, "light_casters_directional" )) {
        return new LightingCastersDirectionalScene;
    } else if (!strcmp(tutorial, "light_casters_point" )) {
        return new LightingCastersPointScene;
    } else if (!strcmp(tutorial, "light_casters_spot" )) {
        return new LightingCastersSpotScene;
    } else if (!strcmp(tutorial, "light_casters_spot_soft" )) {
        return new LightingCastersSpotSoftScene;
    } else if (!strcmp(tutorial, "multiple_lights" )) {
        return new MultipleLightsScene;
    } else if (!strcmp(tutorial, "multiple_lights_exercise1" )) {
    } else if (!strcmp(tutorial, "depth_testing")) {
        return new DepthTestingScene();
    } else if (!strcmp(tutorial, "depth_testing_view")) {
        return new DepthTestingViewScene();
    } else if (!strcmp(tutorial, "stencil_testing")) {
        return new StencilTestingScene();
    } else if (!strcmp(tutorial, "blending_discard")) {
        return new BlendingDiscardScene();
    } else if (!strcmp(tutorial, "blending_sort")) {
        return new BlenderSortScene();
    } else if (!strcmp(tutorial, "face_culling_exercise1")) {
        return new FaceCullingScene;
    } else if (!strcmp(tutorial, "framebuffers")) {
        return new FrameBuffersScene;
    } else if (!strcmp(tutorial, "framebuffers_exercise1")) {
        return new FramebuffersExercise1Scene;
    } else if (!strcmp(tutorial, "framebuffers_multi_textures")) {
        return new FramebuffersMultiTexturesScene;
    } else if (!strcmp(tutorial, "cubemap_skybox")) {
        return new CubemapSkyboxScene;
    } else if (!strcmp(tutorial, "cubemap_environment_mapping" )) {
        return new CubemapsEnvironmentMappingScene;
    } else if (!strcmp(tutorial, "advanced_glsl_ubo")) {
        return new AdvancedGlslUboScene;
    } else if (!strcmp(tutorial, "geometry_shader_houses")) {
        return new GeometryShaderHousesScene;
    } else if (!strcmp(tutorial, "geometry_shader_exploding" )) {
        return new GeometryShaderExplodingScene;
    } else if (!strcmp(tutorial, "geometry_shader_normals")) {
        return new GeometryShaderNormalsScene;
    } else if (!strcmp(tutorial, "instancing_quads")) {
        return new InstancingQuadsScene;
    } else if (!strcmp(tutorial, "asteroids")) {
        return new AsteroidsScene;
    } else if (!strcmp(tutorial, "asteroids_instanced")) {
        return new AsteroidInstancedScene;
    } else if (!strcmp(tutorial, "anti_aliasing_msaa")) {
        return new AntiAliasingMsaaScene;
    } else if (!strcmp(tutorial, "anti_aliasing_offscreen")) {
        return new AntiAliasingOffscreenScene;
    } else if (!strcmp(tutorial, "advanced_lighting")) {
        return new AdvancedLightingScene;
    } else if (!strcmp(tutorial, "gamma_correction")) {
        return new GammaCorrectionScene;
    } else if (!strcmp(tutorial, "shadow_mapping_depth")) {
        return new ShadowMappingDepthScene;
    } else if (!strcmp(tutorial, "shadow_mapping_base")) {
        return new ShadowMappingBaseScene;
    } else if (!strcmp(tutorial, "shadow_mapping")) {
        return new ShadowMappingScene;
    } else if (!strcmp(tutorial, "shadow_mapping_exercise1")) {
        return new ShadowMappingScene;
    } else if (!strcmp(tutorial, "point_shadows")) {
        return new PointShadowsScene;
    } else if (!strcmp(tutorial, "point_shadow_soft")) {
        return new PointShadowSoftScene;
    } else if (!strcmp(tutorial, "csm")) {
        return new CsmScene;
    } else if (!strcmp(tutorial, "normal_mapping")) {
        return new NormalMappingScene;
    } else if (!strcmp(tutorial, "parallax_mapping")) {
        return new ParallaxMappingScene;
    } else if (!strcmp(tutorial, "steep_parallax_mapping")) {
        return new SteepParallaxMappingScene;
    } else if (!strcmp(tutorial, "parallax_occlusion_mapping")) {
        return new ParallaxOcclusionMappingScene;
    } else if (!strcmp(tutorial, "hdr")) {
        return new HdrScene;
    } else if (!strcmp(tutorial, "bloom")) {
        return new BloomScene;
    } else if (!strcmp(tutorial, "deferred_shading")) {
        return new DeferredShadingScene;
    } else if (!strcmp(tutorial, "deferred_shading_volumes")) {
        return new DeferredShadingVolumesScene;
    } else if (!strcmp(tutorial, "ssao")) {
        return new SsaoScene;
    } else if (!strcmp(tutorial, "lighting" )) {
        return new LightingScene;
    } else if (!strcmp(tutorial, "lighting_textured" )) {
        return new LightingTexturedScene;
    } else if (!strcmp(tutorial, "ibl_irradiance_conversion" )) {
        return new IblIrradianceConversionScene;
    } else if (!strcmp(tutorial, "ibl_irradiance" )) {
        return new IblIrradianceScene;
    } else if (!strcmp(tutorial, "ibl_specular" )) {
        return new IblSpecularScene;
    } else if (!strcmp(tutorial, "ibl_specular_textured" )) {
        return new IblSpecularTexturedScene;
    } else if (!strcmp(tutorial, "debugging" )) {
        return new DebuggingScene;
    } else if (!strcmp(tutorial, "text_rendering" )) {
        return new TextRenderingScene;
    } else if (!strcmp(tutorial, "2d_game" )) {
        return new Game2dScene;
    } else if (!strcmp(tutorial, "oit" )) {
        return new OitScene;
    } else if (!strcmp(tutorial, "skeletal_animation" )) {
        return new SkeletalAnimationScene;
    } else if (!strcmp(tutorial, "scene" )) {
        return new SceneExercise;
    } else if (!strcmp(tutorial, "csm" )) {
        return new CsmScene;
    } else if (!strcmp(tutorial, "tessellation" )) {
        return new TessellationScene;
    } else if (!strcmp(tutorial, "dsa" )) {
        return new DsaScene;
    } else if (!strcmp(tutorial, "computeshader_helloworld" )) {
        return new ComputeshaderHelloworld;
    } else if (!strcmp(tutorial, "physically_based_bloom")) {
        return new PhysicallyBasedBloomScene;
    }
    return nullptr;
}

#endif //LEARNGLES_SCENEHELPER_H
