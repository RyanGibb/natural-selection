
#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
  int y;
  int x;
} Point;

typedef struct {
  float health;
} Animal;

typedef struct {
} Plant;

typedef enum {Carn, Herb, Bush} Type;

typedef struct {
  Type type;
  union {
    Animal* animal;
    Plant* plant;
  };
} Entity;

typedef struct node {
  Point loc;
  Entity entity;
  struct node* next;
} Node;

typedef struct {
  Point dimensions;
  Node* head;
  // Node*** node_array;
} World;

Node* make_carn(Point loc, int starting_health);
Node* make_herb(Point loc, int starting_health);
Node* make_bush(Point loc);

void free_node(Node* node);
Node* insert_node(Node* head, Node* new);
void free_list(Node* head);

World* make_world(Point dimensions,
  int start_carns, int start_herbs, int start_food,
  int starting_health);
void free_world(World* world);

#endif
