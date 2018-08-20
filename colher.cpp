// COMPILAR: g++ moinho.cpp -lGL -lGLU -lglut -o moinho && ./moinho
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
GLUnurbsObj *theNurb;
GLdouble camx = 0, camy = 7, camz = 30; // Posição camera inicial
GLfloat concha_colh[4][4][3] = {
    {
        { -0.5, 0.80, 0},    { -0.15, 1.25, 0},
        { 0.15, 1.25, 0},     { 0.5, 0.80, 0}
    },
    {
        { -0.75, 0.5, 0},    { -0.5, 0.5, -0.5},
        { 0.5, 0.5, -0.5},    {0.75, 0.5, 0}
    },
    {
        { -1.0, -0.5, 0},     { -0.5, -0.5, -0.5},
        { 0.5, -0.5, -0.5},       { 1.0, -0.5, 0}
    },
    {
        { -0.5, -1.0, 0},    { -0.15, -1.25, 0},
        { 0.15, -1.25, 0},       { 0.5, -1.0, 0}
    }
};
GLfloat concha_colh_esp[4][4][3] = {
    {
        { -7.5, 0.80, 0},    { -0.15, 1.25, 0},
        { 0.15, 1.25, 0},     { 0.5, 0.80, 0}
    },
    {
        { -0.75, 0.5, 0},    { -0.5, 0.5, 0.5},
        { 0.5, 0.5, 0.5},    {0.75, 0.5, 0}
    },
    {
        { -1.0, -0.5, 0},     { -0.5, -0.5, 0.5},
        { 0.5, -0.5, 0.5},       { 1.0, -0.5, 0}
    },
    {
        { -7.5, -1.0, 0},    { -0.15, -1.25, 0},
        { 0.15, -1.25, 0},       { 0.5, -1.0, 0}
    }
};
GLfloat alca_colh[4][4][3] = {
    {
        { -0.10, 1.5, 0},    { -0.05, 1.5, 0},
        { 0.05, 1.5, 0},     { 0.10, 1.5, 0}
    },
    {
        { -0.10, 0.85, 0.35},    { -0.05, 0.85, 0.50},
        { 0.05, 0.85, 0.50},    {0.10, 0.85, 0.35}
    },
    {
        { -0.25, -0.5, 0},     { -0.15, -0.5, 0},
        { 0.15, -0.5, 0},       { 0.25, -0.5, 0}
    },
    {
        { -0.15, -1.25, 0},    { -0.15, -1.5, 0},
        {0.15, -1.5, 0},       {0.15, -1.25, 0}
    }
};
GLfloat alca_colh_esp[4][4][3] = {
    {
        { -0.10, 1.5, 0},    { -0.05, 1.5, 0},
        { 0.05, 1.5, 0},     { 0.10, 1.5, 0}
    },
    {
        { -0.10, 0.85, -0.35},    { -0.05, 0.85, -0.50},
        { 0.05, 0.85, -0.50},    {0.10, 0.85, -0.35}
    },
    {
        { -0.25, -0.5, 0},     { -0.15, -0.5, 0},
        { 0.15, -0.5, 0},       { 0.25, -0.5, 0}
    },
    {
        { -0.15, -1.25, 0},    { -0.15, -1.5, 0},
        {0.15, -1.5, 0},       {0.15, -1.25, 0}
    }
};
GLfloat colh_diffuse[] = { 0.7, 0.7, 0.7, 1.0 }, colh_specular[] = { 1.0, 1.0, 1.0, 1.0 },
colh_shininess[] = { 20.0 };
// desenha todas as partes
void desenha_colher(void) {
    glColor4f(0.4, 0.4, 0.4, 0.4); // cinza prateado
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colh_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colh_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, colh_shininess);
    glPushMatrix();
        glScalef(0.8, 0.8, 0.8);
        // alca
        glPushMatrix();
            glTranslatef(0, -2.67, 0); //1.5 + 1.25
            drawSurface(alca_colh);
            glColor4f(0.4, 0.4, 0.4, 0.4);
        glPopMatrix();
		// conha
        glPushMatrix();
            // drawSurface(concha_colh);
            glColor4f(0.4, 0.4, 0.4, 0.4);
        glPopMatrix();
    glPopMatrix();
}

void desenha(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Limpa a janela de visualização:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(camx, camy, camz, 0,0,0, 0,1,0);
    glBegin(GL_LINES);
        // Eixo X:
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1000, 0, 0);
        glVertex3f(1000, 0, 0);
        // Eixo Y:
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);
        // Eixo Z:
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, -1000);
        glVertex3f(0, 0, 1000);
    glEnd();
	// DESENHA AQUI !!!
	// ---------------------------------------
	glPushMatrix();
    	glTranslatef(2.0, -1., 0.5);
	    // desenha_colher();
	glPopMatrix();
	//-----------------------------------------
    glutSwapBuffers();
    glFlush();
}

// flag de erros do nurbs
void nurbsError(GLenum errorCode) {
   const GLubyte *estring;
   estring = gluErrorString(errorCode);
   fprintf (stderr, "Nurbs Error: %s\n", estring);
   exit (0);
}

void Redesenha(void) {  glutPostRedisplay(); }

void Inicializa(void) {
	GLfloat luzAmbiente[4] = { 0.2, 0.2, 0.2, 1.0 };
	    GLfloat luzDifusa[4] = { 0.7, 0.6, 0.6, 1.0 };    // "cor"
	    GLfloat luzEspecular[4] = { 0.8, 0.8, 0.8, 1.0 }; // "brilho"
	    GLfloat posicaoLuz[4] = { 10.0, 10.0, 0, 1.0 };
	//
	    // Capacidade de brilho do material
	    GLfloat especularidade[4] = { 0.0,0.0,0.0,1.0 };
	    GLint especMaterial = 2;

	    // Define a reflet�ncia do material
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especularidade);
	    // Define a concentra��o do brilho
	    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, especMaterial);

	    // Ativa o uso da luz ambiente
	    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	    // Define os par�metros da luz de n�mero 0
	    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	    glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
	    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz);

	    // Habilita a defini��o da cor do material a partir da cor corrente
	    glEnable(GL_COLOR_MATERIAL);
	    //Habilita o uso de ilumina��o
	    glEnable(GL_LIGHTING);
	    // Habilita a luz de n�mero 1
	    glEnable(GL_LIGHT1);

	   theNurb = gluNewNurbsRenderer();
	   gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
	   gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
	   gluNurbsCallback(theNurb, GLU_ERROR, (GLvoid (*)()) nurbsError);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	// Evita a divisao por zero
	if (h == 0) h = 1;
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    //Vou usar perspectiva
	gluPerspective(45, ((GLfloat)w / (GLfloat)h), 2, 200);
}

void GerenciaTeclado(unsigned char key, int x, int y){
    switch (key) {
            case 'w':
                    camy -= 1;
                    break;
            case 's':
                    camy += 1;
                    break;
            case 'a':
                    camx -= 1;
                    break;
            case 'd':
                    camx += 1;
                    break;
            case 'z':
                    camz -= 1;
                    break;
            case 'x':
                    camz += 1;
                    break;
    }
    glutPostRedisplay();
}
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(500, 500);
  glutCreateWindow ("Plano");
  glutIdleFunc(Redesenha);
  glutDisplayFunc(desenha);
  glutKeyboardFunc(GerenciaTeclado);
  Inicializa();
  glutReshapeFunc(AlteraTamanhoJanela);
  glutMainLoop();
  return 0;
}
