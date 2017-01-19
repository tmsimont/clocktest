#include <cstring>
#include <algorithm>
#include <omp.h>
#include <stdio.h>

using namespace std;


typedef float real;

int main(int argc, char** argv) {
	int num_threads = 1;

	if (argc >= 2)
		printf("N\tclock\twall\n");

	for (int i = 0; i < 6; ++i) {

		// global start
		clock_t start_clock = clock();
		double start_wall;


		#pragma omp parallel num_threads(num_threads)
		{
			// thread-local "now"
			clock_t now_clock;
			double now_wall;

			int id = omp_get_thread_num();

			// one thread sets the start time
			if (id == 0) {
					start_wall = omp_get_wtime();
			}

			#pragma omp barrier

			while (1) {
				now_clock = clock();
				now_wall = omp_get_wtime();

				if (argc < 2)
				printf("%c %d %.2f %.2f",
						13,
						num_threads,
						((real)(now_clock - start_clock) / (real)CLOCKS_PER_SEC),
						((real)(now_wall - start_wall))
					);
				if (argc < 2)
				fflush(stdout);

				// each thread will break after 10 wall clock seconds
				if (((real)(now_wall - start_wall)) > 10)
					break;
			};

			#pragma omp barrier

			// one thread prints the clock() time from run
			if (id == 0) {
				if (argc >= 2)
				printf("%d\t%.2f\t%.2f\n",  
						num_threads,
						((real)(now_clock - start_clock) / (real)CLOCKS_PER_SEC),
						((real)(now_wall - start_wall))
					);
			}
		}

		num_threads *= 2;

	}
}
