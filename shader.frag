#version 330 core

in vec3 TexCoord;
out vec4 Color;
uniform sampler2D Texture;

void main()
{
	Color = texture(Texture, TexCoord);
	//Color = vec4(1, 1, 1, 1);
}
