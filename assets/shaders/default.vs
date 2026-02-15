#version 460 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;

layout (location = 2) in vec2 v_uvcoord0;
layout (location = 3) in vec2 v_uvcoord1;
layout (location = 4) in vec2 v_uvcoord2;
layout (location = 5) in vec2 v_uvcoord3;

layout (location = 6) in vec4 v_color0;
layout (location = 7) in vec4 v_color1;
layout (location = 8) in vec4 v_color2;
layout (location = 9) in vec4 v_color3;

out vec3 f_position;
out vec3 f_normal;
out vec2 f_uvcoord;

out vec4 f_color0;
out vec4 f_color1;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    f_position = v_position;
    f_normal = v_normal;
    f_uvcoord = v_uvcoord0;

    f_color0 = v_color0;
    f_color1 = v_color1;

    gl_Position = projection * view * model * vec4(v_position, 1.0);

    // vec4 view_space = view * model * vec4(v_position, 1.0);

    // float sign_x = sign(view_space.x);
    // float sign_y = sign(view_space.y);
    // float sign_z = sign(view_space.z);
    // float factor = 5.5;
    // view_space.x = sign_x * sqrt(abs(view_space.x) * factor);
    // view_space.y = sign_y * sqrt(abs(view_space.y) * factor);
    // view_space.z = sign_z * sqrt(abs(view_space.z) * factor);

    // gl_Position = projection * view_space;
}