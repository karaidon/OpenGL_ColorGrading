#version 430 core

out vec4 FragCol;

in  vec2 TexCoords;
uniform sampler3D colourLUT;
uniform sampler2D frameBuf;

const int LUT_FULL_WIDTH = 1024;
const int LUT_SQUARE_DIM = 32;


void main()
{             
  vec2 coords = TexCoords;
  float depth = texture2D(depthBuff, TexCoords).x;
  vec2 texelSz = (vec2(1.0f, 1.0f) / textureSize(frameBuf, 0));

  vec3 inColor = vec3(0,0,0);
  inColor = texture(frameBuf, coords).rgb;

  FragCol = vec4(texture(colourLUT, inColor).rgb, 1.0f);
}
