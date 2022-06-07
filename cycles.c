#include "cycles.h"
/*
POZNAMKA: Vsetky funkcie sluzia na pracu s 3-suvislymi a 4-suvislymi 
bipartitnymi kubickymi grafmi.
Funkcie nesluzia na pracu s inymi typmi grafov, kedze ich vystupy by mohli byt nespravne.
V rocnikovom projekte som sa zaoberal vyssie spomenutymi typmi grafov, preto aj funkcie 
su prisposobene na pracu s danymi typmi grafov (dovody: vyssia rychlost, efektivnost...).  

Pracujem s internou Plantri reprezentaciou grafov: 

    "computes a code by numbering the vertices in a breadth first manner and
    then listing them in code. Code is a sequence of numbers of length ne+nv+1.
    The first entry is the number of vertices.
    Then the numbers of the vertices adjacent to the vertex numbered 1 are
    given -- ended by a 0, and listed in clockwise orientation.
    Then those adjacent to 2, ended by a 0, etc."

Dany komentar s vysvetlenim reprezentacie grafov je dohladatelny v plantri.c pri funkcii compute_code
Plantri je generator grafov (viac informacii v reporte na stranke k rocnikovemu projektu alebo na
https://users.cecs.anu.edu.au/~bdm/plantri/). Subor plantri. pochadza z danej stranky. 

________________________________________________________________________________________________________

Vypis grafu. Ak je hodnota argumentu write_to_file rozna od 0, tak graf sa vypise do textoveho 
suboru output.txt. 
*/
void print_graph(unsigned char code[], int write_to_file){
    FILE *output;
    output = fopen("output.txt", "a");

    int number_of_vertices = code[0];
    for (int i = 1; i <= number_of_vertices; i++){ 
        printf("%d: ", i); 
        if (write_to_file != 0){
            fprintf(output, "%d: ", i);
        }

        for (int j = (i-1) * 4 + 1; j < (i-1) * 4 + number_of_vertices; j++){
            if (code[j] == 0){
                break; 
            } else {
                printf("%d ", code[j]);
                if (write_to_file != 0){
                 fprintf(output, "%d ", code[j]);
                }

            }
        }
        printf("\n"); 
        if (write_to_file != 0){
            fprintf(output, "\n");
        }
    }
    printf("\n"); 
    if (write_to_file != 0){
        fprintf(output, "\n");
    }
    fclose(output);
}

/*
Funkcia zisti, či existuje hrana medzi dvoma vrcholmi. 
*/
int is_edge(int u, int v, unsigned char code[]){
    for (int i = (u-1) * 4 + 1; i < (u-1) * 4 + 4; i++){
        if (code[i] == v){
            return 1;
        }
    }
    return 0; 
}

/*
Pociatocna inicializacia path. Na pozicii 1 sa nachadza vrchol 1, ostatne pozicie v path inicializujeme na -1.
*/
void path_initialization(int path[], int n){
    if (n > 1){
        path[0] = -1; 
        path[1] = 1; 
        for (int i = 2; i <= n; i++){
            path[i] = -1;
        }
    }
}

/*
Funkcie next_vertex a hamiltonian_cycle su bezny backtracking na hladanie 
hamiltonovskych cyklov v grafoch. 
*/
void next_vertex(int path[], int k, unsigned char code[]){
    while(1){
        int duplicate = 0; 
        if ((path[k] + 1) > (code[0])){
            path[k] = -1;
        } else {
            path[k] = path[k] + 1; 
        }
        if (path[k] == (-1)){
            return; 
        }
        if (is_edge(path[k-1],path[k], code)) {
            for (int i = 1; i < k; i++){
                if (path[i] == path[k]){
                    duplicate = 1; 
                    break;
                }
            }
            if (duplicate == 0){
                if ((k < (code[0])) || ((k == (code[0])) && (is_edge(path[1],path[k],code)))){    
                    return; 
                }
            }
        }   
    }  
}

void hamiltonian_cycle(int path[], int k, unsigned char code[], unsigned char code_edges[], int write_to_file){
    while(1){
        next_vertex(path, k, code); 
        if (path[k] == (-1)){
            return;
        }
        if (k == (code[0])){
            print_hamiltonian_cycle(path, code[0], code_edges, write_to_file); 
        } else {
            hamiltonian_cycle(path, (k+1), code, code_edges, write_to_file);
        }
    }  
}

/*
Funkcia vypise hamiltonovsky cyklus a zaroven v poli code_edges prepise hrany, ktore 
sa vyskytli v hamiltonovskom cykle na 255 (kedze pracujeme s unsigned char, tak zaporne hodnoty
pouzivat nemozeme. Zaroven s istotou vieme, ze s grafom o 255 vrcholoch pracovat nebudeme). 
code_edges sluzi na pamatanie si toho, ake hrany sa v hamiltonovskych cykloch vyskytli. Ak sa u-v hrana 
este nevyskytla v ziadnom hamiltonovskom cykle, tak medzi susedmi vrcholu u najdeme v a vice versa. 
Ak sa uz tato hrana v nejakom hamiltonovskom cykle vyskytla, tak medzi susedmi vrchola v najdeme 
namiesto vrchola u hodnotu 255. A samozrejme to plati aj naopak, medzi susedmi vrchola u najdeme 
namiesto vrchola v hodnotu 255.  
Argument write_to_file nam urcuje, ci chceme hamiltonovske cykly zapisovat do textoveho suboru output.txt, 
ak ano, hodnota musi byt rozna od 0. 
*/
void print_hamiltonian_cycle(int path[], int n, unsigned char code_edges[], int write_to_file){
    FILE *output;
    output = fopen("output.txt", "a");

    for (int i = 1; i <= n; i++){
        printf("%d ", path[i]); 
        if (write_to_file != 0){
            fprintf(output, "%d ", path[i]);
        }

        if (i < n){
            for (int j = (path[i]-1) * 4 + 1; j < (path[i]-1) * 4 + 4; j++){
                if (code_edges[j] == path[i+1]){
                    code_edges[j] = 255; 
                    for (int k = (path[i+1]-1) * 4 + 1; k < (path[i+1]-1) * 4 + 4; k++){
                        if (code_edges[k] == path[i]){
                        code_edges[k] = 255; 
                        }
                    }
                }
            }
        } else {
            for (int j = (path[i]-1) * 4 + 1; j < (path[i]-1) * 4 + 4; j++){
                if (code_edges[j] == path[1]){
                    code_edges[j] = 255; 
                    for (int k = (path[1]-1) * 4 + 1; k < (path[1]-1) * 4 + 4; k++){
                        if (code_edges[k] == path[i]){
                        code_edges[k] = 255; 
                        }
                    }
                }
            }
        }
    }

    printf("%d", -2); 
    printf("\n");
    if (write_to_file != 0){
        fprintf(output, "%d", -2);
        fprintf(output, "\n");
    }
    fclose(output);
}