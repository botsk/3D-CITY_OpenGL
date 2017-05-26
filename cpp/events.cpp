
#include <iostream>

#include <GL/glut.h>
#include <GL/glu.h>

#include <math.h>

GLint prevX=-1, prevY=-1;

GLint VIEW[3] = { -66, -33, 0 };
GLint CAMERA[3] = { 0, 0, 0 };
GLint POSITION[3] = { 888, 3192, 0 };

GLfloat SCALE[3] = { 0.2, 0.2, 0.2 };

bool INIT 	= true;

void mouseDragEvent( GLint, GLint );
void mouseEvent( int btn , int state, int x, int y );
void keyEvent( unsigned char key ,int x, int y );
void specialKeyEvent( unsigned char key ,int x, int y );

void mouseDragEvent( GLint x, GLint y )
{
	if( prevX == -1 || prevY == -1 )
	{
		prevX = x;
		prevY = y;

		return;
	}
	
	if( y!=prevY )
	{
		/*glTranslatef( 0, 500, -400 );
		//glRotatef( -(y-prevY)/fabs(y-prevY), 1, 0, 0 );
		glRotatef( 10, 1, 0, 0 );
		glTranslatef( 0, -500, 400 );*/
	}
	
	if( x!=prevX )
	{
		glTranslatef( VIEW[0], VIEW[1], VIEW[2] );
		glRotatef( -(x-prevX)/fabs(x-prevX)*3, 0, 1, 0 );
		glTranslatef( -VIEW[0], -VIEW[1], -VIEW[2] );
	}

	glutPostRedisplay();
	//glutSwapBuffers();

	prevX = x;
	prevY = y;
}

void mouseEvent( int btn , int state, int x, int y )
{
	if( btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
		;//glRotatef(1,1,0.1,0.1);

	//glutPostRedisplay();
}

void keyEvent( unsigned char key ,int x, int y )
{
	int offset=3, max_angle=360;

	switch( key )
	{
		case 'a':

			VIEW[0] = (VIEW[0]-offset);
			break;

		case 'd':

			VIEW[0] = (VIEW[0]+offset);
			break;

		case 's':

			VIEW[1] = (VIEW[1]-offset);
			break;

		case 'w':

			VIEW[1] = (VIEW[1]+offset);
			break;

		case 'z':

			VIEW[2] = (VIEW[2]+offset);
			break;

		case 'r':

			VIEW[0] = 0;
			VIEW[1] = 0;
			VIEW[2] = 200;

		case 'o':

			SCALE[0] -= 0.03;
			SCALE[1] -= 0.03;
			SCALE[2] -= 0.03;

			break;

		case 'i':

			SCALE[0] += 0.03;
			SCALE[1] += 0.03;
			SCALE[2] += 0.03;

			break;

		case 'n':
		case 'N':

			INIT = true;
			break;

		default :

			break;
	}

	glutPostRedisplay();
}

void specialKeyEvent( int key ,int x, int y )
{
	int offset=12, max_angle=360;

	switch( key )
	{
		case GLUT_KEY_LEFT:
			
			POSITION[0] += offset;
			break;

		case GLUT_KEY_RIGHT:
			
			POSITION[0] -= offset;
			break;

		case GLUT_KEY_DOWN:

			POSITION[1] -= offset;
			break; 

		case GLUT_KEY_UP:

			POSITION[1] += offset;
			break; 
	}

	glutPostRedisplay();
}