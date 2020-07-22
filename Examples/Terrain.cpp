#include "Terrain.h"
#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>



Terrain::Terrain(float xsize, float zsize, int xdivs, int zdivs, float smax, float tmax)
{
    srand(time(NULL));
    int nPoints = (xdivs + 1) * (zdivs + 1);
    std::vector<GLfloat> p(3 * nPoints);
    std::vector<GLfloat> n(3 * nPoints);
    std::vector<GLfloat> tex(2 * nPoints);
    // std::vector<GLfloat> tang(4 * nPoints);
    std::vector<GLuint> el(6 * xdivs * zdivs);

    float x2 = xsize / 2.0f;
    float z2 = zsize / 2.0f;
    float iFactor = (float)zsize / zdivs;
    float jFactor = (float)xsize / xdivs;
    float texi = smax / xdivs;
    float texj = tmax / zdivs;
    float x, z;
    int vidx = 0, tidx = 0;
    float yoff = 0;
    float freqFactorX = 1.0f / (xsize - 1);
    float freqFactorZ = 1.0f / (zsize - 1);
    for (int i = 0; i <= zdivs; i++) {
        float xoff = 0;
        z = iFactor * i - z2;
        for (int j = 0; j <= xdivs; j++) {
            x = jFactor * j - x2;
            p[vidx] = x;
            
            p[vidx + 1] = glm::perlin(glm::vec2(xoff, yoff)) * 5;
            
            p[vidx + 2] = z;
           

            n[vidx] = 0.0f;
            n[vidx + 1] = 0.0f;
            n[vidx + 2] = 0.0f;

            tex[tidx] = j * texi;
            tex[tidx + 1] = (zdivs - i) * texj;

            vidx += 3;
            tidx += 2;
            xoff += 0.2;
        }
        yoff += 0.2;
    }

    //for (int i = 0; i < nPoints; i++) {
    //    tang[i * 4 + 0] = 1.0f;
    //    tang[i * 4 + 1] = 0.0f;
    //    tang[i * 4 + 2] = 0.0f;
    //    tang[i * 4 + 3] = 1.0f;
    //}

    GLuint rowStart, nextRowStart;
    int idx = 0;
    glm::vec3 v1, v2, v3;
  
    glm::vec3 faceNormal;
    
    int v1Index, v2Index, v3Index;
    glm::vec3 normalized;
    for (int i = 0; i < zdivs; i++) {
        rowStart = (GLuint)(i * (xdivs + 1));
        nextRowStart = (GLuint)((i + 1) * (xdivs + 1));
        for (int j = 0; j < xdivs; j++) {
            // triangle 1
            el[idx] = rowStart + j;
            el[idx + 1] = nextRowStart + j;
            el[idx + 2] = nextRowStart + j + 1;
            v1Index = el[idx] * 3;
            v2Index = el[idx + 1] * 3;
            v3Index = el[idx + 2] * 3;
            v1 = glm::vec3(p[v1Index], p[v1Index + 1], p[v1Index + 2]);
            v2 = glm::vec3(p[v2Index], p[v2Index + 1], p[v2Index + 2]);
            v3 = glm::vec3(p[v3Index], p[v3Index + 1], p[v3Index + 2]);
            glm::vec3 a = v2 - v1;
            glm::vec3 b = v3 - v1;
            faceNormal = glm::normalize(glm::cross(a, b));
            n[v1Index] += faceNormal[0];
            n[v1Index + 1] += faceNormal[1];
            n[v1Index + 2] += faceNormal[2];
            n[v2Index] += faceNormal[0];
            n[v2Index] += faceNormal[1];
            n[v2Index + 2] += faceNormal[2];
            n[v3Index] += faceNormal[0];
            n[v3Index] += faceNormal[1];
            n[v3Index + 2] += faceNormal[2];


            // triangle 2
            el[idx + 3] = rowStart + j;
            el[idx + 4] = nextRowStart + j + 1;
            el[idx + 5] = rowStart + j + 1;
            v1Index = el[idx + 3] * 3;
            v2Index = el[idx + 4] * 3;
            v3Index = el[idx + 5] * 3;
            v1 = glm::vec3(p[v1Index], p[v1Index + 1], p[v1Index + 2]);
            v2 = glm::vec3(p[v2Index], p[v2Index + 1], p[v2Index + 2]);
            v3 = glm::vec3(p[v3Index], p[v3Index + 1], p[v3Index + 2]);
            a = v2 - v1;
            b = v3 - v1;
            faceNormal = glm::normalize(glm::cross(a, b));
            n[v1Index] += faceNormal[0];
            n[v1Index + 1] += faceNormal[1];
            n[v1Index + 2] += faceNormal[2];
            n[v2Index] += faceNormal[0];
            n[v2Index] += faceNormal[1];
            n[v2Index + 2] += faceNormal[2];
            n[v3Index] += faceNormal[0];
            n[v3Index] += faceNormal[1];
            n[v3Index + 2] += faceNormal[2];
            idx += 6;
        }
    }

    for (int i = 0; i < nPoints; i += 1) {
        glm::vec3 norm = { n[i * 3], n[i * 3 + 1], n[i * 3 + 2] };
        
        normalized = glm::normalize(norm);
        n[i * 3] = normalized[0];
        n[i * 3 + 1] = normalized[1];
        n[i * 3 + 2] = normalized[2];
        
    }




    initBuffers(&el, &p, &n, &tex);
}


