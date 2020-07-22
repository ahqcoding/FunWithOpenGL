#version 430

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in vec3 WorldPos;
layout(binding=0) uniform sampler2D Tex1;

uniform struct LightInfo {
  vec4 Position;  // Light position in eye coords.
  vec3 La;        // Ambient light intesity
  vec3 L;         // Diffuse and specular light intensity
} Light;


layout( location = 0 ) out vec4 FragColor;

vec3 blinnPhong( vec3 position, vec3 n ) {
  // vec3 texColor = texture(Tex1, TexCoord).rgb;
  vec3 texColor = vec3(0.0, 0.0, 0.6);
  if(WorldPos.y > 3) {
    texColor = vec3(0.9, 0.9, 0.9);
  }
  else if(WorldPos.y > 0.5) {
    texColor = vec3(0.0, 0.7, 0.0);
  } else if (WorldPos.y > 0) {
    texColor = vec3(0.3, 0.3, 0.0);
  }
  
  vec3 ambient = Light.La * texColor;
  vec3 s = normalize( Light.Position.xyz - position );
  float sDotN = max( dot(s,n), 0.0 );
  vec3 diffuse = texColor * sDotN;
  
  return ambient + Light.L * diffuse;
}

void main() {
    FragColor = vec4(blinnPhong(Position, normalize(Normal)), 1.0);
}
