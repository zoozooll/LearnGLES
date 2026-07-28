---
sidebar_position: 15
title: Text Rendering
---

# Text Rendering

Text rendering is essential for displaying UI elements and information in 3D applications.

## 📋 Overview

In this tutorial, you will learn:

- How to use FreeType for font rendering
- How to create a text rendering system
- How to render text in 2D and 3D
- How to handle different font sizes and styles

## 🔑 Key Concepts

### FreeType

FreeType is a font rendering engine that:

- Loads TrueType and OpenType fonts
- Renders glyphs to bitmaps
- Provides glyph metrics (advance width, height, bearing)

### Glyph Atlas

A glyph atlas is a texture containing all rendered glyphs:

- Reduces draw calls
- Organizes glyphs efficiently
- Supports multiple font sizes

## 🧮 Mathematical Background

### Glyph Metrics

Each glyph has:

- **Width/Height**: Bounding box dimensions
- **Advance**: Horizontal distance to next glyph
- **Bearing**: Offset from baseline to top-left corner

### Text Layout

Text is laid out by:

1. Starting at baseline position
2. Rendering each glyph at current position
3. Advancing position by glyph's advance width

## 📝 Code Walkthrough

### Initializing FreeType

```cpp
#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library ft;
FT_Init_FreeType(&ft);

FT_Face face;
FT_New_Face(ft, "fonts/Antonio-Regular.ttf", 0, &face);
FT_Set_Pixel_Sizes(face, 0, 48);
```

### Rendering a Glyph

```cpp
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, glyph->bitmap.width, glyph->bitmap.rows, 
             0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

// Set texture parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

### Text Rendering Shader

```glsl
#version 320 es
layout (location = 0) in vec4 vertex;

uniform mat4 projection;

out vec2 TexCoords;

void main() {
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
```

## 🎮 Interactive Demo

In the app, see text rendered in 2D overlay and 3D space.

## ⚠️ Common Pitfalls

1. **Font path**: Ensure font files are in the correct location
2. **Texture atlas size**: May exceed maximum texture size
3. **Glyph caching**: Render glyphs only once
4. **Performance**: Too much text can reduce FPS

## 🧪 Exercises

1. **Text styling**: Add bold, italic, and underline
2. **Multiline text**: Implement line wrapping
3. **Signed distance fields**: Use SDF for scalable text

## 📚 References

- [FreeType Documentation](https://freetype.org/docs/)
- [LearnOpenGL - Text Rendering](https://learnopengl.com/In-Practice/Text-Rendering)
