#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "consum.h"
#include "kg.h"
#include "modificar.h"

int mortalitat=50;  //hauriem de preguntar-ho
int despeseslimit=-1e4;  //nou  //preguntar-ho
int plant = -50;       //nou    //preguntar-ho tambe?
int anybenef;           //nou


int main(int argc, char *nom[])
{
    int edats[mortalitat];
    int anysconreant;
    int arbresmax;
    double permortalitat;
    int desxar, stop, total=0;  //nou
    int contador=0;
    int kg=0;
    int kgp=0;  //kg segurs
    long long int beneficisanuals;
    int pkg;    //preu per kg
    long long int despeses =-1000;
    int despesesseg = despeses;
    int beneficisseg;
    
    int despesesmin, despesesmax;
    
    FILE* f = fopen(nom[1], "w");

    if(f==NULL)
    {
        printf("No existeix el fitxer introduit\n");
        return 1;
    }

    printf("Indica els anys de conreu: ");
    scanf("%d", &anysconreant);
    
    printf("Quants arbres podem plantar com a màxim: ");
    scanf("%d", &arbresmax);

    printf("Indica percentatge arbres que es moren a l'any: ");
    scanf("%lf", &permortalitat);

    printf("Indica el preu per quilogram de fruits: ");
    scanf("%d",&pkg);
    
    printf("Indica despeses mínimes per arbre: ");
    scanf("%d",&despesesmin);

    printf("Indica despeses màximes per arbre: ");
    scanf("%d",&despesesmax);
    
    printf("\n");
    
    desxar = despesesarbre(0,despesesmax, pkg, plant);
    stop=anycomp(despesesmax, pkg, plant);
    
    int llista2[anybenef];
    
    for(int i = 0; i<anybenef; i++)
    {
        llista2[i]=0;
    }
    
    for(int i=0; i<mortalitat; i++)
    {
        edats[i]=0;
    }
    
    edats[0]=plantar(&despesesseg,&despeses, llista2, edats, &contador, desxar,0,arbresmax);
    
    for(int i=1; i<anysconreant; i++)
    {
        printf("Any %d\n", i);

        //Beneficis i despeses reals
                
        kg=kgrecolectats(edats);
        beneficisanuals=pkg*kg-consumanual(edats,despesesmin, despesesmax);
        
        despeses+=beneficisanuals;
        
        //Beneficis i despeses modificades
        
        kgp = kgrecolectatsegurs(edats, llista2, i);
        beneficisseg = pkg*kgp-consumanualsegur(edats,despesesmin, despesesmax);
        despesesseg+= beneficisseg;
        
        despesesseg=armor(edats, llista2, despesesseg, contador, despesesmax, pkg);
        
        modificarllista(edats, permortalitat);

        if(i<(anysconreant-stop))
        {
            edats[0]=plantar(&despesesseg,&despeses, llista2, edats, &contador, desxar,i, arbresmax);
        }
        
        
        for(int i=0; i<mortalitat;i++)
        {
            total=total+edats[i];
        }
        
        printf("despeses %lld / kg any: %d\n", despeses, kg);

        fprintf(f, "%d:    %lld   %lld  %d\n", i, beneficisanuals , despeses,total);  //any, diners guanyats, com estem actualment
        
        total=0;
    }
    
    fclose(f);

    return 0;
}