# Ročníkový projekt
Hľadanie hamiltonovských a skoro hamiltonovských kružníc v kubických grafoch

**Špecifikácia projektu (zimný semester):** Základným cieľom projektu je prehľadať všetky kubické planárne beztrojuholníkové grafy do 26 vrcholov a vyhľadať v nich dvojice (G, e) s vlastnosťou - žiadna hamiltonovská kružnica v G neobsahuje e (všetky planárne grafy do 26 vrcholov majú hamiltonovskú kružnicu). Na tomto výrazne zredukovanom zozname následne vykonať niekoľko podobných výpočtov (napr. nájsť takmer hamiltonovskú kružnicu vynechávajúcu daný vrchol).  

**Zmenená špecifikácia projektu (letný semester):** Základným cieľom projektu je prehľadať všetky 3-súvislé a 4-súvislé bipartitné grafy do určitého počtu vrcholov, ktorý bude závisieť od dostupnej výpočtovej sily. Pri vyšších počtoch vrcholov grafov by sa prehľadávanie mohlo uskutočňovať niekoľko dní, či týždňov. My sa uspokojíme s časom prehľadávania radovo v hodinách. V každom takomto bipartitnom grafe budeme hľadať hranu, ktorá sa nenachádza v žiadnom hamiltonovskom cykle daného grafu.

Na skompilovanie použite príkaz programu: 

        cc -o hamiltonian_plugin -O4 '-DPLUGIN="filter.c"' plantri.c cycles.c
 
Na skompilovanie test.c použite príkaz: 

        gcc test.c cycles.c -o test
        
Viac informácii v reporte na stránke k ročníkovému projektu:   
http://davinci.fmph.uniba.sk/~vanko32/    
Na stránke je aj dostúpna ukážka vygenerovaných 4-súvyslých bipartitných grafov, na ktorých sme spúštali náš algoritmus na hľadanie hamiltonovských cyklov.

Viac informácií ku generátoru grafov Plantri na stránke:   
https://users.cecs.anu.edu.au/~bdm/plantri/
     
