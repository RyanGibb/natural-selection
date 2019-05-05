#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "structures.h"

const int array_terminator = -1;

// Returns -1 if not found, or integer position if found
int val_in_array(int arr[], int val) {
  int i = 0;
  while (arr[i] != array_terminator) {
    if (arr[i] == val) {
      return i;
    }
    i++;
  }
  return -1;
}

void append_array(int arr[], int val, int pos) {
  arr[pos] = val;
  arr[pos + 1] = array_terminator;
}

World* make_world(Point dimensions, int start_carns, int start_herbs, int start_food, int starting_health) {
  PointNode predator_points = NULL;



  int tiles_size = sizeof(Tile*) * y_size + sizeof(Tile) * x_size * y_size;
  Tile*** tiles = malloc(tiles_size);
  Tile** first_tile = (Tile**) tiles + y_size; // pointer to first Tile pointer, in 2D array
  for (int y = 0; y < y_size; y++) {
    // point y column pointer to appropriate location in 2D array (to start of x row)
    tiles[y] = (first_tile + x_size * y);
    for (int x = 0; x < x_size; x++) {
      tiles[y][x] = make_tile();
    }
  }
  int tiles_to_populate = start_carns + start_herbs + start_food;
  int used_x[tiles_to_populate + 1], used_y[tiles_to_populate + 1]; // plus one for array_terminator
  used_y[0] = array_terminator;
  used_x[0] = array_terminator;
  int len_used_y = 0;
  int len_used_x = 0;

  srand(time(0)); // Use current time as seed for random generator
  for (int i = 0; i < start_carns; i++) {
    int y = rand() % y_size;
    int x = rand() % x_size;
    while (
        val_in_array(used_y, y) != -1 &&
        val_in_array(used_x, x) != -1
      ) {
      y = rand() % y_size;
      x = rand() % x_size;
    }
    append_array(used_y, y, len_used_y);
    len_used_y++;
    append_array(used_x, x, len_used_x);
    len_used_x++;
    tiles[y][x]->type = Carn;
    Creature carn = {starting_health};
    tiles[y][x]->creature = carn;
  }

  for (int i = 0; i < start_herbs; i++) {
    int y = rand() % y_size;
    int x = rand() % x_size;
    // while (
    //     val_in_array(used_y, y) != -1 &&
    //     val_in_array(used_x, x) != -1
    //   ) {
    //   y = rand() % y_size;
    //   x = rand() % x_size;
    // }
    append_array(used_y, y, len_used_y);
    len_used_y++;
    append_array(used_x, x, len_used_x);
    len_used_x++;
    tiles[y][x]->type = Herb;
    Creature herb = {starting_health};
    tiles[y][x]->creature = herb;
  }

  for (int i = 0; i < start_food; i++) {
    int y = rand() % y_size;
    int x = rand() % x_size;
    while (
        val_in_array(used_y, y) != -1 &&
        val_in_array(used_x, x) != -1
      ) {
        y = rand() % y_size;
        x = rand() % x_size;
    }
    append_array(used_y, y, len_used_y);
    len_used_y++;
    append_array(used_x, x, len_used_x);
    len_used_x++;
    tiles[y][x]->food = true;
  }

  World* world = malloc(sizeof(World));
  world->x_size = x_size;
  world->y_size = y_size;
  world->tiles = tiles;
  return world;
}

void free_world(World* world) {
  for (int y = 0; y < world->y_size; y++) {
    for (int x = 0; x < world->x_size; x++) {
      // TODO is this needed?
      if (world->tiles[x][y] != NULL) {
        free_tile(world->tiles[x][y]);
      }
    }
  }
  free(world->tiles);
  free(world);
}

Tile* make_tile() {
  Tile* tile = malloc(sizeof(Tile));
  tile->type = None;
  Creature none_creature = {0};
  tile->creature = none_creature;
  tile->food = false;
  return tile;
}

void free_tile(Tile* tile) {
  free(tile);
}
