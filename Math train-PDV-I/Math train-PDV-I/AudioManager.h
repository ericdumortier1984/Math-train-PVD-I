#pragma once
#include "Includes&usings.h"

class AudioManager
{
private:
    // Declaración de los objetos de sonido y música
    Sound whistleSound;
    Sound explosionSound;
    Sound gameOverSound;
    Sound victorySound;

    SoundBuffer whistleBuffer;
    SoundBuffer explosionBuffer;
    SoundBuffer gameOverBuffer;
    SoundBuffer victorBuffer;

    Music music;

    bool isLoopEnabled; // Bandera para controlar el bucle de la música

public:

    void InitAudio(); // Función para inicializar los recursos de audio

    // Funciones para reproducir los diferentes sonidos
    void PlayWhistle();
    void PlayExplosion();
    void PlayGameOver();
    void PlayVictory();

    // Funciones para controlar la reproducción de la música
    void PlayMusic();
    void StopMusic();

    void SetLoopEnabled(bool enabled); // Función para establecer si la música se debe reproducir en bucle
};