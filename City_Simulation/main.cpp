#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 10.f

#include "shader.h"
#include "load_OBJ.h"
using namespace std;

int windowWidth = 800;
int windowHeight = 800;

int view_x = 0, view_y = 0;

float cameraPos_x = 0.0f, cameraPos_y = 5.0f, cameraPos_z = 5.0f;
float cameraDirection_x = 0.0f, cameraDirection_y = 0.0f, cameraDirection_z = 0.0f;
float cameraUp_x = 0.0f, cameraUp_y = 1.0f, cameraUp_z = 0.0f;

float lightPos_x = 0.1f, lightPos_y = 10.0f, lightPos_z = 0.1f;
float angularSpeed = 0.0018f;  // 공전 속도

float build_x = 0.0f, build_y = 0.0f, build_z = 0.0f;
float point_x = 0.0f, point_z = 0.0f;
float angle_x = 0.0f, angle_y = 0.0f, angle_xs = 0.0f, angle_ys = 0.0f;

float build_angle = 0.0f;

bool change_r = false, change_g = false, change_b = false, change_w = true;
bool animation_y = false;
bool move_x = false, move_z = false;
bool build_h = true, build_b = false, build_t = false;
bool build_trigger = false;
bool six_trigger = false, twle_trigger = false;

int house_count = 0, building_count = 0, top_count = 0;

time_t startTime = time(nullptr);
int elapsedSeconds = 0;

int cost_count = 0;
int cost = 3000;
int hour_count = 0;
int hour = 12;
int minute = 0;

struct Cost_Rec {
    GLfloat cost_x, cost_y, cost_z;
};

Cost_Rec costbox[5];

typedef struct Rect {
    GLfloat tri_shapes[8][3];
    GLfloat tri_normals[8][3];
    GLfloat tri_colors[8][3];
};

Rect place;

typedef struct Building_Place {
    GLfloat x[10] = { -9, -7, -5, -3, -1, 1, 3, 5, 7, 9 };
    GLfloat y[10] = { -9, -7, -5, -3, -1, 1, 3, 5, 7, 9 };
};

Building_Place build_place;

typedef struct Tree_Place {
    GLfloat x[8] = { -7, -5, -3, -1, 1, 3, 5, 7 };
    GLfloat y[8] = { -7, -5, -3, -1, 1, 3, 5, 7 };
};

Tree_Place tree_place;

typedef struct Builds {
    GLfloat x[100] = {};
    GLfloat y[100] = {};
    GLfloat angle[100] = {};
    bool build[100] = {};
};

Builds house;
Builds building;
Builds top;

GLuint place_vao, place_vbo[3];
GLuint place_ebo;

unsigned int index_place[] = {
    0, 1, 2,
    0, 2, 3,
    1, 2, 5,
    2, 5, 6,
    0, 3, 4,
    3, 4, 7,
    4, 5, 6,
    4, 6, 7,
    2, 3, 7,
    2, 6, 7,
    0, 1, 4,
    1, 4, 5
};

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;

Objectload Sphere_Load;
GLint Sphere = Sphere_Load.loadObj("obj/Sphere.obj");

GLuint VAO_sphere, VBO_NORMAL_sphere, VBO_VERTEX_sphere, VBO_Texcoord_sphere;

Objectload Tree_Load;
GLint Tree = Tree_Load.loadObj("obj/Tree.obj");

GLuint VAO_tree, VBO_NORMAL_tree, VBO_VERTEX_tree;

Objectload House_Load;
GLint House = House_Load.loadObj("obj/House1.obj");

GLuint VAO_house, VBO_NORMAL_house, VBO_VERTEX_house, VBO_Texcoord_house;

Objectload Building_Load;
GLint Building = Building_Load.loadObj("obj/building1.obj");

GLuint VAO_build, VBO_NORMAL_build, VBO_VERTEX_build, VBO_Texcoord_build;

Objectload Top_Load;
GLint Top = Top_Load.loadObj("obj/top1.obj");

GLuint VAO_top, VBO_NORMAL_top, VBO_VERTEX_top, VBO_Texcoord_top;

Objectload Cube_Load;
GLint Cube = Cube_Load.loadObj("obj/plane.obj");

GLuint VAO_Cube, VBO_NORMAL_Cube, VBO_VERTEX_Cube, VBO_Texcoord_Cuve;

Objectload Grass_Load;
GLint Grass = Grass_Load.loadObj("obj/grass.obj");

GLuint VAO_Grass, VBO_NORMAL_Grass, VBO_VERTEX_Grass, VBO_Texcoord_Grass;

