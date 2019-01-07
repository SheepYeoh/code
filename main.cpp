#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <chrono>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"
float hand1 = 0;
float hand2 = 0;
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
int face = 1;

//blue RGB
float blue1R = 0;
float blue1G = 180 / 255.0;
float blue1B = 255 / 255.0;

float blue3R = 0;
float blue3G = 64 / 255.0;
float blue3B = 255 / 255.0;

//anger rgb
float anger1R = 255 / 255.0;
float anger1G = 0 / 255.0;
float anger1B = 0 / 255.0;

float anger3R = 178 / 255.0;
float anger3G = 34 / 255.0;
float anger3B = 34 / 255.0;

//angerFrequency
float freq1 = anger1R - blue1R;
float freq2 = anger1G - blue1G;
float freq3 = anger1B - blue1B;

float freq4 = anger3R - blue3R;
float freq5 = anger3G - blue3G;
float freq6 = anger3B - blue3B;

boolean angry = false;
boolean enableAnger = true;

double rotateCam = 0;
boolean x = false;

float angle = 0;
float lefthandangle = 0;
float righthandangle = 0;
float leftlegangle = 0;
float rightlegangle = 0;
float leftHandUp = 0;
float rightHandUp = 0;
boolean turn = true;
float speed = 0;
float degree = 15;
float claw = 0.5;
float oldMouseX;
float oldMouseY;
float mouseX;
float mouseY;

float lightX = 0, lightY = 8, lightZ = -8;
float a[] = { 1,0,0,0 };
float d[] = { 1,1,0,0 };
float p[] = { lightX,lightY,lightX };

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_LEFT) { //Camera for y-axis
			rotateCam -= 20;
		}
		else if (wParam == VK_RIGHT) { // Camera for y-axis
			rotateCam += 20;

		}
		else if (wParam == 0x4D) { //M for angry mode
			if (enableAnger) {
				enableAnger = false;
				angry = true;
			}
		}
		else if (wParam == VK_UP) { //Up for shoot missile
			if (!x) {
				x = true;
			}
		}
		else if (wParam == VK_SPACE) { //Space for reload
			if (x) {
				x = false;
			}

		}
		else if (wParam == 0x57) { //W for increase leg movement speed
			if (speed < 5) {
				if (leftlegangle == 0) {
					if (rightlegangle == 0) {
						speed += 0.05;
					}
				}
			}
		}
		else if (wParam == 0x53) { //S for decrease leg movement speed
			if (speed > 0.03) {
				if (leftlegangle == 0) {
					if (rightlegangle == 0) {
						speed -= 0.05;
					}
				}
			}
		}
		else if (wParam == 0x41) { //A for raise left arm
			if (lefthandangle >= -80) {
				lefthandangle -= 20;
			}
		}
		else if (wParam == 0x44) { //D for lower left arm
			if (lefthandangle < 0) {
				lefthandangle += 20;
			}
		}
		else if (wParam == 0x4A) { //J for raise right arm
			if (righthandangle >= -80) {
				righthandangle -= 20;
			}
		}
		else if (wParam == 0x4C) { //L for lower right arm
			if (righthandangle < 0) {
				righthandangle += 20;
			}
		}
		else if (wParam == 0x55) { //U for move left leg forward
			if (leftlegangle >= 0) {
				if (speed == 0) {
					leftlegangle -= 20;
				}
			}
		}
		else if (wParam == 0x49) { //I for move left leg backward
			if (leftlegangle < 20) {
				if (speed == 0) {
					leftlegangle += 20;
				}
			}
		}
		else if (wParam == 0x4F) { //O for move right leg forward
			if (rightlegangle >= 0) {
				if (speed == 0) {
					rightlegangle -= 20;
				}
			}
		}
		else if (wParam == 0x50) { //P for move right leg backward
			if (rightlegangle < 20) {
				if (speed == 0) {
					rightlegangle += 20;
				}
			}
		}
		else if (wParam == 0x56) { //V for left hand downward
			if (hand1 < 90) {
				hand1 += 5;
			}

		}
		else if (wParam == 0x43) { //C left hand upward
			if (hand1 > -15) {
				hand1 -= 5;
			}
		}
		else if (wParam == 0x58) { //X for right hand downward
			if (hand2 < 90) {
				hand2 += 5;
			}
		}
		else if (wParam == 0x5A) { //Z for right hand upward
			if (hand2 > -15) {
				hand2 -= 5;
			}
		}
		else if (wParam == 0x4E) { //B for left hand outward
			if (leftHandUp < 0) {
				leftHandUp += 5;
			}
		}
		else if (wParam == 0x42) { //N for left hand outward
			if (leftHandUp > -90) {
				leftHandUp -= 5;
			}
		}
		else if (wParam == 0x47) { //F for right hand outward
			if (rightHandUp < 90) {
				rightHandUp += 5;
			}
		}
		else if (wParam == 0x46) { //G for right hand outward
			if (rightHandUp > 0) {
				rightHandUp -= 5;
			}
		}
		else if (wParam == 0x45) { //E decrease claw length
			if (claw < 1.5) {
				claw += 0.1;
			}
		}
		else if (wParam == 0x51) { //Q for increase claw length
			claw -= 0.1;
			if (claw < 0.6) {
				claw = 0.5;
			}
		}
		else if (wParam == 0x52) { //R for reset position
			angle = 0;
			lefthandangle = 0;
			righthandangle = 0;
			leftlegangle = 0;
			rightlegangle = 0;
			speed = 0;
			face = 1;
			claw = 0.5;
			hand1 = 0;
			hand2 = 0;
			leftHandUp = 0;
			rightHandUp = 0;
		}
		else if (wParam == 0x31) { //1 normal 
			face = 1;
		}
		else if (wParam == 0x32) { //2 smile 
			face = 2;
		}
		else if (wParam == 0x33) { //3 sad 
			face = 3;
		}
		else if (wParam == 0x34) { //4 scare 
			face = 4;
		}
		else if (wParam == 0x31) { //1 normal 
			face = 1;
		}
		else if (wParam == 0x32) { //2 smile 
			face = 2;
		}
		else if (wParam == 0x33) { //3 sad 
			face = 3;
		}
		else if (wParam == 0x34) { //4 scare 
			face = 4;
		}
		else if (wParam == '5') { //5 Move light position up
			p[1] -= 1;
		}
		else if (wParam == '6') { //6 Move light position down
			p[1] += 1;
		}
		else if (wParam == '7') { //7 Move light position left
			p[0] -= 1;
		}
		else if (wParam == '8') { //8 Move light position right
			p[0] += 1;
		}
		else if (wParam == '9') { //9 Move light position near
			p[2] -= 1;
		}
		else if (wParam == '0') { //0 Move light position far
			p[2] += 1;
		}
		else if (wParam == 'H') {
			if (!glIsEnabled(GL_LIGHTING)) {
				glEnable(GL_LIGHTING);
			}
			else {
				glDisable(GL_LIGHTING);
			}
		}

		break;
	case WM_MOUSEMOVE:
		// save old mouse coordinates
		oldMouseX = mouseX;
		oldMouseY = mouseY;

		// get mouse coordinates from Windows
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);

		// these lines limit the camera's range

		if ((mouseX - oldMouseX) > 0)		// mouse moved to the right
			rotateCam += 5.0f;
		else if ((mouseX - oldMouseX) < 0)	// mouse moved to the left
			rotateCam -= 5.0f;

		return 0;
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

