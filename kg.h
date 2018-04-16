int mortalitat, anybenef;

int kgrecolectats(int [mortalitat]);
int kgrecolectatsegurs(int [mortalitat], int [anybenef]);

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