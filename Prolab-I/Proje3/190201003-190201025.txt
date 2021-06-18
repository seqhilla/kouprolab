#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
int basadet = 0,sonadet = -1,satirsayisi=0;
struct kelimeler
{
    char kelime[255];
    int adet;
    struct kelimeler *sonraki;
    struct kelimeler *onceki;
};
struct kelimeler *ilk;
//struct kelimeler *son=NULL;
void BasaEkle(char* a,int kactane)
{
    struct kelimeler *yeni = (struct kelimeler*) malloc(sizeof(struct kelimeler));
    strcpy(yeni->kelime,a);
    //yeni->kelime[strlen(a)] = '\0';
    // yeni->sonraki = NULL;
    //  yeni->onceki = NULL;
    yeni->adet = kactane;
    yeni->sonraki = NULL;
    basadet = kactane;
    if(ilk==NULL)
    {
        ilk = yeni;
        //printf("%s %d \n",ilk->kelime,ilk->adet);
    }
    else
    {
        //printf("ilkin durumu: %s : %d\n",ilk->kelime,ilk->adet);
        yeni->sonraki=ilk;
        ilk->onceki = yeni;
        ilk = yeni;
    }
    //free(yeni);
}
void ArayaEkle(char* a,int kactane)
{
    struct kelimeler *yeni = (struct kelimeler*) malloc(sizeof(struct kelimeler));
    struct kelimeler *curr = ilk;
    struct kelimeler *tmp;
    strcpy(yeni->kelime,a);
    yeni->adet = kactane;
    while(curr!=NULL){
        if(curr->adet >= kactane && curr->sonraki->adet < kactane){
            tmp = curr->sonraki;
            curr->sonraki = yeni;
            yeni->onceki = curr;
            yeni->sonraki = tmp;
            tmp->onceki = yeni;
            //printf("ilkin durumu: %s : %d\n",ilk->kelime,ilk->adet);
            break;
        }
        else{
            curr=curr->sonraki;
        }
    }
    //free(yeni);
    //free(curr);
}
void SonaEkle(char* a,int kactane)
{
    struct kelimeler *yeni = (struct kelimeler*) malloc(sizeof(struct kelimeler));
    struct kelimeler *curr = ilk;
    strcpy(yeni->kelime,a);
    yeni->adet = kactane;
    sonadet = kactane;
    while(curr->sonraki!=NULL){
        curr = curr->sonraki;
    }
    //printf("ilkin durumu sonaekle calismadan once: %s : %d\n",ilk->kelime,ilk->adet);
    curr->sonraki = yeni;
    yeni->onceki = curr->sonraki;
    yeni->sonraki = NULL;
    //printf("ilkin durumu sonaekle calistiktan sonra: %s : %d\n",ilk->kelime,ilk->adet);
    //free(yeni);
    //free(curr);


}
//aramadan calisir aramadan kelimeyi ve adedini alir node'a ekler
void ekleme(char* a,int kactane)
{
    if(ilk == NULL)
    {
        //printf("basa ekleye giriyor nullken\n");
        BasaEkle(a,kactane);
        return;
    }
    else if(kactane > basadet){
        //printf("basa ekleye giriyor\n");
        BasaEkle(a, kactane);
    }
    else if(kactane <= sonadet || sonadet == -1){
        //printf("sona ekleye giriyor\n");
        SonaEkle(a,kactane);
    }
    else if(kactane <= basadet && kactane > sonadet){
        //printf("araya ekleye giriyor\n");
        ArayaEkle(a,kactane);
    }
}
void kucukharfedonustur(char* donusturulecek){
    for(int i=0; i<strlen(donusturulecek); i++){
        donusturulecek[i] = tolower(donusturulecek[i]);
    }
}

