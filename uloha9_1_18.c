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
	
	}
	
	char mat_save(MAT *mat, char *filename){
		
		int i;
		int FILE = open(filename,O_BINARY | O_CREAT, S_IWUSR);
		if( FILE < 0){
			return 0;
		}
		
		char buf = 'm';
		write(FILE, &buf, 4);
		write(FILE, "1", sizeof(char));
		write(FILE, &mat->rows, sizeof(unsigned int));
		write(FILE, &mat->cols, sizeof(unsigned int));
		printf("%c",buf);
		write(FILE, &mat->elem,sizeof(float)*mat->rows*mat->cols);
		
		
		close(FILE);	
	}
	
	void mat_destroy(MAT *mat){
		free(&mat->elem);
		free(mat);
		
	}

	
	int main(){
		MAT *A = mat_create_with_type(5,5);
		//printf("%2.1f\n", ELEM(A,0,0));
		//printf("%2.1f ",A->elem[0]);
		mat_save(A, "skuska2.bin");
		
		
	}
