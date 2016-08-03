#include <GL\glew.h>
#include <GL\freeglut.h>
#include <SOIL\SOIL.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

GLuint texId = 0;
string imgPath = ".//";

GLuint qtdVerts = 6;

GLfloat verts[] = { -1.0f, -1.0f, 0.0f, //Triangulo 1 - vertice 1
				     1.0f, -1.0f, 0.0f, //Triangulo 1 - vertice 2
				    -1.0f,  1.0f, 0.0f, //Triangulo 1 - vertice 3
				     1.0f, -1.0f, 0.0f, //Triangulo 2 - vertice 1
				     1.0f,  1.0f, 0.0f, //Triangulo 2 - vertice 2
				    -1.0f,  1.0f, 0.0f  //Triangulo 2 - vertice 3
			      };

GLfloat texCoords[] = { 0.0f, 0.0f, //Triangulo 1 - vertice 1
					    1.0f, 0.0f, //Triangulo 1 - vertice 2
					    0.0f, 1.0f, //Triangulo 1 - vertice 3
					    1.0f, 0.0f, //Triangulo 2 - vertice 1
					    1.0f, 1.0f, //Triangulo 2 - vertice 2
					    0.0f, 1.0f  //Triangulo 2 - vertice 3
					  };

GLuint vao; //Vertex array object id
GLuint vbo[2]; //vertex buffer object
GLuint programID; //shader program

//Funcao para leitura dos arquivos dos shaders.
string readShaderFile(string fileName)
{
	string shaderCode;
	ifstream shaderStream(fileName, ios::in);
	if (shaderStream.is_open()) {
		string line = "";
		while (getline(shaderStream, line))
			shaderCode += "\n" + line;
		shaderStream.close();
	}
	else {
		cerr << "Falha ao abrir o arquivo " << fileName << endl;
		exit(1);
	}

	return shaderCode;

}

//Funcao para verificar o estado de compilacao ou ligacao dos shaders
void checkStatus(GLuint id, GLuint statusMacro)
{
	GLint result = GL_FALSE;
	int infoLogLength = 0;

	if (statusMacro == GL_COMPILE_STATUS) {
		glGetShaderiv(id, statusMacro, &result);
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	}
	else if (statusMacro == GL_LINK_STATUS) {
		glGetProgramiv(id, statusMacro, &result);
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	}
	
	if (infoLogLength > 0) {
		vector<char> errorMessage(infoLogLength + 1);
		if (statusMacro == GL_COMPILE_STATUS)
			glGetShaderInfoLog(id, infoLogLength, NULL, &errorMessage[0]);
		else if (statusMacro == GL_LINK_STATUS)
			glGetProgramInfoLog(id, infoLogLength, NULL, &errorMessage[0]);
		printf("%s\n", &errorMessage[0]);
	}
}

//Leitura, compilação e ligação dos shaders. 
GLuint loadShaders(string vShaderFile, string fShaderFile)
{
	//Criando os shaders
	GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Lendo os shaders de seus arquivos
	string vShaderCode = readShaderFile(vShaderFile);
	string fShaderCode = readShaderFile(fShaderFile);

	//Compilando vertex shader
	const char* vSourcePointer = vShaderCode.c_str();
	glShaderSource(vShaderID, 1, &vSourcePointer, NULL);
	glCompileShader(vShaderID);
	checkStatus(vShaderID, GL_COMPILE_STATUS);

	//Compilando fragment shader
	const char* fSourcePointer = fShaderCode.c_str();
	glShaderSource(fShaderID, 1, &fSourcePointer, NULL);
	glCompileShader(fShaderID);
	checkStatus(fShaderID, GL_COMPILE_STATUS);

	//Ligando o programa
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vShaderID);
	glAttachShader(programID, fShaderID);
	glLinkProgram(programID);
	checkStatus(programID, GL_LINK_STATUS);

	glDetachShader(programID, vShaderID);
	glDetachShader(programID, fShaderID);

	glDeleteShader(vShaderID);
	glDeleteShader(fShaderID);

	return programID;
}

void init()
{
	//Definir qual cor deve ser utilizada para "limpar" a janela.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Criando VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Criando VBOs
	glGenBuffers(2, vbo);

	//VBO para os vértices (posicao)
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * qtdVerts, verts, GL_STATIC_DRAW);
	
	//Habilitando o atributo 0, que serão as coordenadas dos nossos vertices.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//VBO para coordenadas de textura
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * qtdVerts, texCoords, GL_STATIC_DRAW);

	//Habilitando o atributo 1, que serão as coordenadas de textura dos vértices.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

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

	//Carregando shaders
	string vShaderFile = imgPath + "vShader.glsl";
	string fShaderFile = imgPath + "fShader.glsl";
	programID = loadShaders(vShaderFile, fShaderFile);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(programID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glUseProgram(0);
	
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
	glutInitWindowSize(1366, 768);

	//Criando janela com o título passado.
	glutCreateWindow("Textura");

	//Inicializando GLEW
	GLuint err = glewInit();
	if (err != GLEW_OK) {
		cerr << "Falha na inicializacao da GLEW" << endl;
		return 1;
	}

	//Callback para a função que será responsável pelos desenhos.
	glutDisplayFunc(display);

	//Função auxiliar para inicializar os estados da GL que desejarmos.
	init();

	//Essa função dá início ao loop de renderização.
	glutMainLoop();
	return 0;
}
