#include "cycles.h"

/*
Jednoduchy test, ktory ma za ulohu overit spravne fungovanie nasho backtrackingu pri hladani
hamiltonovskych cyklov.

Test spravime na grafe kocky, ktory vyzera nasledovne: 

1: 2 4 5 
2: 1 3 6 
3: 2 4 7 
4: 1 3 8
5: 1 6 8 
6: 2 5 7
7: 3 6 8 
8: 4 5 7 

O tomto grafe vieme, ze obsahuje 12 orientovanych hamiltonovskych cyklov. 

1 2 3 4 8 7 6 5 
1 2 3 7 6 5 8 4
1 2 6 5 8 7 3 4 
1 2 6 7 3 4 8 5 

1 4 3 2 6 7 8 5 
1 4 3 7 8 5 6 2 
1 4 8 5 6 7 3 2 
1 4 8 7 3 2 6 5 

1 5 6 2 3 7 8 4 
1 5 6 7 8 4 3 2 
1 5 8 4 3 7 6 2 
1 5 8 7 6 2 3 4 

Nasim cielom je ukazat spravnost fungovania nasho algoritmu tym, ze vsetky tieto hamiltonovske 
cykly v danom grafe najde. 

Druhy graf, na ktorom spravime test bude znamy Petersenov graf, ktory je najmensi kubicky graf
neobsahujuci most, v ktorom sa nenachadza ziaden hamiltonovsky cyklus. 

1: 8, 9, 10
2: 6, 7, 10
3: 5, 7, 9 
4: 5, 6, 8 
5: 3, 4, 10
6: 2, 4, 9 
7: 2, 3, 8 
8: 1, 4, 7
9: 1, 3, 6
10: 1, 2, 5

Vysledkom nasho backtrackingu by teda nemala byt ziaden hamiltonovsky cyklus. 
*/

int check_cycles(int cycles_number, int vertices_number, int cycles[][vertices_number], unsigned char code[], unsigned char code_edges[], int path[]){
    // Vymazanie obsahu, ktory sa nachadza v textovom subore output.txt
    fclose(fopen("output.txt", "w"));

    print_graph(code, 0);
    hamiltonian_cycle(path, 2, code, code_edges, 1);

    int counter = 0; 
    int help_counter = counter; 

    FILE* output; 
    output = fopen("output.txt", "r");

    int c; 
    while(c != EOF){
        int buffer[vertices_number + 1];
        for (int i = 0; i < vertices_number + 1; i++){
            c = fscanf(output, "%d", &buffer[i]);
        } 

        if (buffer[vertices_number] == -2 && c != EOF){
            int helper = 0; 
            help_counter = counter; 
            for (int j = 0; j < cycles_number; j++){
                for (int k = 0; k < vertices_number; k++){
                    if (cycles[j][k] != buffer[k]){
                        break; 
                    }
                    if ((k == (vertices_number - 1)) && cycles[j][k] == buffer[k]){
                        counter = counter + 1; 
                        helper = 1; 
                        break; 
                    }
                    if (helper == 1){
                        break; 
                    }
                }
            }
        }
        if (help_counter == counter && help_counter != 0){
            printf("Test je neuspesny \n"); 
            break;
        }
    }

    if (cycles_number == counter){
        printf("Test je uspesny \n");
    } else {
        printf("Test je neuspesny \n"); 
    }
}

int main(){
    unsigned char cube[33] = {8, 2, 4, 5, 0, 1, 3, 6, 0, 2, 4, 7, 0, 1, 3, 8, 0, 1, 6, 8, 0, 2, 5, 7, 0, 3, 6, 8, 0, 4, 5, 7, 0};
    unsigned char cube_edges[33] = {8, 2, 4, 5, 0, 1, 3, 6, 0, 2, 4, 7, 0, 1, 3, 8, 0, 1, 6, 8, 0, 2, 5, 7, 0, 3, 6, 8, 0, 4, 5, 7, 0};
    int path_cube[cube[0] + 1]; 
    path_initialization(path_cube, cube[0] + 1); 
    
    // Ocakavane hamiltonovske cykly
    int cube_cycles[12][8] = {
        {1, 2, 3, 4, 8, 7, 6, 5}, 
        {1, 2, 3, 7, 6, 5, 8, 4}, 
        {1, 2, 6, 5, 8, 7, 3, 4}, 
        {1, 2, 6, 7, 3, 4, 8, 5}, 
        {1, 4, 3, 2, 6, 7, 8, 5}, 
        {1, 4, 3, 7, 8, 5, 6, 2}, 
        {1, 4, 8, 5, 6, 7, 3, 2}, 
        {1, 4, 8, 7, 3, 2, 6, 5}, 
        {1, 5, 6, 2, 3, 7, 8, 4}, 
        {1, 5, 6, 7, 8, 4, 3, 2}, 
        {1, 5, 8, 4, 3, 7, 6, 2}, 
        {1, 5, 8, 7, 6, 2, 3, 4}
        };
    
    /* Test grafu kocky */ 
    check_cycles(12, 8, cube_cycles, cube, cube_edges, path_cube);

    unsigned char petersen[41] = {10, 10, 9, 8, 0, 6, 7, 10, 0, 5, 7, 9, 0, 5, 6, 8, 0, 3, 4, 10, 0, 2, 4, 9, 0, 2, 3, 8, 0, 1, 4, 7, 0, 1, 3, 6, 0, 1, 2, 5, 0};
    unsigned char petersen_edges[41] = {10, 10, 9, 8, 0, 6, 7, 10, 0, 5, 7, 9, 0, 5, 6, 8, 0, 3, 4, 10, 0, 2, 4, 9, 0, 2, 3, 8, 0, 1, 4, 7, 0, 1, 3, 6, 0, 1, 2, 5, 0};
    int path_petersen[petersen[0] + 1]; 
    path_initialization(path_petersen, petersen[0] + 1); 
    int petersen_cycles[0][0] = {};

    /* Test Petersonovho grafu - odkomentujte */ 
    //check_cycles(0, 0, petersen_cycles, petersen, petersen_edges, path_petersen);
}