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

	// Sprites y texturas de las vías
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

	// Variables para el cronómetro
	float initTime;
	float finishTime;
	int seconds;
	bool timeUp;

	// Posiciones de los vagones
	float x1, x2, x3, x4; 
	float r0, r1, r2, r3, r4;

	// Banderas de colisión
	bool isColisionate; 
	bool colition1, colition2, colition3, colition4; 

	// Variables para el cálculo
	int n1, n2, n3;
	string playerInput; 
	int answer; 
	int solution; 

	// Banderas de entrada, inserción, eliminación y victoria
	bool input;
	bool insert; 
	bool destroy; 
	bool victory; 

public:

	Game(); // Constructor
	~Game(); // Deconstructor

	void InitGame(); // Función para inicializar la clase Game
	void DoEvents(); // Función para manejar los eventos del juego
	void Loop(); // Función principal del juego
	void DrawGame(); // Función para dibujar los elementos del juego
	void CheckColitions(); // Función para verificar las colisiones
	void GameOver(); // Función para manejar el final del juego
	void UpdateCounter(); // Función para actualizar el cronómetro
	void MoveTrain(); // Función para mover el tren
	void ShowCalculate();  // Función para mostrar el cálculo
	void InitRandom(); // Función para inicializar los números aleatorios
};