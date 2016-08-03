#include <cmath>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include <SOIL\SOIL.h>

using namespace std;

GLuint texId = 0;
string imgPath(".//");


void init()
{
	//Definir qual cor deve ser utilizada para "limpar" a janela.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Ativando o uso de texturas
	glEnable(GL_TEXTURE_2D);

	//Carregando textura
	string texName = imgPath + "tex.png";
	cout << texName << endl;
	texId = SOIL_load_OGL_texture(texName.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (texId == 0) {
		cout << "Falha no carregamento da textura" << endl;
		exit(1);
	}

	//Comunicando para a GL qual textura usaremos
	glBindTexture(GL_TEXTURE_2D, texId);

	//Tratamento de limites
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtragem da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);

	//Triangulo 1
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

	//Triangulo 2
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);

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
	glutCreateWindow("Textura");

	//Callback para a função que será responsável pelos desenhos.
	glutDisplayFunc(display);

	//Função auxiliar para inicializar os estados da GL que desejarmos.
	init();

	//Essa função dá início ao loop de renderização.
	glutMainLoop();
	return 0;
}