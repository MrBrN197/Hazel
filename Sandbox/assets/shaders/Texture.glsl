#type vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main(){
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){
	vec4 textureColor = texture(u_Texture, v_TexCoord);
	out_color = (textureColor * textureColor.a) + u_Color * (1 - textureColor.a);
	out_color.a = u_Color.a + textureColor.a;
}