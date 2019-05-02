#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "display.h"
#include "structures.h"

void horizontal_line(int x_size) {
  for (int i = 0; i < x_size + 2; i++) {
    printf("-");
  }
  printf("\n");
}

char* display_tile(Tile* tile) {
  // TODO is NULL check and exists check needed?
  if (tile->creature != NULL && tile->creature->exists && tile->creature->type == Carn) {
    return "H";
  }
  else if (tile->creature != NULL && tile->creature->exists && tile->creature->type == Herb) {
    return "C";
  }
  else if (tile->food == true) {
    return ".";
  }
  else {
    return " ";
  }
}

void display_world(World* world, int num_carns, int num_herbs, int num_food) {
  // clear terminal
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("clear");
#elif defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
  printf("Carnivore: %d \tHerbivore: %d \tFood: %d\n", num_carns, num_herbs, num_food);
  horizontal_line(world->x_size);
  for (int y = 0; y < world->y_size; y ++) {
    printf("|");
    for (int x = 0; x < world->x_size; x ++) {
      printf("%s", display_tile(world->map[y][x]));
    }
    printf("|\n");
  }
  horizontal_line(world->x_size);
}
