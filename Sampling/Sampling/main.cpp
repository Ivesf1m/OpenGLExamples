#include <cmath>
#include <iostream>
#include <GL/glut.h>

using namespace std;

#define PI 3.1415

float minx = -1.0f;
float maxx = 1.0f;
float freq = 0.01f;
float samplingFreq = 0.2f;

bool showFunction = true;
bool showSamples = true;
bool showClosestNeighbor = false;
bool showZeroHold = false;
bool showInterpolation = false;

void init()
{
	//Definir qual cor deve ser utilizada para "limpar" a janela.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

//Desenhando a fun��o seno a partir de liga��o
//de pontos com da fun��o com retas a intervalos
//pequenos.
void drawSineFunction()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for (float i = minx; i <= maxx; i += freq) {
		glVertex3f(i, sin(i * 2.0 * PI), 0.0f);
		glVertex3f(i + freq, sin((i + freq) * 2.0 * PI), 0.0f);
	}
	glEnd();
}

//Desenhando retas para destacar a posi��o das amostras.
void drawSamples()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	int count = 0;
	for (float i = minx; i <= maxx; i += samplingFreq) {
		glVertex3f(i, 0.0f, 0.0f);
		glVertex3f(i, sin(i * 2.0f * PI), 0.0f);
	}
	glEnd();
}

//Reconstru��o pelo m�todo do vizinho mais pr�ximo
void closestNeighbor()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for (float i = minx; i <= maxx; i += samplingFreq) {
		float firstMiddlePoint = ((i - samplingFreq) + i) / 2.0f;
		float secondMiddlePoint = (i + (i + samplingFreq)) / 2.0f;
		glVertex3f(firstMiddlePoint, sin(i * 2.0f * PI), 0.0f);
		glVertex3f(secondMiddlePoint, sin(i * 2.0f * PI), 0.0f);
	}
	glEnd();
}

//Reconstru��o pelo m�todo zero-order hold
void zeroOrderHold()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for (float i = minx; i <= maxx; i += samplingFreq) {
		glVertex3f(i, sin(i * 2.0f * PI), 0.0f);
		glVertex3f(i + samplingFreq, sin(i * 2.0f * PI), 0.0f);
	}
	glEnd();
}

//Reconstru��o pelo m�todo da interpola��o (linear)
void linearInterpolation()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	for (float i = minx; i <= maxx; i += samplingFreq) {
		glVertex3f(i, sin(i * 2.0f * PI), 0.0f);
		glVertex3f(i + samplingFreq, sin((i + samplingFreq) * 2.0f * PI), 0.0f);
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Desenhar eixos x e y
	glBegin(GL_LINES);

	//Eixo x
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	//Eixo y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glEnd();

	if (showFunction)
		drawSineFunction();

	if (showSamples)
		drawSamples();

	if (showClosestNeighbor)
		closestNeighbor();

	if (showZeroHold)
		zeroOrderHold();

	if (showInterpolation)
		linearInterpolation();

	glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
	if (c == 'f' || c == 'F')
		showFunction = !showFunction;
	else if (c == 's' || c == 'S')
		showSamples = !showSamples;
	else if (c == 'n' || c == 'N')
		showClosestNeighbor = !showClosestNeighbor;
	else if (c == 'z' || c == 'Z')
		showZeroHold = !showZeroHold;
	else if (c == 'i' || c == 'I')
		showInterpolation = !showInterpolation;
	else if (c == 'a' || c == 'A') {
		float newFreq;
		cout << "Digite a nova frequencia amostral: " << endl;
		cin >> newFreq;
		samplingFreq = (newFreq == 0.0f) ? samplingFreq : newFreq;
	}

	glutPostRedisplay();
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
	glutCreateWindow("Amostragem e quantiza��o");

	//Callback para a fun��o que ser� respons�vel pelos desenhos.
	glutDisplayFunc(display);

	//Callback para a fun��o que ser� respons�vel pela intera��o via
	//teclado.
	glutKeyboardFunc(keyboard);

	//Fun��o auxiliar para inicializar os estados da GL que desejarmos.
	init();

	//Essa fun��o d� in�cio ao loop de renderiza��o.
	glutMainLoop();
	return 0;
}