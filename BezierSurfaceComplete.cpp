#include <GL/glut.h>
#include <bevgrafmath2017.h>
#include <math.h>
#include <vector>
using namespace std;

GLsizei winWidth = 800, winHeight = 600;
GLint keyStates[256];



int N = 4;
vec3 cube[4][4] = {};
vec3 drawableCube[4][4] = {};
//vec3 points[20] = {};


mat4 w2v, projection;
float alpha = pi() / 10;
float beta = pi() / 20;
float gamma = 0;

int counter = 0;

void initMatrices() {

	projection = perspective(10.0f);
	//projection = ortho();

	vec2 windowSize = { 2, 2 }; //width,height
	vec2 windowPosition = { -1, -1 }; //bottom left corner
	vec2 viewportSize = { 100, 100 };
	vec2 viewportPosition = { 100, 100 };
	w2v = windowToViewport3(windowPosition, windowSize, viewportPosition, viewportSize); //3d
}

void transform() {
	mat4 rotation = rotateX(alpha) * rotateY(beta)* rotateZ(gamma);
	//mat4 rotation = rotateX(pi()) * rotateY(pi()) / 20;
	mat4 M = w2v * projection * rotation;
	//mat4 M = w2v * projection;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
		vec4 pointH = ihToH(cube[i][j]);
		vec4 transformedPoint = M * pointH;

		if (transformedPoint.w != 0)
		{
			vec3 resultIh = hToIh(transformedPoint);
			if (resultIh.z == 0) { // extra if result after projection is zero
				drawableCube[i][j] = vec2(resultIh.x, resultIh.y);
			}
		}

	}
	}

}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(3.0);
	glLineWidth(1.0);


	cube[0][0] = vec3(0.0f, 0.0f, 0.0f); //x y z 
	cube[1][0] = vec3(1.0f, 0.0f, 1.0f);
	cube[2][0] = vec3(2.0f, 0.0f, 1.0f);
	cube[3][0] = vec3(3.0f, 0.0f, 0.0f);
	
	cube[0][1] = vec3(0.0f, 1.0f, 0.0f); //x y z 
	cube[1][1] = vec3(1.0f, 1.0f, 1.5f);
	cube[2][1] = vec3(2.0f, 1.0f, 1.5f);
	cube[3][1] = vec3(3.0f, 1.0f, 0.0f);

	cube[0][2] = vec3(0.0f, 2.0f, 0.0f); //x y z 
	cube[1][2] = vec3(1.0f, 2.0f, 1.5f);
	cube[2][2] = vec3(2.0f, 2.0f, 1.5f);
	cube[3][2] = vec3(3.0f, 2.0f, 0.0f);

	cube[0][3] = vec3(0.0f, 3.0f, 0.0f); //x y z 
	cube[1][3] = vec3(1.0f, 3.0f, 1.0f);
	cube[2][3] = vec3(2.0f, 3.0f, 1.0f);
	cube[3][3] = vec3(3.0f,3.0f, 0.0f);
	


	initMatrices();
	transform();

}
double binomialCoefficient(int n, int k)
{
	if (k > n - k)
		k = n - k;

	double c = 1.0;

	for (int i = 0; i < k; i++)
	{
		c = c * (n - i);
		c = c / (i + 1);
	}
	return c;
}

