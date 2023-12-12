//#define _CRT_SECURE_NO_WARNINGS
//#define MAP_SIZE 10.f
//
//#include "shader.h"
//#include "load_OBJ.h"
//using namespace std;
//
//int windowWidth = 800;
//int windowHeight = 800;
//
//int view_x = 0, view_y = 0;
//
//float cameraPos_x = 0.0f, cameraPos_y = 5.0f, cameraPos_z = 5.0f;
//float cameraDirection_x = 0.0f, cameraDirection_y = 0.0f, cameraDirection_z = 0.0f;
//float cameraUp_x = 0.0f, cameraUp_y = 1.0f, cameraUp_z = 0.0f;
//
//float lightPos_x = 0.0f, lightPos_y = 10.0f, lightPos_z = 0.0f;
//
//float build_x = 0.0f, build_y = 0.0f, build_z = 0.0f;
//float point_x = 0.0f, point_z = 0.0f;
//float angle_x = 0.0f, angle_y = 0.0f, angle_xs = 0.0f, angle_ys = 0.0f;
//
//float build_angle = 0.0f;
//
//bool change_r = false, change_g = false, change_b = false, change_w = true;
//bool animation_y = false;
//bool move_x = false, move_z = false;
//bool build_h = true, build_b = false, build_t = false;
//
//int house_count = 0, building_count = 0, top_count = 0;
//
//time_t startTime = time(nullptr);
//int elapsedSeconds = 0;
//
//int cost = 3000;
//
//typedef struct Rect {
//    GLfloat tri_shapes[8][3];
//    GLfloat tri_normals[8][3];
//    GLfloat tri_colors[8][3];
//};
//
//Rect place;
//
//typedef struct Building_Place {
//    GLfloat x[10] = { -9, -7, -5, -3, -1, 1, 3, 5, 7, 9 };
//    GLfloat y[10] = { -9, -7, -5, -3, -1, 1, 3, 5, 7, 9 };
//};
//
//Building_Place build_place;
//
//typedef struct Tree_Place {
//    GLfloat x[8] = { -7, -5, -3, -1, 1, 3, 5, 7 };
//    GLfloat y[8] = { -7, -5, -3, -1, 1, 3, 5, 7 };
//};
//
//Tree_Place tree_place;
//
//typedef struct Builds {
//    GLfloat x[100] = {};
//    GLfloat y[100] = {};
//    GLfloat angle[100] = {};
//    bool build[100] = {};
//};
//
//Builds house;
//Builds building;
//Builds top;
//
//GLuint place_vao, place_vbo[3];
//GLuint place_ebo;
//
//unsigned int index_place[] = {
//    0, 1, 2,
//    0, 2, 3,
//    1, 2, 5,
//    2, 5, 6,
//    0, 3, 4,
//    3, 4, 7,
//    4, 5, 6,
//    4, 6, 7,
//    2, 3, 7,
//    2, 6, 7,
//    0, 1, 4,
//    1, 4, 5
//};
//
//GLint width, height;
//GLuint shaderProgramID;
//GLuint vertexShader;
//GLuint fragmentShader;
////GLuint shaderID;
//
//Objectload Sphere_Load;
//GLint Sphere = Sphere_Load.loadObj("Sphere.obj");
//
//GLuint VAO_sphere, VBO_NORMAL_sphere, VBO_VERTEX_sphere;
//
//Objectload Tree_Load;
//GLint Tree = Tree_Load.loadObj("Tree.obj");
//
//GLuint VAO_tree, VBO_NORMAL_tree, VBO_VERTEX_tree;
//
//Objectload House_Load;
//GLint House = House_Load.loadObj("House1.obj");
//
//GLuint VAO_house, VBO_NORMAL_house, VBO_VERTEX_house;
//
//Objectload Building_Load;
//GLint Building = Building_Load.loadObj("building1.obj");
//
//GLuint VAO_build, VBO_NORMAL_build, VBO_VERTEX_build;
//
//Objectload Top_Load;
//GLint Top = Top_Load.loadObj("top1.obj");
//
//GLuint VAO_top, VBO_NORMAL_top, VBO_VERTEX_top;
//
//Objectload Cube_Load;
//GLint Cube = Cube_Load.loadObj("cube.obj");
//
//GLuint VAO_Cube, VBO_NORMAL_Cube, VBO_VERTEX_Cube;
//
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//GLvoid TimerFunc(int value);
//GLvoid Mouse(int button, int state, int x, int y);
//GLvoid MouseMove(int x, int y);
//GLvoid Motion(int x, int y);
//
//
//void viewport();
//void viewing();
//void project();
//
//void make_sun();
//void make_tree();
//void make_place();
//void make_build();
//void move_place();
//void make_point();
//
//void light();
//
//enum { xPos, yPos, zPos };
//enum { nxPos, nyPos, nzPos };
//enum { rColor, gColor, bColor };
//
//void initTextures() {
//    Cube_Load.InitTexture("cube_TEX.png");
//}
//
//GLvoid drawScene();
//GLvoid KeyBoard(unsigned char key, int x, int y);
//GLvoid Reshape(int w, int h);
//GLvoid TimerFunc(int x);
//GLvoid Motion(int x, int y);
//
//
//void InitBuffer() {
//    glGenVertexArrays(1, &place_vao);
//    glBindVertexArray(place_vao);
//
//    glGenBuffers(3, place_vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, place_vbo[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(place.tri_shapes), place.tri_shapes, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, place_vbo[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(place.tri_normals), place.tri_normals, GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, place_vbo[2]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(place.tri_colors), place.tri_colors, GL_STATIC_DRAW);
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(2);
//
//    glGenBuffers(1, &place_ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, place_ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_place), index_place, GL_STATIC_DRAW);
//
//    glGenVertexArrays(1, &VAO_sphere);
//    glGenBuffers(1, &VBO_NORMAL_sphere);
//    glGenBuffers(1, &VBO_VERTEX_sphere);
//
//    glBindVertexArray(VAO_sphere);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_sphere);
//    glBufferData(GL_ARRAY_BUFFER, Sphere_Load.outvertex.size() * sizeof(glm::vec3), &Sphere_Load.outvertex[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_sphere);
//    glBufferData(GL_ARRAY_BUFFER, Sphere_Load.outnormal.size() * sizeof(glm::vec3), &Sphere_Load.outnormal[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//
//    glGenVertexArrays(1, &VAO_tree);
//    glGenBuffers(1, &VBO_NORMAL_tree);
//    glGenBuffers(1, &VBO_VERTEX_tree);
//
//    glBindVertexArray(VAO_tree);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_tree);
//    glBufferData(GL_ARRAY_BUFFER, Tree_Load.outvertex.size() * sizeof(glm::vec3), &Tree_Load.outvertex[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_tree);
//    glBufferData(GL_ARRAY_BUFFER, Tree_Load.outnormal.size() * sizeof(glm::vec3), &Tree_Load.outnormal[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//
//    glGenVertexArrays(1, &VAO_house);
//    glGenBuffers(1, &VBO_NORMAL_house);
//    glGenBuffers(1, &VBO_VERTEX_house);
//
//    glBindVertexArray(VAO_house);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_house);
//    glBufferData(GL_ARRAY_BUFFER, House_Load.outvertex.size() * sizeof(glm::vec3), &House_Load.outvertex[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_house);
//    glBufferData(GL_ARRAY_BUFFER, House_Load.outnormal.size() * sizeof(glm::vec3), &House_Load.outnormal[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//
//    glGenVertexArrays(1, &VAO_build);
//    glGenBuffers(1, &VBO_NORMAL_build);
//    glGenBuffers(1, &VBO_VERTEX_build);
//
//    glBindVertexArray(VAO_build);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_build);
//    glBufferData(GL_ARRAY_BUFFER, Building_Load.outvertex.size() * sizeof(glm::vec3), &Building_Load.outvertex[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_build);
//    glBufferData(GL_ARRAY_BUFFER, Building_Load.outnormal.size() * sizeof(glm::vec3), &Building_Load.outnormal[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//
//    glGenVertexArrays(1, &VAO_top);
//    glGenBuffers(1, &VBO_NORMAL_top);
//    glGenBuffers(1, &VBO_VERTEX_top);
//
//    glBindVertexArray(VAO_top);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_top);
//    glBufferData(GL_ARRAY_BUFFER, Top_Load.outvertex.size() * sizeof(glm::vec3), &Top_Load.outvertex[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_top);
//    glBufferData(GL_ARRAY_BUFFER, Top_Load.outnormal.size() * sizeof(glm::vec3), &Top_Load.outnormal[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//
//    glGenVertexArrays(1, &VAO_Cube);
//    glGenBuffers(1, &VBO_NORMAL_Cube);
//    glGenBuffers(1, &VBO_VERTEX_Cube);
//
//    glBindVertexArray(VAO_Cube);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTEX_Cube);
//    glBufferData(GL_ARRAY_BUFFER, Cube_Load.outvertex.size() * sizeof(glm::vec3), &Cube_Load.outvertex[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_NORMAL_Cube);
//    glBufferData(GL_ARRAY_BUFFER, Cube_Load.outnormal.size() * sizeof(glm::vec3), &Cube_Load.outnormal[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//    glEnableVertexAttribArray(1);
//}
//
//
//float GenerateRandomColor() {
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_real_distribution<float> dis(0.0, 1.0);
//    return dis(gen);
//}
//
//int main(int argc, char** argv)
//{
//    srand(time(NULL));
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//    glutInitWindowPosition(0, 0);
//    glutInitWindowSize(800, 800);
//    glutCreateWindow("Example1");
//
//    glewExperimental = GL_TRUE;
//    if (glewInit() != GLEW_OK)
//    {
//        std::cerr << "Unable to initialize GLEW" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    else
//        std::cout << "GLEW Initialized\n";
//
//    for (int i = 0; i < 100; i++) {
//        house.build[i] = false;
//        house.x[i] = 0.0f;
//        house.y[i] = 0.0f;
//        house.angle[i] = 0.0f;
//
//        building.build[i] = false;
//        building.x[i] = 0.0f;
//        building.y[i] = 0.0f;
//        building.angle[i] = 0.0f;
//
//        top.build[i] = false;
//        top.x[i] = 0.0f;
//        top.y[i] = 0.0f;
//        top.angle[i] = 0.0f;
//    }
//
//    InitBuffer();
//    initTextures();
//    shaderID.makeShader("vertexShaderSource.glsl", "fragmentShaderSource.glsl");
//    glutKeyboardFunc(KeyBoard);
//    glutMouseFunc(Mouse);
//    glutMotionFunc(Motion);
//    glutTimerFunc(50, TimerFunc, 0);
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMainLoop();
//}
//
//GLvoid drawScene()
//{
//    shaderID.use();
//   // glBindVertexArray(VAO_H1);
//   // //glBindVertexArray(VAO_H2);
//
//   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   // glEnable(GL_DEPTH_TEST);
//   //glEnable(GL_CULL_FACE);
//
//   // //����
//   // shaderID.setVec3("lightPos", 0.f, 3.f, 0.f);
//   // shaderID.setVec3("lightColor", 3.f, 3.f, 3.f);
//
//   // //���� ��ȯ
//   // glm::mat4 pTransform = glm::mat4(1.0f);
//   // pTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
//   // shaderID.setMat4("projectionTransform", pTransform);
//
//
//   // glm::mat4 vTransform = glm::mat4(1.0f);
//   // glm::vec3 cameraPos = glm::vec3(0, 1.f, 1.f);
//   // glm::vec3 cameraDirection = glm::vec3(0, 0.0f, 0);
//   // glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//   // vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//   // shaderID.setMat4("viewTransform", vTransform);
//   // shaderID.setVec3("viewPos", 0, 0, 0);
//
//   // if(House1){
//   //     glBindTexture(GL_TEXTURE_2D, House_Load.texture);
//   //     glBindVertexArray(VAO_H1);
//   //     glm::mat4 PlayerTransform = glm::mat4(1.0f);
//   //     PlayerTransform = glm::scale(PlayerTransform, glm::vec3(0.005f, 0.005f, 0.005f));
//   //     PlayerTransform = glm::rotate(PlayerTransform, glm::radians(rotateX), glm::vec3(1, 0, 0));
//   //     PlayerTransform = glm::rotate(PlayerTransform, glm::radians(rotateY) - 90.f, glm::vec3(0, 1, 0));
//   //     shaderID.setMat4("modelTransform", PlayerTransform);
//   //     shaderID.setVec3("objectColor", 1.f, 1.f, 1.f);
//   //     glDrawArrays(GL_TRIANGLES, 0, Home1);
//   // }
//
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//    //glUseProgram(shaderID);
//
//    light();
//
//    viewport();
//    viewing();
//    project();
//
//    make_sun();
//    move_place();
//    make_tree();
//    make_build();
//    make_point();
//
//    cout << "Cost: " << cost << endl;
//
//    glutSwapBuffers();
//
//    }
//
//GLvoid Reshape(int w, int h) {
//    glViewport(view_x, view_y, w, h);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glutSwapBuffers();
//}
//
//GLvoid Keyboard(unsigned char key, int x, int y) {
//    switch (key) {
//    case 'q':
//        exit(0);
//        break;
//
//    case 'w':
//        cameraPos_z -= 0.1f;
//        cameraDirection_z -= 0.1f;
//        break;
//
//    case 's':
//        cameraPos_z += 0.1f;
//        cameraDirection_z += 0.1f;
//        break;
//
//    case 'a':
//        cameraPos_x -= 0.1f;
//        cameraDirection_x -= 0.1f;
//        break;
//
//    case 'd':
//        cameraPos_x += 0.1f;
//        cameraDirection_x += 0.1f;
//        break;
//
//    case 'f':
//        cameraPos_y -= 0.1f;
//        cameraDirection_y -= 0.1f;
//        break;
//
//    case 'r':
//        cameraPos_y += 0.1f;
//        cameraDirection_y += 0.1f;
//        break;
//
//    case 'y':
//        build_angle += 1.0f;
//        break;
//
//    case 'Y':
//        build_angle -= 1.0f;
//        break;
//
//    case 'b':
//        if (cost >= 100) {
//            if (build_h) {
//                house.build[house_count] = true;
//                house.x[house_count] = point_x;
//                house.y[house_count] = point_z;
//                house.angle[house_count] = build_angle;
//                house_count++;
//            }
//
//            if (build_b) {
//                building.build[building_count] = true;
//                building.x[building_count] = point_x;
//                building.y[building_count] = point_z;
//                building.angle[building_count] = build_angle;
//                building_count++;
//            }
//
//            if (build_t) {
//                top.build[top_count] = true;
//                top.x[top_count] = point_x;
//                top.y[top_count] = point_z;
//                top.angle[top_count] = build_angle;
//                top_count++;
//            }
//
//            cost -= 100;
//            build_angle = 0.0f;
//        }
//        break;
//
//    case '1':
//        build_h = true;
//        build_b = false;
//        build_t = false;
//        break;
//
//    case '2':
//        build_h = false;
//        build_b = true;
//        build_t = false;
//        break;
//
//    case '3':
//        build_h = false;
//        build_b = false;
//        build_t = true;
//        break;
//    }
//
//    InitBuffer();
//    drawScene();
//    glutPostRedisplay();
//}
//GLvoid TimerFunc(int value)
//{
//    time_t currentTime = time(nullptr);
//    elapsedSeconds = static_cast<int>(difftime(currentTime, startTime));
//
//    if (elapsedSeconds % 10 == 0) {
//        for (int i = 0; i < 100; i++) {
//            if (building.build[i] == true) {
//                cost += 1;
//            }
//        }
//
//        for (int i = 0; i < 100; i++) {
//            if (top.build[i] == true) {
//                cost += 1;
//            }
//        }
//    }
//
//    glutPostRedisplay();
//    glutTimerFunc(50, TimerFunc, 0);
//}
//
//
//GLvoid ConvertWindowXYOpenGLXY(int x, int y, float* ox, float* oy) {
//    *ox = (float)x / windowWidth * 2.0 - 1.0;
//    *oy = 1.0 - (float)y / windowHeight * 2.0;
//}
//
//GLvoid Mouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        move_x = true;
//    }
//
//    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
//        move_z = true;
//    }
//
//    if ((button == GLUT_RIGHT_BUTTON || button == GLUT_LEFT_BUTTON) && state == GLUT_UP) {
//        move_x = false;
//        move_z = false;
//    }
//}
//
//GLvoid MouseMove(int x, int y) {
//    float ox, oy;
//    ConvertWindowXYOpenGLXY(x, y, &ox, &oy);
//    glutPostRedisplay();
//}
//
//GLvoid Motion(int x, int y) {
//    angle_x = x;
//    angle_y = y;
//
//    if (move_x) {
//        if (angle_x < angle_xs) {
//            point_x -= 0.05f;
//
//            if (point_x <= -10.0f) {
//                point_x += 0.05f;
//            }
//        }
//
//        else {
//            point_x += 0.05f;
//
//            if (point_x >= 10.0f) {
//                point_x -= 0.05f;
//            }
//        }
//    }
//
//    if (move_z) {
//        if (angle_y < angle_ys) {
//            point_z -= 0.05f;
//
//            if (point_z <= -10.0f) {
//                point_z += 0.05f;
//            }
//        }
//
//        else {
//            point_z += 0.05f;
//
//            if (point_z >= 10.0f) {
//                point_z -= 0.05f;
//            }
//        }
//    }
//
//    angle_xs = angle_x;
//    angle_ys = angle_y;
//
//    drawScene();
//}
//
//void viewing() {
//    //glm::mat4 view = glm::mat4(1.0f);
//    //glm::vec3 cameraPos = glm::vec3(cameraPos_x, cameraPos_y, cameraPos_z);
//    //glm::vec3 cameraDirection = glm::vec3(cameraDirection_x, cameraDirection_y, cameraDirection_z);
//    //glm::vec3 cameraUp = glm::vec3(cameraUp_x, cameraUp_y, cameraUp_z);
//    //view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//    //unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform");
//    //shaderID.setMat4("viewTransform", vTransform);
//    //shaderID.setVec3("viewPos", 0, 0, 0);
//    //glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//    glm::mat4 vTransform = glm::mat4(1.0f);
//    glm::vec3 cameraPos = glm::vec3(cameraPos_x, cameraPos_y, cameraPos_z);
//    glm::vec3 cameraDirection = glm::vec3(cameraDirection_x, cameraDirection_y, cameraDirection_z);
//    glm::vec3 cameraUp = glm::vec3(cameraUp_x, cameraUp_y, cameraUp_z);
//    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//    shaderID.setMat4("viewTransform", vTransform);
//    shaderID.setVec3("viewPos", 0, 0, 0);
//
//}
//
//void project() {
//    //������ȯ-������
//    //glm::mat4 projection = glm::mat4(1.0f);
//    //projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
//    //projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
//
//    //unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");
//    //glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
//
//      //���� ��ȯ
//    glm::mat4 pTransform = glm::mat4(1.0f);
//    pTransform = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
//    pTransform = glm::translate(pTransform, glm::vec3(0.0, 0.0, -5.0));
//    shaderID.setMat4("projectionTransform", pTransform);
//}
//
//void viewport() {
//
//   /* int modelLoc = glGetUniformLocation(shaderID, "modelTransform");
//    int viewLoc = glGetUniformLocation(shaderID, "viewTransform");
//    int projLoc = glGetUniformLocation(shaderID, "projectionTransform");*/
//
//
//    float yAngle = 0.0f;
//
//    glm::mat4 mTransform = glm::mat4(1.0f);
//    glm::mat4 vTransform = glm::mat4(1.0f);
//    glm::mat4 pTransform = glm::mat4(1.0f);
//
//    glm::vec3 cameraPos = glm::vec3(cameraPos_x, cameraPos_y, cameraPos_z);
//    glm::vec3 cameraDirection = glm::vec3(cameraDirection_x, cameraDirection_y, cameraDirection_z);
//    glm::vec3 cameraUp = glm::vec3(cameraUp_x, cameraUp_y, cameraUp_z);
//
//    mTransform = glm::rotate(mTransform, glm::radians(yAngle), glm::vec3(0.0f, 1.0, 0.0f));
//    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &mTransform[0][0]);
//    shaderID.setMat4("modelTransform", mTransform);
//    shaderID.setVec3("modelTransform", 0, 0, 0);
//    vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//    //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &vTransform[0][0]);
//    shaderID.setMat4("viewTransform", vTransform);
//    shaderID.setVec3("viewPos", 0, 0, 0);
//    pTransform = glm::perspective(glm::radians(60.0f), (float)windowWidth / (float)windowHeight, 0.1f, 200.0f);
//   // glUniformMatrix4fv(projLoc, 1, GL_FALSE, &pTransform[0][0]);
//    shaderID.setMat4("projectionTransform", pTransform);
//    shaderID.setVec3("projectionTransform", 0, 0, 0);
//
//    //glm::mat4 vTransform = glm::mat4(1.0f);
//    //glm::vec3 cameraPos = glm::vec3(0, 1.f, 1.f);
//    //glm::vec3 cameraDirection = glm::vec3(0, 0.0f, 0);
//    //glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//    //vTransform = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//    //shaderID.setMat4("viewTransform", vTransform);
//    //shaderID.setVec3("viewPos", 0, 0, 0);
//
//}
//
//void make_tree() {
//    //unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//    //glUniform3f(oColorLocation, 0.f, 0.5f, 0.f);
//    shaderID.setVec3("objectColor", 0.f, 0.5f, 0.f);
//
//    for (int i = 0; i < 8; ++i) {
//        for (int j = 0; j < 8; ++j) {
//            if (i == 0 || i == 7) {
//                glm::mat4 Tx = glm::mat4(1.0f);
//                glm::mat4 Rz = glm::mat4(1.0f);
//                glm::mat4 TR = glm::mat4(1.0f);
//                glm::mat4 model = glm::mat4(1.0f);
//
//                Tx = glm::translate(Tx, glm::vec3(tree_place.x[i], 0.0, tree_place.y[j]));
//                Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
//                model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
//
//                TR = Rz * Tx * model;
//
//                //unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//                //glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
//                shaderID.setMat4("modelTransform", TR);
//                glBindVertexArray(VAO_tree);
//
//                glEnable(GL_DEPTH_TEST);
//
//                glDrawArrays(GL_TRIANGLES, 0, Tree);
//            }
//
//            else if (j == 0 || j == 7) {
//                glm::mat4 Tx = glm::mat4(1.0f);
//                glm::mat4 Rz = glm::mat4(1.0f);
//                glm::mat4 TR = glm::mat4(1.0f);
//                glm::mat4 model = glm::mat4(1.0f);
//
//                Tx = glm::translate(Tx, glm::vec3(tree_place.x[i], 0.0, tree_place.y[j]));
//                Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
//                model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
//
//                TR = Rz * Tx * model;
//
//                /*unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//                glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//                shaderID.setMat4("modelTransform", TR);
//                glBindVertexArray(VAO_tree);
//                glBindVertexArray(VAO_tree);
//
//                glEnable(GL_DEPTH_TEST);
//
//                glDrawArrays(GL_TRIANGLES, 0, Tree);
//            }
//        }
//    }
//}
//
//void make_sun() {
//    //unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//    //glUniform3f(oColorLocation, 1.0f, 1.0f, 0.0f);
//
//    //glm::mat4 Tx = glm::mat4(1.0f);
//    //glm::mat4 Rz = glm::mat4(1.0f);
//    //glm::mat4 TR = glm::mat4(1.0f);
//    //glm::mat4 model = glm::mat4(1.0f);
//
//    //Tx = glm::translate(Tx, glm::vec3(lightPos_x, lightPos_y, lightPos_z));
//    //Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
//    //model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
//
//    //TR = Rz * Tx * model;
//
//    //unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//    //glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
//    //glBindVertexArray(VAO_sphere);
//
//    //glEnable(GL_DEPTH_TEST);
//
//    //glDrawArrays(GL_TRIANGLES, 0, Sphere);
//}
//
//void light() {
//    //����
//    shaderID.setVec3("lightPos", 0.f, 3.f, 0.f);
//    shaderID.setVec3("lightColor", 3.f, 3.f, 3.f);
//
// /*   unsigned int lightFlagLocation = glGetUniformLocation(shaderID, "light_Flag");
//    glUniform3f(lightFlagLocation, 1.0, 1.0, 1.0);
//
//    unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
//    glUniform3f(lightPosLocation, lightPos_x, lightPos_y, lightPos_z);
//
//    unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
//    glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);*/
//
//    unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
//    glUniform3f(viewPosLocation, cameraPos_x, cameraPos_y, cameraPos_z);
//}
//
//void make_place() {
//    place.tri_shapes[0][xPos] = -0.5;
//    place.tri_shapes[0][yPos] = -0.5;
//    place.tri_shapes[0][zPos] = -0.5;
//
//    place.tri_shapes[1][xPos] = 0.5;
//    place.tri_shapes[1][yPos] = -0.5;
//    place.tri_shapes[1][zPos] = -0.5;
//
//    place.tri_shapes[2][xPos] = 0.5;
//    place.tri_shapes[2][yPos] = 0.5;
//    place.tri_shapes[2][zPos] = -0.5;
//
//    place.tri_shapes[3][xPos] = -0.5;
//    place.tri_shapes[3][yPos] = 0.5;
//    place.tri_shapes[3][zPos] = -0.5;
//
//    place.tri_shapes[4][xPos] = -0.5;
//    place.tri_shapes[4][yPos] = -0.5;
//    place.tri_shapes[4][zPos] = 0.5;
//
//    place.tri_shapes[5][xPos] = 0.5;
//    place.tri_shapes[5][yPos] = -0.5;
//    place.tri_shapes[5][zPos] = 0.5;
//
//    place.tri_shapes[6][xPos] = 0.5;
//    place.tri_shapes[6][yPos] = 0.5;
//    place.tri_shapes[6][zPos] = 0.5;
//
//    place.tri_shapes[7][xPos] = -0.5;
//    place.tri_shapes[7][yPos] = 0.5;
//    place.tri_shapes[7][zPos] = 0.5;
//
//    place.tri_normals[0][nxPos] = -0.1;
//    place.tri_normals[0][nyPos] = -0.1;
//    place.tri_normals[0][nzPos] = -0.1;
//
//    place.tri_normals[1][nxPos] = 0.1;
//    place.tri_normals[1][nyPos] = -0.1;
//    place.tri_normals[1][nzPos] = -0.1;
//
//    place.tri_normals[2][nxPos] = 0.1;
//    place.tri_normals[2][nyPos] = 0.1;
//    place.tri_normals[2][nzPos] = -0.1;
//
//    place.tri_normals[3][nxPos] = -0.1;
//    place.tri_normals[3][nyPos] = 0.1;
//    place.tri_normals[3][nzPos] = -0.1;
//
//    place.tri_normals[4][nxPos] = -0.1;
//    place.tri_normals[4][nyPos] = -0.1;
//    place.tri_normals[4][nzPos] = 0.1;
//
//    place.tri_normals[5][nxPos] = 0.1;
//    place.tri_normals[5][nyPos] = -0.1;
//    place.tri_normals[5][nzPos] = 0.1;
//
//    place.tri_normals[6][nxPos] = 0.1;
//    place.tri_normals[6][nyPos] = 0.1;
//    place.tri_normals[6][nzPos] = 0.1;
//
//    place.tri_normals[7][nxPos] = -0.1;
//    place.tri_normals[7][nyPos] = 0.1;
//    place.tri_normals[7][nzPos] = 0.1;
//
//    for (int i = 0; i < 8; i++) {
//        place.tri_colors[i][rColor] = GenerateRandomColor();
//        place.tri_colors[i][gColor] = GenerateRandomColor();
//        place.tri_colors[i][bColor] = GenerateRandomColor();
//    }
//}
//
//void move_place() {
//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 10; j++) {
//           /* unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//            glUniform3f(oColorLocation, 0.2f, 0.8f, 0.0f);*/
//            shaderID.setVec3("objectColor", 0.2f, 0.8f, 0.0f);
//
//            glm::mat4 Tx = glm::mat4(1.0f);
//            glm::mat4 Rz = glm::mat4(1.0f);
//            glm::mat4 TR = glm::mat4(1.0f);
//            glm::mat4 model = glm::mat4(1.0f);
//
//            Tx = glm::translate(Tx, glm::vec3(build_place.x[i], 0.01, build_place.y[j]));
//            Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
//            model = glm::scale(model, glm::vec3(1.5, 0.0001, 1.5));
//
//            TR = Tx * Rz * model;
//
//           /* unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//            shaderID.setMat4("modelTransform", TR);
//            glBindVertexArray(place_vao);
//
//            glEnable(GL_DEPTH_TEST);
//
//            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//        }
//    }
//
// /*   unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//    glUniform3f(oColorLocation, 0.5f, 0.5f, 0.5f);*/
//    shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);
//    glm::mat4 Tx = glm::mat4(1.0f);
//    glm::mat4 Rz = glm::mat4(1.0f);
//    glm::mat4 TR = glm::mat4(1.0f);
//    glm::mat4 model = glm::mat4(1.0f);
//
//    Tx = glm::translate(Tx, glm::vec3(0.0, 0.0, 0.05));
//    Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
//    model = glm::scale(model, glm::vec3(20.0, 0.0001, 20.0));
//
//    TR = Tx * Rz * model;
//
//   /* unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//    shaderID.setMat4("modelTransform", TR);
//    glBindVertexArray(place_vao);
//
//    glEnable(GL_DEPTH_TEST);
//
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//}
//
//void make_build() {
//    for (int i = 0; i < 100; i++) {
//        if (house.build[i] == true) {
//            /*unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//            glUniform3f(oColorLocation, 0.5f, 0.5f, 0.5f);*/
//            shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);
//
//            glm::mat4 Tx = glm::mat4(1.0f);
//            glm::mat4 Rz = glm::mat4(1.0f);
//            glm::mat4 TR = glm::mat4(1.0f);
//            glm::mat4 model = glm::mat4(1.0f);
//
//            Tx = glm::translate(Tx, glm::vec3(house.x[i], 0.0f, house.y[i]));
//            Rz = glm::rotate(Rz, glm::radians(house.angle[i]), glm::vec3(0.0, 1.0, 0.0));
//            model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
//
//            TR = Tx * Rz * model;
//
//          /*  unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//            shaderID.setMat4("modelTransform", TR);
//            glBindVertexArray(VAO_house);
//
//            glEnable(GL_DEPTH_TEST);
//
//            glDrawArrays(GL_TRIANGLES, 0, House);
//        }
//
//        if (building.build[i] == true) {
//            /*unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//            glUniform3f(oColorLocation, 0.5f, 0.5f, 0.5f);*/
//            shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);
//
//            glm::mat4 Tx = glm::mat4(1.0f);
//            glm::mat4 Rz = glm::mat4(1.0f);
//            glm::mat4 TR = glm::mat4(1.0f);
//            glm::mat4 model = glm::mat4(1.0f);
//
//            Tx = glm::translate(Tx, glm::vec3(building.x[i], 0.0f, building.y[i]));
//            Rz = glm::rotate(Rz, glm::radians(building.angle[i]), glm::vec3(0.0, 1.0, 0.0));
//            model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
//
//            TR = Tx * Rz * model;
//
//          /*  unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//            shaderID.setMat4("modelTransform", TR);
//            glBindVertexArray(VAO_build);
//
//            glEnable(GL_DEPTH_TEST);
//
//            glDrawArrays(GL_TRIANGLES, 0, Building);
//        }
//
//        if (top.build[i] == true) {
//            /*unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//            glUniform3f(oColorLocation, 0.5f, 0.5f, 0.5f);*/
//            shaderID.setVec3("objectColor", 0.5f, 0.5f, 0.5f);
//
//            glm::mat4 Tx = glm::mat4(1.0f);
//            glm::mat4 Rz = glm::mat4(1.0f);
//            glm::mat4 TR = glm::mat4(1.0f);
//            glm::mat4 model = glm::mat4(1.0f);
//
//            Tx = glm::translate(Tx, glm::vec3(top.x[i], 0.0f, top.y[i]));
//            Rz = glm::rotate(Rz, glm::radians(top.angle[i]), glm::vec3(0.0, 1.0, 0.0));
//            model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
//
//            TR = Tx * Rz * model;
//
//           /* unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//            shaderID.setMat4("modelTransform", TR);
//            glBindVertexArray(VAO_top);
//
//            glEnable(GL_DEPTH_TEST);
//
//            glDrawArrays(GL_TRIANGLES, 0, Top);
//        }
//    }
//}
//
//void make_point() {
//    if (build_h) {
//        /*unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//        glUniform3f(oColorLocation, 1.0f, 0.0f, 0.0f);*/
//        shaderID.setVec3("objectColor", 1.0f, 0.0f, 0.0);
//
//        glm::mat4 Tx = glm::mat4(1.0f);
//        glm::mat4 Rz = glm::mat4(1.0f);
//        glm::mat4 TR = glm::mat4(1.0f);
//        glm::mat4 model = glm::mat4(1.0f);
//
//        Tx = glm::translate(Tx, glm::vec3(point_x, 0.0f, point_z));
//        Rz = glm::rotate(Rz, glm::radians(build_angle), glm::vec3(0.0, 1.0, 0.0));
//        model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
//
//        TR = Tx * Rz * model;
//
//        /*unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//        shaderID.setMat4("modelTransform", TR);
//        glBindVertexArray(VAO_house);
//
//        glEnable(GL_DEPTH_TEST);
//
//        glDrawArrays(GL_TRIANGLES, 0, House);
//    }
//
//    if (build_b) {
//        /*unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//        glUniform3f(oColorLocation, 1.0f, 0.0f, 0.0f);*/
//        shaderID.setVec3("objectColor", 1.0f, 0.0f, 0.0);
//
//        glm::mat4 Tx = glm::mat4(1.0f);
//        glm::mat4 Rz = glm::mat4(1.0f);
//        glm::mat4 TR = glm::mat4(1.0f);
//        glm::mat4 model = glm::mat4(1.0f);
//
//        Tx = glm::translate(Tx, glm::vec3(point_x, 0.0f, point_z));
//        Rz = glm::rotate(Rz, glm::radians(build_angle), glm::vec3(0.0, 1.0, 0.0));
//        model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
//
//        TR = Tx * Rz * model;
//
//       /* unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//        shaderID.setMat4("modelTransform", TR);
//        glBindVertexArray(VAO_build);
//
//        glEnable(GL_DEPTH_TEST);
//
//        glDrawArrays(GL_TRIANGLES, 0, Building);
//    }
//
//    if (build_t) {
//       /* unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//        glUniform3f(oColorLocation, 1.0f, 0.0f, 0.0f);*/
//        shaderID.setVec3("objectColor", 1.0f, 0.0f, 0.0);
//
//        glm::mat4 Tx = glm::mat4(1.0f);
//        glm::mat4 Rz = glm::mat4(1.0f);
//        glm::mat4 TR = glm::mat4(1.0f);
//        glm::mat4 model = glm::mat4(1.0f);
//
//        Tx = glm::translate(Tx, glm::vec3(point_x, 0.0f, point_z));
//        Rz = glm::rotate(Rz, glm::radians(build_angle), glm::vec3(0.0, 1.0, 0.0));
//        model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
//
//        TR = Tx * Rz * model;
//
//        /*unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));*/
//        shaderID.setMat4("modelTransform", TR);
//        glBindVertexArray(VAO_top);
//
//        glEnable(GL_DEPTH_TEST);
//
//        glDrawArrays(GL_TRIANGLES, 0, Top);
//    }
//
//    /*unsigned int oColorLocation = glGetUniformLocation(shaderID, "objectColor");
//    glUniform3f(oColorLocation, 1.0f, 0.0f, 0.0f);
//
//    glm::mat4 Tx = glm::mat4(1.0f);
//    glm::mat4 Rz = glm::mat4(1.0f);
//    glm::mat4 TR = glm::mat4(1.0f);
//    glm::mat4 model = glm::mat4(1.0f);
//
//    Tx = glm::translate(Tx, glm::vec3(point_x, 0.0f, point_z));
//    Rz = glm::rotate(Rz, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
//    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
//
//    TR = Rz * Tx * model;
//
//    unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
//    glBindVertexArray(place_vao);
//
//    glEnable(GL_DEPTH_TEST);
//
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/
//}