Objectload Road_Load;
GLint Road = Road_Load.loadObj("obj/grass.obj");

GLuint VAO_Road, VBO_NORMAL_Road, VBO_VERTEX_Road, VBO_Texcoord_Road;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid TimerFunc(int value);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMove(int x, int y);
GLvoid Motion(int x, int y);


void viewport();
void viewport2();
void viewport3();
void viewing();
void project();

void make_sun();
void make_tree();
void make_place();
void make_build();
void move_place();
void make_point();
void Cost_place();
void Time_place();
void make_road();

void light();

enum { xPos, yPos, zPos };
enum { nxPos, nyPos, nzPos };
enum { rColor, gColor, bColor };


void initTextures() {
    Cube_Load.InitTexture("image/2.png");
    Tree_Load.InitTexture("image/Autumn Tree.png");
    Grass_Load.InitTexture("image/grasss.png");
    Road_Load.InitTexture("image/road.png");
    House_Load.InitTexture("image/house_tex.png");
    Building_Load.InitTexture("image/building_tex.png");
    Top_Load.InitTexture("image/top_tex.png");
    Sphere_Load.InitTexture("image/sun_tex.png");
}

void InitBuffer() {
    glGenVertexArrays(1, &place_vao);
    glBindVertexArray(place_vao);

    glGenBuffers(3, place_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, place_vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(place.tri_shapes), place.tri_shapes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, place_vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(place.tri_normals), place.tri_normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, place_vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(place.tri_colors), place.tri_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &place_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, place_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_place), index_place, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO_sphere);
    glGenBuffers(1, &VBO_NORMAL_sphere);
    glGenBuffers(1, &VBO_VERTEX_sphere);
    glGenBuffers(1, &VBO_Texcoord_sphere);

    glBindVertexArray(VAO_sphere);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_sphere);
    glBufferData(GL_ARRAY_BUFFER, Sphere_Load.outvertex.size() * sizeof(glm::vec3), &Sphere_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_sphere);
    glBufferData(GL_ARRAY_BUFFER, Sphere_Load.outnormal.size() * sizeof(glm::vec3), &Sphere_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Texcoord_sphere);
    glBufferData(GL_ARRAY_BUFFER, Sphere_Load.outuv.size() * sizeof(glm::vec2), &Sphere_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &VAO_tree);
    glGenBuffers(1, &VBO_NORMAL_tree);
    glGenBuffers(1, &VBO_VERTEX_tree);

    glBindVertexArray(VAO_tree);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_tree);
    glBufferData(GL_ARRAY_BUFFER, Tree_Load.outvertex.size() * sizeof(glm::vec3), &Tree_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_tree);
    glBufferData(GL_ARRAY_BUFFER, Tree_Load.outnormal.size() * sizeof(glm::vec3), &Tree_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &VAO_house);
    glGenBuffers(1, &VBO_NORMAL_house);
    glGenBuffers(1, &VBO_VERTEX_house);
    glGenBuffers(1, &VBO_Texcoord_house);

    glBindVertexArray(VAO_house);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_house);
    glBufferData(GL_ARRAY_BUFFER, House_Load.outvertex.size() * sizeof(glm::vec3), &House_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_house);
    glBufferData(GL_ARRAY_BUFFER, House_Load.outnormal.size() * sizeof(glm::vec3), &House_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Texcoord_house);
    glBufferData(GL_ARRAY_BUFFER, House_Load.outuv.size() * sizeof(glm::vec2), &House_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &VAO_build);
    glGenBuffers(1, &VBO_NORMAL_build);
    glGenBuffers(1, &VBO_VERTEX_build);
    glGenBuffers(1, &VBO_Texcoord_build);

    glBindVertexArray(VAO_build);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_build);
    glBufferData(GL_ARRAY_BUFFER, Building_Load.outvertex.size() * sizeof(glm::vec3), &Building_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_build);
    glBufferData(GL_ARRAY_BUFFER, Building_Load.outnormal.size() * sizeof(glm::vec3), &Building_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Texcoord_build);
    glBufferData(GL_ARRAY_BUFFER, Building_Load.outuv.size() * sizeof(glm::vec2), &Building_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &VAO_top);
    glGenBuffers(1, &VBO_NORMAL_top);
    glGenBuffers(1, &VBO_VERTEX_top);
    glGenBuffers(1, &VBO_Texcoord_top);

    glBindVertexArray(VAO_top);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_top);
    glBufferData(GL_ARRAY_BUFFER, Top_Load.outvertex.size() * sizeof(glm::vec3), &Top_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_top);
    glBufferData(GL_ARRAY_BUFFER, Top_Load.outnormal.size() * sizeof(glm::vec3), &Top_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Texcoord_top);
    glBufferData(GL_ARRAY_BUFFER, Top_Load.outuv.size() * sizeof(glm::vec2), &Top_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &VAO_Cube);
    glGenBuffers(1, &VBO_NORMAL_Cube);
    glGenBuffers(1, &VBO_VERTEX_Cube);
    glGenBuffers(1, &VBO_Texcoord_Cuve);

    glBindVertexArray(VAO_Cube);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_Cube);
    glBufferData(GL_ARRAY_BUFFER, Cube_Load.outvertex.size() * sizeof(glm::vec3), &Cube_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_Cube);
    glBufferData(GL_ARRAY_BUFFER, Cube_Load.outnormal.size() * sizeof(glm::vec3), &Cube_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Texcoord_Cuve);
    glBufferData(GL_ARRAY_BUFFER, Cube_Load.outuv.size() * sizeof(glm::vec2), &Cube_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &VAO_Grass);
    glGenBuffers(1, &VBO_NORMAL_Grass);
    glGenBuffers(1, &VBO_VERTEX_Grass);
    glGenBuffers(1, &VBO_Texcoord_Grass);

    glBindVertexArray(VAO_Grass);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_Grass);
    glBufferData(GL_ARRAY_BUFFER, Grass_Load.outvertex.size() * sizeof(glm::vec3), &Grass_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_Grass);
    glBufferData(GL_ARRAY_BUFFER, Grass_Load.outnormal.size() * sizeof(glm::vec3), &Grass_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Texcoord_Grass);
    glBufferData(GL_ARRAY_BUFFER, Grass_Load.outuv.size() * sizeof(glm::vec2), &Grass_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &VAO_Road);
    glGenBuffers(1, &VBO_NORMAL_Road);
    glGenBuffers(1, &VBO_VERTEX_Road);
    glGenBuffers(1, &VBO_Texcoord_Road);

    glBindVertexArray(VAO_Road);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_Road);
    glBufferData(GL_ARRAY_BUFFER, Road_Load.outvertex.size() * sizeof(glm::vec3), &Road_Load.outvertex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_Road);
    glBufferData(GL_ARRAY_BUFFER, Road_Load.outnormal.size() * sizeof(glm::vec3), &Road_Load.outnormal[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Texcoord_Road);
    glBufferData(GL_ARRAY_BUFFER, Road_Load.outuv.size() * sizeof(glm::vec2), &Road_Load.outuv[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(2);
}


float GenerateRandomColor() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0, 1.0);
    return dis(gen);
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("City Simulation");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    for (int i = 0; i < 100; i++) {
        house.build[i] = false;
        house.x[i] = 0.0f;
        house.y[i] = 0.0f;
        house.angle[i] = 0.0f;

        building.build[i] = false;
        building.x[i] = 0.0f;
        building.y[i] = 0.0f;
        building.angle[i] = 0.0f;

        top.build[i] = false;
        top.x[i] = 0.0f;
        top.y[i] = 0.0f;
        top.angle[i] = 0.0f;
    }
    make_place();

    InitBuffer();
    initTextures();
    shaderID.makeShader("vertexShaderSource.glsl", "fragmentShaderSource.glsl");
    glutKeyboardFunc(KeyBoard);
    glutTimerFunc(50, TimerFunc, 0);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}

