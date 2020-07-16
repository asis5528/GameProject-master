#version 300 es
precision mediump float;
out vec4 FragColor;
in vec2 uv;
uniform sampler2D tex5;
vec3 inp = vec3(1.03,0.0,0.0);
vec3 outp = vec3(0.0,1.0,0.0);
float strength = 0.3;
float outputColorStrength = 2.0;
int mask = 1;
void main()
{




    vec3 color = texture(tex5,uv).xyz;
    vec3 col2 = color;
    float ilength = length(inp);
    float gradient =(color.x+color.y+color.z)/3.;
    float clength = length(color)*(1.5-gradient);

    float lendiff = abs(ilength-clength)*gradient*5.;



    vec3 color2 = color*(1.5-(clamp(gradient,0.,1.)));

    vec3 tdiff = abs(inp-outp);
    vec3 diff = abs(color-inp);
    vec3 col;
    if((diff.x+diff.y+diff.z)/3.<strength){
        col +=1.;
    }
    color*=1.-col.r;
    vec3 cc;
    if(uv.x<0.7){
        cc = texture(tex5,uv+vec2(0.3,0.0)).xyz;
    }
    vec3 changedColor = (col*diff*outp);

        changedColor+=outp*changedColor.r;


    // changedColor.r = changedColor.g;
    vec3 finalCol =color+changedColor*outputColorStrength;
if(mask==1){
    FragColor = vec4(col.r);
}else{
    FragColor = vec4(finalCol,1.);
}

}

