#version 430 core 
in layout(location = 0) vec3 vposition; //0
in layout(location = 1) vec2 vtexcoord; //2

out vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	texcoord = vtexcoord;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
