#version 330

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_coord;
layout(location = 3) in vec3 vertex_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 color;
uniform float distance;
uniform int isTacActive;
uniform float angle;

out vec3 frag_color;
out vec2 texcoord;

// Output values to fragment shader
out vec3 world_position;
out vec3 world_normal;

void main()
{

	world_position = (Model * vec4(vertex_position, 1)).xyz;
	world_normal = normalize( mat3(Model) * vertex_normal );


	frag_color = color;
	texcoord = vertex_coord;

	gl_Position = Projection * View * Model * vec4(distance * isTacActive * sin(-angle) + vertex_position.x, vertex_position.y, distance * isTacActive * cos(-angle) + vertex_position.z, 1.0);
}