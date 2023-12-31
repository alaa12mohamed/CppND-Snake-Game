#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <mutex> // Added for std::mutex
#include "SDL.h"
#include "snake.h"
#include <memory>
#include <future> // For std::promise and std::future
#include <thread> // For std::thread
#include "Obstacles.h"
#include "Boosters.h"

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  /// Rendering initial static obstacles
  void Render(Snake const snake,
              SDL_Point const &food,
              const std::shared_ptr<Obstacles> obstacles,
              const std::shared_ptr<Boosters> boosters);

  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  // Obstacle surface
  SDL_Surface *obstacleSurface;
  // Obstacle Texture
  SDL_Texture *obstacleTexture;

  // Booster surface
  SDL_Surface *boosterSurface;
  // Booster Texture
  SDL_Texture *boosterTexture;

  // Added mutex for protecting shared data structures
  mutable std::mutex obstaclesMutex;
  mutable std::mutex boostersMutex;

  void placeObstacles(const std::shared_ptr<Obstacles> obstacles) const;
  void placeBoosters(const std::shared_ptr<Boosters> _boosters) const;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  // Method to handle async rendering
  void AsyncRender(std::promise<void> &&renderCompletedPromise, Snake const snake, SDL_Point const &food);
};

#endif
