// COMPILAR: g++ quadrado.cpp -lGL -lGLU -lglut -o moinho && ./moinho
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
GLdouble camx = 0, camy = 7, camz = 30; // Posição camera inicial
GLfloat v[8][3] = {	{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1},
					{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}};
GLUquadricObj *quadrica(bool linha){
	GLUquadricObj *obj1 = gluNewQuadric();
	if(linha) gluQuadricDrawStyle(obj1, GLU_LINE); // FILL, LINE...
	else gluQuadricDrawStyle(obj1, GLU_FILL); // FILL, LINE...
	gluQuadricOrientation(obj1, GLU_OUTSIDE);
	gluQuadricNormals(obj1, GLU_SMOOTH);
	return obj1;
}

void DesenhaQuadrado(void)
{
	glScalef(10, 10, 10);
	glBegin(GL_QUADS);
	// Desenha um Quadrado (TRÁS) com a cor atual. R|G|B: VERDE
	glColor3f(0.2f, 0.8f, 0.2f);
	glVertex3fv(v[4]);
	glVertex3fv(v[5]);
	glVertex3fv(v[6]);
	glVertex3fv(v[7]);

	// Desenha um Quadrado (INFERIOR) com a cor atual. R|G|B: AMARELO
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);
	glVertex3fv(v[5]);
	glVertex3fv(v[4]);

	// Desenha um Quadrado (DIREITA) com a cor atual. R|G|B: ROSA
	glColor3f(1.0f, 0.08f, 0.58f);
	glVertex3fv(v[1]);
	glVertex3fv(v[5]);
	glVertex3fv(v[6]);
	glVertex3fv(v[2]);

	// Desenha um Quadrado (FRENTE) com a cor atual. R|G|B: VERMELHO
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(v[0]);
	glVertex3fv(v[1]);
	glVertex3fv(v[2]);
	glVertex3fv(v[3]);

	// Desenha um Quadrado (SUPERIOR) com a cor atual. R|G|B: CIANO
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3fv(v[3]);
	glVertex3fv(v[2]);
	glVertex3fv(v[6]);
	glVertex3fv(v[7]);

	// Desenha um Quadrado (ESQUERDA) com a cor atual. R|G|B: BRANCO
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3fv(v[0]);
	glVertex3fv(v[4]);
	glVertex3fv(v[7]);
	glVertex3fv(v[3]);

	glEnd();
	glScalef(1, 1, 1);
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
	DesenhaQuadrado();
	//-----------------------------------------
    glutSwapBuffers();
    glFlush();
}

void Redesenha(void) {  glutPostRedisplay(); }

void Inicializa(void) {
    GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4] = { 0.5,0.5,0.5,1.0 };
	GLfloat luzEspecular[4] = { 0.7,0.7,0.7, 1.0 };
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };
	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 0;
    // Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);
	// // Define a reflet�ncia do material
	// glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// // Define a concentra��o do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	//
	// // Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	//
	// // Define os p1.5ar�metros da luz de n�mero 0
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz);

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT1);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0, 0, 0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
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
