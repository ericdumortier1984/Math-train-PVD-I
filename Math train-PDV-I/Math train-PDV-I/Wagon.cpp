#include "Wagon.h"

Wagon::Wagon(int _number, Wagon* _next)
{
	// Inicializa los atributos del vag�n
	wagonNumber = _number;
	next = _next;
	InitWagon();
}

Wagon::~Wagon()
{
	// Libera la memoria de los objetos din�micos
	delete spriteWagon;
	delete textureWagon;
}

void Wagon::Draw(RenderWindow& _window)
{
	// Dibuja el sprite y el texto del vag�n en la ventana
	_window.draw(*spriteWagon);
	_window.draw(wagonText);
}

void Wagon::InitWagon()
{
	// Carga la textura y crea el sprite del vag�n
	textureWagon = new Texture;
	textureWagon->loadFromFile("Assets/Images/vagon.png");
	spriteWagon = new Sprite(*textureWagon);
	spriteWagon->setTexture(*textureWagon);
	spriteWagon->setScale(0.15f, 0.15f);
	spriteWagon->setPosition(wagonCoords);

	// Carga la fuente y crea el texto del n�mero del vag�n
	if (!wagonFont.loadFromFile("Assets/Fonts/ariblk.ttf"))
	{
		// Error al cargar la fuente
	}

	wagonText.setFont(wagonFont);
	// Establece la posici�n del texto en el centro del vag�n
	wagonText.setPosition(spriteWagon->getPosition().x + spriteWagon->getGlobalBounds().width / 2 - wagonText.getGlobalBounds().width / 2,
		spriteWagon->getPosition().y + spriteWagon->getGlobalBounds().height / 2 - wagonText.getGlobalBounds().height / 2);
	wagonText.setCharacterSize(22);
	wagonText.setFillColor(Color::Black);
	wagonText.setString(to_string(wagonNumber));
}

Sprite Wagon::GetSprite()
{
	// Devuelve el sprite del vag�n
	return *spriteWagon;
}

float Wagon::GetPositionX()
{
	// Devuelve la posici�n en X del vag�n
	return spriteWagon->getPosition().x;
}

void Wagon::SetPosition(Vector2f _wagonXY)
{
	// Establece la posici�n del vag�n y actualiza la posici�n del texto
	spriteWagon->setPosition(_wagonXY);
	wagonText.setPosition(spriteWagon->getPosition().x + spriteWagon->getGlobalBounds().width / 2 - wagonText.getGlobalBounds().width / 2,
		spriteWagon->getPosition().y + spriteWagon->getGlobalBounds().height / 2 - wagonText.getGlobalBounds().height / 2);
}


