#version 460 core

in vec3 f_position;
in vec4 f_color;
in vec2 f_texcoord;

out vec4 color;

uniform sampler2D texture_sampler;

void main()
{
    // color = f_color;
    color = texture(texture_sampler, f_texcoord);
}