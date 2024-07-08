#pragma once
#include "Includes&usings.h"

class Wagon
{
private:

	int wagonNumber; // Número del vagón
	Wagon* next; // Puntero al siguiente vagón en la lista
	Sprite* spriteWagon; // Sprite del vagón
	Texture* textureWagon; // Textura del vagón
	Vector2f wagonCoords; // Coordenadas del vagón
	Font wagonFont; // Fuente del texto del vagón
	Text wagonText; // Texto del número del vagón

public:

	friend class Train; // Declaración de la clase Train como amiga, para poder acceder a los atributos privados
	Wagon(int _number, Wagon* _next = NULL);   // Constructor
	~Wagon(); // Deconstructor

	Sprite GetSprite(); // Obtiene el sprite del vagón
	void Draw(RenderWindow& _window);// Dibuja el vagón en la ventana de renderizado
	void InitWagon(); // Inicializa el vagón
	void SetPosition(Vector2f _wagonXY); // Establece la posición del vagón
	float GetPositionX(); // Obtiene la posición en X del vagón
};