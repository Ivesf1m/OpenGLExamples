#include <GL/glut.h>
#include <iostream>

using namespace std;

void init()
{
	//Definir qual cor deve ser utilizada para "limpar" a janela.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Desenhando nosso tri�ngulo
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//Inicializa��o da GLUT - lendo argumentos da linha de comando. 
	glutInit(&argc, argv);

	//Modo de Display
	//GLUT_DOUBLE: ativa��o do double buffering
	//GLUT_RGB: significa que nossos pixels ter�o 3 componentes, nesta ordem.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	//Tamanho da janela em pixels
	glutInitWindowSize(600, 600);

	//Criando janela com o t�tulo passado.
	glutCreateWindow("Meu primeiro triangulo");

	//Callback para a fun��o que ser� respons�vel pelos desenhos.
	glutDisplayFunc(display);

	//Fun��o auxiliar para inicializar os estados da GL que desejarmos.
	init();

	//Essa fun��o d� in�cio ao loop de renderiza��o.
	glutMainLoop();
	return 0;
}