//kelimeyi metinde arar sayisini artirir
void Arama(char* aranacak){
    // '\n' karekteri varsa silmeli
    for(int i=0; i<strlen(aranacak); i++){
        aranacak[i] = tolower(aranacak[i]);
    }
    //printf("hadee\n");
    int indx = strlen(aranacak);
    if(aranacak[indx] == '\n'){
        memmove(aranacak+indx-1,&aranacak+indx,1);
        aranacak[indx] = '\0';
    }


        //printf("hadee2\n");

    //zaten nodeda var mi kontrol varsa buradan cikmasi lazim
    struct kelimeler* curr = ilk;
    while(curr!=NULL){
        if(strcmp(curr->kelime,aranacak) == 0){
            //printf("eklenmekten kacti zaten vardi\n");
            return;
        }
        //printf("curr ustu\n");
        curr = curr->sonraki;
        //printf("dongude\n");
    }
    //printf("hadee3\n");
    FILE *dosya = fopen("oku.txt", "r");
    char *imlec = (char*) malloc(255*sizeof(char));
    char *tmp =(char*) malloc(50*sizeof(char));
    bool flag = true;
    int bas = 0;
    int kactane = 0;
    int sayac=0;
    while(fgets(imlec,255,dosya)){
        for(int i=0; i<strlen(imlec); i++){
            if(flag && (isalpha(imlec[i]) || isdigit(imlec[i]) || ispunct(imlec[i])))
            {
                bas = i;
                flag = false;
            }
            else if(imlec[i] == ' ')
            {
                memmove(tmp,&imlec[bas],i-bas);
                tmp[i-bas] = '\0';
                kucukharfedonustur(tmp);
                if(strcmp(aranacak,tmp) == 0){
                    kactane++;
                    //printf("%s %d\n",tmp, kactane);
                }
                memset(tmp,0,strlen(tmp)+1);
                flag = true;
            }
            else if(i == strlen(imlec)-1 && satirsayisi != sayac)
            {
                memmove(tmp,&imlec[bas],(i-bas+1));
                tmp[i-bas] = '\0';
                kucukharfedonustur(tmp);
                if(strcmp(aranacak,tmp) == 0){
                    kactane++;
                    //printf("%s %d\n",tmp, kactane);
                }
                memset(tmp,0,strlen(tmp)+1);
                flag = true;
            }
            else if(i == strlen(imlec)-1 && satirsayisi == sayac){
                memmove(tmp,&imlec[bas],(i-bas+2));
                tmp[i-bas+1] = '\0';
                kucukharfedonustur(tmp);
                if(strcmp(aranacak,tmp) == 0){
                    kactane++;
                    //printf("%s %d\n",tmp, kactane);
                }
                memset(tmp,0,strlen(tmp)+1);
            }
        }
        sayac++;
    }
    //printf("eklemeye giriyor\n");
    ekleme(aranacak,kactane);


}


void Listele()
{
    //printf("listele basi ilk icin: %s\n",ilk->kelime);
    struct kelimeler *liste=ilk;
    int i=1;
    while(liste!= NULL)
    {
        printf("%d. %s: %d\n",i,liste->kelime,liste->adet);
        liste=liste->sonraki;
        i++;
    }
}

int main()
{
    FILE *okuyucu;
    okuyucu = fopen("oku.txt","r");
    char *str =(char*) malloc(255*sizeof(char));
    int bas = 0;
    bool flag = true;
    char *tmp =(char*) malloc(50*sizeof(char));
    // char tektmp;
    FILE *sayici;
    sayici = fopen("oku.txt","r");
    char* gereksizchar = malloc(255*sizeof(char));
    for(int i=0; fgets(gereksizchar,255,sayici); i++){
        satirsayisi = i;
       // printf("%d ",i);
    }
    //satirsayisi++;
    //printf("%d\n",satirsayisi);
    fclose(sayici);
    int sayac = 0;
    while(fgets(str,255,okuyucu) !=NULL )
    {
        for(int i=0; i<strlen(str); i++)
        {
            if(flag && (isalpha(str[i]) || isdigit(str[i]) || ispunct(str[i])))
            {
                bas = i;
                flag = false;

            }
            else if(str[i] == ' ')
            {
                memmove(tmp,&str[bas],i-bas);
                tmp[i-bas] = '\0';
                //printf("%s main\n",tmp);
                Arama(tmp);
                memset(tmp,0,strlen(tmp)+1);
                flag = true;

            }
            else if(i == strlen(str)-1 && sayac!=satirsayisi)
            {
                memmove(tmp,&str[bas],(i-bas+1));
                tmp[i-bas] = '\0';
                //printf("%s main\n",tmp);
                Arama(tmp);
                memset(tmp,0,strlen(tmp)+1);
                flag = true;

            }
            else if(i == strlen(str)-1 && satirsayisi == sayac){
                memmove(tmp,&str[bas],(i-bas+2));
                tmp[i-bas+1] = '\0';
                //printf("%s main\n",tmp);
                //printf("sonda\n");
                Arama(tmp);
                memset(tmp,0,strlen(tmp)+1);
            }

        }
        sayac++;
    }
    free(tmp);
    fclose(okuyucu);
    free(str);
    Listele();
    free(ilk);
    return 0;
}
