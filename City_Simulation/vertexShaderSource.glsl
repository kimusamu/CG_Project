
#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCord;

out vec3 FragPos; //--- 객체의 위치값을 프래그먼트 세이더로 보낸다.
out vec3 Normal;
out vec2 TexCord;

uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat4 viewTransform;

void main(void) 
{
	gl_Position =  projectionTransform *viewTransform * modelTransform*vec4 (vPos, 1.0);
	FragPos = vec3(modelTransform * vec4(vPos, 1.0));
	Normal = mat3(transpose(inverse(modelTransform))) * vNormal;
	TexCord = vTexCord;
}