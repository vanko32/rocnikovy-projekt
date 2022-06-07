#ifndef FILTER_H_ 
#define FILTER_H_

#include "cycles.h"

/* Plug-in do generatora plantri */
#define FILTER filter_hamiltonian 

#define MAXN 64            // maximalny pocet vrcholov
#define MAXE (6*MAXN-12)   // maximalny pocet orientovanych hran
#define MAXF (2*MAXN-4)    // maximalny pocet stien

// Plantri plug-in 
static int filter_hamiltonian(int nbtot, int nbop, int doflip);

#endif // FILTER_H_