#include "Game.h"

Game::Game()
{

	fps = 60.f; // Establecer la tasa de frames a 60 fps
	wnd = new RenderWindow(VideoMode(800, 600), "MATH TRAIN"); // Crear la ventana de renderizado con un tamaño de 800x600 y el título "MATH TRAIN"
	wnd->setFramerateLimit(fps); // Establecer el límite de tasa de frames a 60 fps
	cout << "[WINDOW:OK]" << endl;

	evt = new Event; // Crear un nuevo evento
	clock = new Clock; // Crear un nuevo reloj
	time = new Time; // Crear un nuevo objeto de tiempo
	cout << "[TIMER:OK]" << endl;
	audioManager.InitAudio(); // Inicializar el audio
	cout << "[AUDIO:OK]" << endl;

	train = new Train(); // Crear un nuevo tren
	
	// Establecer los valores iniciales del cronómetro
	timeUp = false;
	initTime = 5.f;
	finishTime = 0.f;
	seconds = 5;

	// Establecer las posiciones iniciales de las vías
	r0 = 100.0;
	r1 = 200.0;
	r2 = 300.0;
	r3 = 400.0;
	r4 = 500.0;

	// Establecer en random las posiciones iniciales de los vagones
	x1 = rand() % 600 + 100;
	x2 = rand() % 600 + 100;
	x3 = rand() % 600 + 100;
	x4 = rand() % 400 + 100;

	// Inicializar las banderas de colisión, entrada, inserción, eliminación y victoria
	isColisionate = false;
	input = false;
	insert = false;
	destroy = false;
	victory = true;
	gameOver = false;

	colition1, colition2, colition3, colition4 = false; // Inicializar las banderas de colisión individuales

	// Establecer los valores iniciales de los números aleatorios, respuesta y solución
	n1 = rand() % 9;
	n2 = rand() % 9;
	n3 = rand() % 9;
	answer = -1;
	solution = -1;
	playerInput = "";

	InitGame(); // Inicializar el juego
	Loop(); // Ejecutar el bucle principal del juego
}

void Game::InitGame()
{

	wnd->setMouseCursorVisible(false); // Ocultar el cursor del mouse

	// Cargar y configurar la textura y el sprite de fondo
	textureBackground = new Texture;
	textureBackground->loadFromFile("Assets/Images/fondo.png");
	spriteBackground = new Sprite(*textureBackground);
	spriteBackground->setPosition(Vector2f(-20, 0));

	// Cargar y configurar la textura y los sprites de las vías
	textureRail = new Texture;
	textureRail->loadFromFile("Assets/Images/regla.png");
	for (int i = 0; i < 5; i++)
	{
		spriteRail[i] = new Sprite(*textureRail);
		spriteRail[i]->setScale(1.f, 0.25f);
		spriteRail[i]->setPosition(300, r0 + i * 100);
	}

	// Cargar y configurar la textura y el sprite de la caja de texto
	texturetext = new Texture;
	texturetext->loadFromFile("Assets/Images/text_box.png");
	spriteText = new Sprite(*texturetext);
	spriteText->setPosition(250, 0);

	// Cargar y configurar la textura de los vagones
	textureWagons = new Texture;
	textureWagons->loadFromFile("Assets/Images/vagon.png");

	spriteWagon1 = new Sprite(*textureWagons);
	spriteWagon1->setScale(0.15, 0.15);
	spriteWagon1->setPosition(x1, r1 - 50);

	spriteWagon2 = new Sprite(*textureWagons);
	spriteWagon2->setScale(0.15, 0.15);
	spriteWagon2->setPosition(x2, r2 - 50);

	spriteWagon3 = new Sprite(*textureWagons);
	spriteWagon3->setScale(0.15, 0.15);
	spriteWagon3->setPosition(x3, r3 - 50);

	spriteWagon4 = new Sprite(*textureWagons);
	spriteWagon4->setScale(0.15, 0.15);
	spriteWagon4->setPosition(x4, r4 - 50);

	// Cargar la fuente de texto
	if (!font.loadFromFile("Assets/Fonts/ARJULIAN.ttf"))
	{
		// Error al cargar la fuente
	}
	
	// Configurar el texto del cronómetro
	textCounter.setFont(font);
	textCounter.setPosition(600, 30);
	textCounter.setCharacterSize(28);
	textCounter.setFillColor(Color::Green);

	// Configurar el texto del cálculo
	textCalculate.setFont(font);
	textCalculate.setPosition(310, 80);
	textCalculate.setCharacterSize(16);

	// Configurar el texto de la respuesta
	textAnswer.setFont(font);
	textAnswer.setPosition(405, 80);
	textAnswer.setCharacterSize(16);
}

