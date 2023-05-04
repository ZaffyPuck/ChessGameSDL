#pragma once

// General
#include <iostream> // for cout
// Custom
#include "External.h"
#include "ChessWindow.h"

class Application
{
public:
    Application();
    ~Application();

    void loop();
    void draw();
    void mousePress(SDL_MouseButtonEvent& b);
private:
    SDL_Window* m_window = nullptr;
    SDL_Surface* m_window_surface = nullptr;
    ChessWindow* chessWindow = nullptr;
    SDL_Event m_window_event;
    
    int windowWidth = 720;
    int windowHeight = 720; // px
    const char* windowName = "Chess";
    bool keep_window_open = true;

    TTF_Font* textFont = nullptr;
    SDL_Texture* textureText = nullptr;
    SDL_Rect rectangle = {};


    SDL_Surface* loadedImage = nullptr;
    SDL_Texture* textureImg = nullptr;

    SDL_Renderer* renderer = nullptr;
};