int mortalitat, anybenef, despeseslimit, plant, pr=0;

void modificarllista(int [mortalitat], int);

int plantar(int*, long long int*, int [anybenef],int[anybenef], int [mortalitat],int*, int, int, int, int);

int armor(int[mortalitat], int[anybenef], int, int, int, int);  //treu les despeses dels arbres que moren

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

int plantar(int *despeses, long long int *despesesb, int anys[anybenef], int arbres[anybenef], int arbrestotals[mortalitat],int *contador, int desxar, int anyactual, int total, int arbresmax) //despeses segure/llista arbres plantats/llista anys quan s'ha plantats/longitud llista
{
    int arbrespl=0;
    int a=0;
    while(1<2)  //el programa la palma quan fa canvis a total
    {
        *despeses=*despeses+desxar;
        *despesesb=*despesesb+plant;
        arbrespl+=1;
        total+=1;
        if(*despeses<despeseslimit)
        {
            *despeses=*despeses-desxar;
            *despesesb=*despesesb-plant;
            arbrespl-=1;
            total-=1;
            break;
        }
        
        if(total>arbresmax)
        {
            a=total-arbresmax;
            *despeses=*despeses-(a*desxar);
            *despesesb=*despesesb-(a*plant);
            arbrespl-=a;
            total=arbresmax;
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

int armor(int edats[mortalitat], int arbres[anybenef], int despesessegures, int contador,int despesesmax, int pkg)
{
    int a,b,c;
    for(int i=0; i<contador; i++)
    {
        a=edats[i]-arbres[contador-1-i];
        b=despesesarbre(i, despesesmax, pkg, plant);
        c+=a*b;
        arbres[contador-1-i]=edats[i];
    }
    return despesessegures+c;
}
