// Kareem Mohamed Morsy		         , ID: 20190386, Group: CS-S3, Program: CS
// Mohamed Ashraf Mohamed Ali        , ID: 20190424, Group: CS-S3, Program: CS
// Mostafa Mahmoud Anwar Morsy Sadek , ID: 20190544, Group: CS-S3, Program: CS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "mpi.h"

#define ZETA 1.202056903159594

int main(int argc, char *argv[]) {
    int numprocs, rank;
    MPI_Status status; /* return status for recieve*/
    long long interval;
    double sum = 0.0;
    double return_sum;
    long long n;
    double i;
    long long start, end;

    //MPI Start
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0){
        printf("N -> ");
        scanf("%lld", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    interval = n / numprocs;
    start = rank * interval;
    end = start + interval;
    if (rank < n % (numprocs)) {
        start+= rank;
        end+= rank + 1;
    } else {
        start+= n % numprocs;
        end+= n % numprocs;
    }
    
    /* right shift the intervals */
    ++start;
    ++end;

    for (i = start; i < end; i++)
    {
        sum += 1 / (i * i * i);
    }
    
    MPI_Reduce(&sum, &return_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Result: %.15lf, error: %.15lf\n", return_sum, ZETA - return_sum);

    MPI_Finalize();
}