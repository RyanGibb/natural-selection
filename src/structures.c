#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "structures.h"

static Point rand_point(Point dimensions) {
  int y = rand() % dimensions.y;
  int x = rand() % dimensions.x;
  Point p = {.y=y, .x=x};
  return p;
}

static Node* make_node(Point loc, Entity entity, Node* next) {
  Node* node = malloc(sizeof(struct node));
  node->loc = loc;
  node->entity = entity;
  node->next = next;
  return node;
}

static Animal* make_animal(int starting_health) {
  Animal* animal = malloc(sizeof(Animal));
  animal->health = starting_health;
  return animal;
}

static Plant* make_plant() {
  Plant* plant = malloc(sizeof(Plant));
  return plant;
}

Node* make_carn(Point loc, int starting_health) {
  Animal* animal = make_animal(starting_health);
  Entity carn = {Carn, .animal=animal};
  return make_node(loc, carn, NULL);
}

Node* make_herb(Point loc, int starting_health) {
  Animal* animal = make_animal(starting_health);
  Entity herb = {Herb, .animal=animal};
  return make_node(loc, herb, NULL);
}

Node* make_bush(Point loc) {
  Plant* plant = make_plant();
  Entity bush = {Bush, .plant=plant};
  return make_node(loc, bush, NULL);
}

void free_node(Node* node) {
  switch(node->entity.type) {
    case Carn:
    case Herb:
      free(node->entity.animal);
      break;
    case Bush:
      free(node->entity.plant);
      break;
  }
  free(node);
}

Node* insert_node(Node* head, Node* new) {
  Node* prev = NULL;
  Node* node = head;
  while (node != NULL && node->loc.y < new->loc.y) {
    prev = node;
    node = node->next;
  }
  while (node != NULL && node->loc.y == new->loc.y && node->loc.x < new->loc.x) {
    prev = node;
    node = node->next;
  }
  // If new at start of list (or list doesn't exist), make new head
  if (prev == NULL) {
    new->next = head;
    return new;
  }
  prev->next = new;
  new->next = node;
  return head;
}

void free_list(Node* head) {
  Node* last;
  while (head != NULL) {
    last = head;
    head = head->next;
    free_node(last);
  }
}

// void print_list(Node* head) {
//   while (head != NULL) {
//     printf("y %d x %d\n", head->loc.y, head->loc.x);
//     head = head->next;
//   }
// }

World* make_world(Point dimensions, int start_carns, int start_herbs, int start_food, int starting_health) {
  Node* head = NULL;
  srand(time(0)); // Use current time as seed for random generator
  for (int i = 0; i < start_carns; i++) {
    head = insert_node(head, make_carn(rand_point(dimensions), starting_health));
  }
  for (int i = 0; i < start_herbs; i++) {
    head = insert_node(head, make_herb(rand_point(dimensions), starting_health));
  }
  for (int i = 0; i < start_food; i++) {
    head = insert_node(head, make_bush(rand_point(dimensions)));
  }
  // print_list(head);
  World* world = malloc(sizeof(World));
  world->dimensions = dimensions;
  world->head = head;
  return world;
}

void free_world(World* world) {
  free_list(world->head);
  free(world);
}
