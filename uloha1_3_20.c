#include <stdio.h>
#include <stdlib.h>
#include <math.h>
	
void Napln(int p[], int d){
    int i;

	for(i=0;i<d;i++){
	    p[i]=rand()%100;			//generacia nahodnych cisel [0,99], aby som tam nemal prilis velke hodnoty	
	}
}
	
char nahodna_permutacia_s_obmedzenim_vzdialenosti(int *p, int l, int dist){
	int i,j;
	int *helppole = malloc(sizeof(int)*l);
 	int *pole_zoradenie = malloc(sizeof(int)*l);
	int pokracuj=0, done=0;
	int min, max, odzadu=0;	
	int gen;
 	
    for(i=0;i<l;i++){
        helppole[i]=0;
        pole_zoradenie[i]=0;
    }


	if(dist>l)
        dist=l;
 	
 	while (done==0){
 		
	 	for(i=0;i<l;i++){			//prechadzam po novom poli, kde bude presuvanie
			
            odzadu++;
			if (i==l-1)
				done=1; 
			
			pokracuj=0;
			
	 		if(i-dist<=0)
                min=0;
	 		else
                min= i-dist;

	 		if(i+dist>=l)
                max=l;
	 		else
                max= i+dist;
	 		
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
				break;						
	 		}
 		}
 	}
	
	for (i=0;i<l;i++){
		//printf("%2d ", pole_zoradenie[i]);			//pre kontrolu mi vypise, ake nastanu posuny
		helppole[i]=p[i];							//skopiruje povodne pole - priprava na permutaciu
	}
	
	
	for(i=0;i<l;i++){
		p[pole_zoradenie[i]]=helppole[i];
	}

	free(pole_zoradenie);
	free(helppole);
}
	
int main(){
    int i;
	int dist=6;		//sem zadam sam hodnotu  
	int n=50;
	int *pole = malloc(sizeof(int)*n);
	int *p = pole;	

    srand(time(NULL));
	Napln(p,n);			//naplnim povodne pole nahodnymi cislami

	puts("Povodna permutacia:");
	for(i=0;i<n;i++)
	printf("%d ", pole[i]);
		
	nahodna_permutacia_s_obmedzenim_vzdialenosti(p, n, dist);

	puts("\nNova permutacia:");
	for(i=0;i<n;i++)
    printf("%d ", pole[i]);
}
