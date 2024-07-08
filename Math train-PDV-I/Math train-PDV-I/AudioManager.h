#pragma once
#include "Includes&usings.h"

class AudioManager
{
private:
    // Declaraci�n de los objetos de sonido y m�sica
    Sound whistleSound;
    Sound explosionSound;
    Sound gameOverSound;
    Sound victorySound;

    SoundBuffer whistleBuffer;
    SoundBuffer explosionBuffer;
    SoundBuffer gameOverBuffer;
    SoundBuffer victorBuffer;

    Music music;

    bool isLoopEnabled; // Bandera para controlar el bucle de la m�sica

public:

    void InitAudio(); // Funci�n para inicializar los recursos de audio

    // Funciones para reproducir los diferentes sonidos
    void PlayWhistle();
    void PlayExplosion();
    void PlayGameOver();
    void PlayVictory();

    // Funciones para controlar la reproducci�n de la m�sica
    void PlayMusic();
    void StopMusic();

    void SetLoopEnabled(bool enabled); // Funci�n para establecer si la m�sica se debe reproducir en bucle
};