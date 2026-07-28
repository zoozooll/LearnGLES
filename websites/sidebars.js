/** @type {import('@docusaurus/plugin-content-docs').SidebarsConfig} */
const sidebars = {
  homeSidebar: [
    {
      type: 'doc',
      id: 'intro',
      label: 'Introduction',
    },
  ],
  tutorialSidebar: [
    {
      type: 'doc',
      id: 'intro',
      label: 'Introduction',
    },
    {
      type: 'category',
      label: 'Basic Techniques',
      items: [
        'basic/index',
        'basic/basic-gles',
        'basic/depth-testing',
        'basic/stencil-testing',
        'basic/blending',
        'basic/cubemap',
        'basic/geometry-shader',
        'basic/tesselation-shader',
        'basic/compute-shader',
        'basic/instancing',
        'basic/asteroid',
        'basic/model-loading',
        'basic/skeletal-animation',
        'basic/debugging',
        'basic/text-rendering',
        'basic/frustum-culling',
      ],
    },
    {
      type: 'category',
      label: 'Lighting & Post-Processing',
      items: [
        'lighting/index',
        'lighting/basic-lighting',
        'lighting/light-caster',
        'lighting/phong-vs-blinn',
        'lighting/gamma-correction',
        'lighting/multi-lights',
        'lighting/shadow-mapping',
        'lighting/hdr',
        'lighting/bloom',
        'lighting/ssao',
        'lighting/area-lights',
      ],
    },
    {
      type: 'category',
      label: 'Physically Based Rendering',
      items: [
        'pbr/index',
        'pbr/normal-mapping',
        'pbr/parallax-mapping',
        'pbr/pbr-theory',
        'pbr/pbr-textures',
        'pbr/ibl',
      ],
    },
    {
      type: 'category',
      label: 'Advanced Techniques',
      items: [
        'advanced/index',
        'advanced/csm',
        'advanced/oit',
        'advanced/dsa',
      ],
    },
  ],
};

export default sidebars;
