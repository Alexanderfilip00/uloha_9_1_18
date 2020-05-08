#include <stdio.h>
#include <stdlib.h>
#include <math.h>
	
void Napln(int p[], int d){
    int i;

    puts("Generujem zaciatocne poradie:");
	for(i=0;i<d;i++){
	    p[i]=rand()%100;			//generacia nahodnych cisel [0,99], aby som tam nemal prilis velke hodnoty
		printf("%2d ", p[i]);	
	}
	printf("\n \n");
}
	
char nahodna_permutacia_s_obmedzenim_vzdialenosti(int *p, int l, int dist){
	int i,j;
	int *helppole = malloc(sizeof(int)*l);
 	int *pole_zoradenie = malloc(sizeof(int)*l);
 	
    for(i=0;i<l;i++){
        helppole[i]=0;
        pole_zoradenie[i]=0;
    }
	int pokracuj=0, done=0;
	int min, max, odzadu=0;	
	int gen;

	Napln(p,l);			//naplnim povodne pole nahodnymi cislami
	
	if(dist>l)
        dist=l;
 	
 	while (done==0){
 		
	 	for(i=0;i<l;i++){			//prechadzam po novom poli, kde bude presuvanie
			
            odzadu++;
			if (i==l-1)
				done=1; 
			
			pokracuj=0;
			
	 		if(i-dist<=0) min=0;
	 		else min= i-dist;
	 		if(i+dist>=l) max=l;
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
					//for(j=0;j<l;j++)	printf("%d ",helppole[j]);				
					
					//printf("\n\t\t\t\t Podarilo sa: %d \n",i);			//
					for(j=0;j<l;j++)
                        helppole[j]=0;
					odzadu=-1;
					pokracuj=0;
					done=0;
					i=0; 
					//puts("\t\t\tUplne odznova");					//
					break;
				}
				
	 		}
	 		
	 		if(i>dist+1 && helppole[i-dist-1]==0){				//kontrola dozadu - ci to nerata zbytocne
				//for(j=0;j<l;j++)	printf("%d ",helppole[j]);				
				//printf("\n\t\t\t\t Podarilo sa: %d \n",i);			//
				for(j=0;j<l;j++)
                    helppole[j]=0;
				odzadu=-1;
				pokracuj=0;
				i=0; 
				//puts("\t\t\t\t\t\tUplne odznova / kvoli zabudnutiu");					//
				break;						
	 		}
 		}
 	}
	
	puts("Nove poradie:");
	for (i=0;i<l;i++){
		printf("%2d ", pole_zoradenie[i]);			//pre kontrolu mi vypise, ake nastanu posuny
		helppole[i]=p[i];							//skopiruje povodne pole - priprava na permutaciu
	}
	
	
	for(i=0;i<l;i++){
		p[pole_zoradenie[i]]=helppole[i];
	}
	puts("");
	puts("Nova permutacia:");
	for(i=0;i<l;i++)
		printf("%2d ",p[i]);
	
}
	
int main(){
    srand(time(NULL));
    int i;
	int dist=6;		//sem zadam sam hodnotu  
	int n=50;
	int *pole = malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
        pole[i]=-1;
		
	//int pole[n]={-1};
	int *p = pole;	
	nahodna_permutacia_s_obmedzenim_vzdialenosti(p, n, dist);
}
