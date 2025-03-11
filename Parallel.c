#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ROWS 20
#define COLS 20

void parallel_matrix_vector_addition(float matrix[ROWS][COLS], const float vector[COLS], float result[ROWS][COLS]) {
    int num_threads = omp_get_max_threads();
    omp_set_num_threads(num_threads);

    #pragma omp parallel 
    {
        int id = omp_get_thread_num();
        if (id == 0) {
            printf("Using %d threads\n", num_threads);
        }

        #pragma omp for schedule(static, 100)
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                result[i][j] = matrix[i][j] + vector[j];
            }
        }
    }
}

int main() {
    float matrix[ROWS][COLS];
    float result[ROWS][COLS];
    float vector[COLS];

    srand(time(NULL));

    #pragma omp parallel for schedule(static, 100)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = (float)(rand() % 100);
        }
    }

    #pragma omp parallel for schedule(static, 100)
    for (int j = 0; j < COLS; j++) {
        vector[j] = (float)(rand() % 100);
    }

    double start_par = omp_get_wtime();
    parallel_matrix_vector_addition(matrix, vector, result);
    double end_par = omp_get_wtime();

    printf("Parallel Execution Time: %f seconds\n", end_par - start_par);

    return 0;
}
