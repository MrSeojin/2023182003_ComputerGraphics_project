#include <iostream>
#include <random>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLclampf> uid(0.0f, 1.0f), point(-0.8f, 0.8f);

struct sqare {
	GLclampf x1, y1, x2, y2, r, g, b;
	BOOL cheak;
};
GLclampf width = 1200, height = 800, mouseX, mouseY;
sqare sq[10];
BOOL left_button;
int move_sq;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
int inSqare(int i, int a) {		//�浹
	if (!sq[i].cheak)
		return -1;
	else if (sq[i].x1 <= sq[a].x1 && sq[a].x1 <= sq[i].x2 && sq[i].y1 >= sq[a].y1 && sq[a].y1 >= sq[i].y2)
		return i;
	else if (sq[i].x1 <= sq[a].x2 && sq[a].x2 <= sq[i].x2 && sq[i].y1 >= sq[a].y1 && sq[a].y1 >= sq[i].y2)
		return i;
	else if (sq[i].x1 <= sq[a].x1 && sq[a].x1 <= sq[i].x2 && sq[i].y1 >= sq[a].y2 && sq[a].y2 >= sq[i].y2)
		return i;
	else if (sq[i].x1 <= sq[a].x2 && sq[a].x2 <= sq[i].x2 && sq[i].y1 >= sq[a].y2 && sq[a].y2 >= sq[i].y2)
		return i;
	else if (sq[a].x1 <= sq[i].x1 && sq[i].x1 <= sq[a].x2 && sq[a].y1 >= sq[i].y1 && sq[i].y1 >= sq[a].y2)
		return i;
	else if (sq[a].x1 <= sq[i].x2 && sq[i].x2 <= sq[a].x2 && sq[a].y1 >= sq[i].y1 && sq[i].y1 >= sq[a].y2)
		return i;
	else if (sq[a].x1 <= sq[i].x1 && sq[i].x1 <= sq[a].x2 && sq[a].y1 >= sq[i].y2 && sq[i].y2 >= sq[a].y2)
		return i;
	else if (sq[a].x1 <= sq[i].x2 && sq[i].x2 <= sq[a].x2 && sq[a].y1 >= sq[i].y2 && sq[i].y2 >= sq[a].y2)
		return i;
	else
		return -1;
}
int pointerSqare(int i, GLclampf x, GLclampf y) {
	if (!sq[i].cheak)
		return -1;
	else if (sq[i].x1 <= x && x <= sq[i].x2 && sq[i].y1 >= y && y >= sq[i].y2)
		return i;
	else
		return -1;
}
int till_the_end(int start, int a) {
	for (int i = start; i < 10; ++i) {
		if (i == a);
		else if (!sq[i].cheak)
			return -1;
		else if (inSqare(i, a) != -1)
			return inSqare(i, a);
	}
	return -1;
}

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(width, height); // �������� ũ�� ����
	glutCreateWindow("Project_01_03"); // ������ ����(������ �̸�)
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
	glutMotionFunc(Motion);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� ��blue���� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	for (int i = 0; i < 10; ++i) {
		if (sq[i].cheak) {
			glColor3f(sq[i].r, sq[i].g, sq[i].b);
			glRectf(sq[i].x1, sq[i].y2, sq[i].x2, sq[i].y1);
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
	case 'a':
	{
		int add_index;
		for (int i = 0; i < 10; ++i) {
			if (!sq[i].cheak) {
				add_index = i;
				break;
			}
			else if (i == 9)
				add_index = -1;
		}
		if (add_index != -1) {
			sq[add_index].r = uid(dre);
			sq[add_index].b = uid(dre);
			sq[add_index].g = uid(dre);
			sq[add_index].x1 = point(dre);
			sq[add_index].y1 = point(dre);
			sq[add_index].x2 = sq[add_index].x1 + 0.1f;
			sq[add_index].y2 = sq[add_index].y1 - 0.1f;
			while (till_the_end(0, add_index) != -1) {
				sq[add_index].x1 = point(dre);
				sq[add_index].y1 = point(dre);
				sq[add_index].x2 = sq[add_index].x1 + 0.1f;
				sq[add_index].y2 = sq[add_index].y1 - 0.1f;
			}
			sq[add_index].cheak = true;
		}
		glutPostRedisplay();
	}
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
}
GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		left_button = true;
		mouseX = static_cast<GLclampf>(x) / (width / 2) - 1;
		mouseY = 1 - static_cast<GLclampf>(y) / (height / 2);
		for (int i = 0; i < 10; ++i) {
			if (pointerSqare(i, mouseX, mouseY) != -1) {
				move_sq = i;
				break;
			}
			else if (i == 9)
				move_sq = -1;
		}
	}
	else if (state == GLUT_UP && left_button) {
		left_button = false;
		if (move_sq == -1);
		else {
			while (till_the_end(0, move_sq) != -1) {
				int unite_index = till_the_end(0, move_sq);
				GLclampf new_x1, new_x2, new_y1, new_y2;
				if (sq[move_sq].x1 <= sq[unite_index].x1)
					new_x1 = sq[move_sq].x1;
				else
					new_x1 = sq[unite_index].x1;
				if (sq[move_sq].x2 >= sq[unite_index].x2)
					new_x2 = sq[move_sq].x2;
				else
					new_x2 = sq[unite_index].x2;
				if (sq[move_sq].y1 >= sq[unite_index].y1)
					new_y1 = sq[move_sq].y1;
				else
					new_y1 = sq[unite_index].y1;
				if (sq[move_sq].y2 < sq[unite_index].y2)
					new_y2 = sq[move_sq].y2;
				else
					new_y2 = sq[unite_index].y2;
				if (unite_index == 9 || move_sq == 9)
					sq[9].cheak = false;
				if (move_sq < unite_index) {
					for (int i = unite_index; i < 9; ++i) {
						if (!sq[i].cheak)
							break;
						sq[i] = sq[i + 1];
						if (i == 8)
							sq[9].cheak = false;
					}
					for (int i = move_sq; i < 9; ++i) {
						if (!sq[i].cheak)
							break;
						sq[i] = sq[i + 1];
						if (i == 8)
							sq[9].cheak = false;
					}
				}
				else {
					for (int i = move_sq; i < 9; ++i) {
						if (!sq[i].cheak)
							break;
						sq[i] = sq[i + 1];
						if (i == 8)
							sq[9].cheak = false;
					}
					if(unite_index == 9)
						sq[9].cheak = false;
					for (int i = unite_index; i < 9; ++i) {
						if (!sq[i].cheak)
							break;
						sq[i] = sq[i + 1];
						if (i == 8) 
							sq[9].cheak = false;
					}
				}
				for (int i = 0; i < 10; ++i) {
					if (!sq[i].cheak) {
						sq[i].x1 = new_x1;
						sq[i].x2 = new_x2;
						sq[i].y1 = new_y1;
						sq[i].y2 = new_y2;
						sq[i].cheak = true;
						sq[i].r = uid(dre);
						sq[i].g = uid(dre);
						sq[i].b = uid(dre);
						move_sq = i;
						break;
					}
				}
			}
		}
	}
}
GLvoid Motion(int x, int y) {
	GLclampf pointX = static_cast<GLclampf>(x) / (width / 2) - 1, pointY = 1 - static_cast<GLclampf>(y) / (height / 2);
	if (left_button == true) {
		GLclampf moveSizeX = mouseX - pointX, moveSizeY = mouseY - pointY;
		sq[move_sq].x1 -= moveSizeX;
		sq[move_sq].y1 -= moveSizeY;
		sq[move_sq].x2 -= moveSizeX;
		sq[move_sq].y2 -= moveSizeY;
		glutPostRedisplay();
	}
	mouseX = pointX;
	mouseY = pointY;
}