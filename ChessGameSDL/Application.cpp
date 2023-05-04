#include "Application.h"

Application::Application() : m_window_event()
{
    // Create a window with the specified position, dimensions, and flags
    m_window = SDL_CreateWindow(
        windowName,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,   // Made screen square since the board fits better
        SDL_WINDOW_RESIZABLE);
    if (!m_window) // Window error check
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    // Get the SDL surface associated with the window
    m_window_surface = SDL_GetWindowSurface(m_window);
    if (!m_window_surface) // Window surface error check
    {
        std::cout << "Failed to get window's surface\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    // Not sure if this is necessary, but might be necessary for TTF
    renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    // Init TrueType (.ttf) font lib
    if (TTF_Init() < 0) {
        std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
    }

    // Load fonts
    int textFont_PointSize = 32;
    const char* textFont_FilePath = "../Assets/Fonts/Open_Sans/static/OpenSans-Light.ttf";
    const char* textFont_Text = "Chicken nuggets";
    SDL_Color textFont_Color = { 255,255,255 };
    textFont = TTF_OpenFont(textFont_FilePath, textFont_PointSize); // from where is this relative
    if (textFont == nullptr) {
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }
    // Pixels from our text (rasterize)
    SDL_Surface* surfaceText = TTF_RenderText_Blended(textFont, textFont_Text, textFont_Color); //TTF_RenderText_Solid
    textureText = SDL_CreateTextureFromSurface(renderer, surfaceText); // Setup the texture

    // Create a rectangle to draw on
    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(textureText, nullptr, nullptr, &textW, &textH);
    rectangle = { 0 ,0,textW,textH };

    //SDL_BlitScaled(surfaceText, NULL, surfaceText, &rectangle);
    SDL_FreeSurface(surfaceText); // Free the surface

    // Image testing
    loadedImage = SDL_LoadBMP("../Assets/Images/Chess-Board/black-square.bmp");
    textureImg = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage); // Free the surface

    //chessWindow = new ChessWindow();
}

Application::~Application()
{
    SDL_DestroyTexture(textureText); // Destroy texture text
    SDL_FreeSurface(m_window_surface);
    SDL_DestroyWindow(m_window); // Destroy window
    TTF_CloseFont(textFont); // Close font subsystem
    TTF_Quit();
    SDL_Quit();

    delete m_window;
    m_window = nullptr;
    delete m_window_surface;
    m_window_surface = nullptr;
    //delete chessWindow;
    //chessWindow = nullptr;
    delete windowName;
    windowName = nullptr;
    delete textFont;
    textFont = nullptr;
    delete textureText;
    textureText = nullptr;
    delete renderer;
    renderer = nullptr;
}
void Application::mousePress(SDL_MouseButtonEvent& b) {
    if (b.button == SDL_BUTTON_LEFT)
    {
        int x = b.x;
        int y = b.y;
        if (chessWindow->isInsideChessBoard(x, y))
        {
            chessWindow->onLeftClick(this->m_window_surface, x, y);
        }
    }
    if (b.button == SDL_BUTTON_RIGHT)
    {
        int x = b.x;
        int y = b.y;
    }
}

void Application::loop()
{
    while (keep_window_open)
    {
        while (SDL_PollEvent(&m_window_event) > 0)
        {
            switch (m_window_event.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mousePress(m_window_event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                if (m_window_event.button.button == SDL_BUTTON_LEFT) {
                    this->chessWindow->releaseLeftClick();
                }
                break;
            }
            switch (m_window_event.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                m_window_surface = SDL_GetWindowSurface(m_window);
                break;
            }
        }

        //update(1.0 / 60.0);
        draw();
    }
}
<<<<<<< Updated upstream

void Application::mousePress(SDL_MouseButtonEvent& b) {
    if (b.button == SDL_BUTTON_LEFT) {
        int x = b.x;
        int y = b.y;
        if (chessWindow->isInsideChessBoard(x, y)) {
            chessWindow->onLeftClick(this->m_window_surface, x, y);
        }
    }
    if (b.button)
    if (b.button == SDL_BUTTON_RIGHT) {
        int x = b.x;
        int y = b.y;
    }
}

=======
>>>>>>> Stashed changes
void Application::draw()
{
    SDL_UpdateWindowSurface(m_window);
    SDL_FillRect(m_window_surface, NULL, SDL_MapRGB(m_window_surface->format, 0, 0, 0));
    //chessWindow->draw(m_window_surface);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT); // Clear and Draw the Screen
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureImg, nullptr, nullptr);
    SDL_RenderCopy(renderer, textureText, nullptr, &rectangle); // Render our text on a rectangle
    SDL_RenderPresent(renderer); // Finally show what we've drawn

}