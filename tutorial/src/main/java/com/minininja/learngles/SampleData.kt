package com.minininja.learngles

import androidx.activity.ComponentActivity
import com.minininja.learngles.basic.*
import com.minininja.learngles.lighting.*
import com.minininja.learngles.pbr.*
import com.minininja.learngles.advanced.*
import kotlin.reflect.KClass

data class TutorialItem(
    val id: String,
    val titleRes: Int,
    val imagePath: String,
    val activityClass: KClass<out ComponentActivity>
)

// Global and Public Data Provider
object SampleData {
    val basicItems = listOf(
        TutorialItem("basic_gles", R.string.item_basic_gles, "images/basic_gles.png", BasicGlesActivity::class),
        TutorialItem("depth_testing", R.string.item_depth_testing, "images/depth_testing.png", DepthTestingActivity::class),
        TutorialItem("stencil_testing", R.string.item_stencil_testing, "images/stencil_testing.png", StencilTestingActivity::class),
        TutorialItem("blending", R.string.item_blending, "images/blending.png", BlendingActivity::class),
        TutorialItem("cubemap", R.string.item_cubemap, "images/cubemap.png", CubemapActivity::class),
        TutorialItem("geometry_shader", R.string.item_geometry_shader, "images/geometry_shader.png", GeometryShaderActivity::class),
        TutorialItem("tesselation_shader", R.string.item_tesselation_shader, "images/tesselation_shader.png", TesselationShaderActivity::class),
        TutorialItem("compute_shader", R.string.item_compute_shader, "images/compute_shader.png", ComputeShaderActivity::class),
        TutorialItem("instance", R.string.item_instance, "images/instance.png", InstanceActivity::class),
        TutorialItem("asteroid", R.string.item_asteroid, "images/asteroid.png", AsteroidActivity::class),
        TutorialItem("msaa", R.string.item_msaa, "images/msaa.png", MsaaActivity::class),
        TutorialItem("model", R.string.item_model, "images/model.png", ModelActivity::class),
        TutorialItem("skeletal_animation", R.string.item_skeletal_animation, "images/skeletal_animation.png", SkeletalAnimationActivity::class),
        TutorialItem("debugging", R.string.item_debugging, "images/debugging.png", DebuggingActivity::class),
        TutorialItem("text_rendering", R.string.item_text_rendering, "images/text_rendering.png", TextRenderingActivity::class),
        TutorialItem("frustum_culling", R.string.item_frustum_culling, "images/frustum_culling.png", FrustumCullingActivity::class)
    )
    val lightingItems = listOf(
        TutorialItem("basic_lighting", R.string.item_basic_lighting, "images/basic_lighting.png", BasicLightingActivity::class),
        TutorialItem("light_caster", R.string.item_light_caster, "images/light_caster.png", LightCasterActivity::class),
        TutorialItem("phong_vs_blinn", R.string.item_phong_vs_blinn, "images/phong_vs_blinn.png", PhongVsBlinnActivity::class),
        TutorialItem("gamma_correction", R.string.item_gamma_correction, "images/gamma_correction.png", GammaCorrectionActivity::class),
        TutorialItem("multi_lights", R.string.item_multi_lights, "images/multi_lights.png", MultiLightsActivity::class),
        TutorialItem("shadow", R.string.item_shadow, "images/shadow.png", ShadowActivity::class),
        TutorialItem("hdr", R.string.item_hdr, "images/hdr.png", HdrActivity::class),
        TutorialItem("bloom", R.string.item_bloom, "images/bloom.png", BloomActivity::class),
        TutorialItem("ssao", R.string.item_ssao, "images/ssao.png", SsaoActivity::class),
        TutorialItem("area_lights", R.string.item_area_lights, "images/area_lights.png", AreaLightsActivity::class),
        TutorialItem("physically_based_bloom", R.string.item_physically_based_bloom, "images/physically_based_bloom.png", PhysicallyBasedBloomActivity::class)
    )
    val pbrItems = listOf(
        TutorialItem("normal_mapping", R.string.item_normal_mapping, "images/normal_mapping.png", NormalMappingActivity::class),
        TutorialItem("parallax_mapping", R.string.item_parallax_mapping, "images/parallax_mapping.png", ParallaxMappingActivity::class),
        TutorialItem("pbr", R.string.item_pbr, "images/pbr.png", PbrActivity::class),
        TutorialItem("pbr_texture", R.string.item_pbr_texture, "images/pbr_texture.png", PbrTextureActivity::class),
        TutorialItem("theory", R.string.item_theory, "images/theory.png", TheoryActivity::class),
        TutorialItem("ibl", R.string.item_ibl, "images/ibl.png", IblActivity::class)
    )
    val advancedItems = listOf(
        TutorialItem("oit", R.string.item_oit, "images/oit.png", OitActivity::class),
        TutorialItem("scene", R.string.item_scene, "images/scene.png", SceneActivity::class),
        TutorialItem("csm", R.string.item_csm, "images/csm.png", CsmActivity::class),
        TutorialItem("dsa", R.string.item_dsa, "images/dsa.png", DsaActivity::class)
    )


    fun getItemsFor(destination: AppDestinations): List<TutorialItem> = when (destination) {
        AppDestinations.BASIC -> basicItems
        AppDestinations.LIGHTING -> lightingItems
        AppDestinations.PBR -> pbrItems
        AppDestinations.ADVANCED -> advancedItems
    }
}

enum class AppDestinations(
    val label: Int,
    val icon: Int,
) {
    BASIC(R.string.label_basic, R.drawable.ic_basic),
    LIGHTING(R.string.label_lighting, R.drawable.ic_lighting),
    PBR(R.string.label_pbr, R.drawable.ic_pbr),
    ADVANCED(R.string.label_advanced, R.drawable.ic_advanced),
}
