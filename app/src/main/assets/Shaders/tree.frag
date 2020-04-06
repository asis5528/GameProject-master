#version 300 es
precision mediump float;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 col;
in vec2 uv;
in vec3 normal;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float fac;

void main()
{

    vec4 t =  texture(tex1,uv);
    float te = (t.r+t.g+t.b)/3.;
    if(t.x>0.2){
        col = t*1.5*fac;
    }else{
        col = vec4(0.0,0.0,0.0,1.0);
    }

    FragColor = texture(tex0,uv);

}

