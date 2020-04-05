	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#define n 40		//sem zadam sam hodnotu
	
	void Napln(int p[], int d){
		int i;
		for(i=0;i<=d;i++){
			p[i]=rand()%100;			//generacia nahodnych cisel [0,99], aby som tam nemal prilis velke hodnoty
		}
	}
	
 char nahodna_permutacia_s_obmedzenim_vzdialenosti(int *p, int l, int dist){
 	int helpole[n]={-1};
 	int i,temp_a,temp_zaciatok,temp_koniec,abs_pocitadlo,polovica_n;
 	int pocitadlo=-1;
 	
 	for(i=p;i<=p+n;i+4){		//i+4, pretoze sa posuvam po 4 bytoch kvoli integerom
 		
		if (n%2==0){
			polovica_n= n/2;
		} 
		else{
			polovica_n= n+1/2;
		}
		
 		++pocitadlo;
 		abs_pocitadlo = polovica_n - abs(n/2 - pocitadlo) ;		//abs_pocitadlo rata vzdialenost od kraja... ak to je koniec, ma zaporne hodnoty
 		if (pocitadlo>n/2)	abs_pocitadlo*= -1;
 		if (dist>=n || pocitadlo>=dist)	abs_pocitadlo=0;				//ak by sa hodnoty mohli posuvat po celom poli, nerob zmeny
 		
 		temp_a = rand()%((2*dist - (dist-pocitadlo) )+1)-(pocitadlo);
 		printf("%d . hodnota: %d - patri medzi zaciatocne. \n",pocitadlo,temp_a);
 			
 		if (helpole[temp_a]==-1){
			helpole[temp_a]=temp_a;
			}
		else if(temp_a==(i-(i-p))){
			}	
 			
		 	}

 }
	
	int main(){
		srand(time(NULL));
		int dist=5;		//sem zadam sam hodnotu  
		int l[n];
		int *p=l;
		Napln(p,n);		
		nahodna_permutacia_s_obmedzenim_vzdialenosti(p, l, dist);
	}
