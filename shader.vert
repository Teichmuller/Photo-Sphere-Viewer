#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 texCoord;

uniform mat4 transform;
uniform mat4 projection;

out vec3 TexCoord;

void main()
{
	/// leave to initial program
	// float sv = sin(vertex.s);
	// float cv = cos(vertex.s);
	// float sh = sin(vertex.t);
	// float ch = cos(vertex.t);
	// vec3 cartesian = vec3(cv * ch, sv, cv * sh);
    TexCoord = texCoord;
    gl_Position = projection * transform * vec4(vertex, 1.0);
}

