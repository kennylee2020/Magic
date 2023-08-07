#program vertex
#version 330 core
uniform mat4 u_MVP;
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec4 vCol;
out vec4 color;
out vec2 uv;
void main()
{
    gl_Position = u_MVP * vec4(vPos, 1.0);
    color = vCol;
    uv = vUV;
}

#program fragment
#version 330 core
uniform sampler2D u_Texture;
in vec4 color;
in vec2 uv;
out vec4 fragColor;
void main()
{
    vec4 texColor = texture(u_Texture, uv);
    fragColor = texColor * color;
}