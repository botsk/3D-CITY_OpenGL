
#include <iostream>
#include <vector>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "objects.cpp"
#include "events.cpp"
#include "plan.cpp"

using namespace std;

void* CURRENT_FONT;

GLint BOARD_HEIGHT 		= 800;
GLint BOARD_WIDTH 		= 1000;
GLint BOARD_DEPTH 		= 1000;
GLint BOARD_POS_X 		= 0;
GLint BOARD_POS_Y 		= 0;
GLint MODE				= 1;

static GLint count		= 0;

class plan;

void renderBoard();
void initObjects( int );
void renderObjects();
void reDisplay( int );
void displayInitBoard();

int main( int argc, char *argv[] )
{
	glutInit( &argc, argv );
	glutInitWindowPosition( BOARD_POS_X, BOARD_POS_Y );
	glutInitWindowSize( BOARD_WIDTH, BOARD_HEIGHT );
	glutCreateWindow( "3D City" );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
	glOrtho( 0, BOARD_WIDTH, 0, BOARD_HEIGHT, -BOARD_DEPTH*3, BOARD_DEPTH*3 );
	glutDisplayFunc( renderBoard );
	glutMotionFunc( mouseDragEvent );
	glutMouseFunc( mouseEvent );
	glutKeyboardFunc( keyEvent );
	glutSpecialFunc( specialKeyEvent );
	glEnable(GL_DEPTH_TEST);
	//glutTimerFunc( 10, reDisplay, 1 );

	initObjects(0);

	glutMainLoop();

	return 0;
}

void renderBoard()
{
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	glClearColor( 0.01, 0.01, 0.01, 1.0 );

	if( INIT==false )
	{
		displayInitBoard();
	}
	else
	{
		glPushMatrix();

		//gluPerspective( 19, (float)BOARD_WIDTH/(float)BOARD_HEIGHT, 10, BOARD_DEPTH*4 );
		glScalef( SCALE[0], SCALE[1], SCALE[2] );
		glTranslatef( POSITION[0], POSITION[1], POSITION[2] );
		gluLookAt( 0, 0, 200, VIEW[0], VIEW[1], VIEW[2], 0.0, 1.0, 0.0 );

		renderObjects();

		glPopMatrix();

		glBegin( GL_QUADS );

			glColor3f( 0, 32.0/255.0, 138.0/255.0 );
			glVertex3f( 0, 0, -BOARD_DEPTH );
			glVertex3f( BOARD_WIDTH*2, 0, -BOARD_DEPTH );

			glColor3f( 0, 0, 0 );
			glVertex3f( BOARD_WIDTH*2, BOARD_HEIGHT, -BOARD_DEPTH );
			glVertex3f( 0, BOARD_HEIGHT, -BOARD_DEPTH );

		glEnd();

		/*cout << "\n\n SCALE : " << SCALE[0] << " " << SCALE[1] << " " << SCALE[2];
		cout << "\n POSITION : " << POSITION[0] << " " << POSITION[1] << " " << POSITION[2];
		cout << "\n VIEW : " << VIEW[0] << " " << VIEW[1] << " " << VIEW[2];*/
	}

	glutSwapBuffers();
}

void reDisplay( int x )
{
	glutTimerFunc( 1, reDisplay, 1 );
}

void initObjects( int x )
{
	try
	{
		/*object::objectType = GL_LINES;
		object::count = 0;

		obj.clear();
		obj.push_back( object( plan::offset+500, 100, plan::offset, 200, 300, 400, false ) );
		obj.push_back( object( plan::offset+300, plan::offset, plan::offset, 205, 77, 200, false ) );

		obj.push_back( object( plan::offset, plan::offset, plan::offset, 113, 51, 100, false ) );
		obj.push_back( object( plan::offset+200, plan::offset, plan::offset, 113, 51, 100, false ) );
		obj.push_back( object( plan::offset+400, plan::offset, plan::offset, 113, 51, 100, false ) );*/
	}
	catch( exception err )
	{
		cout << "\n Error @InitObjects : " << err.what() ;
	}
}

void renderObjects()
{	
	/*
	renderBuilding1( plan::offset+0800, plan::offset+100, plan::offset+700, 200, 600, 400, false );
	renderBuilding2( plan::offset+0100, plan::offset+100, plan::offset+700, 400, 700, 400, false );
	renderBuilding3( plan::offset+1300, plan::offset+100, plan::offset+700, 500, 700, 400, false );
	renderBuilding4( plan::offset+1500, plan::offset+100, plan::offset+000, 400, 900, 400, false );
	*/

	int n=20;

	for( int i=0; i<n; i++ )
	{
		for( int j=0; j<n; j++ )
		{
			/*glPushMatrix();

			glTranslatef( 100+900*i, -1500, 100+900*j );
			glRotatef( (rand()%4)*90, 0, 1, 0 );
			glTranslatef( -100+900*i, 1500, -100+900*j );

			glPopMatrix();*/

			srand(i+j*n);

			renderBuilding( rand()%4+1, -3000+1100*i, -1500, -3000+1100*j, 500, 300+rand()%1000, 500 );
		}
	}
	renderLineQuad( -3200, -1600, -3200, 500*n+1100*n+400, 30, 500*n+1100*n+200 );
	//renderWindows( 100, 100, 100, 400, 900, 400, false );
}

void setFont(void* font)
{
    CURRENT_FONT = font;
}

void drawstring(float x, float y, float z, const char* string)
{
    const char* c;
    glRasterPos3f(x, y, z);

    for (c = string; *c != '\0'; c++)
    {
        glColor3f(0.0, 1.0, 0.0);
        glutBitmapCharacter( CURRENT_FONT, *c );
    }
}

void displayInitBoard()
{
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 50, -10, 50);
    glMatrixMode(GL_MODELVIEW);

    setFont( GLUT_BITMAP_HELVETICA_10 );
    glColor3f(1, 1, 0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(-5, 25, 0, "PROJECT PATNERS");
    drawstring(-5, 22, 0, "1");
    drawstring(-5, 20, 0, "2");

    glColor3f(1, 1, 0);
    drawstring(20, 25, 0, "PROJECT GUIDES");
    drawstring(20, 22, 0, "Lecturer,CSE");
    drawstring(20, 20, 0, "Lecturer,CSE");

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0, 1, 1);
    drawstring(13, 33, 0, "GRAPHICAL EDGE GAME");
    glColor3f(0, 1, 0);
    drawstring(13, 32, 0, "______________________");
    glColor3f(1, 0, 0);
    drawstring(5, 45, 0, "Colleges");
    glColor3f(1, 0, 1);
    drawstring(13, 40, 0, "CG MINI PROJECT");
    drawstring(13, 39, 0, "________________");
    glColor3f(0, 1, 1);
    drawstring(30, 5, 0, "ENTER N TO CONTINUE");
    glColor3f(0, 0, 1);

    glBegin(GL_LINE_LOOP); //writer head
    glVertex2i(-7, -7);
    glVertex2i(-7, 48);
    glVertex2i(48, 48);
    glVertex2i(48, -7);
    glEnd();

    glEnd();

    glFlush();
}