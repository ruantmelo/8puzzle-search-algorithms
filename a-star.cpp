
#include <queue>
#include "problem.hpp"

int evaluation_function(node &n) {
  return n.distance + manhattan_distance(n);
}

int main() {

  node initial_node = {
    {
      {2, 8, 3},
      {1, 6, 4},
      {7, 5, 0},
    }, 
    {0, 0}, 
    0, 
    nullptr, 
    0};

  
  initial_node.path_cost = manhattan_distance(initial_node);
   
  std::priority_queue<node, std::vector<node>, Compare_PC> frontiers;
  std::set<node> visited;

  frontiers.push(initial_node);
  visited.insert(initial_node);

  while(!frontiers.empty()) {
    node current_node = frontiers.top();
    frontiers.pop();

    print_state(current_node);

    if(is_goal_state(current_node)) {
      printSolutionFound();
      return 0;
    }

    node neighbors[4]; 

    get_neighbors(current_node, neighbors);

    for (int i = 0; i < 4; i++) {
      if (visited.find(neighbors[i]) == visited.end()) {
        visited.insert(neighbors[i]);
        frontiers.push(neighbors[i]);
      }
    }
  }

  std::cout << "Solution NOT found" << std::endl; 

  return 0;
}