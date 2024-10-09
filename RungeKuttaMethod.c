#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct ODEparametre {
    double *katsayilar;
    int *kuvvetler;
};

double f(double,struct ODEparametre,int);
double rungeKutta(double,double,double,double,double,struct ODEparametre,int);
int main() {
    int terimSayisi,i,adimSayisi;
    double y0, x0, arananDeger, h, A, B,gercekCozum,hata=0.0;

    printf("Polinomdaki terim sayisini giriniz: "); // g(x) terim sayısı
    scanf("%d", &terimSayisi);

    struct ODEparametre denklem;
    denklem.katsayilar = (double *)malloc(sizeof(double) * terimSayisi);
    if(denklem.katsayilar == NULL){
        printf("Bellek ayrilamadi! \n");
    }
    denklem.kuvvetler = (int *)malloc(sizeof(int) * terimSayisi);
    if(denklem.kuvvetler == NULL){
        printf("Bellek ayrilamadi! \n");
    }

    for (i = 0; i < terimSayisi; i++) { // g(x) için parametre alma.
        printf("%d. terim icin katsayi giriniz: \n", i + 1);
        scanf("%lf", &(denklem.katsayilar[i]));

        printf("%d. terim icin derece giriniz: \n", i + 1);
        scanf("%d", &(denklem.kuvvetler[i]));
    }

    printf("Lutfen A katsayisini giriniz (A*y' + B*y + g(x) = 0) : \n");
    scanf("%lf", &A);

    printf("Lutfen B katsayisini giriniz (A*y' + B*y + g(x) = 0) : \n");
    scanf("%lf", &B);

    printf("Lutfen y0 baslangic degerini giriniz:\n");
    scanf("%lf", &y0);

    printf("Lutfen x0 baslangic degerini giriniz:\n");
    scanf("%lf", &x0);

    printf("Lutfen x'in hangi degerine ulasmak istediginizi giriniz:\n");
    scanf("%lf", &arananDeger);

    printf("Lutfen adim buyuklugu giriniz:\n");
    scanf("%lf", &h);
    
    printf("Lutfen gercek cozum degerini giriniz: \n");
    scanf("%lf",&gercekCozum);

    adimSayisi = (arananDeger - x0) / h;
    for (i = 0; i < adimSayisi; i++) {
        y0 = rungeKutta(x0, y0, h, A, B, denklem, terimSayisi);
        printf("Iteration %d: x = %lf, y = %lf\n", i + 1, x0, y0);
        x0 += h;
    }
    if(gercekCozum>y0){
        hata = gercekCozum-y0;
    }
    else{
        hata = y0-gercekCozum;
    }
    printf("y(xi+h) = y(xi)+1/6(k1+2k2+2k3+k4)*h : %lf\n", y0);
    printf("Gercek Cozum : %lf  Runge Kutta4 : %lf Hata : %lf\n",gercekCozum,y0,hata);
    // Belleği serbest bırak
    free(denklem.katsayilar);
    free(denklem.kuvvetler);

    return 0;
}

double f(double x, struct ODEparametre denklem, int terimSayisi) { // Polinom Kısmı
    double result = 0.0;
    int i;
    for (i = 0; i < terimSayisi; i++) {
        result += denklem.katsayilar[i] * pow(x, denklem.kuvvetler[i]);
    }
    return result;
}

double rungeKutta(double x, double y, double h, double A, double B, struct ODEparametre denklem, int terimSayisi) {
    double k1, k2, k3, k4;

    k1 = (B * y + f(x, denklem, terimSayisi)) / A;
    k2 = (B * (y + 0.5 * k1 * h) + f(x + 0.5 * h, denklem, terimSayisi)) / A;
    k3 = (B * (y + 0.5 * k2 * h) + f(x + 0.5 * h, denklem, terimSayisi)) / A;
    k4 = (B * (y + k3 * h) + f(x + h, denklem, terimSayisi)) / A;

    return y + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4) * h;
}
