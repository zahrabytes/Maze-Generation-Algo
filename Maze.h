#include <algorithm>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Maze {
public:
  vector<vector<int>> primsMaze(int width, int height);
  vector<vector<int>> kruskalsMaze(int width, int height);
  int solveMaze(vector<vector<int>> &maze);

private:
  bool contains(vector<vector<int>> &s, vector<int> &cell);
  int indexOfSet(vector<vector<vector<int>>> &s, vector<int> &cell);
  vector<vector<int>> neighbors(vector<vector<int>> maze, int ic, int jc);
  vector<pair<int, int>> pathNeighbors(vector<vector<int>> &maze, int i, int j);
};

bool Maze::contains(vector<vector<int>> &s, vector<int> &cell) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i][0] == cell[0] && s[i][1] == cell[1]) {
      return true;
    }
  }
  return false;
}

int Maze::indexOfSet(vector<vector<vector<int>>> &s, vector<int> &cell) {
  for (int i = 0; i < s.size(); i++) {
    if (contains(s[i], cell)) {
      return i;
    }
  }
  return -1; // make sure to check later
}

vector<vector<int>> Maze::neighbors(vector<vector<int>> maze, int ic, int jc) {
  vector<vector<int>> final;
  for (int i = 0; i < 4; i++) {
    vector<int> n = {ic, jc};

    // Iterates through four neighbors
    if (i == 0) {
      n[1] -= 2;
    } else if (i == 1) {
      n[1] += 2;
    } else if (i == 2) {
      n[0] -= 2;
    } else {
      n[0] += 2;
    }

    if (n[0] < maze.size() && n[1] < maze[0].size() && n[0] >= 0 && n[1] >= 0) {

      if (maze[n[0]][n[1]] == 1) {
        final.push_back(n);
      }
    }
  }
  return final;
}

vector<pair<int, int>> Maze::pathNeighbors(vector<vector<int>> &maze, int i,
                                           int j) {
  vector<pair<int, int>> result;
  int m = maze.size();
  int n = maze[0].size();
  if (i > 0 && maze[i - 1][j] == 0) {
    result.push_back(make_pair(i - 1, j));
  }
  if (j > 0 && maze[i][j - 1] == 0) {
    result.push_back(make_pair(i, j - 1));
  }
  if (i < m - 1 && maze[i + 1][j] == 0) {
    result.push_back(make_pair(i + 1, j));
  }
  if (j < n - 1 && maze[i][j + 1] == 0) {
    result.push_back(make_pair(i, j + 1));
  }
  return result;
}

vector<vector<int>> Maze::primsMaze(int width, int height) {
  // Make them odd
  width -= width % 2;
  width++;
  height -= height % 2;
  height++;

  // Fill maze with 1's (walls)
  vector<vector<int>> maze(height, vector<int>(width, 1));

  // Opening at top - start of maze
  maze[0][1] = 0;

  vector<int> start(2);
  do {
    start[0] = rand() % height;
  } while (start[0] % 2 == 0);
  do {
    start[1] = rand() % width;
  } while (start[1] % 2 == 0);

  maze[start[0]][start[1]] = 0;

  // First open cell
  vector<vector<int>> openCells{start};

  // While openCells is not empty
  while (!openCells.empty()) {

    // Get random cell from openCells and generate neighbors
    int index = rand() % openCells.size();
    vector<int> cell = openCells[index];
    vector<vector<int>> n = neighbors(maze, cell[0], cell[1]);

    // If no neighbors, remove cell from openCells and regenerate
    while (n.empty()) {
      openCells.erase(openCells.begin() + index);
      if (openCells.empty()) {
        break;
      }

      index = rand() % openCells.size();
      cell = openCells[index];
      n = neighbors(maze, cell[0], cell[1]);
    }
    if (openCells.empty()) {
      break;
    }

    // Random choice from all neighbors added to openCells
    int choiceIndex = rand() % n.size();
    vector<int> choice = n[choiceIndex];
    openCells.push_back(choice);

    // If that was the only neighbor (length of neighbors array == 0)
    // then remove initial cell from openCells
    if (n.size() == 1) {
      openCells.erase(openCells.begin() + index);
    }

    // Set neighbor to 0 (path, not wall)
    // Set connecting node between cell and choice to 0
    maze[choice[0]][choice[1]] = 0;
    maze[(choice[0] + cell[0]) / 2][(choice[1] + cell[1]) / 2] = 0;
  }

  // Opening at bottom - end of maze
  maze[maze.size() - 1][maze[0].size() - 2] = 0;
  maze[maze.size() - 2][maze[0].size() - 2] = 0;

  return maze;
}

