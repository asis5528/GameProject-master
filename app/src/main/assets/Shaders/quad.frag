#version 300 es
precision mediump float;
out vec4 FragColor;
in vec2 uv;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D tex5;
uniform float data;
uniform float exposure;




void main()
{
    const float gamma = 1.2;
//const float exposure = 0.2;
   vec3 sceneColor = texture(tex1,uv).rgb;
    vec3 blurColor = texture(tex0,uv).rgb;
    vec3 normalColor = texture(tex3,uv).rgb;
   // sceneColor+=blurColor;

    vec3 result = vec3(1.0) - exp(-sceneColor * 1.);
    result = pow(result, vec3(1.0 / gamma));

    FragColor = vec4(result+blurColor*1.4, 1.0);


}

