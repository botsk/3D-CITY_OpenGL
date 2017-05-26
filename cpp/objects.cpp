
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define BOTH -10

using namespace std;

void renderCuboid( int, int, int, int, int, int, int type=GL_QUADS, int lineWidth=1 );
void renderSides( GLint x, GLint y, GLint z, GLint l, GLint h, GLint b, bool randomize=false, GLint type=GL_QUADS );
void renderYSide( GLint x, GLint y, GLint z, GLint l, GLint b, GLint type=GL_QUADS );
void renderWindows( int x, int y, int z, int length, int height, int depth, int type=GL_QUADS, int lineWidth=1 );

void renderBuilding1( int x, int y, int z, int length, int height, int breadth, int type=GL_QUADS, int lineWidth=1 );
void renderBuilding2( int x, int y, int z, int length, int height, int breadth, int type=GL_QUADS, int lineWidth=1 );
void renderBuilding3( int x, int y, int z, int length, int height, int breadth, int type=GL_QUADS, int lineWidth=1 );
void renderBuilding4( int x, int y, int z, int length, int height, int breadth, int type=GL_QUADS, int lineWidth=1 );
void renderBuilding( int, int x, int y, int z, int length, int height, int breadth );

void renderLineQuad( int x, int y, int z, int length, int height, int breadth );

void renderCuboid( int x, int y, int z, int length, int height, int depth, int type, int lineWidth )
{
	try
	{
		if( type==GL_QUADS )
		{
			length-=1;
			height-=0;
			depth-=1;
			glColor3f( 0, 0, 0 );
		}
		else			
			glColor3f( 1, 1, 1 );

		for( int i=0; i<6; i++ )
		{
			glLineWidth(2);

			glBegin( type );

				glVertex3i( x+length*( i==5 ), y+height*( i==2 ), z+depth*( i==3 ) );
				glVertex3i( x+length*( i!=4 ), y+height*( i==2 ), z+depth*( i>2 ) );
				glVertex3i( x+length*( i!=4 ), y+height*( i!=1 ), z+depth*( i>0 ) );
				glVertex3i( x+length*( i==5 ), y+height*( i!=1 ), z+depth*( i>0&&i<4 ) );
				glVertex3i( x+length*( i==5 ), y+height*( i==2 ), z+depth*( i==3 ) );

			glEnd();				
		}

	}
	catch( exception err )
	{
		cout << "\n Error @RenderCube : " << err.what() ;
	}
}

void renderWindows( int x, int y, int z, int length, int height, int depth, int type, int lineWidth )
{

	GLint windowSize_x 	= 40;
	GLint windowSize_y 	= 30;
	GLint offset_x 		= 30;
	GLint offset_y 		= 40;
	GLint count 		= 0;

	srand( 0 );
	int k=0;

	for( int k=0; k<4; k++ )
	{   		
   		glColor3f( 1, 1, 1 );			

    	for( int i=0; i<( (k==0||k==3)*length+(k==1||k==2)*depth )/( windowSize_x+offset_x ); i++ )
    	    for( int j=0; j<height/( windowSize_y+offset_y ); j++ )
    	    {
    	    	/*glBegin( GL_QUADS );

    	    		glVertex3f( x+offset_x*(i+1)+windowSize_x*i, y+offset_y*(j+1)+windowSize_y*j, z );
    	    		glVertex3f( x+( offset_x+windowSize_x )*(i+1), y+offset_y*(j+1)+windowSize_y*j, z );
    	    		glVertex3f( x+( offset_x+windowSize_x )*(i+1), y+( offset_y+windowSize_y )*(j+1), z );
    	    		glVertex3f( x+offset_x*(i+1)+windowSize_x*i, y+( offset_y+windowSize_y )*(j+1), z );

    	    	glEnd();*/

    	   	    renderSides( x+( k==1 )*length+( k==0||k==3 )*( offset_x*(i+1)+windowSize_x*i ),
    	   	    	y+offset_y*(j+1)+windowSize_y*j,
    	   	    	z+( k==0 )*length+( k==1||k==2 )*( offset_x*(i+1)+windowSize_x*i ),
    	   	    	( k==0||k==3 )*windowSize_x, windowSize_y,
    	   	    	( k==1||k==2 )*windowSize_x,
    	   	    	true, type );
    	    }
	}
}

