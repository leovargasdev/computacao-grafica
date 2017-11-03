#include <GL/glut.h>
#include <math.h>
// g++ gluCylinder.cpp -lGL -lGLU -lglut -o out && ./out
GLfloat rotateBase = 0.0, rotateTopo = 360.0;
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
	rotateBase += 0.04;
	if(rotateBase >= 360)
		rotateBase = 0.0;
	rotateTopo -= 0.04;
	if(rotateTopo <= 0)
		rotateTopo = 360.0;

	glPushMatrix();
		glColor3f(255/255.0f, 206/255.0f, 155/255.0f); // ROXO.
		glTranslatef(0, 58, 0);
		glRotatef(90, 1, 0, 0);
		GLUquadricObj *cilindroMeio = quadrica(true);
		gluCylinder(cilindroMeio, 1, 1, 60, 25, 25); //(objeto, raio Base, raio Topo, altura, fatias em redor do z, fatias em pilha)
	glPopMatrix();

	glPushMatrix();
		glColor3f(61/255.0f,4/255.0f,100/255.0f); // ROXO.
		glRotatef(rotateBase, 0, 1, 0);
		GLUquadricObj *cilindroBase = quadrica(false);
		// OBS: O 5º parametro influência na circunferência do cilindro
		gluCylinder(cilindroBase, 1, 8, 30, 8, 25); //(objeto, raio Base, raio Topo, altura, fatias em coluna, fatias em raio)
	glPopMatrix();

	glPushMatrix();
		glColor3f(61/255.0f,4/255.0f,100/255.0f); // ROXO.
		glRotatef(rotateTopo, 0, 1, 0);
		glTranslatef(0, 56, 0);
		GLUquadricObj *cilindroTopo = quadrica(false);
		gluCylinder(cilindroTopo, 1, 8, 30, 4, 25); //(objeto, raio Base, raio Topo, altura, fatias em redor do z, fatias em pilha)
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
	glutCreateWindow("Cylinder");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}
