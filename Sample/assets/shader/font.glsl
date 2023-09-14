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
uniform float u_PixelRange;
uniform sampler2D u_FontTexture;
in vec4 color;
in vec2 uv;
out vec4 fragColor;

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

float screenPxRange() {
    vec2 unitRange = vec2(u_PixelRange)/vec2(textureSize(u_FontTexture, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(uv);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

void main() {
    vec3 msd = texture(u_FontTexture, uv).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    fragColor.a = color.a * opacity;
    fragColor.rgb = color.rgb;
}