//Definicions amb la variable d'activaci� de la llibreria gr�fica, GRAPHICS
#include "Definitions.h"


//Includes de les llibreries gr�fiques
#ifdef GRAPHICS
#define SDL_MAIN_HANDLED
#include "lib\libreria.h"
#include <windows.h>
#endif

//Mida del taulell
const int MIDA_TOTAL = 480;



int main(int argc, char* argv[])
{
#ifdef GRAPHICS
	// Declaraci� de l�objecte de la classe Screen amb una mida determinada
	Screen pantalla = Screen(MIDA_TOTAL, MIDA_TOTAL);

	// Inicialitzaci� de la variable �mao� amb el gr�fic �mao.png�
	//imatge guardada al directori de treball del projecte
	Sprite mao = Sprite("mao.png");

	//Mostra la pantalla gr�fica
	pantalla.show();

	//Dibuixa el ma� dalt a l'esquerra de la pantalla
	mao.draw(0, 0); //(columna/fila)

	//Actualitzaci� de la pantalla                      	
	pantalla.update();
	
	//Espera 5s
	Sleep(5000);

	//Destrueix la pantalla tancant-la degudament
	pantalla.~Screen();
#endif

	return 0;
}

