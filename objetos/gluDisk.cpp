#include <GL/glut.h>
#include <math.h>
#define INCREMENTO 0.01;
// g++ gluDisk.cpp -lGL -lGLU -lglut -o out && ./out
GLfloat rotateVar = 0.0, raioInterno = 0.0;
GLfloat incremento = INCREMENTO;
GLUquadricObj *quadrica(bool completo){
	GLUquadricObj *obj1 = gluNewQuadric();
	if(completo)
		gluQuadricDrawStyle(obj1, GLU_FILL);
	else
		gluQuadricDrawStyle(obj1, GLU_LINE);
	gluQuadricOrientation(obj1, GLU_OUTSIDE);
	gluQuadricNormals(obj1, GLU_SMOOTH);
	return obj1;
}

void Desenha(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	rotateVar += 0.030;
	if(rotateVar >= 360)
		rotateVar = 0.0;
	glRotatef(rotateVar, 1, 0, 0);

	raioInterno += incremento;
	if(incremento < 0 && raioInterno < 0)
		incremento = INCREMENTO;
	if(incremento > 0 && raioInterno > 35)
		incremento = -INCREMENTO;
	glPushMatrix();
		glColor3f(61/255.0f,4/255.0f,100/255.0f); // ROXO.
		glTranslatef(40, 40, 0);
		GLUquadricObj *Disk = quadrica(true);
		gluDisk(Disk, raioInterno, 30, 25, 25); //(objeto, raio Interno, raio Externo, fatias em coluna(eixo z), fatias por raio)
	glPopMatrix();

	glPushMatrix();
		glColor3f(61/255.0f,4/255.0f,100/255.0f); // ROXO.
		glTranslatef(-40, -40, 0);
		GLUquadricObj *Disk2 = quadrica(false);
		gluDisk(Disk2, 0, 30, 25, 25);
	glPopMatrix();

	glutPostRedisplay();
	glFlush();
}

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
	glutCreateWindow("Disk");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}
