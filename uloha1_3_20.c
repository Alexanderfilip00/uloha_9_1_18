	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>

	
	void Napln(int p[], int d){
		int i;
		puts("Generujem zaciatocne poradie:");
		for(i=0;i<=d;i++){
			p[i]=rand()%100;			//generacia nahodnych cisel [0,99], aby som tam nemal prilis velke hodnoty
			printf("%d ", p[i]);
		}
	}
	
 char nahodna_permutacia_s_obmedzenim_vzdialenosti(int *p, int l, int dist){
 	
 	int i=0, n=0;
	while (l[i]==-1){			//zisti dlzku pola
		n++;
		i++;
		} 
	 	
 	int temp_a,temp_zaciatok,temp_koniec,abs_pocitadlo;
 	int pocitadlo=-1;
 	
 	
 	int min, max, odpredu=0, odzadu=n-1;	
	int helppole[n]={0};
 	int pole_zoradenie[n]
	int gen;
	
	printf("Pole ma dlzku: %d \n", n);
	Napln(p,n);	
 	
 	while (done==0){
	 	for(i=0;i<n;i){			//prechadzam po novom poli, kde bude presuvanie
	 		
	 		if(dist>n) dist=n;
	 		if(dist>odpredu) min=0;
	 		else min= odpredu-dist;
	 		if(dist>odzadu) max=n;
	 		else max= odpredu+dist;
	 		
	 		if(max-min != 0){
		 		gen= rand()%(max-min) - (odpredu-min);
		 		
		 		if (helppole[gen]==0){
		 			helppole[gen]=1;
		 			odpredu++;
					odzadu--;
				 	}
				 
		 		else if (gen==max) max--;
		 		else if (gen==min) min++;
		 		
		 		
		 		
				
			else break;
	 		}
 	}
 	}

 }
	
	int main(){
		srand(time(NULL));
		int dist=5;		//sem zadam sam hodnotu  
		int l[n]={-1};
		int *p=l;	
		nahodna_permutacia_s_obmedzenim_vzdialenosti(p, l, dist);
	}
