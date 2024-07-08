#pragma once
#include "Includes&usings.h"

class Wagon
{
private:

	int wagonNumber; // N�mero del vag�n
	Wagon* next; // Puntero al siguiente vag�n en la lista
	Sprite* spriteWagon; // Sprite del vag�n
	Texture* textureWagon; // Textura del vag�n
	Vector2f wagonCoords; // Coordenadas del vag�n
	Font wagonFont; // Fuente del texto del vag�n
	Text wagonText; // Texto del n�mero del vag�n

public:

	friend class Train; // Declaraci�n de la clase Train como amiga, para poder acceder a los atributos privados
	Wagon(int _number, Wagon* _next = NULL);   // Constructor
	~Wagon(); // Deconstructor

	Sprite GetSprite(); // Obtiene el sprite del vag�n
	void Draw(RenderWindow& _window);// Dibuja el vag�n en la ventana de renderizado
	void InitWagon(); // Inicializa el vag�n
	void SetPosition(Vector2f _wagonXY); // Establece la posici�n del vag�n
	float GetPositionX(); // Obtiene la posici�n en X del vag�n
};