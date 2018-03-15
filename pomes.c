#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <time.h>

int mortalitat;

void modificarllista(int [mortalitat], int);
int arbresutils(int [mortalitat], int);
int consumanual(int [mortalitat],int, int);


int main(int argc, char *nom[])
{
    int nombrearbres;
    int anysconreant;
    int permortalitat;
    int arbres=0;
    long long int beneficisanuals;
    int inici;
    int pkg;
    int quantskg;
    long long int despeses=-20000;
    int despesesmin, despesesmax;

    FILE* f = fopen(nom[1], "w");

    if(f==NULL)
    {
        printf("No existeix el fitxer introduit\n");
        return 1;
    }

    printf("Indica arbres a plantar inicialment: ");
    scanf("%d",&nombrearbres);

    printf("Indica els anys de vida màxims: ");
    scanf("%d",&mortalitat);

    printf("Indica anys de conreu: ");
    scanf("%d", &anysconreant);

    printf("Edat que comencem a recol·lectar: ");
    scanf("%d", &inici);

    printf("Indica el percentatge de mortalitat: ");
    scanf("%d", &permortalitat);

    printf("Indica els quilograms de fruits que genera cada arbre per any: ");
    scanf("%d",&quantskg);

    printf("Indica el preu per quilogram de fruits: ");
    scanf("%d",&pkg);
    
    printf("Indica despeses minimes per arbre: ");
    scanf("%d",&despesesmin);

    printf("Indica despeses maximes per arbre: ");
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

        arbres=arbresutils(edats,inici);
        
        beneficisanuals=quantskg*pkg*arbres;
        
        despeses=despeses-consumanual(edats,despesesmin, despesesmax)+beneficisanuals;
        
        modificarllista(edats, permortalitat);

        printf("Els arbres que produeixen de l'any %i són = %i\n",i,arbres);
        printf("Els quilograms obtinguts a l'any %i són = %lld\n",i,beneficisanuals);
        fprintf(f, "%d:    %lld   %lld\n", i, beneficisanuals , despeses);
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


int arbresutils(int edats[mortalitat],int inici)
{
    int arbres=0;

    for(int i=inici;i<mortalitat;i++)
    {
        arbres=arbres+edats[i];
    }

    return arbres;
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