void initCube() {


	/*glBegin(GL_POINTS);
	for (int i = 0; i < 100; i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);
	}
	glEnd();*/
	// right face
	/*glBegin(GL_LINE_LOOP);
	glVertex2f(drawableCube[1].x, drawableCube[1].y);
	glVertex2f(drawableCube[5].x, drawableCube[5].y);
	glVertex2f(drawableCube[6].x, drawableCube[6].y);
	glVertex2f(drawableCube[2].x, drawableCube[2].y);
	glEnd();
	// left face
	glBegin(GL_LINE_LOOP);
	glVertex2f(drawableCube[0].x, drawableCube[0].y);
	glVertex2f(drawableCube[4].x, drawableCube[4].y);
	glVertex2f(drawableCube[7].x, drawableCube[7].y);
	glVertex2f(drawableCube[3].x, drawableCube[3].y);
	glEnd();
	// bottom face
	glBegin(GL_LINE_LOOP);
	glVertex2f(drawableCube[0].x, drawableCube[0].y);
	glVertex2f(drawableCube[1].x, drawableCube[1].y);
	glVertex2f(drawableCube[5].x, drawableCube[5].y);
	glVertex2f(drawableCube[4].x, drawableCube[4].y);
	glEnd();
	// top face
	glBegin(GL_LINE_LOOP);
	glVertex2f(drawableCube[2].x, drawableCube[2].y);
	glVertex2f(drawableCube[6].x, drawableCube[6].y);
	glVertex2f(drawableCube[7].x, drawableCube[7].y);
	glVertex2f(drawableCube[3].x, drawableCube[3].y);
	glEnd();*/

	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++) {
		for (int j = 0;j < 4;j++) {
			glVertex2f(drawableCube[i][j].x, drawableCube[i][j].y);
		}
	}
	glEnd();


	for (int i = 0; i < 4; i++) {
		glBegin(GL_LINE_STRIP);
		for (int j = 0;j < 4;j++) {
			glVertex2f(drawableCube[i][j].x, drawableCube[i][j].y);
		}
		glEnd();
	}

	for (int i = 0; i < 4; i++) {
		glBegin(GL_LINE_STRIP);
		for (int j = 0;j < 4;j++) {
			glVertex2f(drawableCube[j][i].x, drawableCube[j][i].y);
		}
		glEnd();
	}


	// back face
	/*glBegin(GL_LINE_LOOP);
	for (int i = 4; i < 8; i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);

	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < 4; i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);
		glVertex2f(drawableCube[i + 4].x, drawableCube[i + 4].y);


	}
	glEnd();
	*/

	//Horizontal
	for (float u = 0; u < 1.0; u += 0.1) {
		glBegin(GL_LINE_STRIP);
		for (float v = 0.0; v < 1.0; v += 0.1) {

			vec3 curvePoint = { 0.0,0.25,0.0 };
			
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
				{

					double biCoeffu = binomialCoefficient(3, i);
					double oneMinusTu = pow(1 - u, 3 - i);
					double powTu = pow(u, i);
					double oneMinusTv = pow(1 - v, 3 - j);
					double biCoeffv = binomialCoefficient(3, j);
					double powTv = pow(v, j);
					double bu = biCoeffu * oneMinusTu * powTu;
					double bv = biCoeffv * oneMinusTv * powTv;
					curvePoint.x += bu * bv *  cube[i][j].x;
					curvePoint.y += bu * bv *  cube[i][j].y;
					curvePoint.z += bu * bv *  cube[i][j].z;
				}
			}

			//glVertex2f(curvePoint.x, curvePoint.y);
			mat4 rotation = rotateX(alpha) * rotateY(beta)* rotateZ(gamma);
			mat4 M = w2v * projection * rotation;
			vec4 pointH = ihToH(curvePoint);
			vec4 transformedPoint = M * pointH;

			if (transformedPoint.w != 0)
			{
				vec3 resultIh = hToIh(transformedPoint);
				if (resultIh.z == 0) { // extra if result after projection is zero
					glVertex2f(resultIh.x, resultIh.y);
				}
			}

		}
		glEnd();

	}


	//Vertical
	for (float v = 0.0; v < 1.0; v += 0.1) {
		glBegin(GL_LINE_STRIP);
		for (float u = 0; u < 1.0; u += 0.1) {

			vec3 curvePoint = { 0.0,0.25,0.0 };


			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
				{

					double biCoeffu = binomialCoefficient(3, i);
					double oneMinusTu = pow(1 - u, 3 - i);
					double powTu = pow(u, i);
					double oneMinusTv = pow(1 - v, 3 - j);
					double biCoeffv = binomialCoefficient(3, j);
					double powTv = pow(v, j);
					double bu = biCoeffu * oneMinusTu * powTu;
					double bv = biCoeffv * oneMinusTv * powTv;
					curvePoint.x += bu * bv *  cube[i][j].x;
					curvePoint.y += bu * bv *  cube[i][j].y;
					curvePoint.z += bu * bv *  cube[i][j].z;
				}
			}
			

			//glVertex2f(curvePoint.x, curvePoint.y);
			mat4 rotation = rotateX(alpha) * rotateY(beta)* rotateZ(gamma);
			mat4 M = w2v * projection * rotation;
			vec4 pointH = ihToH(curvePoint);
			vec4 transformedPoint = M * pointH;

			if (transformedPoint.w != 0)
			{
				vec3 resultIh = hToIh(transformedPoint);
				if (resultIh.z == 0) { // extra if result after projection is zero
					glVertex2f(resultIh.x, resultIh.y);
				}
			}

		}

		glEnd();
	}




}






void keyPressed(unsigned char key, int x, int y)
{
	if (key == '1') {
		alpha += 0.1;
	}
	if (key == '2') {
		alpha -= 0.1;
	}
	if (key == '3') {
		beta += 0.1;
	}
	if (key == '4') {
		beta -= 0.1;
	}
	if (key == '5') {
		gamma += 0.1;
	}
	if (key == '6') {
		gamma -= 0.1;
	}
	transform();
	glutPostRedisplay();
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0);
    
    initCube();
	//BezierSurface();
    
    glutSwapBuffers();
}




int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Computer Graphics");
    
    init();
    glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);


    
    glutMainLoop();
    return 0;
}

