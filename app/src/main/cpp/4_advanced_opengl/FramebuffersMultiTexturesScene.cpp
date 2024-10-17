//
// Created by Aaron Lee on 2023/8/22.
//

#include "FramebuffersMultiTexturesScene.h"

#include <GLES3/gl32.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

#include "logutil.h"
#include "glerror.h"

void FramebuffersMultiTexturesScene::init() {


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    shader = new Shader("4/5.1.framebuffers_multiattach.vert", "4/5.1.framebuffers_multiattach.frag");
    screenShader = new Shader("4/5.1.framebuffers_multiattach_screen.vert", "4/5.1.framebuffers_multiattach_screen.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float quadVertices[] = {
            // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // NOTE that this plane is now much smaller and at the top of the screen
            // positions   // texCoords
            -1.f,  1.0f,  0.0f, 1.0f,
            -1.f,  -1.f,  0.0f, 0.0f,
            1.f,  -1.f,  1.0f, 0.0f,

            -1.f,  1.0f,  0.0f, 1.0f,
            1.f,  -1.f,  1.0f, 0.0f,
            1.f,  1.0f,  1.0f, 1.0f
    };

    // screen quad VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    check_gl_error();
}

void FramebuffersMultiTexturesScene::resize(int width, int height) {
    BaseScene::resize(width, height);

    glViewport(0, 0, width, height);

    // framebuffer configuration
    // -------------------------

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture

    glGenTextures(1, &textureColorbuffer0);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer0, 0);

    glGenTextures(1, &textureColorbuffer1);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, textureColorbuffer1, 0);

    glGenTextures(1, &textureColorbuffer2);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, textureColorbuffer2, 0);

    // Set active draw buffers
    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, drawBuffers);

    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOGE(__FILE_NAME__, "Framebuffer is not complete");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    check_gl_error();
}

void FramebuffersMultiTexturesScene::draw() {
    BaseScene::draw();
    // first render pass: mirror texture.
    // bind to framebuffer and draw to color texture as we normally
    // would, but with the view camera reversed.
    // bind to framebuffer and draw scene as we normally would to color texture
    // ------------------------------------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

    // make sure we clear the framebuffer's content
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    // second render pass: draw as normal
    // ----------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // now draw the mirror quad with screen texture
    // --------------------------------------------
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

    screenShader->use();
    glBindVertexArray(quadVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer0);
    screenShader->setInt("screenTexture0", 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer1);
    screenShader->setInt("screenTexture1", 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer2);
    screenShader->setInt("screenTexture2", 2);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    check_gl_error();
}

void FramebuffersMultiTexturesScene::destroy() {
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);

    glDeleteFramebuffers(1, &framebuffer);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteTextures(1, &textureColorbuffer0);
    glDeleteTextures(1, &textureColorbuffer1);
    glDeleteTextures(1, &textureColorbuffer2);

    delete shader;
    delete screenShader;
    delete camera;
}