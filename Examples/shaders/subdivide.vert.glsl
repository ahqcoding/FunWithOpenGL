#version 430

layout(location=0) in vec3 vVertex;
void main() {
    gl_Position =  vec4(vVertex, 1);
}