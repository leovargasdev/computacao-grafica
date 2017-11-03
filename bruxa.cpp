#include <GL/glut.h>
#include <math.h>
#define INCREMENTO 0.025
// g++ witch.cpp -lGL -lGLU -lglut -o witch && ./witch
GLfloat rotateVar = 0.0; // Variável uilizada para incrementar a rotação.
GLfloat altura = 0.0;
GLfloat incremento = INCREMENTO;
GLUquadricObj *quadrica1(bool completo){
	GLUquadricObj *obj1 = gluNewQuadric();
	if(completo)
		gluQuadricDrawStyle(obj1, GLU_FILL); // FILL, LINE...
	else
		gluQuadricDrawStyle(obj1, GLU_LINE); // FILL, LINE...
	gluQuadricOrientation(obj1, GLU_OUTSIDE);
	gluQuadricNormals(obj1, GLU_SMOOTH);
	return obj1;
}
void Desenha(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Limpa a janela de visualização:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	rotateVar += 0.040;
	if(rotateVar >= 360) rotateVar = 0.0;
	altura += incremento;
	if(incremento < 0 && altura < 28)
		incremento = INCREMENTO;
	else if(incremento > 0 && altura > 70)
		incremento = -INCREMENTO;
	glRotatef(-98, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(rotateVar, 0, 0, 1);
	// CHAPÉU:
	glPushMatrix();
		glColor3f(61/255.0f,4/255.0f,100/255.0f); // ROXO.
		GLUquadricObj *Chapeu = quadrica1(true);
		gluCylinder(Chapeu, 20, 1, altura, 30, 40); //(obj, base, topo, altura, riscos pilha, riscos culonas)
	glPopMatrix();
	// BOLINHA CHAPEU:
	glPushMatrix();
		glColor3f(147/255.0f, 137/255.0f, 100/255.0f);
		GLUquadricObj *bolinhaChapeu = quadrica1(true);
		glTranslatef(0, 0, altura+1);
		gluSphere(bolinhaChapeu, 2, 5, 5);
	glPopMatrix();
	// ABA:
	glPushMatrix();
		glColor3f(61/255.0f,4/255.0f,100/255.0f); // ROXO.
		GLUquadricObj *Aba = quadrica1(true);
		gluDisk(Aba, 0, 30, 25, 25);
	glPopMatrix();
	// CABEÇA:
	glPushMatrix();
		glColor3f(201/255.0f, 114/255.0f, 116/255.0f); // BEGE.
		GLUquadricObj *Cabeca = quadrica1(true);
		glTranslatef(0, 0, -13);
		gluSphere(Cabeca, 22, 25, 90);
	glPopMatrix();
	// OLHO 1:
	glPushMatrix();
		glColor3f(147/255.0f, 137/255.0f, 100/255.0f);
		GLUquadricObj *Olhum = quadrica1(true);
		glTranslatef(-7, 20.4, -10);
		gluSphere(Olhum, 3, 5, 5);
		glColor3f(0.0f, 0.0f, 0.0f);
		GLUquadricObj *OlhumBolinha = quadrica1(true);
		glTranslatef(1, 2.5,-0.2);
		gluSphere(OlhumBolinha, 1, 5, 5);
	glPopMatrix();
	// OLHO 2:
	glPushMatrix();
		glColor3f(147/255.0f, 137/255.0f, 100/255.0f);
		GLUquadricObj *Olhois = quadrica1(true);
		glTranslatef(8, 20.4, -10);
		gluSphere(Olhois, 3, 5, 5);
		glColor3f(0.0f, 0.0f, 0.0f);
		GLUquadricObj *OlhoisBolinha = quadrica1(true);
		glTranslatef(-1, 2.5, 0);
		gluSphere(OlhoisBolinha, 1, 5, 5);
	glPopMatrix();
	//NARIZ:
	glPushMatrix();
		glColor3f(255/255.0f, 206/255.0f, 155/255.0f); // BEGE.
		glTranslatef(0, 17, -15);
		glRotatef(-90, 1, 0, 0);
		GLUquadricObj *Nariz = quadrica1(false);
		gluCylinder(Nariz, 2.1, 0, 10, 25, 25);
	glPopMatrix();
	glutPostRedisplay();
	glFlush();
}
// Inicializa os parâmetros de Rendering:
void Inicializa(void){
	// Define a cor de fundo da janela de visualização:
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}
// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	// Evita a divisao por zero
	if (h == 0) h = 1;
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Estabelece a janela de seleção (left, right, bottom, top)
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, 100.0f, -100.0f);
}
// Programa Principal
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Witch");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}
