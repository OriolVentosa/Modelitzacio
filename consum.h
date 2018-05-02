int mortalitat;
int anybenef;
int pr;

int despesesarbre(int,int, int, int);
int consumanual(int [mortalitat],int, int);
int consumanualsegur(int [mortalitat],int,int);

int despesesarbre(int k,int dmaxima, int preukg, int plant) //negatiu
{
    float any;
    int anyint;
    for(int i=k;i<31;i++)
    {
            any = (i*i)/6;
//            printf("Valor d'arbres d'edat %d %f\n", i,any);
            anyint=any*preukg;
            if(anyint>dmaxima) 
            {
                if(pr!=1)
                {
                    anybenef=i;
                    pr=1;
                }
                break;
            }
    }
    
    for(int i=k;i<anybenef;i++)
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

int consumanualsegur(int arbres[mortalitat],int dminima, int dmaxima)
{

    int total=0;

    int aleatori = dmaxima-dminima;

    int danuals;

    for(int i=0; i<mortalitat;i++)
    {
        total=total+arbres[i];
    }

    for(int i=0; i<anybenef;i++)
    {
        total=total-arbres[i];
    }

    danuals = rand() % aleatori;

    danuals=danuals+dminima;

    danuals = danuals*total;

    return danuals;
}