GLvoid drawScene()
{
    shaderID.use();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    light();

    viewport();
    glViewport(0, 0, 800, 800);

    viewing();
    project();

    glEnable(GL_DEPTH_TEST);

    make_sun();
    move_place();
    make_road();
    make_build();
    make_tree();

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    make_point();

    viewport2();
    glViewport(600, 740, 200, 60);
    Cost_place();

    viewport3();
    glViewport(-100, 740, 200, 60);
    Time_place();

    glDisable(GL_BLEND);

    glutSwapBuffers();
}

GLvoid Reshape(int w, int h) {
    glViewport(view_x, view_y, w, h);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        exit(-1);
        break;
    case 'w':
        cameraPos_z -= 0.1f;
        cameraDirection_z -= 0.1f;
        break;

    case 's':
        cameraPos_z += 0.1f;
        cameraDirection_z += 0.1f;
        break;

    case 'a':
        cameraPos_x -= 0.1f;
        cameraDirection_x -= 0.1f;
        break;

    case 'd':
        cameraPos_x += 0.1f;
        cameraDirection_x += 0.1f;
        break;

    case 'f':
        cameraPos_y -= 0.1f;
        cameraDirection_y -= 0.1f;
        break;

    case 'r':
        cameraPos_y += 0.1f;
        cameraDirection_y += 0.1f;
        break;

    case 'y':
        build_angle += 1.0f;
        break;

    case 'Y':
        build_angle -= 1.0f;
        break;

    case 'b':
        if (cost >= 100 && 6 <= hour && hour <= 22) {
            if (build_h) {
                house.build[house_count] = true;
                house.x[house_count] = point_x;
                house.y[house_count] = point_z;
                house.angle[house_count] = build_angle;
                house_count++;
            }

            if (build_b) {
                building.build[building_count] = true;
                building.x[building_count] = point_x;
                building.y[building_count] = point_z;
                building.angle[building_count] = build_angle;
                building_count++;
                build_trigger = true;
            }

            if (build_t) {
                top.build[top_count] = true;
                top.x[top_count] = point_x;
                top.y[top_count] = point_z;
                top.angle[top_count] = build_angle;
                top_count++;
                build_trigger = true;
            }

            cost -= 100;
            build_angle = 0.0f;
        }
        break;

    case '1':
        build_h = true;
        build_b = false;
        build_t = false;
        break;

    case '2':
        build_h = false;
        build_b = true;
        build_t = false;
        break;

    case '3':
        build_h = false;
        build_b = false;
        build_t = true;
        break;
    }
    InitBuffer();
    drawScene();
    glutPostRedisplay();
}