void nose(float topRadius, float btmRadius, float height) {
	float x1 = 0.0, y1 = 0.0, x2, y2;
	float angle;
	double radius = 0.2;

	GLUquadricObj *cylinder = NULL;
	cylinder = gluNewQuadric();

	gluQuadricDrawStyle(cylinder, GL_FILL);
	gluCylinder(cylinder, topRadius, btmRadius, height, 3, 10);

	gluDeleteQuadric(cylinder);
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
	float x1 = 0.0, y1 = 0.0, x2, y2;
	float angle;
	double radius = 0.2;
	GLUquadricObj *cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GL_FILL);
	var = gluNewQuadric();

	gluQuadricDrawStyle(var, GLU_FILL);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "weapon1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(cylinder, GL_TRUE);

	glPushMatrix();
	glTranslatef(leftWeaponTranslateX, leftWeaponTranslateY, leftWeaponTranslateZ);
	glRotatef(leftWeaponAngle, leftWeaponAngleX, leftWeaponAngleY, leftWeaponAngleZ);

	glPushMatrix();


	gluCylinder(cylinder, 0.3, 0.3, 2.3, 30, 10);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*0.3;
		y2 = y1 + cos(angle)*0.3;
		glVertex2f(x2, y2);
	}
	glEnd();

	glTranslatef(0.0f, 0.0f, 2.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*0.3;
		y2 = y1 + cos(angle)*0.3;
		glVertex2f(x2, y2);
	}
	glEnd();

	gluCylinder(cylinder, 0.5, 0.5, 0.7, 30, 10);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*0.5;
		y2 = y1 + cos(angle)*0.5;
		glVertex2f(x2, y2);
	}
	glEnd();

	glTranslatef(0.0f, 0.0f, 0.7);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*0.5;
		y2 = y1 + cos(angle)*0.5;
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

}


