#ifndef __FLYOPENGL_HPP
#define __FLYOPENGL_HPP

#include "fly.hpp"

#define GLEW_STATIC
#include "glew.h"
//#define	GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>
void  glInit();



inline void glColor()
{
	glColor4d(Color.x,Color.y,Color.z,Opacity);
}

inline void glVertex(v2_t& a)
{
	glVertex2d(a.x, a.y);
}

typedef GLfloat vertex_real_t;
typedef vector2_c<vertex_real_t> vertex_vector_t;
extern vertex_vector_t*	Vertex_Data;
extern vertex_vector_t*&	Vertex_Cur;

extern GLuint Square_VBO;

inline GLenum GL_Type(vector2_c<GLfloat>* o) { return GL_FLOAT; }
inline GLenum GL_Type(vector2_c<GLdouble>* o) { return GL_DOUBLE; }

void Fly_Matrix_Set();
void Fly_Render_View_Set();

void Cover_Matrix();

bool Texture_Open(GLuint* id,  GLsizei w, GLsizei h);


#endif