#program vertex
#version 330 core
uniform mat4 u_MVP;
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
out vec2 uv;
void main()
{
    gl_Position = u_MVP * vec4(vPos, 1.0);
    uv = vUV;
}

#program fragment
#version 330 core
uniform sampler2D u_ScreenTexture;
in vec2 uv;
out vec4 fragColor;
void main()
{
    vec4 texColor = texture(u_ScreenTexture, uv);
    texColor.rgb = 1.0 - texColor.rgb;
    fragColor = texColor;
}