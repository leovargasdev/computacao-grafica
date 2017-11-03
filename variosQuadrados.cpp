#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
GLfloat squareVertex[8][3] = { // Vértices do Quadrado (1 a 3):
    {1, 3, 3}, {1, 1, 3}, {3, 1, 3}, {3, 3, 3}, // FRENTE
    {1, 3, 1}, {1, 1, 1}, {3, 1, 1}, {3, 3, 1} // TRÁS
};
GLfloat squareColor[6][3] = { // Cores das faces do Quadrado {R, G, B}:
    {50/255.0f, 205/255.0f, 153/255.0f},    // VERDE ÁGUA
    {77/255.0f, 77/255.0f, 255/255.0f},     // LILÁS
    {204/255.0f, 50/255.0f, 53/255.0f},     // ROSA
    {255/255.0f, 127/255.0f, 0/255.0f},     // LARANJA CLARO
    {0/255.0f, 127/255.0f, 255/255.0f},     // AZUL
    {255/255.0f, 0/255.0f, 0/255.0f}        // VERMELHO
};
GLfloat squareRotationY = 0.0f;
GLfloat squareRotationZ = 0.0f;

void DesenhaQuadrado(GLfloat scaleX){
	glScalef(1*scaleX, 1*scaleX, 1*scaleX);
	glBegin(GL_QUADS);
	// Desenha um Quadrado (TRÁS) com a cor atual. R|G|B: VERDE
	glColor3fv(squareColor[0]);
	glVertex3fv(squareVertex[4]);
	glVertex3fv(squareVertex[5]);
	glVertex3fv(squareVertex[6]);
	glVertex3fv(squareVertex[7]);
	// Desenha um Quadrado (INFERIOR) com a cor atual. R|G|B: AMARELO
	glColor3fv(squareColor[1]);
	glVertex3fv(squareVertex[5]);
	glVertex3fv(squareVertex[1]);
	glVertex3fv(squareVertex[2]);
	glVertex3fv(squareVertex[6]);
	// Desenha um Quadrado (DIREITA) com a cor atual. R|G|B: ROSA
	glColor3fv(squareColor[2]);
	glVertex3fv(squareVertex[3]);
	glVertex3fv(squareVertex[2]);
	glVertex3fv(squareVertex[6]);
	glVertex3fv(squareVertex[7]);
	// Desenha um Quadrado (FRENTE) com a cor atual. R|G|B: VERMELHO
	glColor3fv(squareColor[3]);
	glVertex3fv(squareVertex[0]);
	glVertex3fv(squareVertex[1]);
	glVertex3fv(squareVertex[2]);
	glVertex3fv(squareVertex[3]);
	// Desenha um Quadrado (SUPERIOR) com a cor atual. R|G|B: CIANO
	glColor3fv(squareColor[4]);
	glVertex3fv(squareVertex[4]);
	glVertex3fv(squareVertex[0]);
	glVertex3fv(squareVertex[3]);
	glVertex3fv(squareVertex[7]);
	// Desenha um Quadrado (ESQUERDA) com a cor atual. R|G|B: BRANCO
	glColor3fv(squareColor[5]);
	glVertex3fv(squareVertex[4]);
	glVertex3fv(squareVertex[0]);
	glVertex3fv(squareVertex[1]);
	glVertex3fv(squareVertex[5]);
	glEnd();
	glScalef(1, 1, 1);
}

GLUquadricObj *quadrica1(){
	GLUquadricObj *obj1 = gluNewQuadric();
	gluQuadricDrawStyle(obj1, GLU_FILL); // FILL, LINE...
	gluQuadricOrientation(obj1, GLU_OUTSIDE);
	gluQuadricNormals(obj1, GLU_SMOOTH);
	return obj1;
}
void Desenha(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        squareRotationY += 0.01f;
        if(squareRotationY > 360.0f)
            squareRotationY = 0.0f;
		if(squareRotationY <= 90)
			squareRotationZ = 90;
		else if(squareRotationY <= 180)
			squareRotationZ = 180;
		else if(squareRotationY <= 270)
			squareRotationZ = 270;
		else
			squareRotationZ = 180*2;
		printf("%f\n", squareRotationY);
		glRotatef(90, 1, 0, 0); 			// rotação no X
        glRotatef(squareRotationY, 0, 1, 0);// rotação no Y
        glRotatef(squareRotationZ, 0, 0, 1);// rotação no Z
        glTranslatef(2, 2, 2);
        DesenhaQuadrado(0.4f);
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
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 10.0f, -10.0f);
}
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Varios Quadrados");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}
