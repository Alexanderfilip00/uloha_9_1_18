	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#define n 50
	
	void Napln(int p[], int d){
		int i;
		puts("Generujem zaciatocne poradie:");
		for(i=0;i<=d;i++){
			p[i]=rand()%100;			//generacia nahodnych cisel [0,99], aby som tam nemal prilis velke hodnoty
			printf("%d ", p[i]);	
		}
		printf("\n \n");
	}
	
 char nahodna_permutacia_s_obmedzenim_vzdialenosti(int *p, int l[], int dist){
 	
	int i,j;	
 	int helppole[n]={0};
 	int pole_zoradenie[n]={0};
	int pokracuj=0, done=0;
	int min, max, odzadu=0;	
	int gen;

	Napln(p,n);			//naplnim povodne pole nahodnymi cislami
	
	if(dist>n) dist=n;
 	
 	while (done==0){
 		
	 	for(i=0;i<n;i++){			//prechadzam po novom poli, kde bude presuvanie
			
	 		odzadu++;
			if (i==n-1) {
				done=1; 
			}
			
			pokracuj=0;
	 		
			//printf("Zacinam %d\n", i);			//
			
	 		if(i-dist<=0) min=0;
	 		else min= i-dist;
	 		if(i+dist>=n) max=n;
	 		else max= i+dist;
	 		
	 		while(pokracuj==0){
		 		gen= i + rand()%(max-min+1)- (i-min);	
				//printf("Posunutie vzad: %d \n", i-min);			//
		 		//printf("             Gen = %d \n", gen);			//
		 		//printf("             Rozsah = %d \n", max-min+1);			//
		 		
		 		if (helppole[gen]==0){			//kontrolujem, ci nie je poloha obsadena
		 			helppole[gen]=1;
		 			pole_zoradenie[i]=gen;			//napisem, kam sa ma dana poloha posunut
					pokracuj=1;
					//printf("Podarilo sa %d \n", i);		//
					
				 	}
				 
		 		else if (gen==max) {
					//puts("gen = max");			//
					max--; 
					}
		 		else if (gen==min) {
		 			//puts("gen = min");			//
				 	min++;
				 	}
				if(max-min == 0) {						//ak dojdu moznosti, resetuj sa
					//for(j=0;j<n;j++)	printf("%d ",helppole[j]);				
					
					//printf("\n\t\t\t\t Podarilo sa: %d \n",i);			//
					for(j=0;j<n;j++) helppole[j]=0;
					odzadu=-1;
					pokracuj=0;
					i=0; 
					//puts("\t\t\tUplne odznova");					//
					break;
				}
				
	 		}
	 		
	 		if(i>dist+1 && helppole[i-dist-1]==0){				//kontrola dozadu - ci to nerata zbytocne
				//for(j=0;j<n;j++)	printf("%d ",helppole[j]);				
				//printf("\n\t\t\t\t Podarilo sa: %d \n",i);			//
				for(j=0;j<n;j++) helppole[j]=0;
				odzadu=-1;
				pokracuj=0;
				i=0; 
				//puts("\t\t\t\t\t\tUplne odznova / kvoli zabudnutiu");					//
				break;						
	 		}
 		}
 	}
	
	puts("Nove poradie:");
	for (i=0;i<n;i++){
		printf("%d ", pole_zoradenie[i]);			//pre kontrolu mi vypise, ake nastanu posuny
		helppole[i]=l[i];							//skopiruje povodne pole - priprava na permutaciu
	}
	
	
	for(i=0;i<n;i++){
		p[pole_zoradenie[i]-1]=helppole[i];
	}
	puts("");
	puts("Nova permutacia:");
	for(i=0;i<n;i++){
		printf("%d ",p[i]);
	}
	
 }
	
	int main(){
		srand(time(NULL));
		int dist=5;		//sem zadam sam hodnotu  
		int l[n]={-1};
		int *p=l;	
		nahodna_permutacia_s_obmedzenim_vzdialenosti(p, l, dist);
	}
