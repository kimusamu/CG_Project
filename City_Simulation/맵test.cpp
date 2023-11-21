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
   -0.5f, 0.f,0.5f, //�Ʒ���
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
    glutMouseFunc(Mouse); // ���콺 �Է� �ݹ��Լ� ����
    glutMotionFunc(MouseMove); //���콺 Ŭ���� ���¿��� ������
    glutMainLoop();
}
void make_vertexShaders()
{
    vertexSource = filetobuf("vertex.vert");
    //--- ���ؽ� ���̴� ��ü �����
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
    glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
    //--- ���ؽ� ���̴� �������ϱ�
    glCompileShader(vertexShader);
    //--- �������� ����� ���� ���� ���: ���� üũ
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
        return;
    }
}

void make_fragmentShaders()
{
    fragmentSource = filetobuf("fragment.frag");
    //--- �����׸�Ʈ ���̴� ��ü �����
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
    //--- �����׸�Ʈ ���̴� ������
    glCompileShader(fragmentShader);
    //--- �������� ����� ���� ���� ���: ������ ���� üũ
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
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
        std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
        exit(-1);
    }
    glUseProgram(ShaderProgramID);

    return ShaderProgramID;
}
bool depth = false;
GLuint VAO, VBO[2];
void InitBuffer()
{

    glGenVertexArrays(1, &VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
    glBindVertexArray(VAO); //--- VAO�� ���ε��ϱ�
    glGenBuffers(2, VBO); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
    //--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    //--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
    //--- triShape �迭�� ������: 9 * float
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
    //--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //--- attribute �ε��� 0���� ��밡���ϰ� ��
    glEnableVertexAttribArray(0);
    //--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    //--- ���� colors���� ���ؽ� ������ �����Ѵ�.
    //--- colors �迭�� ������: 9 *float 
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
    //--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //--- attribute �ε��� 1���� ��� �����ϰ� ��.
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

    unsigned int vColorLocation = glGetUniformLocation(shaderID, "vColor");//���󺯰�
    unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
    unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform");
    unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");

    glm::mat4 kTransform = glm::mat4(1.0f);
    kTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
    kTransform = glm::translate(kTransform, glm::vec3(0.0, 0.0, -5.0f));

    //���� ����
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &kTransform[0][0]);

    //���� ��ȯ
    glm::mat4 vTransform = glm::mat4(1.0f);
    glm::vec3 cameraPos; //--- ī�޶� ��ġ
    glm::vec3 cameraDirection; //--- ī�޶� �ٶ󺸴� ����

    cameraPos = glm::vec3(cameraX, cameraY, cameraZ); //--- ī�޶� ��ġ
    cameraDirection = glm::vec3(cameraX, cameraY-0.01, cameraZ - 0.02); //--- ī�޶� �ٶ󺸴� ����
    glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, -1.f); //--- ī�޶� ���� ����

    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &vTransform[0][0]);
    glm::mat4 Rz = glm::mat4(1.0f); //--- ȸ�� ��ȯ ���

    //�簢��
    Rz = glm::rotate(Rz, glm::radians(yRotate * 1.0f), glm::vec3(0.0, 1.0, 0.0));

        
        //�ٴ�

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
                //�ʱ�ȭ
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
                if (rec[i][j].check) { //���� ����ִ� ����
                    rec[i][j].check = false;
                }
            }
        }
    }
}

GLvoid MouseMove(int x, int y) //���콺�� Ŭ���� ���¿��� �����϶�
{
    float ox, oy;
    ConvertWindowXYOpenGLXY(x, y, &ox, &oy);

 /*   for (int i = 0; i < 15; ++i) {
        if (shape[i].grab) {
            shape[i].x = ox;
            shape[i].y = oy;
        }
    }*/

    glutPostRedisplay(); //ȭ�� ���ΰ�ħ
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