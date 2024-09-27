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
vector<pair<double, double>> points;
GLint location;
GLuint buffers[1];
GLdouble vertices[2][3];
double width = 500, height = 500;

void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		points.push_back(make_pair((double)x, (double)y));
		if (points.size() < 3) {
			fprintf(stdout, "(%lf,%lf)\n", points[points.size() - 1].first, points[points.size() - 1].second);
		}
	}
}
int main(int argc, char **argv)
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
	GLuint programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
	glUseProgram(programID);

	location = glGetAttribLocation(programID, "vtxPosition");

	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

	glVertexAttribPointer(location, 3, GL_DOUBLE, GL_FALSE, 0, ((void*)(0)));
	glEnableVertexAttribArray(location);

	glutMouseFunc(myMouse);
	glutDisplayFunc(renderScene);

	//enter GLUT event processing cycle
	glutMainLoop();

	glDeleteVertexArrays(1, &VertexArrayID);
	
	return 1; 
}

void renderScene(void)
{
	if (points.size() > 2) {
		Sleep(1000);
		exit(0);
	}
	//Clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	//Let's draw something here
	
	double x, y;
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); i++) {
		x = 2 * points[i].first / (double)width - 1;
		y = 1 - 2 * points[i].second / (double)height;
		vertices[i][0] = x;
		vertices[i][1] = y;
		vertices[i][2] = 0;
		glVertexAttrib3d(location, x, y, 0);
		glDrawArrays(GL_POINTS, i, i + 1);
	}
	glEnd();

	if (points.size() == 2) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBegin(GL_LINE_STRIP);
		glVertex3d(vertices[0][0], vertices[0][1], 0);
		glVertex3d(vertices[1][0], vertices[1][1], 0);
		glDrawArrays(GL_LINE_STRIP, 0, 2);
		glEnd();
		fprintf(stdout, "한 번 더 찍으면 종료!");
	}

	//define the size of point and draw a point.
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

