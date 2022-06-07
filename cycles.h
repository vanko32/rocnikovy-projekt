#ifndef CYCLES_H_ 
#define CYCLES_H_

#include <stdio.h>
#include <stdlib.h>

// Vypis grafu + zistovanie existencie hrany
void print_graph(unsigned char code[], int write_to_file);
int is_edge(int u, int v, unsigned char code[]); 

// Backtracking + vypis hamiltonovskych cyklov
void path_initialization(int path[], int n); 
void hamiltonian_cycle(int path[], int k, unsigned char code[], unsigned char code_edges[], int write_to_file);
void next_vertex(int path[], int k, unsigned char code[]);
void print_hamiltonian_cycle(int path[], int n, unsigned char code_edges[], int write_to_file); 

#endif // CYCLES_H_