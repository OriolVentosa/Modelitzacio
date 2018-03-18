#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <time.h>

int mortalitat=50;

void modificarllista(int [mortalitat], int);
int kgrecolectats(int [mortalitat]);
int consumanual(int [mortalitat],int, int);


int main(int argc, char *nom[])
{
    int nombrearbres;
    int anysconreant;
    int permortalitat;
    int kg=0;
    long long int beneficisanuals;
    int pkg;
    long long int despeses=-20000;
    int despesesmin, despesesmax;

    FILE* f = fopen(nom[1], "w");

    if(f==NULL)
    {
        printf("No existeix el fitxer introduit\n");
        return 1;
    }

    printf("Indica els arbres que vol plantar inicialment: ");
    scanf("%d",&nombrearbres);

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
    
    int edats[mortalitat];

    for(int i=0; i<mortalitat; i++)
    {
        edats[i]=0;
    }

    edats[0]= nombrearbres;
    
    for(int i=0; i<anysconreant; i++)
    {
        printf("Any %d\n", i);

        /*for(int j=0; j<mortalitat; j++)
        {
            printf("Arbres d'edat %d: %d\n", j, edats[j]);
        }*/

        kg=kgrecolectats(edats);
        
        beneficisanuals=pkg*kg-consumanual(edats,despesesmin, despesesmax);
        
        despeses=despeses+beneficisanuals;
        
        modificarllista(edats, permortalitat);

        printf("Els kg que es produeixen l'any %i són = %i\n",i,kg);
        printf("Les despeses de l'any %i són = %lld\n",i,despeses);
        
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

    int edatscanvi[mortalitat];

    int a;
    
    for(int i=0; i<mortalitat; i++)
    {
        a= (i-1+mortalitat)%mortalitat;
        edatscanvi[i]=edats[a];
    }


    for(int i=0; i<mortalitat; i++)
    {
        edats[i]=edatscanvi[i];
    }

    edats[0]=edats[0]+permortalitat;
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
