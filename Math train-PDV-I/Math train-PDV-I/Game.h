#pragma once
#include "Wagon.h"
#include "Train.h"
#include "AudioManager.h"

class Game
{
private:

	RenderWindow* wnd;  // Puntero a la ventana de renderizado
	Event* evt; // Puntero al evento

	// Sprites y texturas de fondo
	Sprite* spriteBackground;
	Texture* textureBackground;

	// Sprites y texturas de las v�as
	Sprite* spriteRail[5];
	Texture* textureRail;

	// Sprites y textura de los vagones
	Sprite* spriteWagon1;
	Sprite* spriteWagon2;
	Sprite* spriteWagon3;
	Sprite* spriteWagon4;
	Texture* textureWagons;

	Train* train; // Objeto del tren
	AudioManager audioManager; // Objeto para el manejo de audio

	// Sprite y textura de la caja de texto
	Sprite* spriteText;
	Texture* texturetext;

	Font font; // Fuente de texto

	// Objetos de texto
	Text textCounter;
	Text textCalculate;
	Text textAnswer;

	bool gameOver; // Bandera para indicar si el juego ha terminado

	// Variables para el manejo de la tasa de frames
	float fps;
	float frameTime;
	float time2;
	Time* time;
	Clock* clock;
	Clock counter;

	// Variables para el cron�metro
	float initTime;
	float finishTime;
	int seconds;
	bool timeUp;

	// Posiciones de los vagones
	float x1, x2, x3, x4; 
	float r0, r1, r2, r3, r4;

	// Banderas de colisi�n
	bool isColisionate; 
	bool colition1, colition2, colition3, colition4; 

	// Variables para el c�lculo
	int n1, n2, n3;
	string playerInput; 
	int answer; 
	int solution; 

	// Banderas de entrada, inserci�n, eliminaci�n y victoria
	bool input;
	bool insert; 
	bool destroy; 
	bool victory; 

public:

	Game(); // Constructor
	~Game(); // Deconstructor

	void InitGame(); // Funci�n para inicializar la clase Game
	void DoEvents(); // Funci�n para manejar los eventos del juego
	void Loop(); // Funci�n principal del juego
	void DrawGame(); // Funci�n para dibujar los elementos del juego
	void CheckColitions(); // Funci�n para verificar las colisiones
	void GameOver(); // Funci�n para manejar el final del juego
	void UpdateCounter(); // Funci�n para actualizar el cron�metro
	void MoveTrain(); // Funci�n para mover el tren
	void ShowCalculate();  // Funci�n para mostrar el c�lculo
	void InitRandom(); // Funci�n para inicializar los n�meros aleatorios
};