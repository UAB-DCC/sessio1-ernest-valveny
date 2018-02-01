// main.cpp: Exemple d'�s de la llibreria gr�fica on es llegeix un fitxer d'entrada es mou un mao
// com s'indica al fitxer i s'escriu el recorregut realitzat en un fitxer.
//

//Definicions amb la variable d'activaci� de la llibreria gr�fica, __viz_graphics__
#include "Definitions.h"

//Includes de les llibreries gr�fiques
#ifdef GRAPHICS
	#define SDL_MAIN_HANDLED 
	#include "lib\libreria.h"
	#include <windows.h>
#endif 

#include <iostream>
#include <fstream>

//Mida del taulell
const int MIDA_TAULELL = 480;

//Numero de caselles i moviments
const int CASELLES = 8;
const int MOVIMENTS = 7;

//Funci� per la lectura de la posici� inicial del ma�
void readInitialPosition(const std::string& filename, int *X, int *Y)
{
	std::ifstream file;
	file.open(filename.c_str()); //filename.c_str
	if (file.is_open())
	{
		file >> *X >> *Y;
		file.close();
	}
	else
	{
		std::cout << "error: file not found" << std::endl;
	}
}

//Funci� per a guardar el fitxer de sortida amb els moviments
void writeExitPath(const std::string& filename, int X[], int Y[], int lengthMov)
{
	std::ofstream fileOut;
	fileOut.open(filename.c_str());
	if (fileOut.is_open())
	{
		for (int i = 0; i < lengthMov; i++)
		{
			fileOut << X[i] << " " << Y[i] << std::endl;
		}
		fileOut.close();
	}
	else
	{
		std::cout << "error: file not found" << std::endl;
	}
}



int main(int argc, char* argv[])
{
	//Arxius per llegir i escriure per par�metre
	if (argc == 3) 
	{

		#ifdef GRAPHICS
			// Declaraci� i instanciaci� de l�objecte de la classe Screen amb un tamany determinat
			Screen pantalla = Screen(MIDA_TAULELL, MIDA_TAULELL);

			// Inicialitzaci� de la variable �mao� amb el gr�fic �mao.png� 
			Sprite mao = Sprite("mao.png");
			// Inicialitzaci� de la variable �cbuida� amb el gr�fic �cnegre.png� 
			Sprite cbuida = Sprite("cnegre.png");
		#endif

		//Declaraci� variables per la posici� del ma�
		int posX = 0;
		int	posY = 0;
		readInitialPosition(argv[1], &posX, &posY); 
		
		//Inicialitzaci� dels vectors per guardar el cam� X,Y
		int pathX[MOVIMENTS];
		int pathY[MOVIMENTS];

		#if GRAPHICS
			//Pantalla gr�fica
			pantalla.show();
			//Dibuixa el ma�
			mao.draw(posX * mao.getScaleY(), posY * mao.getScaleX()); //(columna/fila)

			//Actualitzaci� de la pantalla				
			pantalla.update();
			Sleep(500);
		#endif

		//guardem posici� inicial
		pathX[0]=posX;
		pathY[0]=posY;
		
		//Bucle principal del joc
		do {
			#if GRAPHICS
				//Dibuix de la nova posici� del ma� i casella buida a l'anterior posici�
				cbuida.draw(posX * cbuida.getScaleX(), (posY)* cbuida.getScaleX());
				mao.draw(posX * mao.getScaleX(), (posY + 1) * mao.getScaleX());

				pantalla.update();
				Sleep(500);
			#endif

			//Actualitza i guarda la nova posici� 
			pathX[posY]=posX;
			pathY[posY]=posY;
			posY++;

		} while (posY <= MOVIMENTS-1);

		//Guardem els punts X,Y del cam� seguit
		writeExitPath(argv[2], pathX, pathY, MOVIMENTS); 

		#if GRAPHICS
			//Instruccio necesaria per poder finalitzar els gr�fics de la pantalla
			pantalla.~Screen();
		#endif
	}
	return 0;
}