void renderSides( GLint x, GLint y, GLint z, GLint l, GLint h, GLint b, bool randomize, GLint type )
{
	GLfloat color;

	color = rand()%11;
	color = ( color>5 ? 0 : (rand()%11)/10.0 );
	color = ( color>0.4&&color<0.7 ? 1:color );

	if( randomize==true )
		glColor3f(  color, color, color );

	glBegin( type );

		if( color != 0.0 )
			glColor3f( color, color, color );
		glVertex3f( x, y, z );
		
		if( color != 0.0 )
			glColor3f( (int)( (color+0.1)*10 )%20, (int)( (color+0.1)*10 )%20, (int)( (color+0.1)*10 )%20 );
		glVertex3f( x+l, y, z+b );

		if( color != 0.0 )
			glColor3f( color+0.1, color+0.1, color+0.1 );
		glVertex3f( x+l, y+h, z+b );
		glVertex3f( x, y+h, z );

	glEnd();
}

void renderYSide( GLint x, GLint y, GLint z, GLint l, GLint b, GLint type )
{
	glLineWidth(1);
	glBegin( type );

		glVertex3f( x, y, z );
		glVertex3f( x+l, y, z );
		glVertex3f( x+l, y, z+b );
		glVertex3f( x, y, z+b );

	glEnd();
}

void renderBuilding1( int x, int y, int z, int length, int height, int breadth, int type, int lineWidth )
{
	glColor3f( 1, 1, 1 );

	renderLineQuad( x, y, z, length, height, breadth );
	renderWindows( x, y, z, length, height, breadth );

	renderLineQuad( x, y, z+breadth, length*0.5, height*0.9, 60 );
	renderLineQuad( x-2, y+height*0.9, z+breadth-2, length*0.5+4, height*0.04, 64 );

	renderLineQuad( x+length*0.5, y, z+breadth, length*0.3, height*0.8, 60 );
	renderLineQuad( x+length*0.5-2, y+height*0.8, z+breadth-2, length*0.3+4, height*0.04, 64 );	
	renderLineQuad( x+length*0.8, y, z-30, length*0.4, height*0.3, breadth+60 );

	renderLineQuad( x+length*0.8-2, y+height*0.3, z-30, length*0.4+4, height*0.05, breadth+64 );
	renderLineQuad( x-5, y+height, z, length+10, 10, breadth );

	renderLineQuad( x-60, y-10, z-60, length+120, 10, breadth+120 );
	renderLineQuad( x, y+height+10, z, length, 20, breadth );

	renderLineQuad( x+5, y+height+30, z, length-10, 30, breadth );
}

void renderBuilding2( int x, int y, int z, int length, int height, int breadth, int type, int lineWidth )
{
	glColor3f( 1, 1, 1 );

	renderLineQuad( x, y, z, length, height, breadth );
	renderWindows( x, y, z, length, height, breadth );

	renderLineQuad( x-2, y+height, z-2, length+4, height*0.09, breadth+4 );
	renderLineQuad( x+8, y+height*1.09, z+8, length-16, height*0.06, breadth-16 );
	renderLineQuad( x+18, y+height*1.15, z+18, length-36, height*0.03, breadth-36 );
	renderLineQuad( x+25, y+height*1.18, z+25, length-50, height*0.03, breadth-50 );
	renderLineQuad( x-30+length*0.9, y+height*1.21, z+breadth*0.9-30, length*0.1, height*0.03, breadth*0.1 );
	renderLineQuad( x+length*0.1, y+height*1.21, z+breadth*0.1, length*0.05, height*0.06, breadth*0.05 );
	
	renderLineQuad( x-length*0.2, y, z, length*0.2, height*0.9, breadth*0.8 );
	renderWindows( x-length*0.2, y, z, length*0.2, height*0.9, breadth*0.8 );

	renderLineQuad( x-length*0.2-2, y+height*0.9, z-2, length*0.2+4, height*0.09, breadth*0.8+4 );

	renderLineQuad( x-length*0.5, y, z, length*0.5, height*0.5, breadth*0.9 );
	renderLineQuad( x-length*0.5-2, y+height*0.5, z-2, length*0.5+4, height*0.09, breadth*0.9+4 );

	renderLineQuad( x+length*0.1, y, z+breadth*0.1, length*1.1, height*0.6, breadth*0.9 );
	renderLineQuad( x+length*0.1-2, y+height*0.6, z+breadth*0.1-2, length*1.1+4, height*0.09, breadth*0.9+4 );

	renderLineQuad( x-length*0.5-60, y-10, z-60, length*1.6+120, 20, breadth*1.1+120 );
}


