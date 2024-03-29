#include <graphics.h>
#include <ctype.h>
#include <conio.h>
#include <math.h>
//.txt den noktalari alma
int** str_to_int(const char* str,int* returnSize, int length)
{
    char strNew[255];
    int k=0,x=0,y=0,flag = 0;//k sayinin basladigi index, flag neyi yapacagina karar vermesini saglar
    int columnSize = 2;

    int** returnValue =(int**) malloc(sizeof(int* )*200);
    for(int i=0; i<length; i++)
    {
        if(flag == 0 && isdigit(str[i]) == 1)
        {
            flag = 1;
            k = i;
        }
        else if(flag == 1 && isdigit(str[i]) == 0)
        {
            if(y==0)
            {
                returnValue[x] = (int *) malloc(sizeof(int)*columnSize);
            }

            memmove(strNew, &str[k],(i-k));//Kopyalama islemi

            returnValue[x][y] = atoi(strNew);
            //Girilen sayilar 0 dan kucuk mu???
            if(str[k-1] == '-')
            {
                returnValue[x][y] = -1 * returnValue[x][y];
            }

            memset(strNew,0,strlen(strNew));//strNewi temizler
            y++;
            if(y==2)
            {
                y = 0;
                x++;
            }
            flag = 0;
        }

    }
    returnValue = (int** ) realloc(returnValue, x*sizeof(int* ));//gereksiz hafizayi kucultur
    *returnSize = x;//kac tane nokta oldugunu main fonksiyonuna *returnSize i degistirerek gonderiyorum
    return returnValue;
}
//noktalari  yazdirma
void noktalar(int** nokta,int returnSize)
{
    int i;
    for(i=0; i<returnSize; i++)
    {
        int x = nokta[i][0];
        x = (x*25) + 400;
        int y = nokta[i][1];
        y = (-y*25) + 400;

        setcolor(GREEN);
        circle(x,y,3);
        setfillstyle(SOLID_FILL,GREEN);
        floodfill(x,y,GREEN);
        setcolor(WHITE);
    }
}
const float BUYUK_YARICAP = 1000;
void kordinat()
{
    //800'e 800'luk pencere
    initwindow(801,801);
    char ch[3];
    int n=0;
//X eksenin
    line(0, getmaxy()/2,getmaxx(), getmaxy()/2);
//Y ekseni
    line(getmaxx()/2, 0, getmaxx()/2, getmaxy());
    int i=0;

    i=0;
//y ekseni �izgileri
//+y �izgileri
    for(int n=0; n <15;)
    {
        line(getmaxx()/2-5,25+i,getmaxx()/2+5,25+i);
        i = i + 25;
        n++;
    }
//-y �izgileri

    for(int n=0; n <16;)
    {
        line(getmaxx()/2-5,25+i,getmaxx()/2+5,25+i);
        i = i + 25;
        n++;
    }

//x ekseni �izgileri
//-x kismi
    i=0;
    for(int n=0; n <15;)
    {
        line(25+i,getmaxx()/2-5,25+i,getmaxx()/2+5);
        i = i + 25;
        n++;
    }
//+x kismi

    for(int n=0; n <16;)
    {
        line(25+i,getmaxx()/2-5,25+i,getmaxx()/2+5);
        i = i + 25;
        n++;
    }
    i=0;
//SAYILAR
//[-15 -9) X
    for(int n=-15; n < -9;)
    {
        sprintf(ch,"%d",n);
        outtextxy(15+i,getmaxx()/2+5,ch);
        i = i + 25;
        n++;
    }
    i=i+3;
//[-9,0) X
    for(int n=-9; n < 0;)
    {
        sprintf(ch,"%d",n);
        outtextxy(15+i,getmaxx()/2+5,ch);
        i = i + 25;
        n++;
    }
    i=i+29;
//(0,9) X
    for(int n=1; n < 10;)
    {
        sprintf(ch,"%d",n);
        outtextxy(15+i,getmaxx()/2+5,ch);
        i = i + 25;
        n++;
    }
//(9,15] X;

    for(int n=10; n < 16;)
    {
        sprintf(ch,"%d",n);
        outtextxy(11+i,getmaxx()/2+5,ch);
        i = i + 25;
        n++;
    }
    i=0;

//Y
//[-15 -9) Y
    i=i+5;
    for(int n=15; n > 9;)
    {
        sprintf(ch,"%d",n);
        outtextxy(getmaxy()/2-22,11+i,ch);
        i = i + 25;
        n--;
    }
    i=i+3;
//[-9,0) Y
    for(int n=9; n > 0;)
    {
        sprintf(ch,"%d",n);
        outtextxy(getmaxy()/2-15,11+i,ch);
        i = i + 25;
        n--;
    }
    i=i+29;
//(0,9) Y
    for(int n=-1; n > -10;)
    {
        sprintf(ch,"%d",n);
        outtextxy(getmaxy()/2-19,5+i,ch);
        i = i + 25;
        n--;
    }
//(9,15] Y

    for(int n=-10; n > -16;)
    {
        sprintf(ch,"%d",n);
        outtextxy(getmaxy()/2-27,5+i,ch);
        i = i + 25;
        n--;
    }

}
struct Nokta
{
    double x;
    double y;
};
struct Cember
{
    //burayi noktaya alalim
    /** float x;
        float y;
    **/
    Nokta M;//Merkez
    double r;
};
double mesafe(Nokta A, Nokta B)
{
    return sqrt(pow((A.x - B.x),2) + pow((A.y - B.y),2));
}
bool adresler_icerde_mi(Cember tmp, Nokta adresler[], int adreslerSize)
{
    for(int i=0; i<adreslerSize; i++)
    {
        if(mesafe(tmp.M, adresler[i]) > tmp.r)
        {
            return false;
        }
    }
    return true;
}
Cember kucultme1(Nokta A,Nokta B)
{
    Cember C;
    Nokta Z;
    Z.x = (A.x+B.x)/2;
    Z.y = (A.y+B.y)/2;
    C.r = mesafe(A, B)/2;
    C.M = Z;
    return C;
}
Cember kucultme2(Nokta A,Nokta B, Nokta C)
{
    Nokta Z;
    double T = (A.x*A.x) + (A.y*A.y);
    double Y = (B.x*B.x) + (B.y*B.y);
    double U = (C.x*C.x) + (C.y*C.y);
    double K = ( A.x*(B.y-C.y) - A.y*(B.x-C.x) + (B.x*C.y) - (C.x*B.y) );
    Z.x = ((T*(B.y-C.y) + Y*(C.y - A.y) + U*(A.y - B.y)) / (2*K));
    Z.y = ((T*(C.x-B.x) + Y*(A.x - C.x) + U*(B.x - A.x)) / (2*K));
    double R = sqrt(pow((Z.x - A.x),2) + pow((Z.y - A.y),2));
    Cember sonuc = {Z,R};
    return sonuc;
}
Cember ayarla(Nokta adresler[],int adreslerSize)
{
    Cember guncel = {{0,0},BUYUK_YARICAP};
    // Cemberin sinirlarinda iki nokta varsa
    for(int i=0; i<adreslerSize; i++)
    {
        for(int j=i+1; j<adreslerSize; j++)
        {
            Cember tmp = kucultme1(adresler[i],adresler[j]);

            if(tmp.r < guncel.r && adresler_icerde_mi(tmp, adresler, adreslerSize))
                guncel = tmp;
        }
    }
    // Cemberin sinirlarinda 3 nokta varsa
    for(int i=0; i<adreslerSize; i++)
    {
        for(int j=i+1; j<adreslerSize; j++)
        {
            for(int k=j+1; k<adreslerSize; k++)
            {
                Cember tmp = kucultme2(adresler[i],adresler[j],adresler[k]);

                if(tmp.r < guncel.r && adresler_icerde_mi(tmp, adresler, adreslerSize))
                    guncel = tmp;
            }
        }
    }

    return guncel;
}
void Cembercizici(int** dots, int length_of_dots)
{

    Nokta adresler[length_of_dots];
    for(int i=0; i<length_of_dots; i++)
    {
        adresler[i] = {(double)dots[i][0],(double)dots[i][1]};
    }
    Cember son = ayarla(adresler, length_of_dots);


    //Merkezi g�steren nokta
    double a =son.M.x;
    a = (a*25) + 400;
    double b =son.M.y;
    b = (-b*25) + 400;
    setcolor(YELLOW);
    circle(a, b, 2);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(a,b,YELLOW);
    setcolor(WHITE);
    int t = son.r*25;
    circle(a, b, t);



    for(int i=0; i<length_of_dots; i++)
    {
        if(mesafe(son.M, adresler[i]) == son.r)
        {
            int k = adresler[i].x;
            k = k*25 + 400;
            int l = adresler[i].y;
            l = -l*25 + 400;
            line(a,b,k,l);
            break;
        }
    }

    printf("Cember(%.4f , %.4f) .....  Yaricap == %.4f ",son.M.x, son.M.y, son.r);
}

