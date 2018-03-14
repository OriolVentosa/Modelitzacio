#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int mortalitat;

void modificarllista(int [mortalitat], int);
int arbresutils(int [mortalitat], int);

int main(int argc, char *nom[])
{
    int nombrearbres;
    int anysconreant;
    int permortalitat;
    int arbres=0;
    int inici;
//     int despeses=-2000;
    
    FILE* f = fopen(nom[1], "w");
    
    if(f==NULL)
    {
        printf("No existeix el fitxer introduit\n");
        return 1;
    }
    
    printf("indica arbres a plantar inicialment: ");
    scanf("%d",&nombrearbres);
    
    printf("indica anys de vida maxims: ");
    scanf("%d",&mortalitat);
    
    printf("indica anys de conreu: ");
    scanf("%d", &anysconreant);
    
    printf("A quina edat comencem a recol·lectar?: ");
    scanf("%d", &inici);
    
    printf("Indica percentatge mortalitat: ");
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
        
        arbres=arbresutils(edats,inici);
        
        modificarllista(edats, permortalitat);
        
        printf("Els arbres que produeixen de l'any %i són = %i\n",i,arbres);
        fprintf(f, "%d:    %d\n", i, arbres);
    }
    
    fclose(f);
    
    return 0;
}

void modificarllista(int edats[mortalitat], int permortalitat)
{
    srand(time(NULL));
    
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