GLvoid TimerFunc(int value)
{
    if (build_trigger == true) {
        cost_count++;

        if (cost_count == 50) {
            cost_count = 0;

            for (int i = 0; i < 100; i++) {
                if (building.build[i] == true) {
                    cost += 10;
                }
            }

            for (int i = 0; i < 100; i++) {
                if (top.build[i] == true) {
                    cost += 10;
                }
            }
        }
    }

    hour_count++;

    if (hour_count == 40) {
        hour_count = 0;
        minute += 30;

        if (minute >= 60) {
            hour++;
            minute = 0;
        }

        if (hour >= 24) {
            hour = 0;
        }
    }

    float newX = lightPos_x * cos(angularSpeed) - lightPos_y * sin(angularSpeed);
    float newY = lightPos_x * sin(angularSpeed) + lightPos_y * cos(angularSpeed);
    
    if (hour == 6 && six_trigger == true) {
        newX = 10;
        newY = 0;
        angularSpeed = 0.0033f;
        six_trigger = false;
    }

    if (hour == 12 && twle_trigger == true) {
        newX = 0;
        newY = 10;
        angularSpeed = 0.0018f;
        six_trigger = false;
    }

    if (hour == 5) {
        six_trigger = true;
        twle_trigger = true;
    }
    
    lightPos_x = newX;
    lightPos_y = newY;

    glutPostRedisplay();
    glutTimerFunc(50, TimerFunc, 0);
}


GLvoid ConvertWindowXYOpenGLXY(int x, int y, float* ox, float* oy) {
    *ox = (float)x / windowWidth * 2.0 - 1.0;
    *oy = 1.0 - (float)y / windowHeight * 2.0;
}

GLvoid Mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        move_x = true;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        move_z = true;
    }

    if ((button == GLUT_RIGHT_BUTTON || button == GLUT_LEFT_BUTTON) && state == GLUT_UP) {
        move_x = false;
        move_z = false;
    }
}

GLvoid MouseMove(int x, int y) {
    float ox, oy;
    ConvertWindowXYOpenGLXY(x, y, &ox, &oy);
    glutPostRedisplay();
}

GLvoid Motion(int x, int y) {
    angle_x = x;
    angle_y = y;

    if (move_x) {
        if (angle_x < angle_xs) {
            point_x -= 0.05f;

            if (point_x <= -10.0f) {
                point_x += 0.05f;
            }
        }

        else {
            point_x += 0.05f;

            if (point_x >= 10.0f) {
                point_x -= 0.05f;
            }
        }
    }

    if (move_z) {
        if (angle_y < angle_ys) {
            point_z -= 0.05f;

            if (point_z <= -10.0f) {
                point_z += 0.05f;
            }
        }

        else {
            point_z += 0.05f;

            if (point_z >= 10.0f) {
                point_z -= 0.05f;
            }
        }
    }

    angle_xs = angle_x;
    angle_ys = angle_y;

    drawScene();
}

