	#include <stdio.h>
	#include <stdlib.h>
	#define n 10		//sem zadam sam hodnotu
	
	void Napln(int p[], int d){
		int i;
		for(i=0;i<=d;i++){
			p[i]=rand()%100;			//generacia nahodnych cisel [0,99], aby som tam nemal prilis velke hodnoty
		}
	}
	
 char nahodna_permutacia_s_obmedzenim_vzdialenosti(int *p, int l, int dist){
 	int helpole[n]={0};
 	int i,temp_a,temp_zaciatok,temp_koniec;
 	
 	for(i=p;i<=p+n;i+4){		//i+4, pretoze sa posuvam po 4 bytoch kvoli integerom
 		if (i-p)<dist{
 			temp_a = rand()%((2*dist)+1)-(i-p);
		 	}
		else{
			temp_a = rand()%((2*dist)+1)-dist;	
		}
		
	if (helpole[temp_a]==0){
		helpole[temp_a]=temp_a;
	}
	else if(temp_a==(i-dist*4))	
		
		
	}
 	
 	for (i=0;i<20;i++){
 		printf("%d ",rand()%(2*dist+1)-dist);
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
