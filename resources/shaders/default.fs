#version 460 core

in vec3 f_position;
in vec3 f_normal;
in vec2 f_uvcoord;

in vec4 f_color1;
in vec4 f_color2;

out vec4 color;

uniform sampler2D texture_albedo;

void main()
{
    // color = vec4(f_normal, 1.0);
    color = texture(texture_albedo, f_uvcoord);
}