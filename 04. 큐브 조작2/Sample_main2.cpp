#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>
#include<algorithm>

#include <glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/quaternion.hpp>
#include<glm/gtc/quaternion.hpp>


using namespace std;
using namespace glm;

GLuint programID;
GLint vtxPosition, colorLoc, a_Color;
GLint TransLoc;
GLuint VAO, VBO, ibo;
int y = 1, x = 1;
float width = 500, height = 500;

glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
GLint pro;

GLfloat translation[16] = {
   1.0f, 0.0f, 0.0f, 0.0f ,
   0.0f, 1.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 1.0f
};
GLfloat cube[24][2][3] = {
    //Front
    {{-0.01f, -0.01f, 0.01f}, {1.0f, 0.0f, 0.0f}},
    {{0.01f, -0.01f, 0.01f}, {1.0f, 0.0f, 0.0f}},
    {{0.01f, 0.01f, 0.01f}, {1.0f, 0.0f, 0.0f}},
    {{-0.01f, 0.01f, 0.01f}, {1.0f, 0.0f, 0.0f}},

    //Back
    {{-0.01f, -0.01f, -0.01f}, {0.0f, 1.0f, 0.0f}},
    {{0.01f, -0.01f, -0.01f}, {0.0f, 1.0f, 0.0f}},
    {{0.01f, 0.01f, -0.01f}, {0.0f, 1.0f, 0.0f}},
    {{-0.01f, 0.01f, -0.01f}, {0.0f, 1.0f, 0.0f}},

    //TOP
    {{-0.01f, 0.01f, -0.01f}, {0.0f, 0.0f, 1.0f}},
    {{0.01f, 0.01f, -0.01f}, {0.0f, 0.0f, 1.0f}},
    {{0.01f, 0.01f, -0.01f}, {0.0f, 0.0f, 1.0f}},
    {{-0.01f, 0.01f, -0.01f}, {0.0f, 0.0f, 1.0f}},

    //Bottom
    {{-0.01f, -0.01f, -0.01f}, {1.0f, 1.0f, 0.0f}},
    {{0.01f, -0.01f, -0.01f}, {1.0f, 1.0f, 0.0f}},
    {{0.01f, -0.01f, 0.01f}, {1.0f, 1.0f, 0.0f}},
    {{-0.01f, -0.01f, 0.01f}, {1.0f, 1.0f, 0.0f}},

    //Right
    {{0.01f, -0.01f, -0.01f}, {1.0f, 0.0f, 1.0f}},
    {{0.01f, -0.01f, 0.01f}, {1.0f, 0.0f, 1.0f}},
    {{0.01f, 0.01f, 0.01f}, {1.0f, 0.0f, 1.0f}},
    {{0.01f, 0.01f, -0.01f}, {1.0f, 0.0f, 1.0f}},

    //Left
    {{-0.01f, -0.01f, -0.01f}, {1.0f, 1.0f, 1.0f}},
    {{-0.01f, -0.01f, 0.01f}, {1.0f, 1.0f, 1.0f}},
    {{-0.01f, 0.01f, 0.01f}, {1.0f, 1.0f, 1.0f}},
    {{-0.01f, 0.01f, -0.01f}, {1.0f, 1.0f, 1.0f}}
};
GLint  indices[] = {
    //Front
    0,1,2,
    2,3,0,

    //Back
    4,5,6,
    6,7,4,

    //Top
    8,9,10,
    10,11,8,

    //Bottom
    12,13,14,
    14,15,12,

    //Right
    16,17,18,
    18,19,16,

    //Left
    20,21,22,
    22,23,20
};

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    //create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    //Read the vertex shader code from the file
    string VertexShaderCode;
    ifstream VertexShaderStream(vertex_file_path, ios::in);
    if (VertexShaderStream.is_open())
    {
        string Line = "";
        while (getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    //Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    //Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength != 0) {
        vector<char> VertexShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
    }
    //Read the fragment shader code from the file
    string FragmentShaderCode;
    ifstream FragmentShaderStream(fragment_file_path, ios::in);
    if (FragmentShaderStream.is_open())
    {
        string Line = "";
        while (getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    //Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    //Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength != 0) {
        vector<char> FragmentShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }
    //Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength != 0) {
        vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
bool flag = true;
glm::vec3 cameraPos(0, 0.5, 4);
glm::vec3 cameraTarget(0.5, 0.5, 0.0);
void renderScene(void)
{
    //Clear all pixels
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0, 1, 0));

    GLint TransLoc = glGetUniformLocation(programID, "translation");
    GLint viewLoc = glGetUniformLocation(programID, "view");
    GLint proLoc = glGetUniformLocation(programID, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(pro, 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(pro, 1, GL_FALSE, glm::value_ptr(projection));
    //Let's draw something here    
    float gap = 0.05f;
    glBindVertexArray(VAO);

    float backup = translation[3];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            translation[3] = gap * (j);
            glUniformMatrix4fv(TransLoc, 1, GL_TRUE, translation);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        translation[3] = backup;
        translation[7] = -gap * (i);
    }
    glutPostRedisplay();

    //Double buffer
    glutSwapBuffers();
}

void init()
{
    //initilize the glew and check the errors.
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
    }

    vtxPosition = glGetAttribLocation(programID, "vtxPosition");
    a_Color = glGetAttribLocation(programID, "a_Color");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &ibo);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(sizeof(GLfloat)*3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //select the background color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'p': // perspective projection
        projection = glm::perspective(glm::radians(45.0f), 1.0f * width / height, 0.1f, 50.0f);
        break;
    case 'o': // orthogonal projection
        projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    //init GLUT and create Window
    //initialize the GLUT
    glutInit(&argc, argv);
    //GLUT_DOUBLE enables double buffering (drawing to a background buffer while the other buffer is displayed)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    //These two functions are used to define the position and size of the window. 
    glutInitWindowPosition(300, 50);
    glutInitWindowSize(width, height);
    //This is used to define the name of the window.
    glutCreateWindow("Simple OpenGL Window");

    //call initization function
    init();

    //1.
    //Generate VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    //3. 
    programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
    glUseProgram(programID);
;
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(renderScene);

    //enter GLUT event processing cycle
    glutMainLoop();

    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteVertexArrays(1, &ibo);

    return 1;
}