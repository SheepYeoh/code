#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <chrono>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;
GLUquadricObj *var = NULL;
GLuint* textures = new GLuint[4];
BITMAP image[4];
float shoot = -0.1;
//leftWeapon
float leftWeaponAngle = -40.0f;
float leftWeaponAngleX = 1.0f;
float leftWeaponAngleY = 0.0f;
float leftWeaponAngleZ = 0.0f;
float leftWeaponTranslateX = -1.5f;
float leftWeaponTranslateY = 2.5f;
float leftWeaponTranslateZ = -0.5f;

//rightWeapon
float rightWeaponAngle = -40.0f;
float rightWeaponAngleX = 1.0f;
float rightWeaponAngleY = 0.0f;
float rightWeaponAngleZ = 0.0f;
float rightWeaponTranslateX = 1.5f;
float rightWeaponTranslateY = 2.5f;
float rightWeaponTranslateZ = -0.5f;

double rotateCam = 0;
boolean x = false;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			rotateCam -= 20;
		}
		else if (wParam == VK_RIGHT) {
			rotateCam += 20;

		}

		else if (wParam == VK_DOWN) {

		}
		else if (wParam == VK_UP) {
			if (!x) {
				x = true;
			}
		}
		else if (wParam == 0x52) {
		}

		else if (wParam == VK_SPACE) {
			if (x) {
				x = false;
			}

		}
		else if (wParam == 0x58) {

		}
		else if (wParam == 0x59) {

		}
		else if (wParam == 0x5A) {

		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void cylinder(float topRadius, float btmRadius, float height) {
	float x1 = 0.0, y1 = 0.0, x2, y2;
	float angle;
	double radius = 0.2;

	GLUquadricObj *cylinder = NULL;
	cylinder = gluNewQuadric();

	gluQuadricDrawStyle(cylinder, GL_FILL);
	gluCylinder(cylinder, topRadius, btmRadius, height, 30, 10);

	gluDeleteQuadric(cylinder);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*topRadius;
		y2 = y1 + cos(angle)*topRadius;
		glVertex2f(x2, y2);
	}
	glEnd();

	glTranslatef(0.0f, 0.0f, height);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*btmRadius;
		y2 = y1 + cos(angle)*btmRadius;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void sphere(float radius) {

	GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GL_FILL);
	gluSphere(sphere, radius, 30, 30);

	gluDeleteQuadric(sphere);
}

void pyramid(float height, float width, float length) {
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, width, 0.0f);
	glVertex3f(length, width, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	//face2
	glBegin(GL_TRIANGLES);
	glVertex3f((length / 2), (width / 2), height);
	glVertex3f(0.0f, width, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	//face3
	glBegin(GL_TRIANGLES);
	glVertex3f((length / 2), (width / 2), height);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);
	glEnd();
	//face4
	glBegin(GL_TRIANGLES);
	glVertex3f((length / 2), (width / 2), height);
	glVertex3f(length, 0.0f, 0.0f);
	glVertex3f(length, width, 0.0f);
	glEnd();
	//face5
	glBegin(GL_TRIANGLES);
	glVertex3f((length / 2), (width / 2), height);
	glVertex3f(length, width, 0.0f);
	glVertex3f(0.0f, width, 0.0f);
	glEnd();

}

