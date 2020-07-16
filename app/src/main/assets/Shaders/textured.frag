#version 300 es
out vec4 FragColor;
in vec2 uv;
uniform sampler2D DiffuseTexture;
void main()
{

    FragColor = texture(DiffuseTexture,uv);
}