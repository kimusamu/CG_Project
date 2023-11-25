//#version 330 core
//
//in vec3 FragPos; //--- ��ְ��� ����ϱ� ���� ��ü�� ��ġ���� ���ؽ� ���̴����� �޾ƿ´�.
//in vec3 Normal;
//out vec4 FragColor;
//
//uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform vec3 lightPos;
//uniform vec3 viewPos;
//uniform vec3 light_Flag;
//
//void main () {
//
//   float ambientLight = 0.3; //--- �ֺ� ���� ����
//   vec3 ambient = ambientLight * lightColor; //--- �ֺ� ���� ��
//
//   vec3 normalVector = normalize(Normal);
//   vec3 lightDir = normalize(lightPos-FragPos);
//   float diffuseLight = max(dot(normalVector, lightDir), 0.0); //--- N�� L�� ���� ������ ���� ����: ���� ����
//   vec3 diffuse = diffuseLight * lightColor; //--- ��� �ݻ� ����: ����ݻ簪 * �������
//
//   float specularStrength = 0.3;
//   vec3 viewDir = normalize(viewPos - FragPos);
//   vec3 reflectDir = reflect(-lightDir, normalVector); //--- �ݻ� ����: reflect �Լ� - �Ի� ������ �ݻ� ���� ���
//   float specularLight = pow(max(dot(viewDir, reflectDir), 0.0),32); //--- V�� R�� ���������� ���� ����: ���� ����
//   vec3 specular = specularStrength*specularLight * lightColor; //--- �ſ� �ݻ� ����: �ſ�ݻ簪 * �������
//
//   vec3 result;
//   if(light_Flag.x==1)result+=ambient;
//   if(light_Flag.y==1)result+=diffuse;
//   if(light_Flag.z==1)result+=specular;
//   result *=objectColor;
//
//   //FragColor = vec4 (result, 1.0); // --- �ȼ� ���� ���
//   FragColor = vec4 (FragPos, 1.0); // --- �ȼ� ���� ���
//} 



#version 330

uniform vec4 vColor;
in vec3 out_Color; //--- ���ؽ� ���̴����Լ� ���� ����
out vec4 FragColor; //--- ���� ���

void main(void) {
   FragColor = vColor;  
    if (vColor.w > 0) {
        FragColor =  vec4(out_Color, 1.0);
    }
}

