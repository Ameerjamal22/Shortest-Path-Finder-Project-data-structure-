# Shortest-Path-Finder-Project-data-structure

## Overview

The Shortest Path Finder is a C program that calculates the shortest path and distance between cities using both Breadth-First Search (BFS) and Dijkstra's algorithm. It reads city data from the "cities.txt" file and constructs a graph of cities and their distances. Users can enter source and destination cities, and the program will find and display the shortest path between them along with the distance.

## Getting Started

### Prerequisites

To compile and run the program, you need the following:

- A C compiler (e.g., GCC)
- A terminal or command prompt
- The "cities.txt" file containing city data

### Features

Load Data from File: Load city data from the "cities.txt" file to construct the graph.
Enter Source: Allow the user to input the source city.
Enter Destination: Allow the user to input the destination city.
Calculate Shortest Path (BFS): Calculate and display the shortest path and distance using BFS.
Calculate Shortest Path (Dijkstra's): Calculate and display the shortest path and distance using Dijkstra's algorithm.
Exit: Quit the program.
Data Structures
The program uses the following data structures:

List of Vertices: A list of cities (vertices) and their indexes in the graph.
Adjacency List: An array of linked lists to represent the edges (distances) between cities.
Usage
Choose option 1 to load data from the "cities.txt" file, which constructs the graph.
Enter the source city's name when prompted.
Enter the destination city's name when prompted.
Choose option 3 to calculate the shortest path using BFS.
Choose option 4 to calculate the shortest path using Dijkstra's algorithm.
The program will display the shortest path and distance between the source and destination cities.
Repeat steps 2-6 to find paths for other city pairs or choose option 5 to exit.
Example
Welcome to the shortest Path program 

Enter your Choice :
1-Load data from the file cities.txt .
2-Enter source .
3-Enter destination .
4-Exit
1

Enter your Choice :
1-Load data from the file cities.txt .
2-Enter source .
3-Enter destination .
4-Exit
2
Enter the source :Cairo

Enter your Choice :
1-Load data from the file cities.txt .
2-Enter source .
3-Enter destination .
4-Exit
3
Enter the destination :Alexandria

BFS : [Cairo -> Alexandria ]
Dijkstra :- Distance = 208 :    Path :[Cairo -> Alexandria ]
Data File Format (cities.txt)
The "cities.txt" file should contain city data in the following format:

City1 City2 Distance
City2 City3 Distance
...
Each line represents a connection between two cities (City1 and City2) with a specified distance.
The distances should be integers.
Example:
Cairo Alexandria 208
Cairo Giza 15
Alexandria Giza 220
...

### Compilation

Use the following command to compile the program:

```bash
gcc main.c -o shortest_path_finder
Running the Program
After compiling, run the program with this command:

bash
Copy code
./shortest_path_finder

