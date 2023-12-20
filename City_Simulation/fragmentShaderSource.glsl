#version 330 core

in vec3 FragPos; //--- ��ְ��� ����ϱ� ���� ��ü�� ��ġ���� ���ؽ� ���̴����� �޾ƿ´�.
in vec3 Normal;
in vec2 TexCord;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D outTexture;

void main ()
{
	float ambientLight = 0.65; //--- �ֺ� ���� ����
	vec3 ambient = ambientLight * lightColor; //--- �ֺ� ���� ��

	vec3 normalVector = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);
	float diffuseLight = max(dot(normalVector, lightDir), 0.0); //--- N�� L�� ���� ������ ���� ����: ���� ����
	vec3 diffuse = diffuseLight * lightColor; //--- ��� �ݻ� ����: ����ݻ簪 * �������

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalVector); //--- �ݻ� ����: reflect �Լ� - �Ի� ������ �ݻ� ���� ���
	float specularLight = pow(max(dot(viewDir, reflectDir), 0.0),256); //--- V�� R�� ���������� ���� ����: ���� ����
	vec3 specular = specularLight * lightColor; //--- �ſ� �ݻ� ����: �ſ�ݻ簪 * �������

	vec3 result = (ambient + diffuse + specular) * objectColor; //--- ���� ���� ������ �ȼ� ����: (�ֺ�+����ݻ�+�ſ�ݻ�����)*��ü ����


	FragColor = vec4 (result, 1.0f); // --- �ȼ� ���� ���
	FragColor = texture(outTexture, TexCord)*FragColor;
} 