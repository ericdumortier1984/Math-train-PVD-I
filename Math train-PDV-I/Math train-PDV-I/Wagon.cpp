#include "Wagon.h"

Wagon::Wagon(int _number, Wagon* _next)
{
	// Inicializa los atributos del vagón
	wagonNumber = _number;
	next = _next;
	InitWagon();
}

Wagon::~Wagon()
{
	// Libera la memoria de los objetos dinámicos
	delete spriteWagon;
	delete textureWagon;
}

void Wagon::Draw(RenderWindow& _window)
{
	// Dibuja el sprite y el texto del vagón en la ventana
	_window.draw(*spriteWagon);
	_window.draw(wagonText);
}

void Wagon::InitWagon()
{
	// Carga la textura y crea el sprite del vagón
	textureWagon = new Texture;
	textureWagon->loadFromFile("Assets/Images/vagon.png");
	spriteWagon = new Sprite(*textureWagon);
	spriteWagon->setTexture(*textureWagon);
	spriteWagon->setScale(0.15f, 0.15f);
	spriteWagon->setPosition(wagonCoords);

	// Carga la fuente y crea el texto del número del vagón
	if (!wagonFont.loadFromFile("Assets/Fonts/ariblk.ttf"))
	{
		// Error al cargar la fuente
	}

	wagonText.setFont(wagonFont);
	// Establece la posición del texto en el centro del vagón
	wagonText.setPosition(spriteWagon->getPosition().x + spriteWagon->getGlobalBounds().width / 2 - wagonText.getGlobalBounds().width / 2,
		spriteWagon->getPosition().y + spriteWagon->getGlobalBounds().height / 2 - wagonText.getGlobalBounds().height / 2);
	wagonText.setCharacterSize(22);
	wagonText.setFillColor(Color::Black);
	wagonText.setString(to_string(wagonNumber));
}

Sprite Wagon::GetSprite()
{
	// Devuelve el sprite del vagón
	return *spriteWagon;
}

float Wagon::GetPositionX()
{
	// Devuelve la posición en X del vagón
	return spriteWagon->getPosition().x;
}

void Wagon::SetPosition(Vector2f _wagonXY)
{
	// Establece la posición del vagón y actualiza la posición del texto
	spriteWagon->setPosition(_wagonXY);
	wagonText.setPosition(spriteWagon->getPosition().x + spriteWagon->getGlobalBounds().width / 2 - wagonText.getGlobalBounds().width / 2,
		spriteWagon->getPosition().y + spriteWagon->getGlobalBounds().height / 2 - wagonText.getGlobalBounds().height / 2);
}


