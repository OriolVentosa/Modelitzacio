#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>

double reproduccio(int p, int i, int periodes, double xf);
double mortalitat(int p, int i, int periodes, int mmin, int mmax, int var);
double exbenefici(int p, double xb1, double xb2, int extreure, int i);


int main()
{
    int i,n=12; //5 anys.
    double xf=125, xb1, xb2; //fertilitat, benefici, percentatge mortalitat
    int mmin=4,mmax=12,var=10;
    double poblacioinicial=1000;
    int periodes=1, extreure=1;
    double despesainicial=50000+150000, despesacicleperindividu=6, despesatotal; //despesaincial 50€ per porc(1000x50=50000)+instalacions
    double benefici, bpi=40;

    printf("Percentatge de benefici fix: ");
    scanf("%lf",&xb1);
    
    printf("Percentatge de benefici variable: ");
    scanf("%lf",&xb2);

    double p[n+1];

    p[0]=poblacioinicial;
    printf("-----------------------------------------\n");
    printf("Població inicial = %g\n",p[0]);
    printf("Despeses inicials = %g\n",despesainicial);
    printf("-----------------------------------------\n");

    benefici=0;
    despesatotal=despesainicial;

    for(i=1;i<=n;i++)
    {
        double r,m,b;
        r=reproduccio(p[i-1],i,periodes,xf);
        m=(mortalitat(p[i-1],i,periodes,mmin,mmax,var));
        b=(exbenefici(p[i-1],xb1, xb2,extreure,i));
        p[i]=p[i-1]+r-m-b;

        printf("Fertilitat al període %i = %g\n",i,r);
        printf("Mortalitat al període %i = %g\n",i,m);
        printf("Percentatge de població que extreiem al període %i = %g\n",i,b);
        printf("Població al període %i = %g\n",i,p[i]);
        //printf("Despesa al període %i = %g\n",i,p[i-1]*despesacicleperindividu);
        //printf("Benefici al període %i = %g\n",i,(b*bpi));
        printf("-----------------------------------------\n");
        despesatotal=despesatotal+p[i-1]*despesacicleperindividu;
        benefici=benefici+(b*bpi);
    }

    printf("Despesa acumulada al període %i = %g\n",i-1,despesatotal);
    printf("Benefici acumulat al període %i = %g\n",i-1,benefici);
    printf("Benefici TOTAL acumulat al període %i = %g\n",i-1,benefici-despesatotal);

    return 0;

}


double reproduccio(int p, int i, int periodes, double xf) //nombre de individus, any/mes/dia exacte, cada quant es reprodueixen.
{
    if(i % periodes==0)
    {
        if(p>1150)
        {
            return 0;
        }
        else
        {
            int r;
            r=(int)(p*(xf/100));
                if(p*(xf/100)-r<0.5)
                {
                    return r;
                }
                else
                {
                    return r+1;
                }
        }
    }
    else
    {
        return 0;
    }
}

double mortalitat(int p, int i, int periodes, int mmin, int mmax, int var) //nombre de individus, any/mes/dia exacte, cada quant es reprodueixen.
{
    if(mmin!=mmax)
    {
        double r;

        if(i % periodes==1)
        {
            int j;
            //srand(time(NULL));
            r=(rand() % (mmax-mmin+1))+mmin+var;
            j=(int)(p*(r/100));
            if(((p*(r/100))-j)<0.5)
            {
                return j;
            }
            else
            {
                return j+1;
            }
        }
        else
        {
            int j;
            //srand(time(NULL));
            r=(rand() % (mmax-mmin+1))+mmin;
            j=(int)(p*(r/100));
            if(((p*(r/100))-j)<0.5)
            {
                return j;
            }
            else
            {
                return j+1;
            }
        }
    }
    else
    {
        int j;
        double mmaxdouble;
        mmaxdouble=(double)mmax;
        return p*(mmaxdouble/100);
        j=(int)(p*(mmaxdouble/100));
            if(((p*(mmaxdouble/100))-j)<0.5)
            {
                return j;
            }
            else
            {
                return j+1;
            }
    }
}

double exbenefici(int p, double xb1, double xb2 , int extreure, int i) //nombre de individus, any/mes/dia exacte, cada quant es reprodueixen.
{
        if(p<800 && p>1150)
        {
            return 0;
        }
        else
        {
            int b;
            b=(int)(p*((xb1)/100.))+(p*p*((xb2)/100.));       //modificar aixo (xb+B1*p)
            if(((p*((xb1)/100.))+(p*p*((xb2)/100.))-b)<0.5)
                    {
                        return b;
                    }
                    else
                    {
                        return b+1;
                    }
        }
}
