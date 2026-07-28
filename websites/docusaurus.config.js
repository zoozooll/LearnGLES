const config = {
  title: 'LearnGLES',
  tagline: 'Learn OpenGL ES 3.0+ for Android',
  favicon: 'img/favicon.ico',
  url: 'https://zoozooll.github.io',
  baseUrl: '/LearnGLES/',
  organizationName: 'zoozooll',
  projectName: 'LearnGLES',
  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',
  i18n: {
    defaultLocale: 'en',
    locales: ['en', 'zh-Hans', 'zh-Hant', 'de', 'es', 'fr', 'hi', 'id', 'ja', 'ko', 'pt-BR', 'ru'],
  },

  presets: [
    [
      'classic',
      {
        docs: {
          sidebarPath: './sidebars.js',
          editUrl:
            'https://github.com/zoozooll/LearnGLES/tree/main/',
        },
        blog: {
          showReadingTime: true,
          editUrl:
            'https://github.com/zoozooll/LearnGLES/tree/main/',
        },
        theme: {
          customCss: './src/css/custom.css',
        },
      },
    ],
  ],

  themeConfig: {
    image: 'img/docusaurus-social-card.jpg',
    navbar: {
      title: 'LearnGLES',
      logo: {
        alt: 'LearnGLES Logo',
        src: 'img/logo.svg',
        href: '/docs/',
      },
      items: [
        {
          type: 'docSidebar',
          sidebarId: 'homeSidebar',
          position: 'left',
          label: 'Home',
        },
        {
          type: 'docSidebar',
          sidebarId: 'tutorialSidebar',
          position: 'left',
          label: 'Tutorials',
        },
        {to: '/blog', label: 'Blog', position: 'left'},
        {
          href: 'https://github.com/zoozooll/LearnGLES',
          label: 'GitHub',
          position: 'right',
        },
        {
          type: 'localeDropdown',
          position: 'right',
        },
      ],
    },
    footer: {
      style: 'dark',
      links: [
          {
            title: 'Tutorials',
            items: [
              {
                label: 'Basic Techniques',
                to: '/docs/basic/',
              },
              {
                label: 'Lighting & Post-Processing',
                to: '/docs/lighting/',
              },
              {
                label: 'PBR',
                to: '/docs/pbr/',
              },
              {
                label: 'Advanced',
                to: '/docs/advanced/',
              },
            ],
          },
        {
          title: 'Community',
          items: [
            {
              label: 'GitHub',
              href: 'https://github.com/zoozooll/LearnGLES',
            },
          ],
        },
      ],
      copyright: `Copyright © ${new Date().getFullYear()} LearnGLES. Built with Docusaurus.`,
    },
  },
};

export default config;
