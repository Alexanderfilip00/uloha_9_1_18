#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define ELEM(M,r,c) (M->elem[(M->cols)*r+c])
#ifndef O_BINARY
#define O_BINARY 0
#endif

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
	}MAT;

MAT *mat_create_with_type(unsigned int rows, unsigned int cols){
	
	MAT *A;
	A = (MAT*)malloc(sizeof(MAT));
	
	if(A==NULL){
		free(A);
		return NULL;
	}
	
	float *pole;
	pole = (float*)malloc(sizeof(float)*rows*cols);
	
	A->rows = rows;
	A->cols = cols;
	A->elem = pole;
	
	return A;	
}

MAT *mat_add(MAT *a, MAT *b){		//funkcia na scitanie matic
	int i,j;
	MAT *c = mat_create_with_type(a->rows,a->cols);
	for(i=0; i < a->rows ; i++){
		for(j=0; j < a->cols ; j++){
			ELEM(c,i,j) = ELEM(a,i,j) + ELEM(b,i,j);
		}
	}
	return c;
}

MAT *mat_sub(MAT *a, MAT *b){		//funkcia na odcitanie matic
	int i,j;
	MAT *c = mat_create_with_type(a->rows,a->cols);
	for(i=0; i < a->rows ; i++){
		for(j=0; j < a->cols ; j++){
			ELEM(c,i,j) = ELEM(a,i,j) - ELEM(b,i,j);
		}
	}
	return c;
}


MAT *mat_create_by_file(char *filename){
	
	unsigned int r,s;
	int dlzka;
	char typ[2]={0};
	int FILE = open(filename,O_RDONLY | O_BINARY, S_IRUSR);
	if( FILE < 0){
		//printf("Subor neexistuje.");
		return NULL;
	}
	
	read(FILE, &typ, sizeof(char)*2);
	if(typ[0] != 'M' || typ[1] != '1'){
		//printf("\nCHYBA: Subor nereprezentuje hustu maticu.\n");
		return NULL;
	}

	read(FILE, &r, sizeof(unsigned int));
	read(FILE, &s, sizeof(unsigned int));

	if(r==EOF || s==EOF){
		//printf("\nCHYBA: Koniec suboru.\n");		
		return NULL;
	}
	MAT *A = mat_create_with_type(r,s);

	dlzka = read(FILE, A->elem, sizeof(float)*r*s);
	if (dlzka != sizeof(float)*r*s){
		//printf("\nCHYBA: Nedostatok hodnot.\n");
		return NULL;
	}
	
	close(FILE);
	return A;
}


void mat_unit(MAT *mat){
	int i,j;
	for(i=0 ; i < mat->rows ; i++){
		for(j=0 ; j < mat->cols ; j++){
			if(i != j)
				ELEM(mat,i,j)=0.0;
			else
				ELEM(mat,i,j)=1.0;
		}
	}
}

char mat_save(MAT *mat, char *filename){
	
	int FILE = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, S_IRUSR | S_IWUSR);
	if( FILE < 0){
		//printf("CHYBA: subor sa nepodarilo otvorit.");
		return -1;
	} 

	write(FILE, "M", sizeof(char));
	write(FILE, "1", sizeof(char));

	write(FILE, &mat->rows, sizeof(unsigned int));
	write(FILE, &mat->cols, sizeof(unsigned int));
	write(FILE, mat->elem, sizeof(float)*(mat->rows)*(mat->cols));
	close(FILE);	
}


void mat_destroy(MAT *mat){
	free(mat->elem);
	free(mat);
}

void mat_print(MAT *mat){
	int i,j;
	for(i=0 ; i < mat->rows ; i++){
		for(j=0 ; j < mat->cols ; j++){
			printf("%5.2f ",ELEM(mat,i,j));
		}
		printf("\n");
	}
}

void mat_random(MAT *mat){
	int i,j;
	for(i=0 ; i < mat->rows ; i++){
		for(j=0 ; j < mat->cols ; j++){
			ELEM(mat,i,j)=(rand() / (float)RAND_MAX)*2.0 - 1.0;	
		}
	}

}

MAT *mat_quarter(MAT *a, int q){			//rozdelenie jednej matice na 4 kvadranty, kde vysledkom je stale len ziadany kvadrant
	unsigned int i=0,j=0,r=0,c=0;
	MAT *B = mat_create_with_type((a->rows)/2,(a->cols)/2);
	if(q==1){
		r=0;
		c=0;
	}
	else if(q==2){
		r=0;
		c=(a->cols) / 2;
	}
	else if(q==3){
		r= (a->rows) / 2;
		c= 0;
	}
	else if(q==4){
		r= (a->rows) / 2;
		c= (a->cols) / 2;
	}
	for(i=0 ; i < (a->rows)/2; i++){
		for(j=0 ; j < (a->cols)/2; j++){
			ELEM(B,i,j) = ELEM(a,(i+r),(j+c));
			
		}
	}
	return B;
}

void mat_quad_join(MAT *c, MAT *c1, MAT *c2, MAT *c3, MAT *c4){		//spojenie 4 podmatic do jednej matice
	int i,j;
	int pol = (c->rows)/2;
	for(i=0;i < pol; i++){
		for(j=0;j < pol; j++){
			ELEM(c,i,j) = ELEM(c1,i,j);
			ELEM(c,i,(j+pol)) = ELEM(c2,i,j);
			ELEM(c,(i+pol),j) = ELEM(c3,i,j);
			ELEM(c,(i+pol),(j+pol)) = ELEM(c4,i,j);
		}
	}
}

