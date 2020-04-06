#version 300 es
precision mediump float;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
out vec2 uv;
out vec2 blurTexCoords[11];
uniform float height;

void main()
{

    uv = aUV;
    gl_Position = vec4(aPos.x,aPos.y,0.0,1.0);
    float pixelSize = 1.0/height;
    for(int i=-5;i<5;i++){
        blurTexCoords[i+5]=aUV+vec2(0.0,pixelSize*float(i));
    }
   }

