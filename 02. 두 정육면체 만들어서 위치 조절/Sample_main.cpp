#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>
#include<algorithm>


using namespace std;

void init();
void renderScene(void);
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
GLint location;
GLuint colorLoc;
GLuint TransLoc;
GLuint programID;
double width = 500, height = 500;
GLuint VAO;

GLuint buffers[1];
bool flag = false;
int x = 1;
GLfloat color[] = {
	/* front surface is blue */
	-0.8, 1.0, 0.1,
	-1.0, 0.8, 0.1,
	-0.8, 0.8, 0.1,
	-0.8, 1.0, 0.1,
	-1.0, 1.0, 0.1,
	-1.0, 0.8, 0.1,
	/* left surface is green */
	-1.0, 1.0, 0.1,
	-1.0, 0.8, -0.1,
	-1.0, 0.8, 0.1,
	-1.0, 1.0, 0.1,
	-1.0, 1.0, -0.1,
	-1.0, 0.8, -0.1,
	/* top surface is red */
	-1.0, 1.0, 0.1,
	-0.8, 1.0, -0.1,
	-1.0, 1.0, -0.1,
	-1.0, 1.0, 0.1,
	-0.8, 1.0, 0.1,
	-0.8, 1.0, -0.1,
	/* right surface is yellow */
	-0.8, 1.0, -0.1,
	-0.8, 0.8, 0.1,
	-0.8, 0.8, -0.1,
	-0.8, 1.0, -0.1,
	-0.8, 1.0, 0.1,
	-0.8, 0.8, 0.1,
	/* back surface is cyan */
	-1.0, 1.0, -0.1,
	-0.8, 0.8, -0.1,
	-1.0, 0.8, -0.1,
	-1.0, 1.0, -0.1,
	-0.8, 1.0, -0.1,
	-0.8, 0.8, -0.1,
	/* bottom surface is magenta */
	-1.0, 0.8, -0.1,
	-0.8, 0.8, 0.1,
	-1.0, 0.8, 0.1,
	-1.0, 0.8, -0.1,
	-0.8, 0.8, -0.1,
	-0.8, 0.8, 0.1
};
GLfloat vertices[] = {
	 /* front surface is blue */
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    /* left surface is green */
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    /* top surface is red */
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    /* right surface is yellow */
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    /* back surface is cyan */
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    /* bottom surface is magenta */
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0
};


GLfloat color2[] = {
	/* front surface is blue */
	0.8, 1.0, 0.1,
	1.0, 0.8, 0.1,
	0.8, 0.8, 0.1,
	0.8, 1.0, 0.1,
	1.0, 1.0, 0.1,
	1.0, 0.8, 0.1,
	/* left surface is green */
	1.0, 1.0, 0.1,
	1.0, 0.8, -0.1,
	1.0, 0.8, 0.1,
	1.0, 1.0, 0.1,
	1.0, 1.0, -0.1,
	1.0, 0.8, -0.1,
	/* top surface is red */
	1.0, 1.0, 0.1,
	0.8, 1.0, -0.1,
	1.0, 1.0, -0.1,
	1.0, 1.0, 0.1,
	0.8, 1.0, 0.1,
	0.8, 1.0, -0.1,
	/* right surface is yellow */
	0.8, 1.0, -0.1,
	0.8, 0.8, 0.1,
	0.8, 0.8, -0.1,
	0.8, 1.0, -0.1,
	0.8, 1.0, 0.1,
	0.8, 0.8, 0.1,
	/* back surface is cyan */
	1.0, 1.0, -0.1,
	0.8, 0.8, -0.1,
	1.0, 0.8, -0.1,
	1.0, 1.0, -0.1,
	0.8, 1.0, -0.1,
	0.8, 0.8, -0.1,
	/* bottom surface is magenta */
	1.0, 0.8, -0.1,
	0.8, 0.8, 0.1,
	1.0, 0.8, 0.1,
	1.0, 0.8, -0.1,
	0.8, 0.8, -0.1,
	0.8, 0.8, 0.1
};
GLfloat vertices2[] = {
   /* right surface is yellow */
   1.0, 1.0, 0.0,
   1.0, 1.0, 0.0,
   1.0, 1.0, 0.0,
   1.0, 1.0, 0.0,
   1.0, 1.0, 0.0,
   1.0, 1.0, 0.0,
   /* back surface is cyan */
   0.0, 1.0, 1.0,
   0.0, 1.0, 1.0,
   0.0, 1.0, 1.0,
   0.0, 1.0, 1.0,
   0.0, 1.0, 1.0,
   0.0, 1.0, 1.0,
   /* bottom surface is magenta */
   1.0, 0.0, 1.0,
   1.0, 0.0, 1.0,
   1.0, 0.0, 1.0,
   1.0, 0.0, 1.0,
   1.0, 0.0, 1.0,
   1.0, 0.0, 1.0,

   /* front surface is blue */
  0.0, 0.0, 1.0,
  0.0, 0.0, 1.0,
  0.0, 0.0, 1.0,
  0.0, 0.0, 1.0,
  0.0, 0.0, 1.0,
  0.0, 0.0, 1.0,
  /* left surface is green */
  0.0, 1.0, 0.0,
  0.0, 1.0, 0.0,
  0.0, 1.0, 0.0,
  0.0, 1.0, 0.0,
  0.0, 1.0, 0.0,
  0.0, 1.0, 0.0,
  /* top surface is red */
  1.0, 0.0, 0.0,
  1.0, 0.0, 0.0,
  1.0, 0.0, 0.0,
  1.0, 0.0, 0.0,
  1.0, 0.0, 0.0,
  1.0, 0.0, 0.0
};
void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		flag = true;
	}
}
GLfloat translation[16] = {
	1.0f, 0.0f, 0.0f, 0.0f ,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};
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

	location = glGetAttribLocation(programID, "VertexPosition");
	colorLoc = glGetAttribLocation(programID, "VertexColor");
	TransLoc = glGetUniformLocation(programID, "transform");

	glutMouseFunc(myMouse);
	glutDisplayFunc(renderScene);

	//enter GLUT event processing cycle
	glutMainLoop();

	glDeleteVertexArrays(1, &VertexArrayID);

	return 1;
}
void renderScene(void)
{
	//Clear all pixels
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Let's draw something here
	if (flag) {
		translation[7] = -0.1f * (x++);
	}
	glUniformMatrix4fv(TransLoc, 1, GL_TRUE, translation);
	
	glBindVertexArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 3*12);
	//Double buffer

	glBindVertexArray(2);
	glDrawArrays(GL_TRIANGLES, 0, 3*12);

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

	GLuint vboHandles[4];
	// 버퍼 두개생성.
	glGenBuffers(4, vboHandles);
	GLuint positionBufferHandle1 = vboHandles[0];
	GLuint colorBufferHandle1 = vboHandles[1];

	GLuint positionBufferHandle2 = vboHandles[2];
	GLuint colorBufferHandle2 = vboHandles[3];

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color2), color2, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);



	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(1); 

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle2);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

	glVertexAttribPointer(TransLoc, 16, GL_FLOAT, GL_FALSE, 0, ((void*)(0)));
	glEnableVertexAttribArray(TransLoc);

	//select the background color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

}


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
		vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	}
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

