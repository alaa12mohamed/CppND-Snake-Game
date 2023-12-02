#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <memory>
#include "Obstacles.h"
#include "Boosters.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  /* If snake gets in touch with these obstacles, then the snake loses its life. */
  std::shared_ptr<Obstacles> _obstacles;
  void PlaceObstacles();

  /* If snake gets in touch with these boosters, then snake's speeds increases. */
  std::shared_ptr<Boosters> _boosters;
  void PlaceBoosters();

  int score{0};
  int _numberOfBoosters;
  int _numberOfObstacles;

  void PlaceFood();
  void Update();
};

#endif