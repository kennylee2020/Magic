#program vertex
#version 330 core
uniform mat4 MVP;
layout(location = 0) in vec2 vPos;
layout(location = 1) in vec3 vCol;
layout(location = 2) in vec2 vUV;
varying vec3 color;
varying vec2 uv;
void main()
{
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
    color = vCol;
    uv = vUV;
};

#program fragment
#version 330 core
uniform sampler2D u_Texture;
varying vec3 color;
varying vec2 uv;
void main()
{
    gl_FragColor = texture(u_Texture,uv) * vec4(color, 1.0);
};