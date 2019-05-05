#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "display.h"
#include "structures.h"

static void horizontal_line(int x_size) {
  for (int i = 0; i < x_size + 2; i++) {
    putchar('-');
  }
  putchar('\n');
}

Node* display_node(Point p, Node* node) {
  if (node != NULL  && p.x == node->loc.x && p.y == node->loc.y) {
    // only print 'top' entity
    Type top = node->entity.type;
    while (node != NULL && p.x == node->loc.x && p.y == node->loc.y) {
      if (node->entity.type < top) {
        top = node->entity.type;
      }
      node = node->next;
    }
    if (top == Carn) {
      putchar('C');
    }
    else if (top == Herb) {
      putchar('H');
    }
    else if (top == Bush) {
      putchar('.');
    }
    else {
      putchar('X');
    }
    return node;
  }
  else {
    putchar(' ');
    return node;
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
  horizontal_line(world->dimensions.x);
  Node* node = world->head;
  for (int y = 0; y < world->dimensions.y; y++) {
    putchar('|');
    for (int x = 0; x < world->dimensions.x; x++) {
      Point p = {.y=y, .x=x};
      node = display_node(p, node);
    }
    putchar('|');
    putchar('\n');
  }
  horizontal_line(world->dimensions.x);
}
