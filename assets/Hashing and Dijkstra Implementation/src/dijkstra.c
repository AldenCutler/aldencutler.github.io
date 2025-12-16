#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./dijkstra.exe <filename>\n");
        return 1;
    }

    // Open file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    // Read in number of vertices
    int num_vertices;
    fscanf(fp, "%d", &num_vertices);

    // Read in adjacency matrix
    int **adj_matrix = malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; i++) {
        adj_matrix[i] = malloc(num_vertices * sizeof(int));
        for (int j = 0; j < num_vertices; j++) {
            fscanf(fp, "%d", &adj_matrix[i][j]);
        }
    }

    // allocate arrays
    int *distances = malloc(num_vertices * sizeof(int));
    int *visited = malloc(num_vertices * sizeof(int));
    int *previous = malloc(num_vertices * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < num_vertices; i++) {
        distances[i] = INT_MAX;             // theoretically this should be infinity, but we can't represent that in an int so we use INT_MAX instead
        visited[i] = 0;
        previous[i] = -1;
    }

    // Read in start and end vertices
    int start, end;
    printf("Enter start and end vertices: ");
    scanf("%d %d", &start, &end);

    distances[start] = 0;

    // Dijkstra's algorithm
    for (int i = 0; i < num_vertices; i++) {
        int min = INT_MAX;
        int min_index = -1;
        // find the unvisited vertex with the smallest distance
        for (int j = 0; j < num_vertices; j++) {
            if (visited[j] == 0 && distances[j] < min) {
                min = distances[j];
                min_index = j;
            }
        }

        // if we didn't find a vertex, we're done
        if (min_index == -1) {
            break;
        }
        // mark the vertex as visited
        visited[min_index] = 1;

        // update distances to adjacent vertices
        for (int j = 0; j < num_vertices; j++) {
            if (visited[j] == 0 && adj_matrix[min_index][j] != 0) {
                // if the distance to j through min_index is less than the current distance to j, update the distance
                int new_distance = distances[min_index] + adj_matrix[min_index][j];
                if (new_distance < distances[j]) {
                    distances[j] = new_distance;
                    previous[j] = min_index;
                }
            }
        }
    }

    // print shortest path
    printf("Shortest path from %d to %d:\n", start, end);
    int current = end;
    while (current != start) {
        printf("%d <- ", current);
        current = previous[current];
    }
    printf("%d\n", start);

    printf("Distance: %d\n", distances[end]);

    return 0;
}