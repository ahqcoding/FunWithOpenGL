#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;
out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;
out vec3 WorldPos;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

uniform float time;
const float amplitude = 0.5;
const float frequency = 4;
const float PI = 3.14159;

void main() {
    float distance = length(VertexPosition);
    float y = amplitude * sin(-PI * distance * frequency + time);

    Normal = normalize( NormalMatrix * VertexNormal);
    WorldPos = VertexPosition;
    Position = ( ModelViewMatrix * vec4(VertexPosition,1.0) ).xyz;
    TexCoord = VertexTexCoord;
    gl_Position = MVP * vec4(VertexPosition.x, y, VertexPosition.z,1.0);
}