void viewing() {
    glm::mat4 vTransform = glm::mat4(1.0f);
    glm::vec3 cameraPos = glm::vec3(cameraPos_x, cameraPos_y, cameraPos_z);
    glm::vec3 cameraDirection = glm::vec3(cameraDirection_x, cameraDirection_y, cameraDirection_z);
    glm::vec3 cameraUp = glm::vec3(cameraUp_x, cameraUp_y, cameraUp_z);
    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    shaderID.setMat4("viewTransform", vTransform);
    shaderID.setVec3("viewPos", 0, 0, 0);
}

void project() {
    glm::mat4 pTransform = glm::mat4(1.0f);
    pTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
    pTransform = glm::translate(pTransform, glm::vec3(0.0, 0.0, -5.0));
    shaderID.setMat4("projectionTransform", pTransform);
}

void viewport() {
    float yAngle = 0.0f;

    glm::mat4 mTransform = glm::mat4(1.0f);
    glm::mat4 vTransform = glm::mat4(1.0f);
    glm::mat4 pTransform = glm::mat4(1.0f);

    glm::vec3 cameraPos = glm::vec3(cameraPos_x, cameraPos_y, cameraPos_z);
    glm::vec3 cameraDirection = glm::vec3(cameraDirection_x, cameraDirection_y, cameraDirection_z);
    glm::vec3 cameraUp = glm::vec3(cameraUp_x, cameraUp_y, cameraUp_z);

    mTransform = glm::rotate(mTransform, glm::radians(yAngle), glm::vec3(0.0f, 1.0, 0.0f));
    shaderID.setMat4("modelTransform", mTransform);
    shaderID.setVec3("modelTransform", 0, 0, 0);

    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    shaderID.setMat4("viewTransform", vTransform);
    shaderID.setVec3("viewPos", 0, 0, 0);

    pTransform = glm::perspective(glm::radians(60.0f), (float)windowWidth / (float)windowHeight, 0.1f, 200.0f);
    shaderID.setMat4("projectionTransform", pTransform);
    shaderID.setVec3("projectionTransform", 0, 0, 0);
}

void viewport2() {
    float yAngle = 0.0f;

    glm::mat4 vTransform = glm::mat4(1.0f);
    glm::mat4 pTransform = glm::mat4(1.0f);

    float xValue = 15.7f;
    glm::vec3 cameraPos = glm::vec3(xValue, 1.635f, 0.f);
    glm::vec3 cameraDirection = glm::vec3(xValue, 0.0f, 0);
    glm::vec3 cameraUp = glm::vec3(0, 0, -1.f);

    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    shaderID.setMat4("viewTransform", vTransform);
    shaderID.setVec3("viewPos", 0, 0, 0);

    pTransform = glm::ortho(-1.9f, 1.9f, -1.9f, 1.9f, -5.f, 5.f);
    shaderID.setMat4("projectionTransform", pTransform);
    shaderID.setVec3("projectionTransform", 0, 0, 0);
}

void viewport3() {
    float yAngle = 0.0f;

    glm::mat4 vTransform = glm::mat4(1.0f);
    glm::mat4 pTransform = glm::mat4(1.0f);

    float xValue = -15.7f;
    glm::vec3 cameraPos = glm::vec3(xValue, 1.635f, 0.f);
    glm::vec3 cameraDirection = glm::vec3(xValue, 0.0f, 0);
    glm::vec3 cameraUp = glm::vec3(0, 0, -1.f);

    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
    shaderID.setMat4("viewTransform", vTransform);
    shaderID.setVec3("viewPos", 0, 0, 0);


    pTransform = glm::ortho(-3.9f, 3.9f, -1.9f, 1.9f, -5.f, 5.f);
    shaderID.setMat4("projectionTransform", pTransform);
    shaderID.setVec3("projectionTransform", 0, 0, 0);
}

void make_tree() {
    shaderID.setVec3("objectColor", 0.f, 0.5f, 0.f);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 0 || i == 7) {
                glm::mat4 Tx = glm::mat4(1.0f);
                glm::mat4 Rz = glm::mat4(1.0f);
                glm::mat4 TR = glm::mat4(1.0f);
                glm::mat4 model = glm::mat4(1.0f);

                Tx = glm::translate(Tx, glm::vec3(tree_place.x[i], 0.0, tree_place.y[j]));
                Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
                model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

                TR = Rz * Tx * model;

                shaderID.setMat4("modelTransform", TR);
                shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
                glBindVertexArray(VAO_tree);
                glBindTexture(GL_TEXTURE_2D, Tree_Load.texture);
                glDrawArrays(GL_TRIANGLES, 0, Tree);
            }

            else if (j == 0 || j == 7) {
                glm::mat4 Tx = glm::mat4(1.0f);
                glm::mat4 Rz = glm::mat4(1.0f);
                glm::mat4 TR = glm::mat4(1.0f);
                glm::mat4 model = glm::mat4(1.0f);

                Tx = glm::translate(Tx, glm::vec3(tree_place.x[i], 0.0, tree_place.y[j]));
                Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
                model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

                TR = Rz * Tx * model;

                shaderID.setMat4("modelTransform", TR);
                glBindVertexArray(VAO_tree);
                glBindTexture(GL_TEXTURE_2D, Tree_Load.texture);
                glDrawArrays(GL_TRIANGLES, 0, Tree);
            }
        }
    }
}

