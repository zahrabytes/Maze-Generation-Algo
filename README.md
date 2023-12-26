# Maze Generator and Solver

## Introduction

Welcome! this C++ program provides a maze generation and solving experience using three algorithms: Prim's and Kruskal's for maze generation and Dijkstra's for maze solving. The mazes are visualized using Unicode characters, creating an interactive and visually appealing environment. This project was developed by [Sala Tran-Huu](https://github.com/stranhuu) and [Zahra Bukhari](https://github.com/zahrabytes)

## Maze Generation Algorithms

### Prim's Algorithm
Prim's algorithm initializes with a grid of walls and begins by selecting a random cell as the starting point. It then systematically grows the maze by connecting neighboring cells to the existing structure. This process involves repeatedly selecting a random wall and connecting the two unconnected cells on either side. The algorithm ensures that the maze remains connected throughout, resulting in a tree-like structure. 

### Kruskal's Algorithm
Kruskal's algorithm, on the other hand, views each cell as an independent set and starts with a grid of walls. It then randomly removes walls between different sets, gradually forming a maze. This approach focuses on connecting sets rather than individual cells, resulting in a maze that is also a collection of trees. Kruskal's algorithm ensures the maze is connected, and the final structure is a forest of interconnected trees.

### Dijkstra's Algorithm
Dijkstra's algorithm is employed to find the shortest path from the maze's entrance to its exit.

## Visualization
The program visualizes the mazes using Unicode characters. Walls are represented by emojis, paths are displayed with different emojis, and the solved path is highlighted for clarity.

![Screenshot 2023-09-07 111201](https://github.com/zahrabytes/Maze-Generation-Algo/assets/146145027/41d313c5-b73e-4e01-812b-b83a5f490a09)

## Getting Started

### Prerequisites
Ensure you have a C++ compiler installed on your system. You can use g++ for compilation.

### Usage
- **Enter a random seed:** Provide a seed for the random number generator.
- **Enter an algorithm (Kruskal/Prim):** Choose the maze generation algorithm.
- View the generated maze and its solution.
- Optionally, explore the longest path that we have have generated (so far) for each algorithm.
