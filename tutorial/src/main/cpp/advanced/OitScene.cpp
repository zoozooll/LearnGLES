#include "OitScene.h"

#include "Shader.h"
#include "TargetCamera.h"
#include "Texture.h"

OitScene::OitScene() {

}

void OitScene::init() {
    // build and compile shaders
    // -------------------------
    solidShader = new Shader("shaders/oit/solid.vert", "shaders/oit/solid.frag");
    transparentShader = new Shader("shaders/oit/transparent.vert", "shaders/oit/transparent.frag");
    compositeShader = new Shader("shaders/oit/composite.vert", "shaders/oit/composite.frag");
    screenShader = new Shader("shaders/oit/screen.vert", "shaders/oit/screen.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float quadVertices[] = {
            // positions		// uv
            -1.0f, -1.0f, 0.0f,	0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f, 1.0f, 1.0f,

            1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f
    };

    // quad VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    // set up framebuffers and their texture attachments
    // ------------------------------------------------------------------
    glGenFramebuffers(1, &opaqueFBO);
    glGenFramebuffers(1, &transparentFBO);

    // set up attachments for opaque framebuffer
    glGenTextures(1, &opaqueTexture);
    glBindTexture(GL_TEXTURE_2D, opaqueTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_HALF_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, opaqueFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, opaqueTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOGW(__FILE_NAME__, "ERROR::FRAMEBUFFER:: Opaque framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // set up attachments for transparent framebuffer
    glGenTextures(1, &accumTexture);
    glBindTexture(GL_TEXTURE_2D, accumTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_HALF_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &revealTexture);
    glBindTexture(GL_TEXTURE_2D, revealTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, m_width, m_height, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, transparentFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, accumTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, revealTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0); // opaque framebuffer's depth texture

    const GLenum transparentDrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, transparentDrawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOGW(__FILE_NAME__, "ERROR::FRAMEBUFFER:: Transparent framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OitScene::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);

    // Re-allocate textures
    glBindTexture(GL_TEXTURE_2D, opaqueTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_HALF_FLOAT, NULL);

    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glBindTexture(GL_TEXTURE_2D, accumTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_HALF_FLOAT, NULL);

    glBindTexture(GL_TEXTURE_2D, revealTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, m_width, m_height, 0, GL_RED, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OitScene::draw() {
    // camera matrices
    glm::mat4 projection = camera->getProjectionMatrix();
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 vp = projection * view;

    // transformation matrices
    glm::mat4 redModelMat = calculate_model_matrix(glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 greenModelMat = calculate_model_matrix(glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 blueModelMat = calculate_model_matrix(glm::vec3(0.0f, 0.0f, 2.0f));

    // intermediate variables
    glm::vec4 zeroFillerVec(0.0f);
    glm::vec4 oneFillerVec(1.0f);

    // draw solid objects (solid pass)
    // ------

    // configure render states
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // bind opaque framebuffer to render solid objects
    glBindFramebuffer(GL_FRAMEBUFFER, opaqueFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use solid shader
    if (solidShader) {
        solidShader->use();
        solidShader->setMat4("mvp", vp * redModelMat);
        solidShader->setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // draw transparent objects (transparent pass)
    // -----

    // configure render states
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunci(0, GL_ONE, GL_ONE);
    glBlendFunci(1, GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    glBlendEquation(GL_FUNC_ADD);

    // bind transparent framebuffer to render transparent objects
    glBindFramebuffer(GL_FRAMEBUFFER, transparentFBO);
    glClearBufferfv(GL_COLOR, 0, &zeroFillerVec[0]);
    glClearBufferfv(GL_COLOR, 1, &oneFillerVec[0]);

    // use transparent shader
    if (transparentShader) {
        transparentShader->use();

        // draw green quad
        transparentShader->setMat4("mvp", vp * greenModelMat);
        transparentShader->setVec4("color", glm::vec4(0.0f, 1.0f, 0.0f, 0.5f));
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // draw blue quad
        transparentShader->setMat4("mvp", vp * blueModelMat);
        transparentShader->setVec4("color", glm::vec4(0.0f, 0.0f, 1.0f, 0.5f));
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // draw composite image (composite pass)
    // -----

    // set render states
    glDepthFunc(GL_ALWAYS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // bind opaque framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, opaqueFBO);

    // use composite shader
    if (compositeShader) {
        compositeShader->use();

        // draw screen quad
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, accumTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, revealTexture);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // draw to backbuffer (final pass)
    // -----

    // set render states
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE); // enable depth writes so glClear won't ignore clearing the depth buffer
    glDisable(GL_BLEND);

    // bind backbuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // use screen shader
    if (screenShader) {
        screenShader->use();

        // draw final screen quad
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, opaqueTexture);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void OitScene::destroy() {
    if (solidShader) delete solidShader;
    if (transparentShader) delete transparentShader;
    if (compositeShader) delete compositeShader;
    if (screenShader) delete screenShader;

    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteTextures(1, &opaqueTexture);
    glDeleteTextures(1, &depthTexture);
    glDeleteTextures(1, &accumTexture);
    glDeleteTextures(1, &revealTexture);
    glDeleteFramebuffers(1, &opaqueFBO);
    glDeleteFramebuffers(1, &transparentFBO);
    delete camera;
}

OitScene::~OitScene() {

}

glm::mat4 OitScene::calculate_model_matrix(const glm::vec3 &position,
        const glm::vec3 &rotation,
        const glm::vec3 &scale) {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, position);
    trans = glm::rotate(trans, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    trans = glm::rotate(trans, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    trans = glm::rotate(trans, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, scale);
    return trans;
}
