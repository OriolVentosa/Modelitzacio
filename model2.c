#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <time.h>

int mortalitat=50;
int despeseslimit=-1e5;  //nou
int plant = -50;       //nou
int anybenef;           //nou

void modificarllista(int [mortalitat], int);

int kgrecolectats(int [mortalitat]);
int kgrecolectatsegurs(int [mortalitat], int [anybenef]);

int consumanual(int [mortalitat],int, int);
int consumanualsegur(int [mortalitat], int [anybenef],int,int);

int plantar(int*, int [anybenef],int[anybenef], int [mortalitat],int*, int, int);
int despesesarbre(int, int, int);


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
    long long int despeses =-20000;
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
    printf("any benef %d", anybenef);
//     edats[0]= nombrearbres;
    edats[0]=plantar(&despesesseg,llista1, llista2, edats, &contador, desxar,0);

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
        kgp = kgrecolectatsegurs(edats, llista2);
        printf("KGP %d\n", kgp);
        beneficisseg = pkg*kgp-consumanualsegur(edats, llista2, despesesmin, despesesmax);
        despesesseg+= beneficisseg;
        
        modificarllista(edats, permortalitat);

        edats[0]=plantar(&despesesseg,llista1, llista2, edats, &contador, desxar,i);

//        printf("Els kg que es produeixen l'any %i són = %i\n",i,kg);
//        printf("Les despeses de l'any %i són = %lld\n",i,despeses);
        printf("Despeses segures %i\n",despesesseg);
        fprintf(f, "%d:    %lld   %lld\n", i, beneficisanuals , despeses);    //any, diners guanyats, com estem actualment
    }

    fclose(f);

    return 0;
}

void modificarllista(int edats[mortalitat], int permortalitat)
{
//     srand(time(NULL));
    
    int probabilitat[mortalitat];
    int posicio=0;

    for(int i=0; i<mortalitat;i++) //mortalitat
    {
        probabilitat[i]=posicio+edats[i];
        posicio=posicio+edats[i];
    }

    int random;
    for(int i=0;i<permortalitat;i++) //percentatge de mort
    {
  //      printf("random %d\n", contararbres);

        if(posicio!=0)
        {
        random=rand()%posicio;  //arreglar random
//         printf("random %d \n", random);

        for(int j=0;j<mortalitat;j++)
        {
            if(random<=probabilitat[j])
            {
                edats[j]=edats[j]-1;
                for(int k=j; k<mortalitat;k++)
                {
                    probabilitat[k]=probabilitat[k]-1;
                }
                posicio=posicio-1;
                break;
            }
        }
        }
    }

    
    int edatscanvi[mortalitat];
    for(int i=0; i<mortalitat; i++)
    {
        edatscanvi[i]=0;
    }

    int a;
    
    for(int i=0; i<mortalitat-1; i++)
    {
        a= (i-1);
        edatscanvi[i]=edats[a];
    }

    edatscanvi[0]=0;

    for(int i=0; i<mortalitat; i++)
    {
        edats[i]=edatscanvi[i];
    }
}


int kgrecolectats(int edats[mortalitat])
{
    int kg=0;
    float any;
    int anyint;
    
    for(int i=0;i<mortalitat;i++)
    {
        if(i<31)
        {
            any = (i*i)/6;
//            printf("Valor d'arbres d'edat %d %f\n", i,any);
            any = any*edats[i];
            anyint=any;
        }
        
        else
        {
            any=-((i*i)/10)+250;
//            printf("Valor d'arbres d'edat %d %f\n", i,any);
            any = any*edats[i];
            anyint=any;
            if(anyint<0) anyint=0;
        }
        kg=kg+anyint;
    }

    return kg;
}

int consumanual(int arbres[mortalitat],int dminima, int dmaxima)
{
    int total=0;
    
    for(int i=0; i<mortalitat;i++)
    {
        total=total+arbres[i];
    }
    
    int aleatori = dmaxima-dminima;
    
    int danuals;
    
    danuals = rand() % aleatori;

    danuals=danuals+dminima;
    
    danuals = danuals*total;

    return danuals;
}

int plantar(int *despeses, int anys[anybenef], int arbres[anybenef], int arbrestotals[mortalitat],int *contador, int desxar, int anyactual) //despeses segure/llista arbres plantats/llista anys quan s'ha plantats/longitud llista
{
    int arbrespl=0;

    while(1<2)
    {
        *despeses=*despeses+desxar;
        arbrespl+=1;
        if(*despeses<despeseslimit)
        {
            *despeses=*despeses-desxar;
            arbrespl-=1;
            break;
        }
    }
    
    printf("Arbres plantats %d\n",arbrespl);
    if(*contador == anybenef)
    {
        for(int i=0; i<anybenef-1; i++)
        {
            anys[i]=anys[i+1];
            arbres[i]=arbres[i+1];
        }
        *contador-=1;
    }
    
    anys[*contador]=anyactual;
    arbres[*contador]=arbrespl;
    arbrestotals[anyactual]=arbrespl;
    
    *contador+=1;
    return arbrespl;
}

int despesesarbre(int dmaxima, int preukg, int plant)
{
    float any;
    int anyint;
    for(int i=0;i<mortalitat;i++)
    {
            any = (i*i)/6;
//            printf("Valor d'arbres d'edat %d %f\n", i,any);
            anyint=any*preukg;
            if(anyint>dmaxima) 
            {
                anybenef=i;
                break;
            }
    }
    
    for(int i=0;i<anybenef;i++)
    {
            any = (i*i)/6;
//            printf("Valor d'arbres d'edat %d %f\n", i,any);
            anyint=any*preukg;
            plant= plant+anyint-dmaxima;
    }
    
    return plant;
}

int kgrecolectatsegurs(int arbres[mortalitat], int arbresplantats[anybenef])
{
    
    int kg=0;
    float any;
    int anyint;
    
    for(int i=0;i<mortalitat;i++)
    {
        if(i<31)
        {
            any = (i*i)/6;
            any = any*arbres[i];
            anyint=any;
        }
        
        else
        {
            any=-((i*i)/10)+250;
            any = any*arbres[i];
            anyint=any;
            if(anyint<0) anyint=0;
        }
        kg=kg+anyint;
    }
    
    for(int i=0;i<anybenef;i++)
    {
            any = ((anybenef-i)*(anybenef-i))/6;
            any = any*arbresplantats[i];
            anyint=any;
            kg=kg-anyint;
    }
    
    return kg;
}

int consumanualsegur(int arbres[mortalitat], int arbresplantats[anybenef],int dminima, int dmaxima)
{
    
    int total=0;
    
    for(int i=0; i<mortalitat;i++)
    {
        total=total+arbres[i];
        printf("Arbres d'edat %d: %d\n", i, arbres[i]);
    }
    
    printf("Arbres totals %d\n", total);
    for(int i=0; i<anybenef; i++)
    {
        total = total- arbresplantats[i];
        printf("Arbres plantats %d: %d\n", i, arbresplantats[i]);
    }
        
    int aleatori = dmaxima-dminima;
    
    int danuals;
    
    danuals = rand() % aleatori;

    danuals=danuals+dminima;
    
    danuals = danuals*total;

    return danuals;
}