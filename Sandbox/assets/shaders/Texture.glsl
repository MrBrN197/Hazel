#type vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec3 v_Normal;

void main(){
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1);
	v_Normal = vec3(u_Transform * vec4(a_Normal, 0));
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_TexCoord;
in vec3 v_Normal;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){
	vec4 color = u_Color * texture(u_Texture, v_TexCoord * 10.f);
	vec3 lightDir = normalize(vec3(0.f, 1.f, 1.f));
	float dotproduct = dot(normalize(v_Normal), lightDir);
	if(dotproduct < 0){
		dotproduct = 0;
	}
	out_color = color * dotproduct;
	out_color = max(out_color, vec4(vec3(0.1f), 0.f));
	out_color.w = 1.f;
}