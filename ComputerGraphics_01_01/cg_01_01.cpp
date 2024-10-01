#include <iostream>
#include <random>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <gl\freeglut_ext.h>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_real_distribution<GLclampf> uid(0.0f, 1.0f);
GLclampf backGround_r = 0.0f, backGround_g = 0.0f, backGround_b = 1.0f, backGround_a = 1.0f;
int to_out_change_color = 0;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void change_random_color(int value);

void main(int argc, char** argv)	// ������ ����
{
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);					// �������� ��ġ ����
	glutInitWindowSize(800, 600);					// �������� ũ�� ����
	glutCreateWindow("project_01_01");				// ������ ���� (������ �̸�)
	
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						// glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);						// Ű���� �Է� �ݹ��Լ� ����
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()
{
	glClearColor(backGround_r, backGround_g, backGround_b, backGround_a);			// �������� �Ķ������� ����
	glClear(GL_COLOR_BUFFER_BIT);					// ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		backGround_r = 0.0f;
		backGround_g = 1.0f;
		backGround_b = 1.0f;
		break; //--- ������ û�ϻ����� ����
	case 'm':
		backGround_r = 1.0f;
		backGround_g = 0.0f;
		backGround_b = 1.0f;
		break; //--- ������ ��ȫ������ ����
	case 'y':
		backGround_r = 1.0f;
		backGround_g = 1.0f;
		backGround_b = 0.0f;
		break; //--- ������ ��������� ����
	case 'a':
		backGround_r = uid(dre);
		backGround_g = uid(dre);
		backGround_b = uid(dre);
		break;
	case 'w':
		backGround_r = 0.0f;
		backGround_g = 0.0f;
		backGround_b = 0.0f;
		break;
	case 'k':
		backGround_r = 1.0f;
		backGround_g = 1.0f;
		backGround_b = 1.0f;
		break;
	case 't':
		to_out_change_color = 1;
		glutTimerFunc(100, change_random_color, to_out_change_color); // (�и�����, �Լ���, �Լ��� ������ ��)
		break;
	case 's':
		to_out_change_color = 0;
		// glutLeaveMainLoop();
		break;
	case 'q':
		glutLeaveMainLoop();
		// glutDestroyWindow("project_01_01");->? �̰� ��°��
		break;
	}
	glutPostRedisplay();
}
void change_random_color(int value) 
{
	backGround_r = uid(dre);
	backGround_g = uid(dre);
	backGround_b = uid(dre);
	glutPostRedisplay();
	if (to_out_change_color)
		glutTimerFunc(100, change_random_color, to_out_change_color); // (�и�����, �Լ���, �Լ��� ������ ��)
}