#include <iostream>
#include <random>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/GL.h>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLclampf> uid(0.0f, 1.0f);

GLfloat width = 1200, height = 900;
GLfloat backGround_r = 0.0f, backGround_g = 0.0f, backGround_b = 1.0f;
typedef struct sqare{
	float x1, y1, x2, y2, r, g, b;
}sq;
sq back_sq[4];
void set_backSqare()
{
	for (int i = 0; i < 4; ++i) {
		if (i % 2 == 1) {//¦�� x�� �� �κ�
			back_sq[i].x1 = width / 2;
			back_sq[i].x2 = width;
		}
		else {
			back_sq[i].x1 = 0;
			back_sq[i].x2 = width / 2;
		}
		if (i < 2) {//���� �� �׸�
			back_sq[i].y1 = 0;
			back_sq[i].y2 = height / 2;
		}
		else {
			back_sq[i].y1 = height / 2;
			back_sq[i].y2 = height;
		}
		back_sq[i].r = uid(dre);
		back_sq[i].g = uid(dre);
		back_sq[i].b = uid(dre);
	}
}

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(width, height); // �������� ũ�� ����
	set_backSqare();
	glutCreateWindow("Project_01_02"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(backGround_r, backGround_g, backGround_b, 1.0f); // �������� ��blue���� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �簢�� �׸��� ------------------------------------------------
	for (int i = 0; i < 4; ++i) {
		glColor3f(back_sq[i].r, back_sq[i].g, back_sq[i].b);
		glRectf((back_sq[i].x1 - width / 2) / (width / 2), (height / 2 - back_sq[i].y2) / (height / 2), (back_sq[i].x2 - width / 2) / (width / 2), (height / 2 - back_sq[i].y1) / (height / 2));
	}
	// --------------------------------------------------------------
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);
}
void Mouse(int button, int state, int x, int y) 
{
	if (state == GLUT_DOWN) {
		for (int i = 0; i < 4; ++i) {
			if (button == GLUT_LEFT_BUTTON) {
				if (back_sq[i].x1 < x && x < back_sq[i].x2 &&
					back_sq[i].y1 < y && y < back_sq[i].y2) {
					back_sq[i].r = uid(dre);
					back_sq[i].g = uid(dre);
					back_sq[i].b = uid(dre);
					break;
				}
				else if (i == 3) {
					backGround_r = uid(dre);
					backGround_g = uid(dre);
					backGround_b = uid(dre);
					// glColor3f(backGround_r, backGround_g, backGround_b);
				}
				// (i % 2 * width / 2 < x && x < (i / 2 + 1) * width / 2
				// && i / 2 * height / 2 < y && y < (i / 2 + 1) * height / 2)
			}
			else if (button == GLUT_RIGHT_BUTTON) {
				if (back_sq[i].x1 < x && x < back_sq[i].x2 &&
					back_sq[i].y1 < y && y < back_sq[i].y2) {
					back_sq[i].x1 += 5;
					back_sq[i].x2 -= 5;
					back_sq[i].y1 += 5;
					back_sq[i].y2 -= 5;
					if (back_sq[i].x1 >= back_sq[i].x2 || back_sq[i].y1 >= back_sq[i].y2) {
						back_sq[i].x1 -= 5;
						back_sq[i].x2 += 5;
						back_sq[i].y1 -= 5;
						back_sq[i].y2 += 5;
					}
					break;
				}
				else if (i == 3) {
					for (int j = 0; j < 4; ++j) {
						back_sq[j].x1 -= 5;
						back_sq[j].x2 += 5;
						back_sq[j].y1 -= 5;
						back_sq[j].y2 += 5;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}
