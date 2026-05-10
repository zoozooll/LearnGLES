package com.minininja.learngles

// Global and Public Data Provider
object SampleData {
    val basicItems = listOf(
        "Basic GLES",
        "Depth Testing",
        "Stencil Testing",
        "Blending",
        "Cubemap",
        "Geometry Shader",
        "Tesselation Shader",
        "Compute Shader",
        "Instance",
        "Asteriod",
        "MSAA",
        "Model",
        "Skeletal Animation",
        "Debugging",
        "Text Rendering",
        "Frustum Culling"
    )
    val lightingItems = listOf(
        "Basic Lighting",
        "Light Caster",
        "Phone vs Blinn",
        "Gamma Correction",
        "Multi Lights",
        "Shadow",
        "HDR",
        "Bloom",
        "SSAO",
        "Area lights",
        "Physically Based Bloom"
    )
    val pbrItems = listOf(
        "Normal Mapping",
        "Parallax Mapping",
        "PBR",
        "PBR Texture",
        "Theory",
        "IBL"
    )
    val advancedItems = listOf(
        "OIT",
        "Scene",
        "CSM",
        "DSA"
    )

    fun getItemsFor(destination: AppDestinations): List<String> = when (destination) {
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
