#pragma once

#include <GL/glew.h>
#include "Drawable.h"

#include <vector>

class Grid : public Drawable {
private:
    std::vector<GLuint> buffers;
    GLuint vao;
    GLsizei nVerts;

public:
    Grid(float size = 10.0f, int nDivisions = 10);
    virtual ~Grid();
    void render() const override;
};


