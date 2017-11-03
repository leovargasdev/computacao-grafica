#include <GL/glut.h>
#include <math.h>
// g++ esfera.cpp -lGL -lGLU -lglut -o esfera
GLfloat colorVar1 = 0.0f;
GLfloat rotateVar = 0.0; // Variável uilizada para incrementar a rotação.
GLfloat v[8][3] = {
				{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}, // FRENTE
				{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1} // TRÁS
				};

// Função chamada para Desenhar a ESFERA na tela:
void DesenhaEsfera(GLfloat sizeMul, GLfloat R1, GLfloat G1, GLfloat B1, GLfloat R2, GLfloat G2, GLfloat B2){	
	GLfloat PI = 3.141592f;
	GLfloat x, y, z, alpha, beta; // Variáveis para coordenadas e ângulos.
	GLfloat radius = 10.0f * sizeMul; // Tamanho Base = 10.
	int gradation = 25;
	GLfloat color = 0.0f; // Variável de Variação de Cores.

	for (alpha = 0.0; alpha < PI; alpha += PI/gradation)
	{

		if(color == 0.0f){
			glColor3f(R1/255.0f, G1/255.0f, B1/255.0f); // 1 faixa.
		}
		else{
			glColor3f(R2/255.0f, G2/255.0f, B2/255.0f); // 2 faixas.
		}
		color += 1.0f;
		if(color > 2.0f){
			color = 0.0f;
		}

		glBegin(GL_TRIANGLE_STRIP);
		for (beta = 0.0; beta < 2.01*PI; beta += PI/gradation)
		{

			x = radius*cos(beta)*sin(alpha);
			y = radius*sin(beta)*sin(alpha);
			z = radius*cos(alpha);
			glVertex3f(x, y, z);
			x = radius*cos(beta)*sin(alpha + PI/gradation);
			y = radius*sin(beta)*sin(alpha + PI/gradation);
			z = radius*cos(alpha + PI/gradation);
			glVertex3f(x, y, z);
		}
	}

	glEnd();
}

// Função chamada para Desenhar o QUADRADO na tela:
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

void Desenha(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rotateVar += 0.03;
	if(rotateVar >= 360){
		rotateVar = 0.0;
	}

	glRotatef(25, 1, 0, 0);
	glRotatef(rotateVar, 0, 1, 0);

	DesenhaEsfera(3.0f, 0, 255, 128, 0, 128, 255);
	glTranslatef(60, 0, 0);
	DesenhaEsfera(0.75f, 224, 224, 224, 192, 192, 192);
	//DesenhaQuadrado();
	glutPostRedisplay();
	glFlush();
}

// Inicializa os parâmetros de Rendering:
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualização:
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);


}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
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
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Esfera");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}
