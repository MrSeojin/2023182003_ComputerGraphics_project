#include <iostream>
#include <random>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLclampf> color(0.0f, 1.0f), point(-0.1f, 0.1f);

struct sqare {
	GLclampf x1, y1, x2, y2, r, g, b;
	int dir;
	BOOL cheak;
};
sqare sq[5], return_sq[5];
GLclampf size_x, size_y;
int moving_form, to_out_move_sqare = false;

GLvoid drawScene (GLvoid);
GLvoid Reshape (int w, int h);
GLvoid Keyboard (unsigned char key, int x, int y);
GLvoid move_sqare (int value);
GLvoid Mouse(int button, int state, int x, int y);

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(900, 900); // �������� ũ�� ����
	glutCreateWindow("Project_01_04"); // ������ ����(������ �̸�)
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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // �������� ��blue���� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	for (int i = 0; i < 5; ++i) {
		if (sq[i].cheak) {
			glColor3f(sq[i].r, sq[i].g, sq[i].b);
			glRectf(sq[i].x1 - size_x / 4, sq[i].y2 - size_y / 4, sq[i].x2 + size_x / 4, sq[i].y1 + size_y / 4);
		}
	}
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		if (to_out_move_sqare&& moving_form == 1)
			to_out_move_sqare = false;
		else if (!to_out_move_sqare) {
			moving_form = 1;
			to_out_move_sqare = true;
			glutTimerFunc(100, move_sqare, moving_form);
		}
		else
			moving_form = 1;
		break;
	case '2':
		if (to_out_move_sqare && moving_form == 2)
			to_out_move_sqare = false;
		else if (!to_out_move_sqare) {
			moving_form = 2;
			to_out_move_sqare = true;
			glutTimerFunc(100, move_sqare, moving_form);
		}
		else
			moving_form = 2;
		break;
	case '3':
		if (to_out_move_sqare && moving_form == 3)
			to_out_move_sqare = false;
		else if (!to_out_move_sqare) {
			moving_form = 3;
			to_out_move_sqare = true;
			glutTimerFunc(100, move_sqare, moving_form);
		}
		else
			moving_form = 3;
		break;
	case '4':
		if (to_out_move_sqare && moving_form == 4)
			to_out_move_sqare = false;
		else if (!to_out_move_sqare) {
			moving_form = 4;
			to_out_move_sqare = true;
			glutTimerFunc(100, move_sqare, moving_form);
		}
		else
			moving_form = 4;
		break;
	case 's':
		to_out_move_sqare = false;
		break;
	case 'm':
		for (int i = 0; i < 5; ++i) 
			sq[i] = return_sq[i];
		size_x = 0;
		size_y = 0;
		glutPostRedisplay();
		break;
	case 'r':
		for (int i = 0; i < 5; ++i) {
			sq[i].cheak = false;
			return_sq[i].cheak = false;
		}
		size_x = 0;
		size_y = 0;
		glutPostRedisplay();
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
}
GLvoid move_sqare(int value)
{
	switch (value) {
	case 1:	// ��ġ ��ȭ1-> �簢������ ���� �밢������ �̵��ϰ� ���� ������ ƨ�� �ٸ� �������� �̵�
		for (int i = 0; i < 5; ++i) {
			if (sq[i].cheak) {
				switch (sq[i].dir) {
				case 1:	// cross right up
					sq[i].x1 += 0.05f;
					sq[i].x2 += 0.05f;
					sq[i].y1 += 0.05f;
					sq[i].y2 += 0.05f;
					if (sq[i].x2 >= 1.0f || sq[i].y1 >= 1.0f) 
						sq[i].dir = 2;
					if (sq[i].x2 > 1.0f) {
						sq[i].x1 = sq[i].x1 - (sq[i].x2 - 1.0f);
						sq[i].x2 = 1.0f;
					}
					if (sq[i].y1 > 1.0f) {
						sq[i].y2 = sq[i].y2 - (sq[i].y1 - 1.0f);
						sq[i].y1 = 1.0f;
					}
					break;
				case 2:	// cross right down
					sq[i].x1 += 0.05f;
					sq[i].x2 += 0.05f;
					sq[i].y1 -= 0.05f;
					sq[i].y2 -= 0.05f;
					if (sq[i].x2 >= 1.0f || sq[i].y2 <= -1.0f) 
						sq[i].dir = 3;
					if (sq[i].x2 > 1.0f) {
						sq[i].x1 = sq[i].x1 - (sq[i].x2 - 1.0f);
						sq[i].x2 = 1.0f;
					}
					if (sq[i].y2 < -1.0f) {
						sq[i].y1 = sq[i].y1 - (sq[i].y2 + 1.0f);
						sq[i].y2 = -1.0f;
					}
					break;
				case 3:	// cross left down
					sq[i].x1 -= 0.05f;
					sq[i].x2 -= 0.05f;
					sq[i].y1 -= 0.05f;
					sq[i].y2 -= 0.05f;
					if (sq[i].x1 <= -1.0f || sq[i].y2 <= -1.0f)
						sq[i].dir = 4;
					if (sq[i].x1 < -1.0f) {
						sq[i].x2 = sq[i].x2 - (sq[i].x1 + 1.0f);
						sq[i].x1 = -1.0f;
					}
					if (sq[i].y2 < -1.0f) {
						sq[i].y1 = sq[i].y1 - (sq[i].y2 + 1.0f);
						sq[i].y2 = -1.0f;
					}
					break;
				case 4:	// cross left up
					sq[i].x1 -= 0.05f;
					sq[i].x2 -= 0.05f;
					sq[i].y1 += 0.05f;
					sq[i].y2 += 0.05f;
					if (sq[i].x1 <= -1.0f || sq[i].y1 >= 1.0f)
						sq[i].dir = 1;
					if (sq[i].x1 < -1.0f) {
						sq[i].x2 = sq[i].x2 - (sq[i].x1 + 1.0f);
						sq[i].x1 = -1.0f;
					}
					if (sq[i].y1 > 1.0f) {
						sq[i].y2 = sq[i].y2 - (sq[i].y1 - 1.0f);
						sq[i].y1 = 1.0f;
					}
					break;
				}
			}
		}
		break;
	case 2: // ��ġ ��ȭ2-> �簢������ ������׷� �̵�
		for (int i = 0; i < 5; ++i) {
			if (sq[i].cheak) {
				switch (sq[i].dir) {
				case 1:	// cross right up
					sq[i].x1 += 0.1f;
					sq[i].x2 += 0.1f;
					sq[i].y1 += 0.05f;
					sq[i].y2 += 0.05f;
					if (sq[i].x2 > 1.0f) {
						sq[i].x1 = sq[i].x1 - (sq[i].x2 - 1.0f);
						sq[i].x2 = 1.0f;
					}
					if (sq[i].y1 > 1.0f) {
						sq[i].y2 = sq[i].y2 - (sq[i].y1 - 1.0f);
						sq[i].y1 = 1.0f;
					}
					if (sq[i].y1 == 1.0f)
						sq[i].dir += 2;
					else if(sq[i].x2 == 1.0f)
						sq[i].dir += 1;
					break;
				case 2:	// cross left up
					sq[i].x1 -= 0.1f;
					sq[i].x2 -= 0.1f;
					sq[i].y1 += 0.05f;
					sq[i].y2 += 0.05f;
					if (sq[i].x1 < -1.0f) {
						sq[i].x2 = sq[i].x2 - (sq[i].x1 + 1.0f);
						sq[i].x1 = -1.0f;
					}
					if (sq[i].y1 > 1.0f) {
						sq[i].y2 = sq[i].y2 - (sq[i].y1 - 1.0f);
						sq[i].y1 = 1.0f;
					}
					if (sq[i].y1 == 1.0f)
						sq[i].dir += 2;
					else if (sq[i].x1 == -1.0f)
						sq[i].dir -= 1;
					break;
				case 3:	// cross right down
					sq[i].x1 += 0.1f;
					sq[i].x2 += 0.1f;
					sq[i].y1 -= 0.05f;
					sq[i].y2 -= 0.05f;
					if (sq[i].x2 > 1.0f) {
						sq[i].x1 = sq[i].x1 - (sq[i].x2 - 1.0f);
						sq[i].x2 = 1.0f;
					}
					if (sq[i].y2 < -1.0f) {
						sq[i].y1 = sq[i].y1 - (sq[i].y2 + 1.0f);
						sq[i].y2 = -1.0f;
					}
					if (sq[i].y2 == -1.0f)
						sq[i].dir -= 2;
					else if (sq[i].x2 == 1.0f)
						sq[i].dir += 1;
					break;
				case 4:	// cross left down
					sq[i].x1 -= 0.1f;
					sq[i].x2 -= 0.1f;
					sq[i].y1 -= 0.05f;
					sq[i].y2 -= 0.05f;
					if (sq[i].x1 < -1.0f) {
						sq[i].x2 = sq[i].x2 - (sq[i].x1 + 1.0f);
						sq[i].x1 = -1.0f;
					}
					if (sq[i].y2 < -1.0f) {
						sq[i].y1 = sq[i].y1 - (sq[i].y2 + 1.0f);
						sq[i].y2 = -1.0f;
					}
					if (sq[i].y2 == -1.0f)
						sq[i].dir -= 2;
					else if(sq[i].x1 == -1.0f)
						sq[i].dir -= 1;
					break;
				}
			}
		}
		break;
	case 3:	// ũ�� ��ȭ -> �簢���� ũ�Ⱑ �پ��ϰ� ��ȭ
		size_x = point(dre);
		size_y = point(dre);
		break;
	case 4:	// ���� ��ȭ -> �簢���� ������ �����ϰ� ��ȭ
		for (int i = 0; i < 5; ++i) {
			if (sq[i].cheak) {
				sq[i].r = color(dre);
				sq[i].g = color(dre);
				sq[i].b = color(dre);
			}
		}
		break;
	}
	glutPostRedisplay();
	if (to_out_move_sqare)
		glutTimerFunc(100, move_sqare, moving_form); // (�и�����, �Լ���, �Լ��� ������ ��)
}
GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < 5; ++i) {
			if (!sq[i].cheak) {
				GLclampf center_x = static_cast<GLclampf>(x) / 450 - 1, center_y = 1 - static_cast<GLclampf>(y) / 450;
				sq[i].cheak = true;
				sq[i].x1 = center_x - 0.1f;
				sq[i].x2 = center_x + 0.1f;
				sq[i].y1 = center_y + 0.1f;
				sq[i].y2 = center_y - 0.1f;
				sq[i].dir = 1;
				sq[i].r = color(dre);
				sq[i].g = color(dre);
				sq[i].b = color(dre);
				return_sq[i] = sq[i];
				break;
			}
		}
	}
	glutPostRedisplay();
}