void renderBuilding3( int x, int y, int z, int length, int height, int breadth, int type, int lineWidth )
{
	renderLineQuad( x, y, z, length, height, breadth );
	renderWindows( x, y, z, length, height, breadth );

	renderLineQuad( x-2, y+height, z-2, length-4, height*0.09, breadth-4 );
	renderLineQuad( x+12, y+height*1.09, z+12, length-28, height*0.06, breadth-28 );
	renderLineQuad( x+24, y+height*1.15, z+24, length-50, height*0.04, breadth-50 ) ;

	renderLineQuad( x+length*0.1, y, z+breadth*0.1, length, height*0.9, breadth );
	renderLineQuad( x+length*0.1-2, y+height*0.9, z+breadth*0.1-2, length+4, height*0.02, breadth+4 );

	renderLineQuad( x-length*0.1, y, z, length*0.8, height*0.6, breadth );
	renderLineQuad( x-length*0.1-2, y+height*0.6, z-2, length*0.8+4, height*0.02, breadth+4 );

	renderLineQuad( x+length*0.7, y, z-breadth*0.1, length*0.6, height*0.5, breadth*1.2 );
	renderLineQuad( x+length*0.7-2, y+height*0.5, z-breadth*0.1-2, length*0.6+4, height*0.02, breadth*1.2+4 );
	
	renderLineQuad( x-length*0.1-60, y-10, z-breadth*0.1-60, length*1.4+120, 20, breadth*1.2+120 );
}

void renderBuilding4( int x, int y, int z, int length, int height, int breadth, int type, int lineWidth )
{
	glColor3f( 1.0, 1.0, 1.0 );

	renderLineQuad( x, y, z, length, height, breadth );
	renderWindows( x, y, z, length, height, breadth );

	renderLineQuad( x-2, y+height, z-2, length+4, height*0.09, breadth+4 );
	renderLineQuad( x+12, y+height*1.09, z+12, length-24, height*0.07, breadth-24 );
	renderLineQuad( x+24, y+height*1.16, z+24, length-48, height*0.05, breadth-48 );
	renderLineQuad( x+30, y+height*1.21, z+30, length-60, height*0.03, breadth-60 );
	
	renderLineQuad( x, y, z+breadth, length, height*0.7, breadth*0.4 );
	renderLineQuad( x-2, y+height*0.7, z+breadth-2, length+4, height*0.09, breadth*0.4+4 );

	renderLineQuad( x-60, y, z-60, length+120, 20, breadth*1.3+120 );
}

void renderPillars( int x, int y, int z, int length, int height, int breadth )
{


}

void renderLineQuad( int x, int y, int z, int length, int height, int breadth )
{
	renderCuboid( x, y, z, length, height, breadth, GL_LINE_LOOP );
	renderCuboid( x, y, z, length, height, breadth, GL_QUADS );
}

void renderBuilding( int id, int x, int y, int z, int length, int height, int breadth )
{
	if( id==1 )
		renderBuilding1( x, y, z, length, height, breadth );
	if( id==2 )
		renderBuilding2( x, y, z, length, height, breadth );
	if( id==3 )
		renderBuilding3( x, y, z, length, height, breadth );
	if( id==4 )
		renderBuilding4( x, y, z, length, height, breadth );
}