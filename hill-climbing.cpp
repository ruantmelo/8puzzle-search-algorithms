
#include <queue>
#include "problem.hpp"

int evaluation_function(node &n) {
  return manhattan_distance(n);
}

int main() {

  node current_node = {
    {
      {1, 7, 2},
      {8, 4, 5},
      {6, 3, 0},
    },
    // {
    //   {2, 8, 3},
    //   {1, 6, 4},
    //   {7, 5, 0},
    // }, 
    {0, 0}, 
    0, 
    nullptr, 
    0};

  
  current_node.path_cost = manhattan_distance(current_node);
   
  std::set<node> visited;

  while(true) {
    print_state(current_node);

    node neighbors[4]; 

    get_neighbors(current_node, neighbors);

    int best_neighbor_idx = 0;

    for (int i = 0; i < 4; i++) {
      if (neighbors[i].path_cost < neighbors[best_neighbor_idx].path_cost) {
        best_neighbor_idx = i;
      }
    }

    if (current_node.path_cost <= neighbors[best_neighbor_idx].path_cost) {
      std::cout << "Best solution found" << std::endl;
      return 0;
    } 

    current_node = neighbors[best_neighbor_idx];
  }

  return 0;
}