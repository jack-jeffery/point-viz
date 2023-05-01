#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

uniform mat4 view;
uniform mat4 projection;

void main() 
{
   gl_PointSize = 2.0f;
   gl_Position = projection * view * vec4(position, 1.0);
   fragColor = color;
}