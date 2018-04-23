int mortalitat;
int anybenef;

int despesesarbre(int, int, int);
int consumanual(int [mortalitat],int, int);
int consumanualsegur(int [mortalitat], int [anybenef],int,int);

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

int consumanualsegur(int arbres[mortalitat], int arbresplantats[anybenef],int dminima, int dmaxima)
{
    
    int total=0;
        
    int aleatori = dmaxima-dminima;
    
    int danuals;
    
    danuals = rand() % aleatori;

    danuals=danuals+dminima;
    
    danuals = danuals*total;

    return danuals;
}


