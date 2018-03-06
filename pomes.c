#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void modificarllista(int [5]);
int recolecta(int [5], int);

int main()
{
    int nombrearbres=100;
    int mortalitat=5;
    int anysconreant;
    int kgtotals=0;
    int inici;
//     printf("indica anys de vida maxims: ");
//     scanf("%d",&mortalitat);
    printf("indica anys de conreu: ");
    scanf("%d", &anysconreant);
    printf("A quina edat comencem a recol·lectar?\n");
    scanf("%d", &inici);
    
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
        modificarllista(edats);
        printf("Els kg totals de l'any %i són = %i\n",i,kgtotals);
    }
    
    return 0;
}

void modificarllista(int edats[5])
{
    int probabilitat[5];
    int posicio=0;
    
    for(int i=0; i<5;i++) //mortalitat
    {
        probabilitat[i]=posicio+edats[i];
        posicio=posicio+edats[i];
    }
    
    int random;
    for(int i=0;i<5;i++) //percentatge de mort
    {
        random=rand()%posicio;  //arreglar random
        printf("random %d \n", random);
        for(int j=0;j<5;j++)
        {
            if(random<=probabilitat[j])
            {
                edats[j]=edats[j]-1;
                break;
            }
            
        }
        
    }
    
    int edatscanvi[5];
    int a;
    for(int i=0; i<5; i++)
    {
        a= (i-1+5)%5;
        edatscanvi[i]=edats[a];
    }
    
    for(int i=0; i<5; i++)
    {
        edats[i]=edatscanvi[i];
    }
    
    edats[0]=edats[0]+5;
}


int recolecta(int edats[5],int inici)
{
    int arbres=0;

    for(int i=inici;i<5;i++)
    {
        arbres=arbres+edats[i];
    }
    int kg;
    kg=2*arbres;
    
    return kg;    
}









