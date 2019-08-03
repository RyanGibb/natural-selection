#include <stdbool.h>
#include <time.h>

#include "display.h"
#include "structures.h"

int x_size = 200;
int y_size = 50;
int start_carns = 100;
int start_herbs = 200;
int start_food = 400;

float growth_rate = 0.5;
float atttrition = 1;
float eat_food_health = 10;
float eat_prey_health_modifier = 0.6;
float starting_health = 100;
float reproduce_health = 200;

bool stop = false;
unsigned int wait_ms = 500;

int num_carns = 0;
int num_herbs = 0;
int num_food = 0;

// def get_moves(tile_condition, x, y):
//     moves = []
//     for delta_x in range (-1, 2, 1):
//         possible_x = (x + delta_x)
//         if possible_x >= x_size or possible_x < 0:
//             continue
//         for delta_y in range (-1, 2, 1):
//             possible_y = (y + delta_y)
//             if possible_y >= y_size or possible_y < 0:
//                 continue
//             if tile_condition(world[possible_y][possible_x]):
//                 assert delta_y != 0 or delta_x != 0
//                 moves.append((possible_x, possible_y))
//     return moves

int tick(World* world) {
  Node* newHead = NULL;
  Node* node = world->head;
  while (node != NULL) {
    node->loc.x = (node->loc.x + 1) % world->dimensions.x;
    Entity entity = node->entity;
    Type type = entity.type;
    switch(type) {
      case Carn: {
        Animal* animal = entity.animal;
        break;
      }
      case Herb:{
        Animal* animal = entity.animal;
        break;
      }
      case Bush:{
        Plant* plant = entity.plant;
        break;
      }
    }
    Node* newNode = node;
    node = node->next;
    newHead = insert_node(newHead, newNode);
  }
  world->head = newHead;
  return 0;
  //   global prey, predators
  // new_predators = []
  // for x, y in predators:
  //     p = world[y][x].entity
  //     assert isinstance(p, Predator)
  //     p.health -= atttrition
  //     if p.health <= 0:
  //         world[y][x].entity = None
  //         if (x, y) in no_food:
  //             world[y][x].food = True
  //             no_food.remove((x, y))
  //         # predators.remove((x, y))
  //         continue
  //     # moves anywhere but onto another predator
  //     moves = get_moves(lambda tile: not isinstance(tile.entity, Predator), x, y)
  //     if len(moves) > 0:
  //         new_x, new_y = random.choice(moves)
  //         new_p = world[new_y][new_x].entity
  //         if isinstance(new_p, Prey):
  //             p.health += new_p.health * eat_prey_health_modifier
  //             # not strictly needed: world[y][x].entity = None
  //             prey.remove((new_x, new_y))
  //         if p.health > reproduce_health:
  //             world[new_y][new_x].entity = Predator(p.health / 2)
  //             p.health = p.health / 2
  //             new_predators.append((x, y))
  //         else:
  //             world[y][x].entity = None
  //             world[new_y][new_x].entity = p
  //             # predators.remove((x, y))
  //         new_predators.append((new_x, new_y))
  // predators = new_predators
  //
  // new_prey = []
  // for x, y in prey:
  //     p = world[y][x].entity
  //     assert isinstance(p, Prey)
  //     p.health -= atttrition
  //     if world[y][x].food == True:
  //         world[y][x].food = False
  //         no_food.append((x, y))
  //         p.health += eat_food_health
  //     if p.health <= 0:
  //         world[y][x].entity = None
  //         if (x, y) in no_food:
  //             world[y][x].food = True # 1
  //             no_food.remove((x, y))
  //         # prey.remove((x, y))
  //         continue
  //     # moves anywhere but onto another prey OR predator
  //     moves = get_moves(lambda tile: tile.entity == None, x, y)
  //     if len(moves) > 0:
  //         new_x, new_y = random.choice(moves)
  //         if p.health > reproduce_health:
  //             world[new_y][new_x].entity = Prey(p.health / 2)
  //             p.health = p.health / 2
  //             new_prey.append((x, y))
  //         else:
  //             world[y][x].entity = None
  //             world[new_y][new_x].entity = p
  //             # prey.remove((x, y))
  //         assert x != new_x or y != new_y
  //         # print("x {} y {}".format(x, y))
  //         # print("new x {} new y {}".format(new_x, new_y))
  //         new_prey.append((new_x, new_y))
  //
  // prey = new_prey
  //
  // for i in range(growth):
  //     if len(no_food) <= 0:
  //         continue
  //     x, y = random.choice(no_food)
  //     world[y][x].food = True
  //     no_food.remove((x, y))
}

int run(World* world){
  display_world(world, num_carns, num_herbs, num_food);
  while(!stop){
    tick(world);
    display_world(world, num_carns, num_herbs, num_food);
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    #include <unistd.h> // for usleep
    usleep(wait_ms * 1000);
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h> // for Sleep
    Sleep(wait_ms);
#endif
  }
  return 0;
}


int main(int argc, char* argv[]) {
  (void) argc;
  (void) argv;
  Point dimensions = {.y=y_size, .x=x_size};
  World* world = make_world(dimensions,
                            start_carns, start_herbs, start_food,
                            starting_health);
  run(world);
  free_world(world);
  return 0;
}
