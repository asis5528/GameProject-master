#version 300 es
precision mediump float;
out vec4 FragColor;
in vec2 uv;
in vec2 blurTexCoords[11];
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float data;

float kernals[11] =float[] (0.0093,0.028002,0.065984,0.121703,0.175713,0.198596, 0.175713,0.121703,0.065984,0.028002,0.0093);
void main()
{
    FragColor = vec4(0.0);

    for(int i=0;i<11;i++){
        FragColor += texture(tex0, blurTexCoords[i]) * kernals[i];
    }
    /*
    FragColor += textureLod(tex0, blurTexCoords[1],2.) * 0.028002;
    FragColor += textureLod(tex0, blurTexCoords[2],2.) * 0.065984;
    FragColor += textureLod(tex0, blurTexCoords[3],2.) * 0.121703;
    FragColor += textureLod(tex0, blurTexCoords[4],2.) * 0.175713;
    FragColor += textureLod(tex0, blurTexCoords[5],2.) * 0.198596;
    FragColor += textureLod(tex0, blurTexCoords[6],2.) * 0.175713;
    FragColor += textureLod(tex0, blurTexCoords[7],2.) * 0.121703;
    FragColor += textureLod(tex0, blurTexCoords[8],2.) * 0.065984;
    FragColor += textureLod(tex0, blurTexCoords[9],2.) * 0.028002;
    FragColor += textureLod(tex0, blurTexCoords[10],2.) * 0.0093;

*/
}