vector<vector<int>> Maze::kruskalsMaze(int width, int height) {
  // Make dimensions odd
  width -= width % 2;
  width++;
  height -= height % 2;
  height++;

  // Initialize maze and sets/ edges
  vector<vector<int>> maze(height, vector<int>(width, 0));
  vector<vector<vector<int>>> sets;
  vector<vector<int>> edges;

  // Fill each
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      bool add = !(i % 2 == 1 && j % 2 == 1);
      maze[i][j] = add ? 1 : 0; // Shorthand for if else set value
      if (!add) {
        sets.push_back({{i, j}});
      }
      if (i != height - 2 && !add) {
        edges.push_back({i + 1, j});
      }
      if (j != width - 2 && !add) {
        edges.push_back({i, j + 1});
      }
    }
  }

  maze[0][1] = 0;

  // Iterate while edges is not empty, removing randomly
  // Before it was a for loop which is where I messed up
  while (!edges.empty()) {
    int index = rand() % edges.size();
    auto removed = edges[index]; // automatically assigns type
    edges.erase(edges.begin() + index);

    int horiz = removed[0] % 2;
    vector<int> cell1, cell2;

    if (horiz) {
      cell1 = {removed[0], removed[1] - 1};
      cell2 = {removed[0], removed[1] + 1};
    } else {
      cell1 = {removed[0] - 1, removed[1]};
      cell2 = {removed[0] + 1, removed[1]};
    }

    int ind1 = indexOfSet(sets, cell1);
    int ind2 = indexOfSet(sets, cell2);

    if (ind1 != ind2) {
      auto add = sets[ind2]; // automatically assigns type
      sets.erase(sets.begin() + ind2);
      if (ind2 < ind1)
        ind1--;
      sets[ind1].insert(sets[ind1].end(), add.begin(), add.end());
      maze[removed[0]][removed[1]] = 0;
    }
  }

  maze[height - 1][width - 2] = 0;
  return maze;
}

int Maze::solveMaze(vector<vector<int>> &maze) {
  int m = maze.size();
  int n = maze[0].size();

  // Initialize distances to infinity
  vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
  // Initialize previous cell pointers to (-1, -1)
  vector<vector<pair<int, int>>> prev(m, vector<pair<int, int>>(n, {-1, -1}));

  // Priority queue for Dijkstra's algorithm
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      pq;

  // Starting cell
  dist[0][1] = 0;
  pq.push(make_pair(0, make_pair(0, 1)));

  while (!pq.empty()) {
    // Get cell with smallest distance from the priority queue
    pair<int, pair<int, int>> front = pq.top();
    pq.pop();
    int d = front.first;
    int i = front.second.first;
    int j = front.second.second;

    // If we have already found a shorter path to this cell, skip it
    if (d > dist[i][j]) {
      continue;
    }

    // Update the distances and previous cell pointers for each neighbor
    vector<pair<int, int>> neighbors = pathNeighbors(maze, i, j);
    for (const auto &neighbor : neighbors) {
      int ni = neighbor.first;
      int nj = neighbor.second;
      int nd = d + 1;
      if (nd < dist[ni][nj]) {
        dist[ni][nj] = nd;
        prev[ni][nj] = {i, j};
        pq.push(make_pair(nd, make_pair(ni, nj)));
      }
    }
  }

  // Mark the shortest path in the maze
  int i = m - 2;
  int j = n - 2;
  while (prev[i][j].first != -1) {
    maze[i][j] = 2;
    int pi = prev[i][j].first;
    int pj = prev[i][j].second;
    i = pi;
    j = pj;
  }
  maze[i][j] = 2;

  maze[maze.size() - 1][maze[0].size() - 2] = 2;
  maze[maze.size() - 2][maze[0].size() - 2] = 2;

  // Return the length of the shortest path
  return dist[m - 2][n - 2] + 2;
}