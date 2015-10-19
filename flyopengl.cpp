#include "flyopengl.hpp"


zone_s	Zone;

color_t		Color;
r_t			Opacity;
r_t			Thick = 1;

float Square_Data[] = { 0,0,  1,0,  1,1,  0,1 };
GLuint Square_VBO;


void glInit()
{
	glewInit();

	Fly_Render_View_Set();

	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnableClientState(GL_VERTEX_ARRAY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &Zone.matrix);
	//glPushMatrix();

	glGenBuffers(1, &Square_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, Square_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Square_Data), Square_Data, GL_STATIC_DRAW);   
}

void Fly_Render_View_Set()
{
	glViewport(0, 0, (GLsizei)Raster.x, (GLsizei)Raster.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslated(-1.0, 1, 0);
	glScaled(2.0/Raster.x, -2.0/Raster.y, 1);
	glMatrixMode(GL_MODELVIEW);
}

void Cover_Matrix()
{
	GLint n;
	glMatrixMode(GL_MODELVIEW);
	glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &n);
	n -= Zone.matrix;
	if (n < 0)
	{
		// error
	}
	else
	{
		for (; n > 0; n--)
		{
			glPopMatrix();
		}
		glPushMatrix();
	}
}

bool Rect_And(v2_t& p1, v2_t& d1, v2_t& p2, v2_t& d2)
{
	v2_t ma = Max(p1 + d1, p2 + d2) ;
	v2_t mi = Min(p1, p2);
	v2_t d = ma - mi;
	return d.x < d1.x + d2.x && d.y < d1.y + d2.y;
}

v2_t Zero_v2 = 0;


zone_c::zone_c()
{
	v2_t p = XY*Raster;
	v2_t d = WH*Raster;
	v2_t p0 = p - Pin*d;

	run = 1;
	//run = Rect_And(p0, d, Zone.screen, Resolution);
	//if (run)
	{
		Cover_Matrix();
		data = Zone;
		Zone.visible = Rect_And(p0, d, Zone.screen, Resolution);

		Mouse = Pin + (Mouse - XY)/WH;

		glTranslated(p.x,p.y,0);
		glRotated(Angle, 0, 0, 1);
		glTranslated(-Pin.x*d.x,-Pin.y*d.y,0);

		Zone.matrix++;
		Zone.screen -= p0;
		Raster = d;

		XY = 0;
		WH = 1;
		Pin = 0;
		Angle = 0;
	}
}


void Fly_Matrix_Set()
{
	v2_t p = XY*Raster;
	v2_t d = WH*Raster;

	Cover_Matrix();

	glTranslated(p.x,p.y,0);
	glRotated(Angle, 0, 0, 1);
	glScaled(d.x, d.y, 1);
	glTranslated(-Pin.x,-Pin.y,0);
}



vertex_vector_t*	Vertex_Data = 0;
vertex_vector_t*&	Vertex_Cur = (vertex_vector_t*&)Stack_Cur;

void Vertex(r_t x, r_t y)
{
	if (Vertex_Data == 0)
	{
		Vertex_Data = Vertex_Cur;
	}
	if ( Stack_End - Stack_Cur >= sizeof(Vertex_Data[0]) )
	{
		Vertex_Cur->x =(vertex_real_t) x;
		Vertex_Cur->y =(vertex_real_t) y;
		Vertex_Cur++;
	}
}

void Vertex(r_t x, r_t y, color_t color)
{
	if (Vertex_Data == 0)
	{
		Vertex_Data = Vertex_Cur;
	}
	if ( Stack_End - Stack_Cur >= sizeof(Vertex_Data[0]) )
	{
		Vertex_Cur->x =(vertex_real_t) x;
		Vertex_Cur->y =(vertex_real_t) y;
		Vertex_Cur++;
	}
}




void Zigzag()
{
	GLsizei count = Vertex_Cur - Vertex_Data;
	if (count > 1)
	{
		vertex_vector_t b = Vertex_Data[0];
		for (GLsizei i = 1; i < count; i++)
		{
			b = Max(b, Vertex_Data[i]);
		}

		Cover_Matrix();

		v2_t p = XY*Raster;
		v2_t d = WH*Raster;

		glTranslated(p.x,p.y,0);
		glRotated(Angle, 0, 0, 1);
		glScaled(d.x, d.y, 1);
		glTranslated(-Pin.x*b.x,-Pin.y*b.y,0);

		//glColor4d(Color.r,Color.g,Color.b,Opacity);
		glColor();
		glLineWidth((GLfloat)Thick);

		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexPointer(sizeof(vertex_vector_t)/sizeof(vertex_real_t), GL_Type(Vertex_Data), 0, Vertex_Data);
		glDrawArrays(GL_LINE_STRIP, 0, count);
	}
	Stack_Set(Vertex_Data);
	Vertex_Data = 0;
}

