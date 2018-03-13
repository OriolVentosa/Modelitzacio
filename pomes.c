#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int mortalitat;

void modificarllista(int [mortalitat], int);
int recolecta(int [mortalitat], int);

int main()
{
    int nombrearbres;
    int anysconreant;
    int permortalitat;
    int kgtotals=0;
    int inici;
    
    
    printf("indica arbres a plantar inicialment: ");
    scanf("%d",&nombrearbres);
    
    printf("indica anys de vida maxims: ");
    scanf("%d",&mortalitat);
    
    printf("indica anys de conreu: ");
    scanf("%d", &anysconreant);
    
    printf("A quina edat comencem a recol·lectar?: ");
    scanf("%d", &inici);
    
    printf("indica percentatge mortalitat");
    scanf("%d", &permortalitat);
    
    int edats[mortalitat];
    
    for(int i=0; i<mortalitat; i++)
    {
        edats[i]=0;
    }
    
    edats[0]= nombrearbres;
    for(int i=0; i<anysconreant; i++)
    {
        printf("Any %d\n", i);
        
        for(int j=0; j<mortalitat; j++)
        {
            printf("Arbres d'edat %d: %d\n", j, edats[j]);
        }
        
        kgtotals=recolecta(edats,inici)+kgtotals;
        modificarllista(edats, permortalitat);
        printf("Els kg totals de l'any %i són = %i\n",i,kgtotals);
    }
    
    return 0;
}

void modificarllista(int edats[mortalitat], int permortalitat)
{
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


int recolecta(int edats[mortalitat],int inici)
{
    int arbres=0;

    for(int i=inici;i<mortalitat;i++)
    {
        arbres=arbres+edats[i];
    }
    int kg;
    kg=2*arbres;
    
    return kg;    
}