void make_sun() {
    shaderID.setVec3("objectColor", 1.0f, 1.0f, 0.0f);

    glm::mat4 Tx = glm::mat4(1.0f);
    glm::mat4 Rz = glm::mat4(1.0f);
    glm::mat4 TR = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    Tx = glm::translate(Tx, glm::vec3(lightPos_x, lightPos_y, lightPos_z));
    Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

    TR = Rz * Tx * model;

    shaderID.setMat4("modelTransform", TR);
    glBindVertexArray(VAO_sphere);
    glBindTexture(GL_TEXTURE_2D, Sphere_Load.texture);
    glDrawArrays(GL_TRIANGLES, 0, Sphere);
}

void light() {
    shaderID.setVec3("lightPos", lightPos_x, lightPos_y, lightPos_z);

    if (hour >= 6 && hour <= 22) {
        shaderID.setVec3("lightColor", 1.f, 1.f, 1.f);
    }

    else {
        shaderID.setVec3("lightColor", 0.6f, 0.6f, 0.6f);
    }
    
    shaderID.setVec3("viewPos", cameraPos_x, cameraPos_y, cameraPos_z);
}

void make_place() {
    place.tri_shapes[0][xPos] = -0.5;
    place.tri_shapes[0][yPos] = -0.5;
    place.tri_shapes[0][zPos] = -0.5;

    place.tri_shapes[1][xPos] = 0.5;
    place.tri_shapes[1][yPos] = -0.5;
    place.tri_shapes[1][zPos] = -0.5;

    place.tri_shapes[2][xPos] = 0.5;
    place.tri_shapes[2][yPos] = 0.5;
    place.tri_shapes[2][zPos] = -0.5;

    place.tri_shapes[3][xPos] = -0.5;
    place.tri_shapes[3][yPos] = 0.5;
    place.tri_shapes[3][zPos] = -0.5;

    place.tri_shapes[4][xPos] = -0.5;
    place.tri_shapes[4][yPos] = -0.5;
    place.tri_shapes[4][zPos] = 0.5;

    place.tri_shapes[5][xPos] = 0.5;
    place.tri_shapes[5][yPos] = -0.5;
    place.tri_shapes[5][zPos] = 0.5;

    place.tri_shapes[6][xPos] = 0.5;
    place.tri_shapes[6][yPos] = 0.5;
    place.tri_shapes[6][zPos] = 0.5;

    place.tri_shapes[7][xPos] = -0.5;
    place.tri_shapes[7][yPos] = 0.5;
    place.tri_shapes[7][zPos] = 0.5;

    place.tri_normals[0][nxPos] = -0.1;
    place.tri_normals[0][nyPos] = -0.1;
    place.tri_normals[0][nzPos] = -0.1;

    place.tri_normals[1][nxPos] = 0.1;
    place.tri_normals[1][nyPos] = -0.1;
    place.tri_normals[1][nzPos] = -0.1;

    place.tri_normals[2][nxPos] = 0.1;
    place.tri_normals[2][nyPos] = 0.1;
    place.tri_normals[2][nzPos] = -0.1;

    place.tri_normals[3][nxPos] = -0.1;
    place.tri_normals[3][nyPos] = 0.1;
    place.tri_normals[3][nzPos] = -0.1;

    place.tri_normals[4][nxPos] = -0.1;
    place.tri_normals[4][nyPos] = -0.1;
    place.tri_normals[4][nzPos] = 0.1;

    place.tri_normals[5][nxPos] = 0.1;
    place.tri_normals[5][nyPos] = -0.1;
    place.tri_normals[5][nzPos] = 0.1;

    place.tri_normals[6][nxPos] = 0.1;
    place.tri_normals[6][nyPos] = 0.1;
    place.tri_normals[6][nzPos] = 0.1;

    place.tri_normals[7][nxPos] = -0.1;
    place.tri_normals[7][nyPos] = 0.1;
    place.tri_normals[7][nzPos] = 0.1;

    for (int i = 0; i < 8; i++) {
        place.tri_colors[i][rColor] = GenerateRandomColor();
        place.tri_colors[i][gColor] = GenerateRandomColor();
        place.tri_colors[i][bColor] = GenerateRandomColor();
    }
}