void Game::DoEvents()
{
	
	while (wnd->pollEvent(*evt)) // Procesar los eventos de la ventana
	{
		switch (evt->type)
		{
		case Event::Closed:
			exit(1); // Cerrar la aplicación
			break;

		case Event::TextEntered:
			// Procesar la entrada de texto
			if ((isColisionate) && (!gameOver) && (seconds > 0)) // Verificar si se ha producido una colisión, el juego no ha terminado y aún queda tiempo
			{
				if ((evt->text.unicode >= 48) && (evt->text.unicode <= 57)) // Verificar si el carácter (código ASCII entre 48 y 57) ingresado es un dígito (entre 0 y 9)
				{
					playerInput += evt->text.unicode; // Agregar el número ingresado al string de entrada
				}
				else if (evt->text.unicode == 8) // Verificar si se presionó la tecla de retroceso por si el player lo desea (código ASCII 8)
				{
					if (!playerInput.empty()) // Verificar si el string de entrada no está vacío
					{
						playerInput.pop_back(); // Eliminar el último carácter del string de entrada
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Enter)) 
				{
					// Procesar la entrada cuando se presiona Enter
					if (playerInput.empty()) // Si el string de entrada está vacío
					{
						// Establecer la respuesta en 0 y marcar la entrada como válida
						answer = 0;
						input = true;
					}

					else // Si el string de entrada no está vacío
					{
						// Convertir el string de entrada a entero y establecer la respuesta
						cout << "RESPUESTA: " << playerInput << endl; 
						answer = stoi(playerInput); 
						input = true;
					}
				}
			}
			break;

		case Event::KeyPressed:
			// Procesar la entrada de teclas
			if (Keyboard::isKeyPressed(Keyboard::Escape)) 
			{
				exit(1); // Cerrar la aplicación
			}
			break;
		}
	}
}

void Game::MoveTrain()
{

	int velocity = 3; // Establecer la velocidad del tren

	if (!gameOver) // Verificar si el juego no ha terminado
	{
		if ((!input) && (isColisionate)) // Si no hay entrada y hay una colisión
		{
			if (seconds > 0) // Si aún queda tiempo
			{
				train->Move(0); // Detener el tren
			}
			else if (seconds < 0) // Si no queda tiempo
			{
				train->Move(velocity); // Mover el tren a la velocidad establecida
			}
		}

		if ((input) && (isColisionate)) // Si hay entrada y hay una colisión
		{
			train->Move(velocity); // Mover el tren a la velocidad establecida
		}

		if ((!input) && (!isColisionate)) // Si no hay entrada y no hay colisión
		{
			train->Move(velocity); // Mover el tren a la velocidad establecida
		}
	}

	else 
	{
		train->Move(0); // Si el juego ha terminado, detener el tren
	}
}

