#version 300 es
out vec4 FragColor;
in vec2 uv;
in vec4 weight;
uniform sampler2D DiffuseTexture;
void main()
{

    FragColor = texture(DiffuseTexture,uv);
   // FragColor = weight;
}