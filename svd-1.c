
; This program first defines a 10x5 data matrix and initializes it with random values. 
; It then performs the SVD decomposition of the data matrix using the gsl_linalg_SV_decomp() function 
; from the GNU Scientific Library (GSL).
;
; Next, it reduces the dimensionality of the data by setting all but the top 3 singular values to zero. 
; It then computes the reduced data matrix using the gsl_linalg_SV_reconstruct() function and prints it to the terminal.
;
; Finally, it frees the memory allocated for the SVD decomposition and the reduced data matrix.
;
; This simple program demonstrates how to use the SVD to reduce the dimensionality of a high-dimensional data set in C. 
; You can modify the program by changing the value of k to control the desired reduced dimensionality of the data.
; sj


#include <stdio.h>
#include <gsl/gsl_linalg.h>

int main() {
  int i, j;

  // Define the dimensions of the data matrix
  int m = 10;
  int n = 5;

  // Allocate memory for the data matrix and initialize it with random values
  double data[m][n];
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      data[i][j] = rand() % 10;
    }
  }

  // Allocate memory for the SVD decomposition
  gsl_matrix *U = gsl_matrix_alloc(m, m);
  gsl_matrix *V = gsl_matrix_alloc(n, n);
  gsl_vector *S = gsl_vector_alloc(n);

  // Perform the SVD decomposition
  gsl_linalg_SV_decomp(data, U, V, S);

  // Reduce the dimensionality by retaining only the top k singular values
  int k = 3;
  for (i = k; i < n; i++) {
    gsl_vector_set(S, i, 0);
  }

  // Allocate memory for the reduced data matrix
  gsl_matrix *reduced_data = gsl_matrix_alloc(m, k);

  // Compute the reduced data matrix using the SVD decomposition
  gsl_linalg_SV_reconstruct(U, V, S, reduced_data);

  // Print the reduced data matrix
  for (i = 0; i < m; i++) {
    for (j = 0; j < k; j++) {
      printf("%lf ", gsl_matrix_get(reduced_data, i, j));
    }
    printf("\n");
  }

  // Free the allocated memory
  gsl_matrix_free(U);
  gsl_matrix_free(V);
  gsl_vector_free(S);
  gsl_matrix_free(reduced_data);

  return 0;
}