void Game::CheckColitions()
{
	// Verificar si el tren colisiona con algún vagón
	if ((train->GetSprite().getGlobalBounds().intersects(spriteWagon1->getGlobalBounds())) ||
		(train->GetSprite().getGlobalBounds().intersects(spriteWagon2->getGlobalBounds())) ||
		(train->GetSprite().getGlobalBounds().intersects(spriteWagon3->getGlobalBounds())) ||
		(train->GetSprite().getGlobalBounds().intersects(spriteWagon4->getGlobalBounds())))
	{
		// Establecer la bandera de colisión a true y mostrar el cálculo
		isColisionate = true;
		ShowCalculate();
	}
	else
	{
		// Establecer la bandera de colisión a false y restablecer las banderas de entrada, inserción y eliminación
		isColisionate = false;
		input = false;
		insert = false; 
		destroy = false;
		playerInput = "";
	}

	if (train->GetSprite().getGlobalBounds().intersects(spriteWagon1->getGlobalBounds())) // Verificar si el tren colisiona con cada vagón individualmente
	{
		if ((destroy) || (insert)) // Si se ha solicitado la eliminación o inserción 
		{
			spriteWagon1->setColor(Color::Transparent); // Hacer que el vagón sea transparente
		}
	}

	if (train->GetSprite().getGlobalBounds().intersects(spriteWagon2->getGlobalBounds()))
	{
		if ((destroy) || (insert))
		{
			spriteWagon2->setColor(Color::Transparent); // Hacer que el vagón sea transparente
		}
	}

	if (train->GetSprite().getGlobalBounds().intersects(spriteWagon3->getGlobalBounds()))
	{
		if ((destroy) || (insert))
		{
			spriteWagon3->setColor(Color::Transparent); // Hacer que el vagón sea transparente
		}
	}

	if (train->GetSprite().getGlobalBounds().intersects(spriteWagon4->getGlobalBounds()))
	{
		if ((destroy) || (insert))
		{
			spriteWagon4->setColor(Color::Transparent); // Hacer que el vagón sea transparente
		}
	}
}

