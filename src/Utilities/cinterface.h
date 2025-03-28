#ifndef CINTERFACE_H
#define CINTERFACE_H

#ifdef __cplusplus
using namespace ColPack;

extern "C" {
#endif

// Builds coloring, bicoloring or partial coloring from file
int build_coloring_from_file(void** ref, int* len, const char* filename, const char* method, const char* order, int verbose);
int build_partial_coloring_from_file(void** ref, int* len, const char* filename, const char* method, const char* order, int verbose);
int build_bicoloring_from_file(void** ref, int* len1, int* len2, const char* filename, const char* method, const char* order, int verbose);

// Builds coloring, bicoloring or partial coloring from ADOLC compressed row format
int build_coloring_from_adolc(void** ref, int* len, unsigned int** csr, int nrows, const char* method, const char* order, int verbose);
int build_partial_coloring_from_adolc(void** ref, int* len, unsigned int** csr, int nrows, int ncols, const char* method, const char* order, int verbose);
int build_bicoloring_from_adolc(void** ref, int* len1, int* len2, unsigned int** csr, int nrows, int ncols, const char* method, const char* order, int verbose);

// Build partial coloring and bicoloring from CSR format
int build_partial_coloring_from_csr(void** ref, int* len, int* rowptr, int* colval, int nrows, int ncols, const char* method, const char* order, int verbose);
int build_bicoloring_from_csr(void** ref, int* len1, int* len2, int* rowptr, int* colval, int nrows, int ncols, const char* method, const char* order, int verbose);

// Build partial coloring and bicoloring from CSC format
int build_partial_coloring_from_csc(void** ref, int* len, int* rowval, int* colptr, int nrows, int ncols, const char* method, const char* order, int verbose);
int build_bicoloring_from_csc(void** ref, int* len1, int* len2, int* rowval, int* colptr, int nrows, int ncols, const char* method, const char* order, int verbose);

// Recover the ordering of the vertices
void order_coloring(void* ref, int* ordering);
void order_partial_coloring(void* ref, int* ordering);
void order_bicoloring(void* ref, int* ordering);

double timer_order_coloring(void* ref);
double timer_order_partial_coloring(void* ref);
double timer_order_bicoloring(void* ref);

// Recover the coloring of the vertices
void colors_coloring(void* ref, int* coloring);
void colors_partial_coloring(void* ref, int* coloring);
void colors_bicoloring(void* ref, int* left_coloring, int* right_coloring);

double timer_colors_coloring(void* ref);
double timer_colors_partial_coloring(void* ref);
double timer_colors_bicoloring(void* ref);

int ncolors_coloring(void* ref);
int ncolors_partial_coloring(void* ref);
int ncolors_bicoloring(void* ref);

void free_coloring(void* ref);
void free_partial_coloring(void* ref);
void free_bicoloring(void* ref);

#ifdef __cplusplus
}
#endif

#endif
