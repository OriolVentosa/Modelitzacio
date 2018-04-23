#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "consum.h"
#include "kg.h"
#include "modficar.h"

// #include <time.h>

int mortalitat=50;
int despeseslimit=-1e4;  //nou
int plant = -50;       //nou
int anybenef;           //nou


int main(int argc, char *nom[])
{
//     int nombrearbres;
    int edats[mortalitat];
    int anysconreant;
    int permortalitat;
    int desxar;  //nou
    int contador=0;
    int kg=0;
    int kgp=0;
    long long int beneficisanuals;
    int pkg;
    long long int despeses =-100;
    int despesesseg = despeses;
    int beneficisseg;
    
    int despesesmin, despesesmax;
    
    FILE* f = fopen(nom[1], "w");

    if(f==NULL)
    {
        printf("No existeix el fitxer introduit\n");
        return 1;
    }

//     printf("Indica els arbres que vol plantar inicialment: ");
//     scanf("%d",&nombrearbres);

//     printf("Indica els anys de vida màxims: ");
//     scanf("%d",&mortalitat);

    printf("Indica els anys de conreu: ");
    scanf("%d", &anysconreant);

//     printf("Edat que comencem a recol·lectar: ");
//     scanf("%d", &inici);

    printf("Indica la mitjana d'arbres que es moren a l'any: ");
    scanf("%d", &permortalitat);

//     printf("Indica els quilograms de fruits que genera cada arbre per any: ");
//     scanf("%d",&quantskg);

    printf("Indica el preu per quilogram de fruits: ");
    scanf("%d",&pkg);
    
    printf("Indica despeses mínimes per arbre: ");
    scanf("%d",&despesesmin);

    printf("Indica despeses màximes per arbre: ");
    scanf("%d",&despesesmax);
    
    
    desxar = despesesarbre(despesesmax, pkg, plant);
    
    int llista1[anybenef];
    int llista2[anybenef];
    
    for(int i = 0; i< anybenef; i++)
    {
        llista1[i]=0;
        llista2[i]=0;
    }
    for(int i=0; i<mortalitat; i++)
    {
        edats[i]=0;
    }
//     edats[0]= nombrearbres;
    edats[0]=plantar(&despesesseg,&despeses, llista1, llista2, edats, &contador, desxar,0);

    for(int i=1; i<anysconreant; i++)
    {
        printf("Any %d\n", i);

//         for(int j=0; j<mortalitat; j++)
//         {
//             printf("Arbres d'edat %d: %d\n", j, edats[j]);
//         }
        
        //Beneficis i despeses reals
        kg=kgrecolectats(edats);
        beneficisanuals=pkg*kg-consumanual(edats,despesesmin, despesesmax);
        despeses+=beneficisanuals;

        //Beneficis i despeses modificades
        kgp = kgrecolectatsegurs(edats, llista2, i);
        printf("KGP %d\n", kgp);
        beneficisseg = pkg*kgp-consumanualsegur(edats, llista2, despesesmin, despesesmax);
        despesesseg+= beneficisseg;
        
        modificarllista(edats, permortalitat);
        
        if(i<(anysconreant-anybenef))
        {
            edats[0]=plantar(&despesesseg,&despeses, llista1, llista2, edats, &contador, desxar,i);
        }
//        printf("Els kg que es produeixen l'any %i són = %i\n",i,kg);
//        printf("Les despeses de l'any %i són = %lld\n",i,despeses);
        printf("Despeses segures %i\n",despesesseg);
        fprintf(f, "%d:    %lld   %lld\n", i, beneficisanuals , despeses);  //any, diners guanyats, com estem actualment
    }
    int total=0;
    for(int i=0; i<mortalitat;i++)
    {
        total=total+edats[i];
    }
    printf("Arbres totals = %i", total);
    
    
    fclose(f);

    return 0;
}



