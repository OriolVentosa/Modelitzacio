#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>

double reproduccio(int p, int i, int periodes, double xf);
double mortalitat(int p, int i, int periodes, int mmin, int mmax, int var);
double exbenefici(int p, double xb1, double xb2, int extreure, int i);


int main(int argc, char *nom[])
{
    int i,n=60; //5 anys.
    double xf=500, xb1, xb2; //fertilitat, benefici.
    int mmin=1,mmax=3,var=10;
    double poblacioinicial=1000;
    int periodes=4, extreure=1;
    double despesainicial=50000+150000, despesacicleperindividu=6, despesatotal; //despesaincial 50€ per porc(1000x50=50000)+instalacions
    double benefici, bpi=40;

    FILE* f = fopen(nom[1], "w");

    if(f==NULL)
    {
        printf("No existeix el fitxer introduit\n");
        return 1;
    }

    /*printf("Períodes totals:");
    scanf("%i",&n);

    printf("Població inicial:");
    scanf("%i",&poblacioinicial);

    printf("Cada quants períodes és reprodueixen:"); //cada quants anys, mesos, dies es reprodueixen.
    scanf("%i",&periodes);

    printf("Percentatge de fertilitat:");
    scanf("%lf",&xf);

    printf("Percentatge de mortalitat mínima:");
    scanf("%i",&mmin);

    printf("Percentatge de mortalitat màxima:");
    scanf("%i",&mmax);

    printf("Percentatge de variança de mortalitat:"); //percentatge que aumenta (tan el mínim com el màxim) al any seguent al de cria
    scanf("%i",&var);*/


    printf("Percentatge de benefici lineal:");
    scanf("%lf",&xb1);
    
    printf("Percentatge de benefici quadratic:");
    scanf("%lf",&xb2);

    /*printf("Despesa inicial:");
    scanf("%lf",&despesainicial);

    printf("Despesa per cicle per individu:");
    scanf("%lf",&despesacicleperindividu);

    printf("Benefici per individu:");
    scanf("%lf",&bpi);*/

    double p[n+1];

    p[0]=poblacioinicial;
    printf("-----------------------------------------\n");
    printf("Població inicial = %g\n",p[0]);
    printf("Despeses inicials = %g\n",despesainicial);

    //printf("Mortalitat al període  = %i\n",mortalitat(p[0],0,periodes,mmin,mmax,var));
    //printf("Despesa al període 1 = %g\n",p[0]*despesacicleperindividu+despesainicial);
    //printf("Benefici al període 1 = %g\n",(p[0]*(xb/100)*bpi));
    printf("-----------------------------------------\n");

    benefici=0;
    despesatotal=despesainicial;

    for(i=1;i<=n;i++)
    {
        double r,m,b;
        r=reproduccio(p[i-1],i,periodes,xf);
        m=(mortalitat(p[i-1],i,periodes,mmin,mmax,var));
        b=(exbenefici(p[i-1],xb1, xb2 ,extreure,i));
        p[i]=p[i-1]+r-m-b;
//         printf("Fertilitat al període %i = %g\n",i,r);
//         printf("Mortalitat al període %i = %g\n",i,m);
//         printf("Percentatge de població que extreiem al període %i = %g\n",i,b);
// 
//         //printf("p[i-1]+reproduccio(p[i-1],i,periodes,xf) = %lf\n",p[i-1]+r);
//         //printf("p[i-1]-mortalitat(p[i-1],i,periodes,mmin,mmax,var) = %lf\n",p[i-1]-m);
//         //printf("p[i-1]-(exbenefici(p[i-1],xb)) = %lf\n",p[i-1]-b);
// 
//         printf("Població al període %i = %g\n",i,p[i]);
//         printf("Despesa al període %i = %g\n",i,p[i-1]*despesacicleperindividu);
//         printf("Benefici al període %i = %g\n",i,(b*bpi));
//         printf("-----------------------------------------\n");
        despesatotal=despesatotal+p[i-1]*despesacicleperindividu;
        benefici=benefici+(b*bpi);
    }
    
    printf("Població final = %g\n",p[n]);
    printf("Despesa acumulada al període %i = %g\n",i-1,despesatotal);
    printf("Benefici acumulat al període %i = %g\n",i-1,benefici);
    printf("Benefici TOTAL acumulat al període %i = %g\n",i-1,benefici-despesatotal);

    //fprintf(f, "PERIODES:    POBLACIÓ\n");

    /*for(i=0;i<=60;i++)
    {
        fprintf(f, "%i:    %g\n", i, p[i]);
    }*/
    
    //fprintf(f, "CADA QUATRE PERIODES:    POBLACIÓ\n");

    for(i=0;i<=60;i++)
    {
        if(i % periodes==0)
        {
            fprintf(f, "%i:    %g\n", i, p[i]);
        }
    }
    fclose(f);
    return 0;

}


double reproduccio(int p, int i, int periodes, double xf) //nombre de individus, any/mes/dia exacte, cada quant es reprodueixen.
{
    if(i % periodes==0)
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

double exbenefici(int p, double xb1, double xb2, int extreure, int i) //nombre de individus, any/mes/dia exacte, cada quant es reprodueixen.
{
    if(i % extreure==0)
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
    else
    {
        return 0;
    }
}

