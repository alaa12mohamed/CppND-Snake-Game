#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL_thread.h>
#include <mutex>
#include "SDL.h"
#include "Boosters.h"
#include "Obstacles.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      obstacleSurface(nullptr),
      obstacleTexture(nullptr),
      boosterSurface(nullptr),
      boosterTexture(nullptr),
      obstacleSurfaceAsync(nullptr),
      obstacleTextureAsync(nullptr),
      boosterSurfaceAsync(nullptr),
      boosterTextureAsync(nullptr)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Start the asynchronous texture loading thread
  std::thread textureLoadingThread(&Renderer::LoadTexturesAsync, this);
  textureLoadingThread.detach(); // Detach the thread since it will run independently
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake,
                      SDL_Point const &food,
                      const std::shared_ptr<Obstacles> obstacles,
                      const std::shared_ptr<Boosters> boosters)
{
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body)
  {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive)
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  }
  else
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Place obstacles
  placeObstacles(obstacles);

  // Place boosters
  placeBoosters(boosters);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::LoadTexturesAsync()
{
  AsyncRender([this]() {
        // Creating Obstacle Texture
        obstacleSurfaceAsync = SDL_LoadBMP("../assets/unlit-bomb.bmp");
        obstacleTextureAsync = SDL_CreateTextureFromSurface(sdl_renderer, obstacleSurface);

        boosterSurfaceAsync = SDL_LoadBMP("../assets/rocket.bmp");
        boosterTextureAsync = SDL_CreateTextureFromSurface(sdl_renderer, boosterSurface);

        // Notify that textures have been loaded
        UpdateTextures();
    });
}

void Renderer::UpdateTextures()
{
  // Update the member variables in a thread-safe manner
  {
    std::lock_guard<std::mutex> lock(textureMutex);
    obstacleSurface = obstacleSurfaceAsync;
    obstacleTexture = obstacleTextureAsync;
    boosterSurface = boosterSurfaceAsync;
    boosterTexture = boosterTextureAsync;
  }
}

void Renderer::placeObstacles(const std::shared_ptr<Obstacles> obstacles) const
{
  for (const Coordinate &coordinate : obstacles->getCoordinates())
  {
    // Rect which will be hosting the obstacle.
    SDL_Rect obstacleRect;
    obstacleRect.w = screen_width / grid_width;
    obstacleRect.h = screen_height / grid_height;
    obstacleRect.x = coordinate.getXCoordinate() * obstacleRect.w;
    obstacleRect.y = coordinate.getYCoordinate() * obstacleRect.h;

    // Render the obstacles
    {
      std::lock_guard<std::mutex> lock(textureMutex);
      SDL_RenderCopy(sdl_renderer, obstacleTexture, NULL, &obstacleRect);
    }
  }
}

void Renderer::placeBoosters(const std::shared_ptr<Boosters> boosters) const
{
  for (const Coordinate &coordinate : boosters->getCoordinates())
  {
    // Rect which will be hosting the booster
    SDL_Rect obstacleRect;
    obstacleRect.w = screen_width / grid_width;
    obstacleRect.h = screen_height / grid_height;
    obstacleRect.x = coordinate.getXCoordinate() * obstacleRect.w;
    obstacleRect.y = coordinate.getYCoordinate() * obstacleRect.h;

    // Render the obstacles
    {
      std::lock_guard<std::mutex> lock(textureMutex);
      SDL_RenderCopy(sdl_renderer, boosterTexture, NULL, &obstacleRect);
    }
  }
}