void rightWeapon() {
	float x1 = 0.0, y1 = 0.0, x2, y2;
	float angle;
	double radius = 0.2;
	GLUquadricObj *cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GL_FILL);
	var = gluNewQuadric();

	gluQuadricDrawStyle(var, GLU_FILL);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "weapon1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(cylinder, GL_TRUE);

	glPushMatrix();
	glTranslatef(rightWeaponTranslateX, rightWeaponTranslateY, rightWeaponTranslateZ);
	glRotatef(rightWeaponAngle, rightWeaponAngleX, rightWeaponAngleY, rightWeaponAngleZ);

	glPushMatrix();


	gluCylinder(cylinder, 0.3, 0.3, 2.3, 30, 10);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*0.3;
		y2 = y1 + cos(angle)*0.3;
		glVertex2f(x2, y2);
	}
	glEnd();

	glTranslatef(0.0f, 0.0f, 2.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*0.3;
		y2 = y1 + cos(angle)*0.3;
		glVertex2f(x2, y2);
	}
	glEnd();

	gluCylinder(cylinder, 0.5, 0.5, 0.7, 30, 10);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*0.5;
		y2 = y1 + cos(angle)*0.5;
		glVertex2f(x2, y2);
	}
	glEnd();

	glTranslatef(0.0f, 0.0f, 0.7);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle <= 360.0f; angle += 0.2f) {
		x2 = x1 + sin(angle)*0.5;
		y2 = y1 + cos(angle)*0.5;
		glVertex2f(x2, y2);
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

}

