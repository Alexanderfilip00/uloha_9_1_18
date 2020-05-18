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
	
	float *pole;
	pole = (float*)malloc(sizeof(float)*rows*cols);
	
	A->rows = rows;
	A->cols = cols;
	A->elem = pole;
	
	if(A==NULL){
		free(A);
		free(pole);
		return NULL;
	}
	return A;	
}

MAT *mat_create_by_file(char *filename){
	
	unsigned int r,s;
	int dlzka;
	char typ[2]={0};
	int FILE = open(filename,O_RDONLY | O_BINARY, S_IRUSR);
	if( FILE < 0){
		printf("Subor neexistuje.");
		return NULL;
	}
	
	read(FILE, &typ, sizeof(char)*2);
	if(typ[0] != 'M' || typ[1] != '1'){
		printf("\nCHYBA: Subor nereprezentuje hustu maticu.\n");
		return NULL;
	}

	read(FILE, &r, sizeof(unsigned int));
	read(FILE, &s, sizeof(unsigned int));

	if(r==EOF || s==EOF){
		printf("\nCHYBA: Koniec suboru.\n");		
		return NULL;
	}
	MAT *A = mat_create_with_type(r,s);

	dlzka = read(FILE, A->elem, sizeof(float)*r*s);
	if (dlzka != sizeof(float)*r*s){
		printf("\nCHYBA: Nedostatok hodnot.\n");
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
		printf("CHYBA.");
		return 0;
	} 

	write(FILE, "M", sizeof(char));
	write(FILE, "1", sizeof(char));

	write(FILE, &mat->rows, sizeof(unsigned int));
	write(FILE, &mat->cols, sizeof(unsigned int));
	write(FILE, mat->elem, sizeof(float)*(mat->rows)*(mat->cols));
	close(FILE);	
}


void mat_destroy(MAT *mat){
	free(&mat->elem);
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
			ELEM(mat,i,j)=(rand() / 32767.0)*2.0 - 1.0;	
		}
	}

}

//...............................................................................................

int main(){
	srand(time(NULL));
	MAT *A = mat_create_with_type(4,4);
	mat_random(A);
	mat_print(A);


	
}
