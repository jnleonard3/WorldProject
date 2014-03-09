#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
 
#include <SDL.h>
#include <SDL_opengl.h>
 
void Display_InitGL() {
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );
 
    /* Set the background black */
    glClearColor( 1.0f, 0.0f, 0.0f, 0.0f );
 
    /* Depth buffer setup */
    glClearDepth( 1.0f );
 
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
 
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );
 
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar ) {
 const GLdouble pi = 3.1415926535897932384626433832795;
 GLdouble fW, fH;

 //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
 fH = tan( fovY / 360 * pi ) * zNear;
 fW = fH * aspect;

 glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

/* function to reset our viewport after a window resize */
int Display_SetViewport( int width, int height ) {
    /* Height / width ration */
    GLfloat ratio;
 
    /* Protect against a divide by zero */
    if ( height == 0 ) {
        height = 1;
    }
 
    ratio = ( GLfloat )width / ( GLfloat )height;
 
    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
 
    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
 
    /* Set our perspective */
    perspectiveGL( 45.0f, ratio, 0.1f, 100.0f );
 
    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );
 
    /* Reset The View */
    glLoadIdentity( );
 
    return 1;
}
 
void Display_Render(SDL_Window* displayWindow){
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef( -1.5f, 0.0f, -6.0f );
 
    glBegin( GL_TRIANGLES );            /* Drawing Using Triangles */
      glVertex3f(  0.0f,  1.0f, 0.0f ); /* Top */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
    glEnd( );                           /* Finished Drawing The Triangle */
 
    /* Move Right 3 Units */
    glTranslatef( 3.0f, 0.0f, 0.0f );
 
    glBegin( GL_QUADS );                /* Draw A Quad */
      glVertex3f( -1.0f,  1.0f, 0.0f ); /* Top Left */
      glVertex3f(  1.0f,  1.0f, 0.0f ); /* Top Right */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
    glEnd( );                           /* Done Drawing The Quad */
    
    SDL_GL_SwapWindow(displayWindow);
}
 
int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* displayWindow = SDL_CreateWindow("", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(displayWindow);

    Display_InitGL();
    
    Display_SetViewport(800, 600);
    
    Display_Render(displayWindow);
    
    SDL_Delay(5000);
    SDL_Quit();
    
    return 0;
}