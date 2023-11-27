#version 330

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_color;

out vec3 FragPos; //--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ������.
out vec3 Normal;

uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat4 viewTransform;

void main(void) 
{
   gl_Position =  projectionTransform *viewTransform * modelTransform*vec4 (in_position, 1.0);
   FragPos = vec3(modelTransform * vec4(in_position, 1.0));
   //FragPos = in_color;
   Normal = mat3(transpose(inverse(modelTransform))) * in_position; 
}