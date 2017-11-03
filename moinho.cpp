// COMPILAR: g++ moinho.cpp -lGL -lGLU -lglut -o moinho && ./moinho
#include<stdio.h>
#include <GL/glut.h>
#include <math.h>
#define VELOCIDADE_HELICES 1.3
#define VELOCIDADE_SOL 0.8
#define VELOCIDADE_SOL_RAIO 0.3
#define MAX_RAIO 0.18
GLdouble camx = 0, camy = 7, camz = 30; // Posição camera inicial
GLfloat girarMoinho = 0;
GLfloat girarSol = 0;
GLfloat girarRaioSol = 0;
GLfloat alturaMoinho = 6.5;
GLfloat baseMoinho = 1.7;
GLfloat raioFlag2 = -0.004, raioFlag1 = 0.004;
GLfloat raio1 = 0, raio2 = MAX_RAIO;


GLUquadricObj *quadrica(bool linha){
	GLUquadricObj *obj1 = gluNewQuadric();
	if(linha) gluQuadricDrawStyle(obj1, GLU_LINE); // FILL, LINE...
	else gluQuadricDrawStyle(obj1, GLU_FILL); // FILL, LINE...
	gluQuadricOrientation(obj1, GLU_OUTSIDE);
	gluQuadricNormals(obj1, GLU_SMOOTH);
	return obj1;
}

void desenha(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Limpa a janela de visualização:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Camera
    gluLookAt(camx, camy, camz, 0,0,0, 0,1,0);
    // DESENHANDO LINHAS DE ORIENTAÇÃO:
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
	// Sol
	glPushMatrix();
		glTranslatef(10, 14, -20);
		glPushMatrix();
			glTranslatef(0,0,0.1);
			girarRaioSol += VELOCIDADE_SOL_RAIO;
			if(girarRaioSol >= 360.0)
				girarRaioSol = 0.0;
			glRotatef(girarRaioSol,0,0,1);
			glColor3f(234/255.0f, 222/255.0f, 38/255.0f); // Amarelo SOL
			GLUquadricObj *raioSol = quadrica(false);
			glPushMatrix();
				raio1 = raio1 + raioFlag1;
				if(raio1 <= 0 || raio1 >= MAX_RAIO)
					raioFlag1 *= (-1);
				glScalef(1+raio1, 1+raio1, 0);
				gluDisk(raioSol, 0.1, 2, 4, 10);
				glRotatef(-45,0,0,1);
				gluDisk(raioSol, 0.1, 2, 4, 10);
			glPopMatrix();
			glPushMatrix();
				raio2 = raio2 + raioFlag2;
				if(raio2 <= 0 || raio2 >= MAX_RAIO)
					raioFlag2 *= (-1);
				glScalef(1+raio2, 1+raio2, 0);
				glRotatef(45,0,0,1);
				gluDisk(raioSol, 0.1, 2, 4, 10);
			glPopMatrix();
		glPopMatrix();
		girarSol += VELOCIDADE_SOL;
		if(girarSol >= 360.0)
			girarSol = 0.0;
		glScalef(1,1,0.15);
		glColor3f(234/255.0f, 222/255.0f, 38/255.0f); // Amarelo SOL
		glRotatef(girarSol,1,0,0);
		glutSolidSphere(2.1, 5, 5);
		glColor3f(220/255.0f, 210/255.0f, 28/255.0f); // Amarelo SOL
		glRotatef(girarSol,0,1,0);
		glutSolidSphere(2.2, 6, 5);
	glPopMatrix();
	// Base moinho
	glPushMatrix();
		glColor3f(80/255.0f, 40/255.0f, 5/255.0f); // marrom coco
		glRotatef(90,1,0,0);
		glRotatef(38,0,0,1);
		glScalef(1,1,1.2);
		glutSolidTorus(0.28,baseMoinho-0.1,7,7);
	glPopMatrix();
	// corpoMoiho
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0,0,-alturaMoinho);
		GLUquadricObj *moinho = quadrica(false);
		GLUquadricObj *gradeMoinho = quadrica(true);
		// corpoMoiho
		glColor3f(99/255.0f, 64/255.0f, 10/255.0f); // marrom
		gluCylinder(moinho, baseMoinho, baseMoinho, alturaMoinho, 7, 15);
		glColor3f(78/255.0f, 51/255.0f, 8/255.0f); // marrom mais escuro
		gluCylinder(gradeMoinho, baseMoinho+0.008, baseMoinho+0.008, alturaMoinho, 7, 15); // grade
		glPushMatrix();
			glColor3f(80/255.0f, 40/255.0f, 5/255.0f); // marrom coco
			glRotatef(90,0,0,1);
			glScalef(1,1,0.4);
			glutSolidTorus(0.23,baseMoinho-0.1,7,7);
		glPopMatrix();
		// cabeça moinho
		glRotatef(180, 1, 0, 0);
		glRotatef(25, 0, 0, 1);
		glColor3f(99/255.0f, 64/255.0f, 10/255.0f); // marrom
		gluCylinder(moinho, baseMoinho, 0.1, alturaMoinho/2.5, 7, 15);

		glColor3f(78/255.0f, 51/255.0f, 8/255.0f); // marrom mais escuro
		gluCylinder(gradeMoinho, baseMoinho+0.008, 0.208, alturaMoinho/2.5, 7, 15); // grade
	glPopMatrix();
	// Bolinha central e as helices do moinho
	glPushMatrix();
		glColor3f(147/255.0f, 137/255.0f, 100/255.0f);
		GLUquadricObj *bolinhaMoinho = quadrica(false);
		glTranslatef(0, alturaMoinho-0.8, 1.5);
		glPushMatrix();
			glScalef(1,0.9,0.5);
			gluSphere(bolinhaMoinho, 0.65, 10, 10);
		glPopMatrix();
		girarMoinho += VELOCIDADE_HELICES;
		if(girarMoinho >= 361.0)
			girarMoinho = 0.0;
		glRotatef(girarMoinho, 0, 0, 1);
		glPushMatrix();
			glTranslatef(0,0,0.32);
			glRotatef(90, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			// Desenha as 4 helices
			for(int a = 0; a < 4; a++){
				glRotatef(90*a, 1, 0, 0);
				glColor3f(1, 1, 1);
				GLUquadricObj *helice = quadrica(true);
				gluCylinder(helice, 0.05, 0.8, 3.5, 2, 20);
				glPushMatrix();
					glColor3f(169/255.0f, 169/255.0f, 169/255.0f);
					glTranslatef(0.05,0,0);
					GLUquadricObj *heliceBorda = quadrica(false);
					gluCylinder(heliceBorda, 0.07, 0.95, 3.6, 2, 20);
				glPopMatrix();
			}
		glPopMatrix();
	glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void Redesenha(void) {  glutPostRedisplay(); }

// Inicializa parâmetros de rendering
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
  glutCreateWindow ("MOINHONHONHONHO");
  glutIdleFunc(Redesenha);
  glutDisplayFunc(desenha);
  glutKeyboardFunc(GerenciaTeclado);
  Inicializa();
  glutReshapeFunc(AlteraTamanhoJanela);
  glutMainLoop();
  return 0;
}