void Polygon()
{
	GLsizei count = Vertex_Cur - Vertex_Data;
	if (count > 1)
	{
		vertex_vector_t b = Vertex_Data[0];
		for (GLsizei i = 1; i < count; i++)
		{
			b = Max(b, Vertex_Data[i]);
		}

		Cover_Matrix();

		v2_t p = XY*Raster;
		v2_t d = WH*Raster;

		glTranslated(p.x,p.y,0);
		glRotated(Angle, 0, 0, 1);
		glScaled(d.x, d.y, 1);
		glTranslated(-Pin.x*b.x,-Pin.y*b.y,0);

		//glColor4d(Color.r,Color.g,Color.b,Opacity);
		glColor();

		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexPointer(sizeof(vertex_vector_t)/sizeof(vertex_real_t), GL_Type(Vertex_Data), 0, Vertex_Data);
		glDrawArrays(GL_TRIANGLE_FAN, 0, count);
	}
	Stack_Set(Vertex_Data);
	Vertex_Data = 0;
}

void Diagonal()
{
	Vertex(0,		0);
	Vertex(Thick/abs(W),	0);
	Vertex(1,		1);
	Vertex(1 - Thick/abs(W), 1);
	Polygon();
}

void Box()
{
	Fly_Matrix_Set();
	
	glLineWidth((GLfloat)Thick);
	glColor();
	//glColor4d(Color.r,Color.g,Color.b,Opacity);

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, Square_VBO);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void Line()
{
	Fly_Matrix_Set();
	//glColor4d(Color.r,Color.g,Color.b,Opacity);
	glColor();
	glDisable(GL_TEXTURE_2D);
	glLineWidth((GLfloat)Thick);
	glBegin(GL_LINES);
	glVertex2d(0,0);
	glVertex2d(1,1);
	glEnd();
}




void Fill()
{
	if (Opacity)
	{
		Fly_Matrix_Set();
	
		//glColor4d(Color.r,Color.g,Color.b,Opacity);
		glColor();

		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, Square_VBO);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
}

float Triangle_Data[] = { 0.5,0, 1,1,  0,1 };
GLuint Triangle_VBO = 0;
void Triangle()
{
	if (Triangle_VBO == 0)
	{
		glGenBuffers(1, &Triangle_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, Triangle_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle_Data), Triangle_Data, GL_STATIC_DRAW);
	}

	Fly_Matrix_Set();
	
	//glColor4d(Color.r,Color.g,Color.b,Opacity);
	glColor();

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, Triangle_VBO);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
}

const int Circle_Dots = 360;
vertex_vector_t Circle_Data[Circle_Dots + 1];
GLuint Circle_VBO = 0;

GLuint Circle_VBO_Get()
{
	if (Circle_VBO == 0)
	{
		Circle_Data[0] = 0.5;
		for (int i = 0; i < Circle_Dots; i++)
		{
			double angle  = i*360/Circle_Dots*M_PI/180;
			Circle_Data[i+1].x = vertex_real_t(0.5 + 0.5*cos(angle));
			Circle_Data[i+1].y = vertex_real_t(0.5 + 0.5*sin(angle));
		}

		glGenBuffers(1, &Circle_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, Circle_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Circle_Data), Circle_Data, GL_STATIC_DRAW);
	}
	return Circle_VBO;
}

void Circle()
{
	Fly_Matrix_Set();
	
	//glColor4d(Color.r,Color.g,Color.b,Opacity);
	glColor();

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, Circle_VBO_Get());
	glVertexPointer(2, GL_Type(Circle_Data), 0, NULL);
	glDrawArrays(GL_TRIANGLE_FAN, 1, Circle_Dots);
}

void Pie(r_t angle)
{
	Fly_Matrix_Set();
	
	//glColor4d(Color.r,Color.g,Color.b,Opacity);
	glColor();

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, Circle_VBO_Get());
	glVertexPointer(2, GL_Type(Circle_Data), 0, NULL);
	r_t dots = (r_t(Circle_Dots)*angle/360.0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, GLsizei(Circle_Dots*angle/360 + 2));
}


bool Texture_Open(GLuint* id,  GLsizei w, GLsizei h)
{
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return 1;
}