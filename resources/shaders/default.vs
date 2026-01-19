#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_uvcoord;

layout (location = 3) in vec4 v_color1;
layout (location = 4) in vec4 v_color2;

out vec3 f_position;
out vec3 f_normal;
out vec2 f_uvcoord;

out vec4 f_color1;
out vec4 f_color2;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    f_position = v_position;
    f_normal = v_normal;
    f_uvcoord = v_uvcoord;

    f_color1 = v_color1;
    f_color2 = v_color2;

    gl_Position = projection * view * model * vec4(v_position, 1.0);
}