#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct yigin{
	float puan;
	char film[200];
	yigin *sonraki;
}yiginlar;
yiginlar *tmpStack=NULL;//input y���n�ndan bu y���na aktarma
yiginlar *inputStack=NULL;//dosyadan ald���m�z y���n
void yigin_bastir()//tempStack y���n�n� ekrana bast�rma fonksiyonu
{
	yiginlar *gecici=tmpStack;
	while(gecici->sonraki!=NULL)
	{
		printf("%s-->%.1f\n",gecici->sonraki->film,gecici->sonraki->puan);
		gecici=gecici->sonraki;
	}
}
void ilk_bastir(int k)//ilk ba�ta dosyadan ald���m�z �nputStack y���n�n� ekrana bast�rma
{
	yiginlar *gecici1=inputStack;
	for(int i=0;i<k;i++)
	printf("%c",gecici1->film[i]);
	printf("-->%.1f\n",gecici1->puan);
}
void tmp_ekle(char filmm[],float sayi)//inputStackten ekleme 
{
	int i;
	if(tmpStack==NULL)
	{
		tmpStack=(yiginlar*)malloc(sizeof(yiginlar));
		tmpStack->sonraki=NULL;
	}
	for(i=0;i<strlen(filmm);i++)
	{
		tmpStack->film[i]=filmm[i];
	}
	tmpStack->puan=sayi;
	yiginlar *yeni2=(yiginlar*)malloc(sizeof(yiginlar));
	yeni2->sonraki=tmpStack;
	tmpStack=yeni2;
}
void input_ekle(char filmm[],float sayi)//dosyadan al�nan de�erleri ilk y���na ekleme
{
	int i;
	if(inputStack==NULL)
	{
		inputStack=(yiginlar*)malloc(sizeof(yiginlar));
		inputStack->sonraki=NULL;
	}
	for(i=0;i<strlen(filmm);i++)
	{
		inputStack->film[i]=filmm[i];		
	}
	inputStack->puan=sayi;
	ilk_bastir(i);
	yiginlar *yeni=(yiginlar*)malloc(sizeof(yiginlar));
	
	yeni->sonraki=inputStack;
	inputStack=yeni;
	tmp_ekle(inputStack->sonraki->film,inputStack->sonraki->puan);
}
int main()
{
	FILE *fp=fopen("filmler.txt","r");
	char film[15][50];
	char ktr,ktr1;
	int i=-1,j;
	float sayi;

	if(fp==NULL)

	printf("Dosya bulunamadi...");//Dosyan�n bulunamama hali
	while(!feof(fp))
	{	
		i++;
		j=0;
		ktr=fgetc(fp);
		while(ktr!=',')//filmleri karakter karakter alma
		{
			film[i][j]=ktr;
			j++;
			ktr=fgetc(fp);
		}
		fscanf(fp,"%f",&sayi);//virgulden sonra sayiyi float olarak alma
		
		input_ekle(film[i],sayi);
		ktr=fgetc(fp);
		if(ktr=='\n')
		continue;
		
	}
	printf("\n");
	yigin_bastir();

}
