#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <time.h>

GLint width = 800;
GLint height = 800;


GLvoid drawScene();
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMove(int x, int y);
GLvoid ConvertWindowXYOpenGLXY(int x, int y, float* ox, float* oy);
GLvoid SpecialKeyBoard(int key, int x, int y);
GLvoid Reshape(int w, int h);
GLvoid TimerFunc(int x);

void InitBuffer();
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
char* filetobuf(const char* file)
{
    FILE* fptr;
    long length;
    char* buf;
    fptr = fopen(file, "rb"); // Open file for reading 
    if (!fptr) // Return NULL on failure 
        return NULL;
    fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
    length = ftell(fptr); // Find out how many bytes into the file we are 
    buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
    fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
    fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
    fclose(fptr); // Close the file 
    buf[length] = 0; // Null terminator 
    return buf; // Return the buffer 
}

float vertexPosition[] = {
   -0.5f, 0.f,0.5f, //아랫면
   -0.5f, 0.f,-0.5f,
   0.5f,  0.f,-0.5f,
   0.5f,  0.f,0.5f,
};

float vertexColor[] = {
    0
};

GLchar* vertexSource, * fragmentSource;
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;

struct REC {
    GLfloat x, y, z;
    GLfloat r, g, b;
    GLboolean check = false;
};

REC rec[10][10];

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Example1");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    make_vertexShaders();
    make_fragmentShaders();
    shaderID = make_shaderProgram();
    InitBuffer();
    glutKeyboardFunc(KeyBoard);
    glutSpecialFunc(SpecialKeyBoard);
    glutTimerFunc(10, TimerFunc, 1);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse); // 마우스 입력 콜백함수 지정
    glutMotionFunc(MouseMove); //마우스 클릭한 상태에서 움직임
    glutMainLoop();
}
void make_vertexShaders()
{
    vertexSource = filetobuf("vertex.vert");
    //--- 버텍스 세이더 객체 만들기
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //--- 세이더 코드를 세이더 객체에 넣기
    glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
    //--- 버텍스 세이더 컴파일하기
    glCompileShader(vertexShader);
    //--- 컴파일이 제대로 되지 않은 경우: 에러 체크
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
}

void make_fragmentShaders()
{
    fragmentSource = filetobuf("fragment.frag");
    //--- 프래그먼트 세이더 객체 만들기
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //--- 세이더 코드를 세이더 객체에 넣기
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
    //--- 프래그먼트 세이더 컴파일
    glCompileShader(fragmentShader);
    //--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
}
GLuint make_shaderProgram()
{
    GLuint ShaderProgramID;

    ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderProgramID, vertexShader);
    glAttachShader(ShaderProgramID, fragmentShader);
    glLinkProgram(ShaderProgramID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];

    glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
        std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
        exit(-1);
    }
    glUseProgram(ShaderProgramID);

    return ShaderProgramID;
}
bool depth = false;
GLuint VAO, VBO[2];
void InitBuffer()
{

    glGenVertexArrays(1, &VAO); //--- VAO 를 지정하고 할당하기
    glBindVertexArray(VAO); //--- VAO를 바인드하기
    glGenBuffers(2, VBO); //--- 2개의 VBO를 지정하고 할당하기
    //--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    //--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
    //--- triShape 배열의 사이즈: 9 * float
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
    //--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //--- attribute 인덱스 0번을 사용가능하게 함
    glEnableVertexAttribArray(0);
    //--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    //--- 변수 colors에서 버텍스 색상을 복사한다.
    //--- colors 배열의 사이즈: 9 *float 
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
    //--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //--- attribute 인덱스 1번을 사용 가능하게 함.
    glEnableVertexAttribArray(1);
}


float yRotate = 0.f;
float cameraZ = 5.0f;
float cameraX = 0.0f;
float cameraY = 7.f;
int pressH = 0;
int cameradir = 0;


float convert(float x)
{
    return (x - 400) * (1.0 / 400);
}