void body() {

	GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GL_FILL);

	glPushMatrix();
	glColor3f(blue1R, blue1G, blue1B);
	glTranslatef(-3, -3, -2);
	glRotatef(20.0f, 1, 0, 0);
	cube(3, 6, 6, "weapon1.bmp");
	glPopMatrix();

	var = gluNewQuadric();
	gluQuadricDrawStyle(var, GLU_FILL);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "brown1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(sphere, GL_TRUE);

	glPushMatrix();
	glTranslatef(0, -0.15, -1);
	glColor3f(1, 1, 1);
	gluSphere(sphere, 3.0, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void rightHand() {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "weapon1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	glPushMatrix();
	glTranslatef(3.4f, 0, 0);
	glColor3f(blue3R, blue3G, blue3B);
	gluSphere(var, 0.8, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5f, -0.8f, 0);
	glRotatef(rightHandUp, 0, 0, 1);
	glPushMatrix();
	glRotatef(90.0f, 1, 0, 0);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	gluCylinder(var, 0.3, 0.3, 0.5, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "weapon1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	glPushMatrix();
	glTranslatef(0, -0.4f, 0);
	glRotatef(hand2, 1, 0, 0);
	glPushMatrix();
	glColor3f(blue3R, blue3G, blue3B);
	gluCylinder(var, 0.3, 0.5, 2.0, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPushMatrix();
	glTranslatef(-0.35, -0.36, 1.9f);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	cube(0.75, 0.75, 0.75, "weapon1.bmp");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.25f, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, claw);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, claw);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.25, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, claw);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.35, 2.5);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.3);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void leftHand() {

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "weapon1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	glPushMatrix();
	glTranslatef(-3.4f, 0, 0);
	glColor3f(blue3R, blue3G, blue3B);
	gluSphere(var, 0.8, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5f, -0.8f, 0);
	glRotatef(leftHandUp, 0, 0, 1);
	glPushMatrix();
	glRotatef(90.0f, 1, 0, 0);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	gluCylinder(var, 0.3, 0.3, 0.5, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "weapon1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	glPushMatrix();
	glTranslatef(0, -0.4f, 0);
	glRotatef(hand1, 1, 0, 0);
	glPushMatrix();
	glColor3f(blue3R, blue3G, blue3B);
	gluCylinder(var, 0.3, 0.5, 2.0, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPushMatrix();
	glTranslatef(-0.35, -0.36, 1.9f);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	cube(0.75, 0.75, 0.75, "weapon1.bmp");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.25f, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, claw);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, claw);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.25, 2.6);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, claw);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.35, 2.5);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(211 / 255.0, 211 / 255.0, 211 / 255.0);
	cylinder(0.1, 0.001, 0.3);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void leftLeg() {
	if (turn) {
		angle += speed;
	}
	if (!turn) {
		angle -= speed;
	}
	if (angle > degree) {
		turn = false;
	}
	if (angle < -degree) {
		turn = true;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "weapon1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	glPushMatrix();
	glRotatef(angle, 1, 0, 0);
	glTranslatef(-1.5f, -4.0, 0);
	glColor3f(blue3R, blue3G, blue3B);
	gluSphere(var, 0.7, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 1, 0, 0);
	glTranslatef(-1.5f, -5.0, 0);
	glColor3f(blue1R, blue1G, blue1B);
	gluSphere(var, 0.8, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);


	glPushMatrix();
	glRotatef(angle, 1, 0, 0);
	glTranslatef(-2.5f, -6.0, -1);
	glColor3f(blue3R, blue3G, blue3B);
	cube(3.0, 1.0, 2.0, "weapon1.bmp");
	glPopMatrix();
}

void rightLeg() {
	if (turn) {
		angle += speed;
	}
	if (!turn) {
		angle -= speed;
	}
	if (angle > degree) {
		turn = false;
	}
	if (angle < -degree) {
		turn = true;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "weapon1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	gluQuadricTexture(var, GL_TRUE);

	glPushMatrix();
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(1.5f, -4.0, 0);
	glColor3f(blue3R, blue3G, blue3B);
	gluSphere(var, 0.7, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(1.5f, -5.0, 0);
	glColor3f(blue1R, blue1G, blue1B);
	gluSphere(var, 0.8, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPushMatrix();
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(0.5f, -6.0, -1);
	glColor3f(blue3R, blue3G, blue3B);
	cube(3.0, 1.0, 2.0, "weapon1.bmp");
	glPopMatrix();
}

void head() {
	glPushMatrix();
	glTranslatef(-1.0f, 1.5, 1.3);

	glColor3f(blue3R, blue3G, blue3B);
	cube(2.0, 2.0, 2.0, "weapon1.bmp");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 3.5, 2);
	glRotatef(-90.0f, 1, 0, 0);

	glColor3f(blue1R, blue1G, blue1B);
	pyramid(1.0, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 3.5, 2);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(blue1R, blue1G, blue1B);
	pyramid(1.0, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 2.8, 2.9);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(0, 0, 0);
	sphere(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 2.8, 2.9);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(0, 0, 0);
	sphere(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 2.8, 3.225);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(1, 1, 1);
	sphere(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 2.8, 3.225);
	glRotatef(-90.0f, 1, 0, 0);
	glColor3f(1, 1, 1);
	sphere(0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2.3, 3.25);
	glColor3f(160 / 255.0, 82 / 255.0, 45 / 255.0);
	nose(0.4, 0, 0.2);
	glPopMatrix();

	if (face == 1) {
		glPushMatrix();
		glTranslatef(0, 1.9, 3.35);
		glColor3f(1, 1, 1);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2f(0.5, 0);
		glVertex2f(-0.5, 0);
		glEnd();
		glPopMatrix();
	}
	else if (face == 2) {
		glPushMatrix();
		glTranslatef(0, 2.5, 3.35);
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		double x = 2.047;
		double y = 3.5;
		double r = 0.8;
		double start_angle = 4;
		double end_angle = 5.4;
		double max_angle = 2 * (22 / 7.0);
		double angle_increment = (22 / 7.0) / 1000;
		for (double theta = start_angle; theta < end_angle; theta += angle_increment)
		{
			x = r * cos(theta);
			y = r * sin(theta);
			glColor3f(1, 1, 1);
			glVertex2f(x, y);
		}
		glEnd();
		glPopMatrix();
	}
	else if (face == 3) {
		glPushMatrix();
		glTranslatef(0, 1.1, 3.35);
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		double x = 2.047;
		double y = 3.5;
		double r = 0.8;
		double start_angle = 7.2;
		double end_angle = 8.6;
		double max_angle = 2 * (22 / 7.0);
		double angle_increment = (22 / 7.0) / 1000;
		for (double theta = start_angle; theta < end_angle; theta += angle_increment)
		{
			x = r * cos(theta);
			y = r * sin(theta);
			glColor3f(1, 1, 1);
			glVertex2f(x, y);
		}
		glEnd();
		glPopMatrix();
	}
	else if (face == 4) {
		glPushMatrix();
		glTranslatef(0, 2, 3.35);
		glLineWidth(2);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-0.5, 0);
		glVertex2f(-0.4, -0.2);
		glVertex2f(-0.3, 0);
		glVertex2f(-0.2, -0.2);
		glVertex2f(-0.1, 0);
		glVertex2f(0, -0.2);
		glVertex2f(0.1, 0);
		glVertex2f(0.2, -0.2);
		glVertex2f(0.3, 0);
		glVertex2f(0.4, -0.2);
		glVertex2f(0.5, 0);
		glEnd();
		glPopMatrix();
	}
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
	glColor3f(1, 1, 1);
	glRotatef(45, 1, 0, 0);
	glTranslatef(-1.5, -2.2, -4.2);
	gluCylinder(var, 0.001, 0.2, 0.7, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

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
	glColor3f(1, 1, 1);
	glRotatef(-135, 1, 0, 0);
	glTranslatef(-1.5, 2.2, 1.5);
	gluCylinder(var, 0.2, 0.2, 2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glRotatef(-135, 1, 0, 0);
	glTranslatef(-1.5, 2.2, 1.5);
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
	glColor3f(1, 1, 1);
	glRotatef(45, 1, 0, 0);
	glTranslatef(1.5, -2.2, -4.2);
	gluCylinder(var, 0.001, 0.2, 0.7, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

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
	glColor3f(1, 1, 1);
	glRotatef(-135, 1, 0, 0);
	glTranslatef(1.5, 2.2, 1.5);
	gluCylinder(var, 0.2, 0.2, 2, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glRotatef(-135, 1, 0, 0);
	glTranslatef(1.5, 2.2, 1.5);
	gluSphere(var, 0.2, 20, 20);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPopMatrix();
}

void angryMode() {
	if (!angry) {
		if (blue1R >= 0 / 255.0) {
			blue1R -= freq1 / 1000;
		}
		if (blue1G <= 180 / 255.0) {
			blue1G -= freq2 / 1000;
		}
		if (blue1B <= 255 / 255.0) {
			blue1B -= freq3 / 1000;
		}

		if (blue3R >= 0 / 255.0) {
			blue3R -= freq4 / 1000;
		}
		if (blue3G <= 64 / 255.0) {
			blue3G -= freq5 / 1000;
		}
		if (blue3B <= 255 / 255.0) {
			blue3B -= freq6 / 1000;
		}

		if (blue1R <= 0 / 255.0&& blue1G >= 180 / 255.0 && blue1B <= 255 / 255.0 &&
			blue3R <= 0 / 255.0&& blue3G >= 64 / 255.0 && blue3B <= 255 / 255.0) {
			enableAnger = true;
		}
	}
	else {

		if (blue1R <= anger1R) {
			blue1R += freq1 / 20;
		}
		if (blue1G >= anger1G) {
			blue1G += freq2 / 20;
		}
		if (blue1B >= anger1B) {
			blue1B += freq3 / 20;
		}

		if (blue3R <= anger3R) {
			blue3R += freq4 / 20;
		}
		if (blue3G >= anger3G) {
			blue3G += freq5 / 20;
		}
		if (blue3B >= anger3B) {
			blue3B += freq6 / 20;
		}

		if (blue1R >= anger1R && blue1G <= anger1G && blue1B <= anger1B &&
			blue3R >= anger3R && blue3G <= anger3G && blue3B <= anger3B) {
			angry = false;
		}
	}
}

void floor() {
	glPushMatrix();
	glTranslatef(-23, -6, -23);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear background colour (default : black)
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "ocean.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
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
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0, 0, 50);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(50, 0, 50);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(50, 0, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	glPopMatrix();
}

void light() {
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	glLightfv(GL_LIGHT0, GL_POSITION, p);

	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_AMBIENT, a);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.196078f, 0.6f, 0.8f, 1.0f);
	glPushMatrix();
	angryMode();

	glRotatef(10, 1, 0, 0);

	glRotatef(rotateCam, 0, 1, 0);
	glPushMatrix();

	light();
	floor();
	leftWeapon();
	rightWeapon();
	head();
	body();

	glPushMatrix();
	glRotatef(lefthandangle, 1, 0, 0);
	leftHand();
	glPopMatrix();

	glPushMatrix();
	glRotatef(righthandangle, 1, 0, 0);
	rightHand();
	glPopMatrix();

	glPushMatrix();
	glRotatef(leftlegangle, 1, 0, 0);
	leftLeg();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rightlegangle, 1, 0, 0);
	rightLeg();
	glPopMatrix();

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
	glOrtho(-7.0f, 7.0f, -7.0f, 7.0f, -25.0f, 25.0f);
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
