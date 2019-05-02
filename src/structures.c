#include <stdbool.h>
#include <stdlib.h>

#include "structures.h"

World* make_world(int x_size, int y_size, int num_carns, int num_herbs, int num_food) {
  (void) num_carns;
  (void) num_herbs;
  (void) num_food;
  int map_size = sizeof(Tile*) * y_size + sizeof(Tile) * x_size * y_size;
  Tile*** map = malloc(map_size);
  Tile** first_tile = (Tile**) map + y_size; // pointer to first Tile pointer, in 2D array

  //   global tiles
  // global start_prey
  // global start_predators
  // global start_food
  // global growth
  // tiles = int(x_size * y_size)
  // start_prey = int(tiles * start_prey_per_tile)
  // start_predators = int(tiles * start_predators_per_tile)
  // start_food = int(tiles * start_food_per_tile)
  // growth = int(tiles * growth_per_tile)
  //
  // global world
  // global predators
  // global prey
  // global no_food
  // world = [[Tile() for x in range(x_size)] for y in range(y_size)]
  // predators = [None] * start_predators
  // prey = [None] * start_prey
  // no_creatures = [(x, y) for x in range(x_size) for y in range(y_size)]
  // no_food = [(x, y) for x in range(x_size) for y in range(y_size)]
  // for i in range(start_predators):
  //     x, y = random.choice(no_creatures)
  //     world[y][x].entity = Predator(starting_health)
  //     predators[i] = (x, y)
  //     no_creatures.remove((x, y))
  // for i in range(start_prey):
  //     x, y = random.choice(no_creatures)
  //     world[y][x].entity = Prey(starting_health)
  //     prey[i] = (x, y)
  //     no_creatures.remove((x, y))
  // for i in range(start_food):
  //     x, y = random.choice(no_food)
  //     world[y][x].food = True
  //     no_food.remove((x, y))
  // run()
  for (int y = 0; y < y_size; y++) {
    // point y column pointer to appropriate location in 2D array (to start of x row)
    map[y] = (first_tile + x_size * y);
    for (int x = 0; x < x_size; x++) {
      // Creature* creature = make_creature(false, Herb, 0);
      Tile* tile = make_tile(NULL, false);
      map[y][x] = tile;
    }
  }
  World* world = malloc(sizeof(World));
  world->x_size = x_size;
  world->y_size = y_size;
  world->map = map;
  return world;
}

void free_world(World* world) {
  for (int y = 0; y < world->y_size; y++) {
    for (int x = 0; x < world->x_size; x++) {
      // TODO is this needed?
      if (world->map[x][y] != NULL) {
        free_tile(world->map[x][y]);
      }
    }
  }
  free(world->map);
  free(world);
}

Tile* make_tile(Creature* creature, bool food) {
  Tile* tile = malloc(sizeof(Tile));
  tile->creature = creature;
  tile->food = food;
  return tile;
}

void free_tile(Tile* tile) {
  // TODO is this needed?
  if (tile->creature != NULL) {
    free_creature(tile->creature);
  }
  free(tile);
}

Creature* make_creature(bool exists, Type type, float health) {
  Creature* creature = malloc(sizeof(Creature));
  creature->exists = exists;
  // creature->loc = loc;
  creature->type = type;
  creature->health = health;
  return creature;
}

void free_creature(Creature* creature) {
  free(creature);
}
