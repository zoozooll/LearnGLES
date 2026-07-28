---
sidebar_position: 12
title: Model Loading
---

# Model Loading

Model loading allows you to import complex 3D models created in external tools like Blender.

## 📋 Overview

In this tutorial, you will learn:

- How to use Assimp for model loading
- How to parse model data (meshes, materials, textures)
- How to handle different model formats
- How to render loaded models

## 🔑 Key Concepts

### Assimp

Assimp (Open Asset Import Library) supports over 40 model formats:

- OBJ
- FBX
- GLTF
- 3DS
- Collada
- And many more

### Model Structure

A loaded model consists of:

- **Meshes**: Vertex data, indices, material references
- **Materials**: Textures, colors, shaders
- **Textures**: Diffuse, specular, normal maps

## 🧮 Mathematical Background

### Coordinate System Conversion

Assimp uses a different coordinate system than OpenGL:

- Assimp: Y-up, right-handed
- OpenGL: Y-up, right-handed (same)
- But some exporters use Z-up

Need to convert:
- Flip Y coordinate
- Adjust winding order

## 📝 Code Walkthrough

### Loading a Model

```cpp
Model ourModel("objects/backpack/backpack.obj");
```

### Model Class Implementation

In [Model.h](file:///e:/workspaces/cpp/LearnGLES/tutorial/src/main/cpp/model/Model.h):

```cpp
class Model {
public:
    std::vector<Mesh> meshes;
    std::string directory;
    
    Model(std::string const &path) {
        loadModel(path);
    }
    
    void Draw(Shader &shader) {
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }
    
private:
    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};
```

### Mesh Processing

```cpp
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        // ...
        vertices.push_back(vertex);
    }
    
    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    return Mesh(vertices, indices, textures);
}
```

## 🎮 Interactive Demo

In the app, load and rotate complex 3D models like a backpack or cyborg.

## ⚠️ Common Pitfalls

1. **Missing textures**: Ensure texture paths are correct
2. **Coordinate system**: Model may appear flipped or rotated
3. **Large models**: May cause memory issues on mobile
4. **Unsupported formats**: Not all formats are equally well-supported

## 🧪 Exercises

1. **Animated models**: Load models with skeletal animation
2. **Custom materials**: Apply custom shaders to loaded models
3. **Model optimization**: Reduce polygon count for mobile

## 📚 References

- [Assimp Documentation](https://assimp-docs.readthedocs.io/)
- [LearnOpenGL - Model Loading](https://learnopengl.com/Model-Loading/Assimp)
