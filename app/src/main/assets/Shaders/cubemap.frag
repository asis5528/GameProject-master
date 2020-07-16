#version 300 es
precision mediump float;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 col;
layout (location = 2) out vec4 positionColor;
layout (location = 3) out vec4 normalColor;
in vec2 uv;
in vec3 normal;
in vec3 position;
in vec3 pos;
uniform samplerCube tex;
void main()
{
    positionColor.rgb = pos;
    normalColor.rgb = normal;
    col = vec4(0.);
    FragColor = texture(tex,vec3(position.x,1.-position.y,position.z))*1.0;
}

