#pragma once
#include "Wagon.h"

typedef Wagon* pNode; // Definici�n de un tipo de puntero a un nodo Wagon

class Train
{
private:

	Wagon* first; // Puntero al primer nodo de la lista enlazada
	Wagon* last; // Puntero al �ltimo nodo de la lista enlazada
	Sprite* spriteTrain; // Sprite de la locomotora
	Texture* textureTrain; // Textura de la locomotora
	float rail_0, rail_1, rail_2, rail_3, rail_4; // Posiciones de los rieles
	int randomNumberWagon; // N�mero aleatorio para los vagones

public:

	Train(); // Constructor
	~Train(); // Deconstructor

	Sprite GetSprite(); // Obtiene el sprite de la locomotora
	float GetPosX(); // Obtiene la posici�n en X de la locomotora
	float GetPosY(); // Obtiene la posici�n en Y de la locomotora
	void LoadList(); // Carga la lista de vagones
	void Move(int _vel); // Mueve la locomotora
	void InitTrain();  // Inicializa la locomotora
	void Draw(RenderWindow& _window); // Dibuja la locomotora y los vagones
	int GetLast(); // Obtiene el n�mero del �ltimo vag�n
	void Insert(int _w); // Inserta un vag�n en la lista
	void EliminateNode(int _w); // Elimina un nodo de la lista
	int GetWagonCant(); // Obtiene la cantidad de vagones
};