void Game::GameOver()
{

	if ((gameOver) && (!victory)) // Si el juego ha terminado y no se ha ganado
	{
		if (!timeUp) // Si no se ha activado el tiempo agotado
		{
			audioManager.PlayGameOver(); // Reproducir el sonido de "Game Over"
			timeUp = true; // Establecer la bandera de tiempo agotado a true
		}
	}

	if (!gameOver) // Si el juego no ha terminado
	{
		if ((train->GetPosX() > 530) && (train->GetPosY() == 450)) // Si el tren ha llegado a la manzana
		{   
			audioManager.SetLoopEnabled(false); // Establecer el loop de la musica a false
			audioManager.StopMusic(); // Detener la música
			audioManager.PlayVictory(); // Reproducir el sonido de victoria
			victory = true; // Establecer la bandera de victoria a true
			textCounter.setPosition(Vector2f(550.0, 30.0));
			textCounter.setFillColor(Color::Green); // Cambiar el color contador
			textCounter.setString("YOU WIN!!!"); // Cambiar el texto del contador
			gameOver = true; // Establecer la bandera de "Game Over" a true
		}
	}

	if ((isColisionate) && (!gameOver)) // Si hay una colisión y el juego no ha terminado
	{
		if (seconds > 0) // Si aún queda tiempo
		{
			if ((input) & (solution == answer)) // Si hay entrada y la respuesta es correcta
			{
				textCounter.setFillColor(Color::Green); // Establecer el color del contador a verde
				textCounter.setString("GREAT!"); // Establecer el texto a GREAT!

				if (!insert)
				{
					train->Insert(answer); // Insertar el vagón
					audioManager.PlayWhistle(); // Reproducir campanita
					cout << "EL NUEVO ULTIMO VAGON ES: " << train->GetLast() << endl; // Establecer el nuevo ultimo vagon
					cout << "CANTIDAD DE VAGONES AHORA: " << train->GetWagonCant() << endl << endl; // Establecer la nueva cantidad de vagones
					insert = true;
				}
				playerInput = "";
			}

			if ((input) & (solution != answer)) // Si hay entrada y la respuesta es incorrecta
			{
				textCounter.setFillColor(Color::Red); // Establecer el color del contador a rojo
				textCounter.setString("NOP!"); // Establecer el texto a NOP!

				if ((!destroy) && (train->GetWagonCant() > 0)) // Si no se destruyó y si la cantidad de vagones es mayor a 0
				{
					train->EliminateNode(train->GetLast()); // Eliminar el último vagón
					audioManager.PlayExplosion(); // Reproducir el sonido de explosión
					cout << "CANTIDAD DE VAGONES AHORA: " << train->GetWagonCant() << endl << endl; // Establecer la nueva cantidad de vagones
					destroy = true;
				}
				playerInput = "";

				if ((!destroy) && (train->GetWagonCant() == 0)) // Si no se destruyó y si la cantidad de vagones es igual a 0
				{
					audioManager.PlayExplosion(); // Reproducir el sonido de explosión
					cout << "CANTIDAD DE VAGONES AHORA: " << train->GetWagonCant() << endl << endl; // Establecer la nueva cantidad de vagones
					audioManager.SetLoopEnabled(false); // Establecer el loop de la musica a false
					audioManager.StopMusic(); // Detener la musica
					textCounter.setPosition(Vector2f(550.0, 30.0));
					textCounter.setFillColor(Color::Red); // Establecer el texto de el contador a rojo
					textCounter.setString("NEXT TIME!"); // Establecer el texto del contador como derrota
					victory = false;
					destroy = true;
					gameOver = true;
				}
				playerInput = "";
			}
		}
		else if (seconds < 0)  // Si no queda tiempo
		{
			if ((!destroy) && (train->GetWagonCant() > 0)) // Si no se destruyó y si la cantidad de vagones es mayor a 0
			{
				train->EliminateNode(train->GetLast()); // Eliminar el último vagón
				audioManager.PlayExplosion(); // Reproducir el sonido de explosión
				cout << "CANTIDAD DE VAGONES AHORA: " << train->GetWagonCant() << endl << endl; // Establecer la nueva cantidad de vagones
				destroy = true;
			}

			if ((!destroy) && (train->GetWagonCant() == 0)) // Si no se destruyó y si la cantidad de vagones es igual a 0
			{
				audioManager.PlayExplosion(); // Reproducir el sonido de explosión
				cout << "CANTIDAD DE VAGONES AHORA: " << train->GetWagonCant() << endl << endl; // Establecer la nueva cantidad de vagones
				audioManager.SetLoopEnabled(false); // Establecer el loop de la musica a false
				audioManager.StopMusic(); // Detener la musica
				textCounter.setPosition(Vector2f(550.0, 30.0));
				textCounter.setFillColor(Color::Red); // Establecer el texto de el contador a rojo
				textCounter.setString("NEXT TIME!"); // Establecer el texto del contador como derrota
				victory = false;
				gameOver = true;
				destroy = true;
			}
		}
	}
}

void Game::UpdateCounter()
{
	
	if (!isColisionate) // Si no hay colisión
	{
		textCounter.setFillColor(Color::White); // Establecer el color del contador a amarillo
		counter.restart(); // Reiniciar el contador
		seconds = 5; // Establecer los segundos a 5
	}

	if ((!gameOver) && (isColisionate)) // Si el juego no ha terminado y hay una colisión
	{
		finishTime = counter.getElapsedTime().asSeconds(); // Obtener el tiempo transcurrido desde que se inició el contador
		seconds = (int)(initTime - finishTime); // Calcular los segundos restantes restando el tiempo transcurrido del tiempo inicial

		if (seconds > 0) // Si aún quedan segundos
		{
			// Formatear el texto del contador con los segundos restantes
			char buffer[20];
			sprintf_s(buffer, "TIME: %i", seconds);
			textCounter.setString(buffer);
		}

		if (seconds == 0) // Si no quedan segundos
		{
			// Formatear el texto del contador con los segundos restantes y establecer el color a rojo
			char buffer[20];
			sprintf_s(buffer, "TIME: %i", seconds);
			textCounter.setString(buffer);
			textCounter.setFillColor(Color::Red);
		}
	}
}

