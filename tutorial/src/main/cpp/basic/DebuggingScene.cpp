#include "DebuggingScene.h"

#include "logutil.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

DebuggingScene::DebuggingScene() {

}

void DebuggingScene::init() {
    m_camera = new Camera;
    // enable OpenGL debug context if context allows for debug context
    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_pShader = new Shader("debuging/debugging.vs", "debuging/debugging.fs");

    // configure 3D cube
    float vertices[] = {
            // back face
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, // bottom-left
            0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f, // bottom-right
            0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
            // front face
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
            0.5f,  0.5f,  0.5f,  1.0f,  1.0f, // top-right
            0.5f,  0.5f,  0.5f,  1.0f,  1.0f, // top-right
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f, // top-left
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left
            // left face
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f, // top-right
            -0.5f,  0.5f, -0.5f, -1.0f,  1.0f, // top-left
            -0.5f, -0.5f, -0.5f, -0.0f,  1.0f, // bottom-left
            -0.5f, -0.5f, -0.5f, -0.0f,  1.0f, // bottom-left
            -0.5f, -0.5f,  0.5f, -0.0f,  0.0f, // bottom-right
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f, // top-right
            // right face
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // top-left
            0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // bottom-right
            0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
            0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // bottom-right
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // top-left
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left
            // bottom face
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // top-right
            0.5f, -0.5f, -0.5f,  1.0f,  1.0f, // top-left
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-left
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-left
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // top-right
            // top face
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
            0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f  // bottom-left
    };
    glGenVertexArrays(1, &m_cubeVAO);
    glGenBuffers(1, &m_cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(m_cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_texture = loadTexture("textures/wood.png");

    m_pShader->use();
    m_pShader->setInt("tex", 0);
}

void DebuggingScene::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void DebuggingScene::draw() {
    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_pShader)
    {
        m_pShader->use();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 10.0f);
        m_pShader->setMat4("projection", projection);


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0, 0.0f, -2.5));
        model = glm::rotate(model, glm::radians(30.f), glm::vec3(1.0f, 1.0f, 1.0f));
        m_pShader->setMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glBindVertexArray(m_cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}

void DebuggingScene::destroy() {
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_cubeVAO != 0)
    {
        glDeleteVertexArrays(1, &m_cubeVAO);
        m_cubeVAO = 0;
    }
    if (m_cubeVBO != 0)
    {
        glDeleteBuffers(1, &m_cubeVBO);
        m_cubeVBO = 0;
    }
    if (m_texture != 0)
    {
        glDeleteTextures(1, &m_texture);
        m_texture = 0;
    }
    delete m_camera;
}

DebuggingScene::~DebuggingScene() {

}

void DebuggingScene::glDebugOutput(GLenum source,
                                    GLenum type,
                                    unsigned int id,
                                    GLenum severity,
                                    GLsizei length,
                                    const char *message,
                                    const void *userParam) {
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            LOGI("GLDEBUG", "Source: API");
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            LOGI("GLDEBUG", "Source: Window System");
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            LOGI("GLDEBUG", "Source: Shader Compiler");
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            LOGI("GLDEBUG", "Source: Third Party"); break;
        case GL_DEBUG_SOURCE_APPLICATION:
            LOGI("GLDEBUG", "Source: Application"); break;
        case GL_DEBUG_SOURCE_OTHER:
            LOGI("GLDEBUG", "Source: Other"); break;
    }

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            LOGI("GLDEBUG", "Type: Error"); break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            LOGI("GLDEBUG", "Type: Deprecated Behaviour"); break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            LOGI("GLDEBUG", "Type: Undefined Behaviour"); break;
        case GL_DEBUG_TYPE_PORTABILITY:
            LOGI("GLDEBUG", "Type: Portability"); break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            LOGI("GLDEBUG", "Type: Performance"); break;
        case GL_DEBUG_TYPE_MARKER:
            LOGI("GLDEBUG", "Type: Marker"); break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            LOGI("GLDEBUG", "Type: Push Group"); break;
        case GL_DEBUG_TYPE_POP_GROUP:
            LOGI("GLDEBUG", "Type: Pop Group"); break;
        case GL_DEBUG_TYPE_OTHER:
            LOGI("GLDEBUG", "Type: Other"); break;
    }

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            LOGI("GLDEBUG", "Severity: high"); break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            LOGI("GLDEBUG", "Severity: medium"); break;
        case GL_DEBUG_SEVERITY_LOW:
            LOGI("GLDEBUG", "Severity: low"); break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            LOGI("GLDEBUG", "Severity: notification"); break;
    }
}
