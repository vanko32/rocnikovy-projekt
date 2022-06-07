#include "filter.h"

/*
Samotny plug-in do programu plantri. Je to tzv. filter, teda, ak vraciame 1, plantri 
vrati graf, ak vraciame 0, plantri graf odfiltruje. My aktualne vraciame kazdy graf, ktory 
zaroven aj vypisujeme na standardny vystup. Pre blizsie informacie o implementacii pluginu do generatora 
plantri odporucam pozriet guide (https://users.cecs.anu.edu.au/~bdm/plantri/plantri-guide.txt).

Pracujeme s 3-suvislymi a 4-suvislymi kubickymi bipartitnymi grafmi. Je potrebne preto z 
vygenerovaneho grafu spravit dual (dual z 3-suvisleho eulerovskej planarnej triangulacie je 
3-suvisly bipartitny graf. Rovnako to plati aj pre 4-suvisle).
Pre viac info odporucam pozriet funkciu compute_dual_code v plantri.c a guide 
(https://users.cecs.anu.edu.au/~bdm/plantri/plantri-guide.txt).
*/
static int filter_hamiltonian(int nbtot, int nbop, int doflip){
    unsigned char code[MAXF+MAXE+1];
    unsigned char code_edges[MAXF+MAXE+1];

    compute_dual_code(code);
    compute_dual_code(code_edges); 
    print_graph(code, 0);

    int path[code[0] + 1]; 
    path_initialization(path, code[0] + 1);
    hamiltonian_cycle(path, 2, code, code_edges, 0);

    /*
    Overime, ci existuje nejaka hrana, ktora sa nenachadza v ziadnom 
    hamiltonovskom cykle. Ak ano, tak vypiseme hranu a prislusny graf. 
    */
    for (int i = 1; i <= code[0]; i++){
        for (int j = 1; j <= code[0]; j++){
            if (is_edge(i, j, code_edges)){
                printf("%d : %d", i, j);
                printf("\n");
                print_graph(code, 1); 
            }
        }
    }
    return 1; 
}