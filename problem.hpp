
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

struct node{
  int state[3][3];
  int action[2];
  double path_cost; // Cost calculated using evaluation function f(n)
  node *parent;
  int distance; 

  std::string uniqueKey() const {
    std::ostringstream oss;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            oss << state[i][j] << ",";
        }
    }
    // oss << action[0] << "," << action[1] << ",";
    // oss << std::fixed << std::setprecision(2) << path_cost;
    return oss.str();
  }

  bool operator<(const node& other) const {
    return uniqueKey() < other.uniqueKey();
  }
};

int evaluation_function(node &n);

int actions[4][2] = {
  {-1, 0},
  {1, 0},
  {0, -1},
  {0, 1}
};

int GOAL_STATE[3][3] = {
  {1, 2, 3},
  {8, 0, 4},
  {7, 6, 5}
};

int get_index(int *state, int length, int value) {
  for(int i = 0; i < length; i++) {
    if(*(state + i) == value) return i;
  }

  return -1;
}

class Compare_PC {
  public:
    bool operator()(node a, node b) {
      return a.path_cost > b.path_cost; // Bigger (True) - Swap elements 
    }
};

int manhattan_distance(node &n) {
  int distance = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (n.state[i][j] == 0) continue;

      if (n.state[i][j] != GOAL_STATE[i][j]) {
        int goal_index = get_index(GOAL_STATE[0], 9, n.state[i][j]);
        distance += abs(i - (goal_index / 3)) + abs(j - (goal_index % 3));
      }
    }
  }
         
  return distance;        
}

node* get_neighbors(node &n, node *neighbors) {
  int i = 0;  
  for (auto a: actions) {
    node new_node = n;

    int blank_index = get_index(new_node.state[0], 9, 0);
    
    int row = blank_index / 3 + a[0];
    int column = blank_index % 3 + a[1]; 

    if (row >= 0 && row < 3 && column >= 0 && column < 3) {
      std::swap(*(new_node.state[0] + blank_index), new_node.state[row][column]);

      new_node.action[0] = a[0];
      new_node.action[1] = a[1];

    }

    new_node.path_cost = evaluation_function(new_node);
    
    
    new_node.distance++;
    new_node.parent = &n;

    neighbors[i] = new_node;

    i++;
  }

  return neighbors;
};

bool is_goal_state(node &n) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3 ; j++) {
      if (n.state[i][j] !=  GOAL_STATE[i][j]) return false;
    }
  }

  return true;
}

void print_state(node &n) {
  std::cout << std::string(30, '-') << std::endl; 

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cout << n.state[i][j];
      std::cout << " " ;    
      
    };

    std::cout << std::endl;
  };

  std::cout << "Action: " << n.action[0] << "," << n.action[1] << std::endl; 
  std::cout << "Path Cost: " << n.path_cost << std::endl;
  std::cout << "Distance: " << n.distance << std::endl;

  std::cout << std::string(30, '-') << std::endl;

}

void printSolutionFound() {
    std::cout << std::string(30, '*') << std::endl;
    std::cout << "*     SOLUTION FOUND!        *" << std::endl;
    std::cout << std::string(30, '*') << std::endl;
}