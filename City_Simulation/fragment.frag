//#version 330 core
//
//in vec3 FragPos; //--- 노멀값을 계산하기 위해 객체의 위치값을 버텍스 세이더에서 받아온다.
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
//   float ambientLight = 0.3; //--- 주변 조명 세기
//   vec3 ambient = ambientLight * lightColor; //--- 주변 조명 값
//
//   vec3 normalVector = normalize(Normal);
//   vec3 lightDir = normalize(lightPos-FragPos);
//   float diffuseLight = max(dot(normalVector, lightDir), 0.0); //--- N과 L의 내적 값으로 강도 조절: 음수 방지
//   vec3 diffuse = diffuseLight * lightColor; //--- 산란 반사 조명값: 산란반사값 * 조명색상값
//
//   float specularStrength = 0.3;
//   vec3 viewDir = normalize(viewPos - FragPos);
//   vec3 reflectDir = reflect(-lightDir, normalVector); //--- 반사 방향: reflect 함수 - 입사 벡터의 반사 방향 계산
//   float specularLight = pow(max(dot(viewDir, reflectDir), 0.0),32); //--- V와 R의 내적값으로 강도 조절: 음수 방지
//   vec3 specular = specularStrength*specularLight * lightColor; //--- 거울 반사 조명값: 거울반사값 * 조명색상값
//
//   vec3 result;
//   if(light_Flag.x==1)result+=ambient;
//   if(light_Flag.y==1)result+=diffuse;
//   if(light_Flag.z==1)result+=specular;
//   result *=objectColor;
//
//   //FragColor = vec4 (result, 1.0); // --- 픽셀 색을 출력
//   FragColor = vec4 (FragPos, 1.0); // --- 픽셀 색을 출력
//} 



#version 330

uniform vec4 vColor;
in vec3 out_Color; //--- 버텍스 세이더에게서 전달 받음
out vec4 FragColor; //--- 색상 출력

void main(void) {
   FragColor = vColor;  
    if (vColor.w > 0) {
        FragColor =  vec4(out_Color, 1.0);
    }
}