void move_place() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; j++) {
            shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);

            glm::mat4 Tx = glm::mat4(1.0f);
            glm::mat4 Rz = glm::mat4(1.0f);
            glm::mat4 TR = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);

            Tx = glm::translate(Tx, glm::vec3(build_place.x[i], 0.01, build_place.y[j]));
            Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
            model = glm::scale(model, glm::vec3(0.12f, 0.001f, 0.12f));

            TR = Tx * Rz * model;

            shaderID.setMat4("modelTransform", TR);
            glBindVertexArray(VAO_Grass);
            glBindTexture(GL_TEXTURE_2D, Grass_Load.texture);
            glDrawArrays(GL_TRIANGLES, 0, Grass);
        }
    }
}

void make_road() {
    shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);
    glm::mat4 Tx = glm::mat4(1.0f);
    glm::mat4 Rz = glm::mat4(1.0f);
    glm::mat4 TR = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    Tx = glm::translate(Tx, glm::vec3(0.0, 0.0, 0.05));
    Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(10.0, 0.0001, 10.0));

    TR = Tx * Rz * model;

    shaderID.setMat4("modelTransform", TR);
    glBindVertexArray(VAO_Road);
    glBindTexture(GL_TEXTURE_2D, Road_Load.texture);
    glDrawArrays(GL_TRIANGLES, 0, Road);
}

void make_build() {
    for (int i = 0; i < 100; i++) {
        if (house.build[i] == true) {
            shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);

            glm::mat4 Tx = glm::mat4(1.0f);
            glm::mat4 Rz = glm::mat4(1.0f);
            glm::mat4 TR = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);

            Tx = glm::translate(Tx, glm::vec3(house.x[i], 0.0f, house.y[i]));
            Rz = glm::rotate(Rz, glm::radians(house.angle[i]), glm::vec3(0.0, 1.0, 0.0));
            model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));

            TR = Tx * Rz * model;

            shaderID.setMat4("modelTransform", TR);
            glBindVertexArray(VAO_house);
            glBindTexture(GL_TEXTURE_2D, House_Load.texture);
            glDrawArrays(GL_TRIANGLES, 0, House);
        }

        if (building.build[i] == true) {
            shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);

            glm::mat4 Tx = glm::mat4(1.0f);
            glm::mat4 Rz = glm::mat4(1.0f);
            glm::mat4 TR = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);

            Tx = glm::translate(Tx, glm::vec3(building.x[i], 0.0f, building.y[i]));
            Rz = glm::rotate(Rz, glm::radians(building.angle[i]), glm::vec3(0.0, 1.0, 0.0));
            model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));

            TR = Tx * Rz * model;

            shaderID.setMat4("modelTransform", TR);
            glBindVertexArray(VAO_build);
            glBindTexture(GL_TEXTURE_2D, Building_Load.texture);
            glDrawArrays(GL_TRIANGLES, 0, Building);
        }

        if (top.build[i] == true) {
            shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);

            glm::mat4 Tx = glm::mat4(1.0f);
            glm::mat4 Rz = glm::mat4(1.0f);
            glm::mat4 TR = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);

            Tx = glm::translate(Tx, glm::vec3(top.x[i], 0.0f, top.y[i]));
            Rz = glm::rotate(Rz, glm::radians(top.angle[i]), glm::vec3(0.0, 1.0, 0.0));
            model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));

            TR = Tx * Rz * model;

            shaderID.setMat4("modelTransform", TR);
            glBindVertexArray(VAO_top);
            glBindTexture(GL_TEXTURE_2D, Top_Load.texture);
            glDrawArrays(GL_TRIANGLES, 0, Top);
        }
    }
}

