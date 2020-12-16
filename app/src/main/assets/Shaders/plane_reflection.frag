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

void main()
{
    normalColor.rgb = normal;
    positionColor.a = 1.0;
    positionColor.rgb = pos;
    col=vec4( 0.0);

    FragColor = vec4(0.);
}

