// datove typy
typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;
	
// makra
#define ELEM(M,r,c) (M->elem[(M->cols)*r+c])

// prototypy
void mat_destroy(MAT*);
MAT *mat_create_with_type(unsigned int, unsigned int);
//MAT *mat_add(MAT*, MAT*);
//MAT *mat_sub(MAT*, MAT*);
MAT *mat_create_by_file(char*);
void mat_unit(MAT*);
char mat_save(MAT*, char*);
void mat_destroy(MAT*);
void mat_print(MAT*);
void mat_random(MAT*);
//MAT *mat_quarter(MAT*, int);
//void mat_quad_join(MAT*, MAT*, MAT*, MAT*, MAT*);
char mat_multiply_strassen(MAT*, MAT*, MAT*);

// niekolko poucnych slov
//
// 1) vsimnite si, ze pri deklaracii prototypu netreba uvadzat mena argumentov
//    kompilator to nepotrebuje... kompilator potrebuje vediet iba, akeho su
//    typu
//
// 2) tym, ze niektore prototypy v tomto hlavickom subore neuvediem (vid 4 za
//    komentovane prototypy) vyjadrujem tym, ze si nezelam, aby boli teto fun
//    kcie pristupne v inych castiach zdrojoveho kodu vacsieho programu. To je
//    krasna ukazka toho, ako sa da v uplne plochom Ccku emulovat objektovost,
//    konkretne existencia sukromnych a verejnych metod objektu. Pretoze funk
//    cie na odcitovanie, scitovanie matic, stvrtenie matice a spajanie matic
//    su vyslovene obsluzne rutiny pre strassenovo nasobenie, je rozumne ich
//    existenciu mimo suboru matice.c zatajit. Docieli sa to tym, ze sa ich
//    prototypy NEuvedu v prislusnom hlavickovom subore.
//
//    Tu treba dodat, aby bolo jasne, o com tu pisem, ze pri programovani vel
//    kych projektov je zdrojovy kod, samozrejme, rozdeleny na viacero suborov.
//
