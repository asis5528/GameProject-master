#version 300 es
precision mediump float;
out vec4 FragColor;
in vec2 uv;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float data;
void main()
{
    vec2 st = gl_FragCoord.xy/vec2(512.0,512.);
    st = fract(st*3.);
    st-=vec2(0.5);
    float c = smoothstep(0.2,0.1,length(st));
   // FragColor= (texture(tex0,uv)*2.3+texture(tex1,uv)*0.6)*0.5;
    FragColor = texture(tex1,uv)+texture(tex0,uv,4.);
    //FragColor = vec4(uv,0.,1.);
}

