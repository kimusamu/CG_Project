#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <time.h>
#include <vector>


struct Objectload {

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    std::vector< glm::vec3 > outvertex, outnormal;
    std::vector< glm::vec2 > outuv;

    float sumX{ 0.0 }, sumY{ 0.0 }, sumZ{ 0.0 };
    float aveX{ 0.0 }, aveY{ 0.0 }, aveZ{ 0.0 };
    float scaleX{ 0.0 }, scaleY{ 0.0 }, scaleZ{ 0.0 };
    float minX{ 0.0 }, minY{ 0.0 }, minZ{ 0.0 };
    float maxX{ 0.0 }, maxY{ 0.0 }, maxZ{ 0.0 };
    float scaleAll{ 0.0 };

    float sizeX{ 0.0 }, sizeY{ 0.0 }, sizeZ{ 0.0 };
    unsigned int texture;

    int loadObj(const char* filename);
    void InitTexture(const char* filename);
}; int Objectload::loadObj(const char* filename)
{
    FILE* objFile;

    fopen_s(&objFile, filename, "rb");

    if (objFile == NULL) {
        printf("Impossible to open the file !\n");
        return false;
    }
    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(objFile, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

            if (vertex.x < minX) minX = vertex.x;
            if (vertex.y < minY) minY = vertex.y;
            if (vertex.z < minZ) minZ = vertex.z;
            if (vertex.x > maxX) maxX = vertex.x;
            if (vertex.y > maxY) maxY = vertex.y;
            if (vertex.z > maxZ) maxZ = vertex.z;
            sumX += vertex.x;
            sumY += vertex.y;
            sumZ += vertex.z;

            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
            int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
            /* if (matches != 9) {
                 printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                 return false;
             }*/
            if (matches == 9)
            {
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
            else if (matches == 12)
            {
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[2]);
                vertexIndices.push_back(vertexIndex[3]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[2]);
                uvIndices.push_back(uvIndex[3]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[2]);
                normalIndices.push_back(normalIndex[3]);
            }
        }
    }

    std::cout << "minX: " << minX << " minY: " << minY << " minZ: " << minZ << std::endl;
    std::cout << "maxX: " << maxX << " maxY: " << maxY << " maxZ: " << maxZ << std::endl;

    aveX = sumX / vertexIndices.size();
    aveY = sumY / vertexIndices.size();
    aveZ = sumZ / vertexIndices.size();
    scaleX = (1.0 - maxX) * 10 + 1;
    scaleY = (1.0 - maxY) * 10 + 1;
    scaleZ = (1.0 - maxZ) * 10 + 1;

    if (scaleX > scaleY) {
        if (scaleY > scaleZ)
            scaleAll = scaleZ;
        else
            scaleAll = scaleY;
    }
    else if (scaleX < scaleY) {
        if (scaleX < scaleZ)
            scaleAll = scaleX;
        else
            scaleAll = scaleZ;
    }
    std::cout << "aveX: " << aveX << " aveY: " << aveY << " aveZ: " << aveZ << std::endl;

    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        outvertex.push_back(vertex);
    }
    for (unsigned int i = 0; i < uvIndices.size(); i++) {
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 vertex = temp_uvs[uvIndex - 1];
        outuv.push_back(vertex);
    }
    for (unsigned int i = 0; i < normalIndices.size(); i++) {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 vertex = temp_normals[normalIndex - 1];
        outnormal.push_back(vertex);
    }
    return outvertex.size();
}
//텍스쳐 로딩 함수
void Objectload::InitTexture(const char* filename)
{
    glGenTextures(1, &texture);
    stbi_set_flip_vertically_on_load(true);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 텍스처 wrapping/filtering 옵션 설정(현재 바인딩된 텍스처 객체에 대해)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 텍스처 로드 및 생성
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
