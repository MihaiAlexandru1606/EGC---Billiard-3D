#version 330

// lumina
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform sampler2D texture;
uniform int useTexture;

in vec3 frag_color; 
in vec2 texcoord;


layout(location = 0) out vec4 out_color;

void main()
{

	vec3 object_color;

	if(useTexture == 1) {
		object_color = vec3(texture2D(texture, texcoord));
	} else {
		object_color = frag_color;
	}

	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = reflect(L, N);

	float ambient_light = 0.25 * material_kd;

	float diffuse_light =  material_kd * max (dot(N, L), 0);

	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow( max( dot(N, H) , 0),  material_shininess);
	}
 
	float att = 1 /pow(length(light_position - world_position), 2) * 2;

	vec3 color_f;
	float light;

	light = ambient_light + att * (specular_light + diffuse_light);

	color_f = object_color * light;
	out_color = vec4(color_f, 1);
}