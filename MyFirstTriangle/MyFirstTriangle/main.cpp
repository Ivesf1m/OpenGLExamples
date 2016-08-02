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

	//Desenhando nosso triângulo
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
	//Inicialização da GLUT - lendo argumentos da linha de comando. 
	glutInit(&argc, argv);

	//Modo de Display
	//GLUT_DOUBLE: ativação do double buffering
	//GLUT_RGB: significa que nossos pixels terão 3 componentes, nesta ordem.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	//Tamanho da janela em pixels
	glutInitWindowSize(600, 600);

	//Criando janela com o título passado.
	glutCreateWindow("Meu primeiro triangulo");

	//Callback para a função que será responsável pelos desenhos.
	glutDisplayFunc(display);

	//Função auxiliar para inicializar os estados da GL que desejarmos.
	init();

	//Essa função dá início ao loop de renderização.
	glutMainLoop();
	return 0;
}