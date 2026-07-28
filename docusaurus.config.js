module.exports = {
  title: 'LearnGLES Docs',
  tagline: 'OpenGL ES tutorials and examples',
  url: 'https://zoozooll.github.io',
  baseUrl: '/LearnGLES/',
  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',
  favicon: 'img/favicon.ico',
  organizationName: 'zoozooll',
  projectName: 'LearnGLES',
  i18n: {
    defaultLocale: 'en',
    locales: ['en'],
  },
  presets: [
    [
      '@docusaurus/preset-classic',
      {
        docs: {
          sidebarPath: require.resolve('./sidebars.js'),
          routeBasePath: '/',
          editUrl: 'https://github.com/zoozooll/LearnGLES/tree/dev/',
        },
        blog: false,
        theme: {
          customCss: require.resolve('./src/css/custom.css'),
        },
      },
    ],
  ],
  themeConfig: {
    navbar: {
      title: 'LearnGLES',
      logo: {
        alt: 'LearnGLES Logo',
        src: 'img/logo.svg',
      },
      items: [
        {
          to: '/',
          label: 'Docs',
          position: 'left',
        },
        {
          href: 'https://github.com/zoozooll/LearnGLES',
          label: 'GitHub',
          position: 'right',
        },
      ],
    },
    footer: {
      style: 'dark',
      links: [],
      copyright: `Copyright © ${new Date().getFullYear()} zoozooll`,
    },
  },
};
