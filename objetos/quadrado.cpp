
#include <GL/glut.h>

// Fun��o callback chamada para fazer o desenho
void Desenha(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualiza��o com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT);

	// Especifica que a cor corrente � vermelha
	//         R     G     B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Desenha um quadrado preenchido com a cor corrente
	glBegin(GL_QUADS);
	glVertex2i(-1,-1);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2i(1, -1);
	// Especifica que a cor corrente � azul
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2i(1, 1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(-1, 1);
	glEnd();

	// Executa os comandos OpenGL
	glFlush();
}

// Inicializa par�metros de rendering
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualiza��o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if (h == 0) h = 1;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (left, right, bottom, top)
	if (w <= h)
		gluOrtho2D(-2.0f, 2.0f, -2.0f, 2.0f*h / w);
	else
		gluOrtho2D(-2.0f, 2.0f*w / h, -2.0f, 2.0f);
}

// Programa Principal
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 350);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Quadrado");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}