char mat_multiply_strassen(MAT *a, MAT *b, MAT *c){
	int pol_velkost;
	float velkost = (float)a->rows;
	unsigned int n=0;									//cislo n hovori o komplexnosti strassenovho algoritmu

	while(velkost != 1.0 || n==0){						//test, ci je matica velkosti 2^n
		velkost /= 2.0;
		n++;
		if((velkost - (int)velkost) != .0){
			//printf("CHYBA: Nespravna velkost, nie je to 2^n!");
			return -1;
		}
	}
	
	velkost = a->cols;						//test, ci su vsetky matice rovnakej velkosti
	
	if(((int)velkost != a->rows) || ((int)velkost != b->cols) || ((int)velkost != b->rows) || ((int)velkost != c->cols) || ((int)velkost != c->rows)){
		//printf("CHYBA: Matice maju roznu velkost!\n");
		return -1;
	}

	if(n==1){					//ak matica je velkosti 2x2, spravi to priamy vypocet
		float p[8]={0};	
		p[1] = ELEM(a,0,0) * (ELEM(b,0,1) - ELEM(b,1,1) );		//ciastocne vypocty
		p[2] = (ELEM(a,0,0) + ELEM(a,0,1)) * ELEM(b,1,1);
		p[3] = (ELEM(a,1,0) + ELEM(a,1,1)) * ELEM(b,0,0);
		p[4] = ELEM(a,1,1) * ( ELEM(b,1,0) - ELEM(b,0,0) );
		p[5] = (ELEM(a,0,0) + ELEM(a,1,1)) * (ELEM(b,0,0) + ELEM(b,1,1));
		p[6] = (ELEM(a,0,1) - ELEM(a,1,1)) * (ELEM(b,1,0) + ELEM(b,1,1));
		p[7] = (ELEM(a,0,0) - ELEM(a,1,0)) * (ELEM(b,0,0) + ELEM(b,0,1));
		
		ELEM(c,0,0) = p[5] + p[4] - p[2] + p[6];
		ELEM(c,0,1) = p[1] + p[2];
		ELEM(c,1,0) = p[3] + p[4];
		ELEM(c,1,1) = p[1] + p[5] - p[3] - p[7];
		return 0;
	}
	
	else{
		pol_velkost = (int)velkost / 2;
		
		MAT *p1 = mat_create_with_type(pol_velkost,pol_velkost);										//stale vytvori novu maticu
		mat_multiply_strassen((mat_quarter(a,1)),(mat_sub(mat_quarter(b,2),mat_quarter(b,4))),p1);		//vypocty podla vzorcov
		MAT *p2 = mat_create_with_type(pol_velkost,pol_velkost);
		mat_multiply_strassen(mat_add(mat_quarter(a,1),mat_quarter(a,2)),mat_quarter(b,4),p2);
		MAT *p3 = mat_create_with_type(pol_velkost,pol_velkost);
		mat_multiply_strassen(mat_add(mat_quarter(a,3),mat_quarter(a,4)),mat_quarter(b,1),p3);
		MAT *p4 = mat_create_with_type(pol_velkost,pol_velkost);
		mat_multiply_strassen(mat_quarter(a,4),mat_sub(mat_quarter(b,3),mat_quarter(b,1)),p4);
		MAT *p5 = mat_create_with_type(pol_velkost,pol_velkost);
		mat_multiply_strassen(mat_add(mat_quarter(a,1),mat_quarter(a,4)),mat_add(mat_quarter(b,1),mat_quarter(b,4)),p5);
		MAT *p6 = mat_create_with_type(pol_velkost,pol_velkost);
		mat_multiply_strassen(mat_sub(mat_quarter(a,2),mat_quarter(a,4)),mat_add(mat_quarter(b,3),mat_quarter(b,4)),p6);
		MAT *p7 = mat_create_with_type(pol_velkost,pol_velkost);
		mat_multiply_strassen(mat_sub(mat_quarter(a,1),mat_quarter(a,3)),mat_add(mat_quarter(b,1),mat_quarter(b,3)),p7);
		
		MAT *c1 = mat_add(mat_sub(mat_add(p5,p4),p2),p6);		//finalne operacie podmatic
		MAT *c2 = mat_add(p1,p2);
		MAT *c3 = mat_add(p3,p4);
		MAT *c4 = mat_sub(mat_sub(mat_add(p1,p5),p3),p7);
	
		mat_quad_join(c, c1,c2,c3,c4);			//spojenie podmatic
		
		mat_destroy(c1);		//precistenie nadbytocnych matic
		mat_destroy(c2);
		mat_destroy(c3);
		mat_destroy(c4);
		mat_destroy(p1);
		mat_destroy(p2);
		mat_destroy(p3);
		mat_destroy(p4);
		mat_destroy(p5);
		mat_destroy(p6);
		mat_destroy(p7);
	}	
}


//...............................................................................................

/*int main(){
	int a=4;			//nastavenie velkosti vsetkych matic, na testovacie ucely
	srand(time(NULL));
	MAT *A = mat_create_with_type(a,a);
	MAT *B = mat_create_with_type(a,a);
	MAT *C = mat_create_with_type(a,a);
	mat_random(A);
	mat_random(B);
	
	mat_print(A);
	puts("");
	mat_print(B);

	mat_multiply_strassen(A,B,C);
	puts("");
	mat_print(C);

} */

int main(){
	int a=4;
	srand(time(NULL));
	MAT *A = mat_create_with_type(a,a);
	mat_random(A);
	puts("Povodna matica:");
	mat_print(A);
	
	mat_save(A, "matica_A.bin");
	MAT *B = mat_create_by_file("matica_A.bin");
	puts("Precitana matica:");
	mat_print(B);
	
}
