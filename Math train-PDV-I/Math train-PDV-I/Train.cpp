#include "Train.h"

Train::Train() 
{
	// Inicializa las posiciones de los rieles y posicion de los vagones en el eje X
	rail_0 = 100.0;
	rail_1 = 200.0;
	rail_2 = 300.0;
	rail_3 = 400.0;
	rail_4 = 500.0;
	wagonPos = 50.f; 

	first = last = NULL; // Inicializa los punteros de la lista enlazada
	LoadList(); // Carga la lista de vagones
	InitTrain();// Inicializa la locomotora

	// Imprime en consola la cantidad de vagones y el n�mero del �ltimo vag�n (DEBUG)
	cout << "CANTIDAD DE VAGONES: " << GetWagonCant() << endl; 
	cout << "ULTIMO VAGON: " << GetLast() << endl << endl;
	
}

Train::~Train()
{
	// Elimina todos los vagones de la lista enlazada
	while (first != NULL) {
		Wagon* temp = first;
		first = first->next;
		delete temp;
	}
	// Libera la memoria de la textura y el sprite de la locomotora
	delete textureTrain;
	delete spriteTrain;
}

void Train::LoadList()
{
	cout << "[LOADLIST:OK]" << endl << endl;
	// Agrega 2 vagones a la lista
	for (int i = 0; i < 2; i++) 
	{
		randomNumberWagon = rand() % 9;
		cout << "VAGON NUMERO " << i << ": " << randomNumberWagon << endl; 
		Insert(randomNumberWagon);
	}
}

void Train::InitTrain()
{
	// Carga la textura de la locomotora
	textureTrain = new Texture;
	textureTrain->loadFromFile("Assets/Images/locomotora.png");
	// Crea el sprite de la locomotora
	spriteTrain = new Sprite(*textureTrain);
	spriteTrain->setTexture(*textureTrain);
	spriteTrain->setScale(0.15f, 0.15f);
	spriteTrain->setPosition(10, rail_0);
}


void Train::Insert(int _w)
{
	// Inserta un nuevo vag�n en la lista
	Wagon* ant;// Puntero al nodo anterior al que se va a insertar
	if ((first == NULL) || (first->wagonNumber > _w)) // Si la lista est� vac�a o el primer nodo tiene un n�mero mayor que el nuevo vag�n
	{
		first = new Wagon(_w, first); // Crea un nuevo nodo y lo hace el primer nodo de la lista
	}
	else
	{
		ant = first; // Inicializa el puntero al primer nodo
		while (ant->next && ant->next->wagonNumber <= _w) // Recorre la lista hasta encontrar la posici�n correcta para insertar el nuevo nodo
		{
			ant = ant->next; // Avanza al siguiente nodo
		}

		ant->next = new Wagon(_w, ant->next); // Crea un nuevo nodo con el n�mero del vag�n y lo inserta despu�s del nodo anterior
	}
}

void Train::EliminateNode(int _w) 
{
	// Elimina un vag�n de la lista
	Wagon* antNode, * aux; // Punteros al nodo anterior y al nodo actual
	aux = first; // Inicializa el puntero al primer nodo
	antNode = NULL; // Inicializa el puntero al nodo anterior en NULL

	while (aux && aux->wagonNumber < _w) // Recorre la lista hasta encontrar el nodo con el n�mero de vag�n buscado
	{
		antNode = aux; // Guarda el nodo anterior
		aux = aux->next; // Avanza al siguiente nodo
	}
	if (!aux || aux->wagonNumber != _w) // Si no se encontr� el nodo o el n�mero de vag�n no coincide
	{
		return; // Sale de la funci�n sin hacer nada
	}
	else
	{
		if (!antNode) // Si el nodo a eliminar es el primero de la lista
		{
			first = aux->next; // Actualiza el puntero al primer nodo de la lista
		}
		else
		{
			antNode->next = aux->next; // Actualiza los punteros del nodo anterior para omitir el nodo a eliminar
		}
		delete aux; // Libera la memoria del nodo eliminado
	}
}

void Train::Draw(RenderWindow& _window)
{
	// Dibuja la locomotora y los vagones
	last = first; // Inicializa el puntero al �ltimo nodo (�ltimo vag�n) con el primer nodo
	int index = 1; // �ndice para posicionar los vagones

	if (first) // Si la lista no est� vac�a
	{
		while (last->next) // Recorre la lista hasta llegar al �ltimo nodo
		{
			if (last) // Si el nodo actual es v�lido
			{
				index++; // Incrementa el �ndice
				last = last->next; // Avanza al siguiente nodo
				last->SetPosition({ spriteTrain->getPosition().x - 100.f * index, spriteTrain->getPosition().y }); // Establece la posici�n del vag�n
				last->Draw(_window); // Dibuja el vag�n
			}
		}
		first->SetPosition({ spriteTrain->getPosition().x - 100.f, spriteTrain->getPosition().y }); // Establece la posici�n del primer vag�n
		first->Draw(_window); // Dibuja el primer vag�n
	}
}

float Train::GetPosX()
{
	return spriteTrain->getPosition().x; // Obtiene la posici�n en X de la locomotora
}

float Train::GetPosY()
{
	return spriteTrain->getPosition().y; // Obtiene la posici�n en Y de la locomotora
}

void Train::Move(int _vel)
{
	
	float x, y;
	y = spriteTrain->getPosition().y;
	x = spriteTrain->getPosition().x;
	spriteTrain->setPosition(x + _vel, y); // Mueve la locomotora (x + _vel)

	// Cambia la posici�n de la locomotora a los diferentes rieles
	if ((x > 800 + spriteTrain->getGlobalBounds().width) && (y == rail_0))
	{
		spriteTrain->setPosition(-spriteTrain->getGlobalBounds().width, rail_1);
	}

	if ((x > 800 + spriteTrain->getGlobalBounds().width) && (y == rail_1))
	{
		spriteTrain->setPosition(-spriteTrain->getGlobalBounds().width, rail_2);
	}

	if ((x > 800 + spriteTrain->getGlobalBounds().width) && (y == rail_2))
	{
		spriteTrain->setPosition(-spriteTrain->getGlobalBounds().width, rail_3);
	}

	if ((x > 800 +spriteTrain->getGlobalBounds().width) && (y == rail_3))
	{
		spriteTrain->setPosition(-spriteTrain->getGlobalBounds().width, rail_4);
	}
}

Sprite Train::GetSprite()
{
	return *spriteTrain; // Obtiene el sprite de la locomotora
}

int Train::GetWagonCant()
{
	// Obtiene la cantidad de vagones
	if (first == NULL) // Si la lista est� vac�a
	{
		return 0; // Devuelve 0
	}

	int wCount = 0; // Contador de vagones
	last = first; // Inicializa el puntero al �ltimo nodo con el primer nodo

	while (last != NULL) // Recorre la lista hasta llegar al final
	{
		if (last) // Si el nodo actual es v�lido
		{
			last = last->next; // Avanza al siguiente nodo
		}
		wCount++; // Incrementa el contador de vagones
	}
	return wCount; // Devuelve la cantidad de vagones
}

int Train::GetLast()
{
	// Obtiene el n�mero del �ltimo vag�n
	last = first; // Inicializa el puntero al �ltimo nodo con el primer nodo

	if (first != NULL) // Si la lista no est� vac�a
	{
		while (last->next) // Recorre la lista hasta llegar al �ltimo nodo
		{
			if (last) // Si el nodo actual es v�lido
			{
				last = last->next; // Avanza al siguiente nodo
			}
		}
	}

	return last->wagonNumber; // Devuelve el n�mero del �ltimo vag�n
}