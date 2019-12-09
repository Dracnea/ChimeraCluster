/*
* Nicholas Ashenfelter
* Madhava-Leibniz formula for pi
* 2019-12-08
*/
#include <stdio.h>
#include <stdlib.h> // strtold()
#include <math.h>   // M_PI
#include <time.h>   // clock()
#include <mpi.h>

long double sums(long double start, long double stop, long double deno)
{
	long double sum = 0.0;
	long double factor = 1.0;
	long double denominator = deno;
	
	for (unsigned term = start; term < stop; term++) {
	sum += factor * (long double)1.0 / denominator;
	factor = -factor;
	denominator += 2;  // odd values only
	}
	return 4 * sum;
}

int main(int argc, char **argv)
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv); // ...or just "MPI_Init(NULL, NULL);"

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
	
    double nterms = 1024;
	
    if (argc > 1) {
        int power = atoi(argv[1]);
        nterms = pow(2.0, power);
        fprintf(stderr, "%u power --> %.0lf terms\n", power, nterms);
    }

    time_t timestart = clock();

    long double deno =  1.0L / nterms;
    long double range = nterms / world_size;
    long double start = processor_rank * range;
    long double stop = (processor_rank + 1) * range;
    
    //call fucntion based on amount of processers
    long double pi_piece = sums(start, stop, deno);   // 4.0 factor in the ftn...

    int tag = 0;
    if (processor_rank != 0) {  // not root process
        MPI_Send(&pi_piece, 1, MPI_LONG_DOUBLE, 0, tag, MPI_COMM_WORLD);

    } else {    // root process
        long double pi_approx = pi_piece;
        for (int rank = 1; rank < world_size; rank++) {
            MPI_Recv(&pi_piece, 1, MPI_LONG_DOUBLE, rank, tag,
                        MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pi_approx += pi_piece;
        }

        //------------------------------------------------------------------
        // Report the calculation results:
        long double error = fabs( pi_approx - M_PI );
        if (error < 0.0L)
            error = -error;
        int width = (fabs(log10(error)) + 1);  // show digits
        printf("  M_PI: %.*lf\napprox: %.*Lf\nerror=%.3Le\n",
                width, M_PI, width, pi_approx, error);

    }
    MPI_Finalize();

    time_t timestop = clock();
    printf("\n(%.6lf seconds)\n",
            (double)(timestop-timestart)/(double)CLOCKS_PER_SEC);

    return 0;
}