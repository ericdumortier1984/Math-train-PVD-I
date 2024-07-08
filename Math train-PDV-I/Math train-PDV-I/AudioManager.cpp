#include "AudioManager.h"

void AudioManager::InitAudio()
{
    // Cargar los archivos de sonido
    if (!whistleBuffer.loadFromFile("Assets/Sounds/bocina.ogg"))
    {
        // Error al cargar el archivo de silbato
    }
    whistleSound.setBuffer(whistleBuffer);

    if (!victorBuffer.loadFromFile("Assets/Sounds/level_win.ogg"))
    {
        // Error al cargar el archivo de victoria
    }
    victorySound.setBuffer(victorBuffer);

    if (!gameOverBuffer.loadFromFile("Assets/Sounds/game_over.ogg"))
    {
        // Error al cargar el archivo de game over
    }
    gameOverSound.setBuffer(gameOverBuffer);

    if (!explosionBuffer.loadFromFile("Assets/Sounds/explosion.ogg"))
    {
        // Error al cargar el archivo de explosión
    }
    explosionSound.setBuffer(explosionBuffer);

    // Cargar y reproducir la música del juego
    if (!music.openFromFile("Assets/Sounds/swing_train.ogg"))
    {
        // Error al cargar el archivo de música
    }
    isLoopEnabled = true;
    music.setLoop(isLoopEnabled);
    music.setVolume(50);
    music.play();
}

void AudioManager::PlayWhistle()
{
    whistleSound.play();
}

void AudioManager::PlayExplosion()
{
    explosionSound.play();
}

void AudioManager::PlayGameOver()
{
    gameOverSound.play();
}

void AudioManager::PlayVictory()
{
    victorySound.play();
}

void AudioManager::PlayMusic()
{
    music.play();
}

void AudioManager::StopMusic()
{
    music.stop();
}

void AudioManager::SetLoopEnabled(bool enabled)
{
    isLoopEnabled = enabled;
    music.setLoop(isLoopEnabled);
}
