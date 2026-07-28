---
sidebar_position: 14
title: Debugging
---

# Debugging

Debugging OpenGL applications requires specialized tools and techniques.

## 📋 Overview

In this tutorial, you will learn:

- How to detect OpenGL errors
- How to use debug output
- How to inspect shader variables
- Common debugging techniques

## 🔑 Key Concepts

### Error Detection

OpenGL provides error codes via `glGetError()`:

| Error | Description |
|-------|-------------|
| `GL_NO_ERROR` | No error occurred |
| `GL_INVALID_ENUM` | Invalid enumerant |
| `GL_INVALID_VALUE` | Invalid value |
| `GL_INVALID_OPERATION` | Invalid operation |
| `GL_OUT_OF_MEMORY` | Out of memory |

### Debug Output

OpenGL 4.3+ provides debug output that gives detailed error information:

```cpp
glEnable(GL_DEBUG_OUTPUT);
glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
glDebugMessageCallback(debugCallback, nullptr);
```

## 🧮 Mathematical Background

### Debug Callbacks

The debug callback function receives:

- **Source**: Where the error occurred (API, window system, shader compiler, etc.)
- **Type**: Error type (error, deprecated behavior, performance warning)
- **ID**: Message ID
- **Severity**: Severity level (high, medium, low, notification)
- **Message**: Human-readable description

## 📝 Code Walkthrough

### Error Checking Macro

```cpp
#define check_gl_error() \
    do { \
        GLenum err = glGetError(); \
        if (err != GL_NO_ERROR) { \
            LOGE(__FILE_NAME__, "OpenGL error %d at %s:%d", err, __FILE__, __LINE__); \
        } \
    } while(0)
```

### Debug Callback

```cpp
void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, 
                            GLenum severity, GLsizei length, 
                            const GLchar* message, const void* userParam) {
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
    
    LOGD("Debug", "Source: %d, Type: %d, ID: %d, Message: %s", 
         source, type, id, message);
}
```

### Using RenderDoc

RenderDoc is a powerful debugging tool:

1. Capture a frame
2. Inspect draw calls
3. View shader inputs/outputs
4. Examine texture and buffer contents

## 🎮 Interactive Demo

In the app, observe debug information displayed on screen.

## ⚠️ Common Pitfalls

1. **Ignoring errors**: Always check for OpenGL errors
2. **Debug builds only**: Error checking has performance cost
3. **Invalid state**: Ensure OpenGL context is valid before calling functions

## 🧪 Exercises

1. **Custom debug overlay**: Display FPS, draw calls, and memory usage
2. **Shader debugging**: Use `glGetShaderInfoLog` for compile errors
3. **Frame capture**: Use RenderDoc to analyze a frame

## 📚 References

- [OpenGL Debug Output](https://www.khronos.org/opengl/wiki/Debug_Output)
- [RenderDoc](https://renderdoc.org/)