void cube(float maxHeight, float maxWidth, float maxLength) {
	glBegin(GL_QUADS);
	//face1
	glVertex3f(0.0f, 0.0f, maxHeight);
	glVertex3f(maxLength, 0.0f, maxHeight);
	glVertex3f(maxLength, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	//face2
	glVertex3f(0.0f, maxWidth, maxHeight);
	glVertex3f(0.0f, 0.0f, maxHeight);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, maxWidth, 0.0f);

	//face3
	glVertex3f(0.0f, maxWidth, 0.0f);
	glVertex3f(maxLength, maxWidth, 0.0f);
	glVertex3f(maxLength, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	//face4
	glVertex3f(0.0f, maxWidth, maxHeight);
	glVertex3f(maxLength, maxWidth, maxHeight);
	glVertex3f(maxLength, 0.0f, maxHeight);
	glVertex3f(0.0f, 0.0f, maxHeight);

	//face5
	glVertex3f(0.0f, maxWidth, maxHeight);
	glVertex3f(maxLength, maxWidth, maxHeight);
	glVertex3f(maxLength, maxWidth, 0.0f);
	glVertex3f(0.0f, maxWidth, 0.0f);

	//face6
	glVertex3f(maxLength, maxWidth, maxHeight);
	glVertex3f(maxLength, 0.0f, maxHeight);
	glVertex3f(maxLength, 0.0f, 0.0f);
	glVertex3f(maxLength, maxWidth, 0.0f);
	glEnd();

}

void cube(float maxHeight, float maxWidth, float maxLength, const char bitmap[]) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), bitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_QUADS);
	//face1
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, maxHeight);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(maxLength, 0.0f, maxHeight);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(maxLength, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	glBegin(GL_QUADS);
	//face2
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, maxWidth, maxHeight);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, maxHeight);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, maxWidth, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	//face3
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, maxWidth, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(maxLength, maxWidth, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(maxLength, 0.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	//face4*
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, maxWidth, maxHeight);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(maxLength, maxWidth, maxHeight);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(maxLength, 0.0f, maxHeight);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, maxHeight);
	glEnd();
	glBegin(GL_QUADS);
	//face5*
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, maxWidth, maxHeight);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(maxLength, maxWidth, maxHeight);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(maxLength, maxWidth, 0.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, maxWidth, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	//face6
	glTexCoord2f(0.0, 0.0);
	glVertex3f(maxLength, maxWidth, maxHeight);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(maxLength, 0.0f, maxHeight);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(maxLength, 0.0f, 0.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(maxLength, maxWidth, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}


void leftWeapon() {
	glPushMatrix();

	glTranslatef(leftWeaponTranslateX, leftWeaponTranslateY, leftWeaponTranslateZ);
	glRotatef(leftWeaponAngle, leftWeaponAngleX, leftWeaponAngleY, leftWeaponAngleZ);

	glPushMatrix();

	glColor3f(192 / 255.0, 192 / 255.0, 192 / 255.0);
	cylinder(0.3, 0.3, 1.8);

	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.5, 0.5, 0.7);
	glPopMatrix();


	glPopMatrix();
}


void rightWeapon() {
	glPushMatrix();

	glTranslatef(rightWeaponTranslateX, rightWeaponTranslateY, rightWeaponTranslateZ);
	glRotatef(rightWeaponAngle, rightWeaponAngleX, rightWeaponAngleY, rightWeaponAngleZ);

	glPushMatrix();

	glColor3f(192 / 255.0, 192 / 255.0, 192 / 255.0);
	cylinder(0.3, 0.3, 1.8);

	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.5, 0.5, 0.7);
	glPopMatrix();

	glPopMatrix();
}

void body() {
	glPushMatrix();
	glTranslatef(-3, -3, -2);
	glRotatef(20.0f, 1, 0, 0);
	glColor3f(0, 180 / 255.0, 45 / 1);
	cube(3, 6, 6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -1);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	sphere(3.0);
	glPopMatrix();
}

void rightHand() {
	glPushMatrix();
	glTranslatef(3.4f, 0, 0);
	glColor3f(0, 64 / 255.0, 45 / 1);
	sphere(0.8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5f, -0.8f, 0);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	glRotatef(90.0f, 1, 0, 0);
	cylinder(0.3, 0.3, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5f, -1.3f, 0);
	glColor3f(0, 64 / 255.0, 45 / 1);
	cylinder(0.3, 0.5, 2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.15f, -1.7f, 1.9f);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	cube(0.75, 0.75, 0.75);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5f, -1.6f, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5f, -1.35f, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5f, -1.1f, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5f, -1.0f, 2.3);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.3);
	glPopMatrix();
}

void leftHand() {
	glPushMatrix();
	glTranslatef(-3.4f, 0, 0);
	glColor3f(0, 64 / 255.0, 45 / 1);
	sphere(0.8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5f, -0.8f, 0);
	glRotatef(90.0f, 1, 0, 0);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	cylinder(0.3, 0.3, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5f, -1.3f, 0);
	glColor3f(0, 64 / 255.0, 45 / 1);
	cylinder(0.3, 0.5, 2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.9f, -1.7f, 1.9f);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	cube(0.75, 0.75, 0.75);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5f, -1.6f, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5f, -1.35f, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5f, -1.1f, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5f, -1.0f, 2.3);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.3);
	glPopMatrix();
}