GLUquadricObj* Planet;
GLvoid drawScene() {

    glUseProgram(shaderID);
    glBindVertexArray(VAO);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    unsigned int vColorLocation = glGetUniformLocation(shaderID, "vColor");//색상변경
    unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
    unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform");
    unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");

    glm::mat4 kTransform = glm::mat4(1.0f);
    kTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
    kTransform = glm::translate(kTransform, glm::vec3(0.0, 0.0, -5.0f));

    //원근 투영
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &kTransform[0][0]);

    //뷰잉 변환
    glm::mat4 vTransform = glm::mat4(1.0f);
    glm::vec3 cameraPos; //--- 카메라 위치
    glm::vec3 cameraDirection; //--- 카메라 바라보는 방향

    cameraPos = glm::vec3(cameraX, cameraY, cameraZ); //--- 카메라 위치
    cameraDirection = glm::vec3(cameraX, cameraY-0.01, cameraZ - 0.02); //--- 카메라 바라보는 방향
    glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, -1.f); //--- 카메라 위쪽 방향

    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &vTransform[0][0]);
    glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 변환 행렬

    //사각형
    Rz = glm::rotate(Rz, glm::radians(yRotate * 1.0f), glm::vec3(0.0, 1.0, 0.0));

        
        //바닥

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {


                if ((i + j) % 2 == 0) 
                    glUniform4f(vColorLocation, 0.0f, 1.0f, 0.0f, 0.0f);            
                else
                    glUniform4f(vColorLocation, 0.02f, 0.9f, 0.0f, 0.0f);

            /*    if (rec[i][j].check) {
                    glUniform4f(vColorLocation, 1.0f, 0.0f, 0.0f, 0.5f);
                }*/
                
                Rz = glm::translate(Rz, glm::vec3(-7.f, 0.f, -7.f));
                Rz = glm::translate(Rz, glm::vec3(rec[i][j].x  + (1.5 * i), 0.f, rec[i][j].z + (1.5 * j)));
                Rz = glm::scale(Rz, glm::vec3(1.5f, 1.f, 1.5f));
                glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Rz));
                glDrawArrays(GL_QUADS, 0, 4);
                //초기화
                Rz = glm::scale(Rz, glm::vec3(1.f / 1.5f, 1.f, 1.f / 1.5f));
                Rz = glm::translate(Rz, glm::vec3(rec[i][j].x - (1.5 * i), 0.f, rec[i][j].z - (1.5 * j)));
                Rz = glm::translate(Rz, glm::vec3(7.f, 0.f, 7.f));

            }
        }
      

    glutSwapBuffers();

}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}



GLvoid ConvertWindowXYOpenGLXY(int x, int y, float* ox, float* oy)
{
    *ox = (float)(x - (float)width / 2.0) * (float)(1.0 / (float)(width / 2.0));
    *oy = -(float)(y - (float)height / 2.0) * (float)(1.0 / (float)(height / 2.0));
}

GLvoid Mouse(int button, int state, int x, int y) {
    float ox, oy;
    ConvertWindowXYOpenGLXY(x, y, &ox, &oy);

                        std::cout << ox << " " << oy << std::endl;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; j++) {
                if (sqrt(pow(ox - rec[i][j].x, 2) + pow(oy - rec[i][j].y, 2)) <= 1.5 / 2) {
                        rec[i][j].check = true;
                        break;
                    }
                
            }
        }
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; j++) {
                if (rec[i][j].check) { //내가 잡고있는 도형
                    rec[i][j].check = false;
                }
            }
        }
    }
}

GLvoid MouseMove(int x, int y) //마우스를 클릭한 상태에서 움직일때
{
    float ox, oy;
    ConvertWindowXYOpenGLXY(x, y, &ox, &oy);

 /*   for (int i = 0; i < 15; ++i) {
        if (shape[i].grab) {
            shape[i].x = ox;
            shape[i].y = oy;
        }
    }*/

    glutPostRedisplay(); //화면 새로고침
}


GLvoid KeyBoard(unsigned char key, int x, int y) {
    int minusRan = 0;
    switch (key) {
    case 'h':
    case 'H':
        pressH = 1 - pressH;
        break;
    }

    glutPostRedisplay();
}

GLvoid SpecialKeyBoard(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        cameraY -= 0.1f;
        break;
    case GLUT_KEY_DOWN:
        cameraY += 0.1f;
        break;
    case GLUT_KEY_LEFT:
        cameraX -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        cameraX += 0.1f;
        break;
    }
    glutPostRedisplay();
}
GLvoid TimerFunc(int x)
{
    switch (x)
    {
    case 1:
        if (pressH) {
                cameraZ += 0.1f;
                cameraY += 0.05f;
                if (cameraZ >= 30 && cameraY >= 1) pressH = 0;
                //std::cout << cameraZ << std::endl;
        }
        break;
    }

    glutTimerFunc(10, TimerFunc, 1);
    glutPostRedisplay();
}