void make_point() {
    if (build_h) {
        shaderID.setVec3("objectColor", 1.0f, 0.0f, 0.0f);

        glm::mat4 Tx = glm::mat4(1.0f);
        glm::mat4 Rz = glm::mat4(1.0f);
        glm::mat4 TR = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        Tx = glm::translate(Tx, glm::vec3(point_x, 0.0f, point_z));
        Rz = glm::rotate(Rz, glm::radians(build_angle), glm::vec3(0.0, 1.0, 0.0));
        model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));

        TR = Tx * Rz * model;

        shaderID.setMat4("modelTransform", TR);
        glBindVertexArray(VAO_house);
        glBindTexture(GL_TEXTURE_2D, House_Load.texture);
        glDrawArrays(GL_TRIANGLES, 0, House);
    }

    if (build_b) {
        shaderID.setVec3("objectColor", 1.0f, 0.0f, 0.0f);

        glm::mat4 Tx = glm::mat4(1.0f);
        glm::mat4 Rz = glm::mat4(1.0f);
        glm::mat4 TR = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        Tx = glm::translate(Tx, glm::vec3(point_x, 0.0f, point_z));
        Rz = glm::rotate(Rz, glm::radians(build_angle), glm::vec3(0.0, 1.0, 0.0));
        model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));

        TR = Tx * Rz * model;

        shaderID.setMat4("modelTransform", TR);
        glBindVertexArray(VAO_build);
        glBindTexture(GL_TEXTURE_2D, Building_Load.texture);
        glDrawArrays(GL_TRIANGLES, 0, Building);
    }

    if (build_t) {
        shaderID.setVec3("objectColor", 1.0f, 0.0f, 0.0f);

        glm::mat4 Tx = glm::mat4(1.0f);
        glm::mat4 Rz = glm::mat4(1.0f);
        glm::mat4 TR = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        Tx = glm::translate(Tx, glm::vec3(point_x, 0.0f, point_z));
        Rz = glm::rotate(Rz, glm::radians(build_angle), glm::vec3(0.0, 1.0, 0.0));
        model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));

        TR = Tx * Rz * model;

        shaderID.setMat4("modelTransform", TR);
        glBindVertexArray(VAO_top);
        glBindTexture(GL_TEXTURE_2D, Top_Load.texture);
        glDrawArrays(GL_TRIANGLES, 0, Top);
    }
}

void Cost_place() {

    glBindVertexArray(VAO_Cube);
    glBindTexture(GL_TEXTURE_2D, Cube_Load.texture);

    int value[4];
    int valueCount = 4;

    int tempCost = cost;

    while (tempCost > 0) {
        int tempValue = tempCost % 10;
        value[--valueCount] = tempValue;
        tempCost /= 10;
    }

    for (int i = 0; i < 4; i++) {
        string path = "image/" + to_string(value[i]) + ".png";
        Cube_Load.InitTexture(path.c_str());


        glm::mat4 CostBox = glm::mat4(1.0f);
        CostBox = glm::translate(CostBox, glm::vec3(15.f, 1.f, 0.f));
        CostBox = glm::translate(CostBox, glm::vec3(0.75f * i, 0.f, 0.f));
        CostBox = glm::scale(CostBox, glm::vec3(0.1f, 0.1f, 0.1f));
        shaderID.setMat4("modelTransform", CostBox);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, 0, Cube);
    }

}


void Time_place() {
    glBindVertexArray(VAO_Cube);
    glBindTexture(GL_TEXTURE_2D, Cube_Load.texture);

    int hvalue[2];
    int hvalueCount = 2;

    int temphour = hour;
    hvalue[0] = 0;
    hvalue[1] = 0;

    while (temphour > 0) {
        int temphValue = temphour % 10;
        hvalue[--hvalueCount] = temphValue;
        temphour /= 10;
    }

    for (int i = 0; i < 3; i++) {
        if (i < 2) {
            string path = "image/T" + to_string(hvalue[i]) + ".png";
            Cube_Load.InitTexture(path.c_str());
        }
        else if (i == 2) Cube_Load.InitTexture("image/and.png");

        glm::mat4 CostBox = glm::mat4(1.0f);
        CostBox = glm::translate(CostBox, glm::vec3(-15.f, 1.f, 0.f));
        CostBox = glm::translate(CostBox, glm::vec3(0.75f * i, 0.f, 0.f));
        CostBox = glm::scale(CostBox, glm::vec3(0.1f, 0.1f, 0.1f));
        shaderID.setMat4("modelTransform", CostBox);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, 0, Cube);
    }

    for (int i = 3; i < 5; ++i) {
        Cube_Load.InitTexture("image/T0.png");
        glm::mat4 CostBox = glm::mat4(1.0f);
        CostBox = glm::translate(CostBox, glm::vec3(-15.05f, 1.f, 0.f));
        CostBox = glm::translate(CostBox, glm::vec3(0.75f * i, 0.f, 0.f));
        CostBox = glm::scale(CostBox, glm::vec3(0.1f, 0.1f, 0.1f));
        shaderID.setMat4("modelTransform", CostBox);
        shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, 0, Cube);
    }
}