void Game::ShowCalculate()
{

	textCalculate.setFillColor(Color::Black); // Establecer el color del texto del cálculo a negro
	textCalculate.setString(to_string(n1) + " + " + to_string(n2) + " + " + to_string(n3) + " = "); // Establecer el texto del cálculo con los números aleatorios
	solution = n1 + n2 + n3; // Calcular la solución sumando los números aleatorios
	textAnswer.setFillColor(Color::Black); // Establecer el color del texto de la respuesta a negro
	textAnswer.setString(playerInput); // Establecer el texto de la respuesta con el input del jugador
}

void Game::InitRandom()
{
	
	if (!isColisionate) // Si no hay colisión
	{
		// Generar números aleatorios entre 0 y 8 para n1, n2 y n3
		n1 = rand() % 9;
		n2 = rand() % 9;
		n3 = rand() % 9;
	}
}

void Game::Loop()
{
	
	while (wnd->isOpen()) // Mientras la ventana esté abierta
	{
		*time = clock->getElapsedTime(); // Obtener el tiempo transcurrido desde el inicio del juego

		if (time2 + frameTime < time->asSeconds()) // Si ha transcurrido el tiempo suficiente para una nueva iteración
		{
			time2 = time->asSeconds(); // Actualizar el tiempo de la última iteración
			UpdateCounter();  // Actualizar el contador
			wnd->clear(Color::Black); // Limpiar la ventana
			DoEvents(); // Procesar eventos
			MoveTrain(); // Mover el tren
			CheckColitions(); // Comprobar colisiones
			InitRandom(); // Inicializar los números aleatorios
			GameOver(); // Comprobar si el juego ha terminado
			DrawGame(); // Dibujar el juego
			wnd->display(); // Mostrar la ventana
		}
	}
}

void Game::DrawGame()
{
	// Dibujar el fondo
	wnd->draw(*spriteBackground);

	// Dibujar las vías
	for (int i = 0; i < 5; i++)
	{
		if (i == 4) // Si es la última vía
		{
			spriteRail[i]->setScale(0.75f, 0.25f); // Establecer al 0.75 del tamaño en x
		}
		spriteRail[i]->setPosition(0, r0 + i * 100);
		wnd->draw(*spriteRail[i]);
	}

	// Dibujar los vagones del tren
	train->Draw(*wnd);
	wnd->draw(*spriteWagon1);
	wnd->draw(*spriteWagon2);
	wnd->draw(*spriteWagon3);
	wnd->draw(*spriteWagon4);

	// Si el juego no ha terminado, dibujar el tren
	if (!gameOver)
	{
		wnd->draw(train->GetSprite());
	}

	// Si el juego ha terminado y se ha ganado, dibujar el tren y el texto del contador en verde
	else if ((gameOver) && (victory))
	{
		wnd->draw(train->GetSprite());
		textCounter.setFillColor(Color::Green);
		wnd->draw(textCounter);
	}

	// Si hay una colisión y el juego no ha terminado, dibujar el texto del cálculo y la respuesta
	if ((isColisionate) && (!gameOver))
	{
		wnd->draw(*spriteText);
		wnd->draw(textCalculate);
		wnd->draw(textAnswer);
	}

	// Si hay una colisión, dibujar el contador
	if (isColisionate)
	{
		wnd->draw(textCounter);
	}
}

Game::~Game()
{
	// Liberar los recursos dinámicos
	delete wnd;
	delete evt;
	delete clock;
	delete time;
	delete train;
	delete spriteBackground;
	delete textureBackground;
	for (int i = 0; i < 5; i++)
	{
		delete spriteRail[i];
	}
	delete textureRail;
	delete spriteText;
	delete texturetext;
	delete spriteWagon1;
	delete spriteWagon2;
	delete spriteWagon3;
	delete spriteWagon4;
	delete textureWagons;
}