void leftLeg() {
	glPushMatrix();
	glTranslatef(-1.5f, -4.0, 0);

	glColor3f(0, 64 / 255.0, 45 / 1);
	sphere(0.7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -5.0, 0);

	glColor3f(0, 180 / 255.0, 45 / 1);
	sphere(0.8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5f, -6.0, -1);
	glColor3f(0, 270 / 255.0, 45 / 1);
	cube(4.0, 1.0, 2.0);
	glPopMatrix();
}

void rightLeg() {
	glPushMatrix();
	glTranslatef(1.5f, -4.0, 0);
	glColor3f(0, 64 / 255.0, 45 / 1);
	sphere(0.7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5f, -5.0, 0);
	glColor3f(0, 180 / 255.0, 45 / 1);
	sphere(0.8);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, -6.0, -1);
	glColor3f(0, 270 / 255.0, 45 / 1);
	cube(4.0, 1.0, 2.0);
	glPopMatrix();
}

void head() {
	glPushMatrix();
	glTranslatef(-1.0f, 1.5, 1.3);

	glColor3f(0, 64 / 255.0, 45 / 1);
	cube(2.0, 2.0, 2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 3.5, 2);
	glRotatef(-90.0f, 1, 0, 0);

	glColor3f(0, 150 / 255.0, 45 / 1);
	pyramid(1.0, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 3.5, 2);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(0, 150 / 255.0, 45 / 1);
	pyramid(1.0, 0.5, 0.5);
	glPopMatrix();
}

void leftMissile() {

	glPushMatrix();

	glRotatef(-45.0f, 1, 0, 0);
	var = gluNewQuadric();
	gluQuadricDrawStyle(var, GLU_FILL);

	//texture missile cone
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "grey.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	//missile cone
	glPushMatrix();
	glRotatef(45, 1, 0, 0);
	glTranslatef(-1.5, -2.2, -0.7);
	gluCylinder(var, 0.001, 0.2, 0.7, 20, 20);
	glPopMatrix();


	//texture missile cylinder
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	//missile cylinder
	glPushMatrix();
	glRotatef(-135, 1, 0, 0);
	glTranslatef(-1.5, 2.2, -2);
	gluCylinder(var, 0.2, 0.2, 2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-135, 1, 0, 0);
	glTranslatef(-1.5, 2.2, -2);
	gluSphere(var, 0.2, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPopMatrix();
}

void rightMissile() {

	glPushMatrix();

	glRotatef(-45.0f, 1, 0, 0);
	var = gluNewQuadric();
	gluQuadricDrawStyle(var, GLU_FILL);

	//texture missile cone
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "grey.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	//missile cone
	glPushMatrix();
	glRotatef(45, 1, 0, 0);
	glTranslatef(1.5, -2.2, -0.7);
	gluCylinder(var, 0.001, 0.2, 0.7, 20, 20);
	glPopMatrix();


	//texture missile cylinder
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	//missile cylinder
	glPushMatrix();
	glRotatef(-135, 1, 0, 0);
	glTranslatef(1.5, 2.2, -2);
	gluCylinder(var, 0.2, 0.2, 2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-135, 1, 0, 0);
	glTranslatef(1.5, 2.2, -2);
	gluSphere(var, 0.2, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPopMatrix();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glRotatef(rotateCam, 0, 1, 0);
	glPushMatrix();
	leftWeapon();
	rightWeapon();
	head();
	body();
	leftHand();
	rightHand();
	leftLeg();
	rightLeg();
	glPopMatrix();

	glPushMatrix();
	if (x) {
		glRotatef(140.0f, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, shoot);
		leftMissile();
		rightMissile();
		shoot -= 0.2;
	}
	else {
		glRotatef(140.0f, 1, 0, 0);
		leftMissile();
		rightMissile();
		glLoadIdentity();
		shoot = -0.1;
	}
	glPopMatrix();

	glPopMatrix();

}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-7.0f, 7.0f, -7.0f, 5.0f, -5.0f, 5.0f);
	glMatrixMode(GL_MODELVIEW);
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
