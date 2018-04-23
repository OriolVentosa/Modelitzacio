
int mortalitat, anybenef, despeseslimit, plant;

void modificarllista(int [mortalitat], int);

int plantar(int*, long long int*, int [anybenef],int[anybenef], int [mortalitat],int*, int, int);

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
        a= (i-1+mortalitat)%mortalitat;
        edatscanvi[i]=edats[a];
    }

    edatscanvi[0]=0;

    for(int i=0; i<mortalitat; i++)
    {
        edats[i]=edatscanvi[i];
    }
}

int plantar(int *despeses, long long int *despesesb, int anys[anybenef], int arbres[anybenef], int arbrestotals[mortalitat],int *contador, int desxar, int anyactual) //despeses segure/llista arbres plantats/llista anys quan s'ha plantats/longitud llista
{
    int arbrespl=0;

    while(1<2)
    {
        *despeses=*despeses+desxar;
        *despesesb=*despesesb+plant;
        arbrespl+=1;
        if(*despeses<despeseslimit)
        {
            *despeses=*despeses-desxar;
            *despesesb=*despesesb-plant;
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
    
    *contador+=1;
    return arbrespl;
}