//B-splini olusturmamizi saglayan 3 fonksiyon
double recursive(double knots[],int n,double v,int i,int k)
{
    if(k==1)
    {
        if(knots[i]<=v && v<knots[i+1])
            return 1;
        return 0;
    }
    double basisVal;
    basisVal = ((v-knots[i])/(knots[i+k-1]-knots[i])*recursive(knots,n,v, i, k-1)) + ((knots[i+k]-v)/(knots[i+k]-knots[i+1])*recursive(knots,n,v, i+1, k-1));
    return basisVal;

}
double Yuvarla(double sayi)
{
    double donecek =(int) ((sayi*100) + .5);
    donecek =(double) donecek / 100;
    return donecek;
}
void bspline(Nokta A[],int n)
{
    /** m = k + n + 1;
        n kontorol noktasi son indexi
        m = vektorun sayisi
        k = b spline in mertebesi
    **/
    // k=2 olursa dogru olur
    // ben k = 3 olmasini istedim
    int k = 3;
    int m = n + k;
    double knots[m];//vektor bu

    double v, basis;
    //Dugum noktalrini atadik
    for(int i=0; i<m; i++)
    {
        knots[i] = (((double)i)/(m-1));
    }


    //v hep 0 ile 1 arasinda olacak cunku basis

    for(v=0; v<=1; v+=0.0001)
    {
        double x = 0;
        double y = 0;
        //B spline olmasi icin asagidaki if komutuna uymasi lazim
        if(knots[k-1]<v && v <knots[n])
        {
            for(int i=0; i<n; i++)
            {
                basis = recursive(knots,n, v, i, k);
                x =  x + (basis*A[i].x);
                y =  y + (basis*A[i].y);
            }

            double nx = x;
            nx = (nx*25) + 400;
            double ny = y;
            ny = (-ny*25) + 400;

            putpixel(Yuvarla(nx),Yuvarla(ny),CYAN);
        }
    }

}


int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char* )"");
    initwindow(801,801);
    FILE * dosya;
    dosya = fopen("prolab1.txt","r");
    char line[255];
    int returnSize = 0;
    int** dots;

    fgets(line, 255, dosya);
    int lengthStr = (int)strlen(line);
    dots = str_to_int(line,&returnSize, lengthStr);

    kordinat();
    noktalar(dots,returnSize);
    Cembercizici(dots,returnSize);
    //Iki boyutlu pointerdan structa gecis
    Nokta N[returnSize];
    for(int i=0; i<returnSize; i++)
    {
        N[i].x =(double)dots[i][0];
        N[i].y =(double)dots[i][1];
    }
    //B spline
    bspline(N,returnSize);


    fclose(dosya);
    free(dots);
    getch();
    closegraph();
    return 0;

}



