#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;
std::string ResourceManager::resource_path;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(const std::string& name)
{
    auto it = Shaders.find(name);
    if (it != Shaders.end())
        return it->second;

    std::cerr << "ERROR::SHADER: Shader not found with name " << name << std::endl;
    return Shader();
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, const std::string& name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(const std::string& name)
{
    auto it = Textures.find(name);
    if (it != Textures.end())
        return it->second;

    std::cerr << "ERROR::Texture: Texture not found with name " << name << std::endl;
    return Texture2D();
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    std::string vertexCode, fragmentCode, geometryCode;

    try
    {
        std::ifstream vertexShaderFile(resource_path + "/" + vShaderFile), fragmentShaderFile(resource_path + "/" + fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if (gShaderFile)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryCode = gShaderStream.str();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR::SHADER: Failed to read shader files: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = gShaderFile ? geometryCode.c_str() : nullptr;

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    Texture2D texture;
    int nrChannels;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
        nrChannels = 4;
    }
    else
    {
        texture.Internal_Format = GL_RGB;
        texture.Image_Format = GL_RGB;
        nrChannels = 3;
    }

    int width = 0, height = 0;
    sf::Image image;
    image.loadFromFile(resource_path + "/" + file);
    unsigned char* data = textureToCharArray(image, width, height);

    if (data)
    {
        texture.Generate(width, height, data);
        delete[] data;
    }
    else
    {
        std::cerr << "ERROR::TEXTURE: Failed to generate texture for " << file << std::endl;
    }

    return texture;
}

void ResourceManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

void ResourceManager::Init()
{
#ifdef DEBUG
    std::string dirPath = getPath().string();
    replaceChar(dirPath, '\\', '/');
    std::cout << "Debug Build \n";
    std::string resourcePath = dirPath + "/resources";
    std::cout << "Resource Path: " << resourcePath << "\n";
#elif defined(RELEASE)
    auto exePath = std::filesystem::current_path().string();
    replaceChar(exePath, '\\', '/');
    auto resourcePath = exePath + "/resources";
    std::cout << "Release Build \n";
#endif
    ResourceManager::resource_path = resourcePath;
}

unsigned char* ResourceManager::textureToCharArray(const sf::Image& image, int& width, int& height)
{
    const sf::Uint8* pixels = image.getPixelsPtr();
    unsigned int width_ = image.getSize().x;
    unsigned int height_ = image.getSize().y;

    size_t size = width_ * height_ * 4;

    unsigned char* pixelArray = new unsigned char[size];
    std::memcpy(pixelArray, pixels, size);

    width = width_;
    height = height_;

    return pixelArray;
}

void ResourceManager::replaceChar(std::string& str, char oldChar, char newChar)
{
    for (char& c : str)
    {
        if (c == oldChar)
        {
            c = newChar;
        }
    }
}

std::filesystem::path ResourceManager::getPath()
{
    std::string target = "SFML";
    std::filesystem::path currentPath = std::filesystem::current_path();
    while (currentPath.filename().string() != target)
    {
        currentPath = currentPath.parent_path();
    }
    return currentPath;
}