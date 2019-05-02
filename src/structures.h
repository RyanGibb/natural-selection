
#ifndef STRUCTURES_H
#define STRUCTURES_H

// typedef struct {
//   int x;
//   int y;
// } Point;

typedef enum {Carn, Herb} Type;

typedef struct {
  bool exists;
  // Point loc;
  Type type;
  float health;
  // float attack;
  // int speed;
  // int size;
} Creature;

typedef struct {
  Creature* creature;
  int food;
} Tile;

typedef struct {
  int x_size;
  int y_size;
  Tile*** map;
} World;

World* make_world(int x_size, int y_size, int num_carns, int num_preds, int num_food);
void free_world(World* world);

Tile* make_tile(Creature* creature, bool food);
void free_tile(Tile* tile);

Creature* make_creature(bool exists, Type type, float health);
void free_creature(Creature* creature);

#endif
