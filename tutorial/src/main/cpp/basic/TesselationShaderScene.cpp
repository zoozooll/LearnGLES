#include "TesselationShaderScene.h"

#include "Shader.h"
#include "Camera.h"
#include "logutil.h"
#include "Texture.h"

static const unsigned int NUM_PATCH_PTS = 4;

TesselationShaderScene::TesselationShaderScene() {

}

void TesselationShaderScene::init() {
    m_camera = new Camera;
    GLint maxTessLevel;
    glGetIntegerv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);
    LOGI(__FILE_NAME__, "Max available tess level: %d", maxTessLevel);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    tessHeightMapShader = new Shader("shaders/tesselation_shaders/8.3.gpuheight.vert",
            "shaders/tesselation_shaders/8.3.gpuheight.frag",
            nullptr,
            "shaders/tesselation_shaders/8.3.gpuheight.tesc",
            "shaders/tesselation_shaders/8.3.gpuheight.tese");

    // load and create a texture
    // -------------------------
    texture = loadTexture("heightmaps/iceland_heightmap.png");
    tessHeightMapShader->use();
    tessHeightMapShader->setInt("heightMap", 0);


}

void TesselationShaderScene::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> vertices;
    for(unsigned i = 0; i <= rez-1; i++)
    {
        for(unsigned j = 0; j <= rez-1; j++)
        {
            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v

            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v
        }
    }

    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);
    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);
}

void TesselationShaderScene::draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (tessHeightMapShader) {
        tessHeightMapShader->use();
        glm::mat4 projection = m_camera->getProjectionMatrix();
        glm::mat4 view = m_camera->getViewMatrix();
        tessHeightMapShader->setMat4("projection", projection);
        tessHeightMapShader->setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        tessHeightMapShader->setMat4("model", model);

        glBindVertexArray(terrainVAO);
        glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS * rez * rez);
    }
}

void TesselationShaderScene::destroy() {
    if (tessHeightMapShader) delete tessHeightMapShader;
    glDeleteVertexArrays(1, &terrainVAO);
    glDeleteBuffers(1, &terrainVBO);
    glDeleteTextures(1, &texture);
    delete m_camera;
}

TesselationShaderScene::~TesselationShaderScene() {

}
