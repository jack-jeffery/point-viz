#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;
out float colorModifier;

uniform mat4 view;
uniform mat4 projection;
uniform float pointSize;

void main() 
{
   gl_PointSize = pointSize;
   gl_Position = projection * view * vec4(position, 1.0);
   fragColor = color;
}