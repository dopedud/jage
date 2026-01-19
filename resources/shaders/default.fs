#version 460 core

in vec3 f_position;
in vec3 f_normal;
in vec3 f_uvcoord;

in vec4 f_color1;
in vec4 f_color2;

out vec4 color;

uniform sampler2D texture_sampler;

void main()
{
    color = f_color1;
    // color = texture(texture_sampler, f_texcoord);
}