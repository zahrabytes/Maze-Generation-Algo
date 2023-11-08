#include "Maze.h"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

void printMaze(vector<vector<int>> maze, char mazeType) {
  // Print out maze
  string border;
  string path;
  if (mazeType == 'k') {
    path = "\U0001F3C3";
    border = "\U0001F7EA";
  } else if (mazeType == 'p') {
    border = u8"\U0001F47D";
    path = u8"\U0001F47E"; 
  }
  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[i].size(); j++) {
      if (maze[i][j] == 1) {
        cout << border;
      } else if (maze[i][j] == 2) {
        cout << path;
      } else {
        cout << "  ";
      }
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  int seed;
  string algorithm;
  char ans;

  cout << "Enter a random seed: ";
  cin >> seed;
  srand(seed);

  cout << "Enter an algorithm (Kruskal/Prim): ";
  cin >> algorithm;

  char choice = tolower(algorithm[0]);

  if (choice == 'p') {
    cout << endl
         << u8"\U0001F47D" << " Prim's Maze: Brought to You by Sala "
         << u8"\U0001F47E" << endl
         << endl;
    Maze prims;

    vector<vector<int>> salasmaze = prims.primsMaze(30, 30);

    double primspath = prims.solveMaze(salasmaze);
    double primspercent = (primspath / 900.0) * 100.0;
    printMaze(salasmaze, 'p');
    cout << "Seed: " << seed << ", Path length: " << primspath
         << ", Percent of maze: "
         << "(" << primspercent << "%)" << endl;

    cout << endl
         << "Would you like to see the longest path Prim's Maze? (Y/N): ";
    cin >> ans;
    ans = toupper(ans);

    if (ans == 'Y') {
      seed = 1074203989;
      srand(seed);

      cout << endl
           << u8"\U0001F47D" << " Prim's Longest Maze: Brought to You by Sala "
           << u8"\U0001F47E" << endl
           << endl;

      Maze Largest_prims;

      vector<vector<int>> Largest_salasmaze = Largest_prims.primsMaze(30, 30);
      printMaze(Largest_salasmaze, 'p');
      double Largest_primspath = prims.solveMaze(Largest_salasmaze);
      double Largest_primspercent = (Largest_primspath / 900.0) * 100.0;
      printMaze(Largest_salasmaze, 'p');
      cout << "Seed: " << seed << ", Path length: " << Largest_primspath
           << ", Percent of maze: "
           << "(" << Largest_primspercent << "%)" << endl;
    } else {
      cout << endl
           << "We hope you had an a-maze-ing time ;) Have fun alien hunting!"
           << u8"\U0001F47E" << endl;
    }
  } else if (choice == 'k') {
    cout << endl
         <<  "\U0001F607" << " Kruskal's Maze: Brought to You by Zahra "
         << "\U0001F52A" << endl
         << endl;
    Maze kruskals;
    vector<vector<int>> zsmaze = kruskals.kruskalsMaze(30, 30);
    printMaze(zsmaze, 'k');
    double kruspath = kruskals.solveMaze(zsmaze);
    double kruspercent = (kruspath / 900.0) * 100.0;
    printMaze(zsmaze, 'k');
    cout << "Seed: " << seed << ", Path length: " << kruspath
         << ", Percent of maze: "
         << "(" << kruspercent << "%)" << endl;
    cout << endl
         << "Would you like to see the longest path Kruskal's Maze? (Y/N): ";
    cin >> ans;
    ans = toupper(ans);
    if (ans == 'Y') {
      seed = 2013798595;
      srand(seed);

      cout << endl
           << "\U0001F607" << " Kruskal's Longest Maze: Brought to You by Zahra "
           << "\U0001F52A" << endl
           << endl;

      Maze Largest_kruskal;

      vector<vector<int>> Largest_zsmaze = Largest_kruskal.kruskalsMaze(30, 30);

      double Largest_kruskalpath = Largest_kruskal.solveMaze(Largest_zsmaze);
      double Largest_kruskalpercent = (Largest_kruskalpath / 900.0) * 100.0;
      printMaze(Largest_zsmaze, 'k');
      cout << "Seed: " << seed << ", Path length: " << Largest_kruskalpath
           << ", Percent of maze: "
           << "(" << Largest_kruskalpercent << "%)" << endl;
    } else {
      cout << endl
           << "We hope you had an a-maze-ing time ;) Have fun alien hunting!"
           << u8"\U0001F47E" << endl;
    }
  } else {
    cerr << "Invalid Algorithm." << endl;
  }

  return 0;
}
