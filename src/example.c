#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    double start = MPI_Wtime();

    int el = 100;

    int world_size;
    int world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // amount of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // current process
    int elements_in_sub_array = el / (world_size - 1);
    int *sub_array = malloc(elements_in_sub_array * sizeof(int));
    int *occures = malloc(100 * sizeof(int));

    if (world_rank == 0) {
        printf("Proces %d - Generowanie tablicy z el losowych elementow\n", world_rank);
        int numbers[el];
        for (int i = 0; i < el; i++) {
            numbers[i] = rand() % 100;
        }

        int head_of_array = 0;
        for (int process_index = 1; process_index < world_size; process_index++) {
            printf("Proces %d - Przygotowywanie fragmentu tablicy w zakresie od %d do %d\n", world_rank, head_of_array, (head_of_array + elements_in_sub_array));
            int tmp_index = 0;
            for (int i = head_of_array; i <= (head_of_array + elements_in_sub_array); i++) {
                sub_array[tmp_index++] = numbers[i];
            }
            head_of_array += elements_in_sub_array;

            
            printf("Proces %d - Przesylanie fragmentu tablicy dla procesu: %d\n", world_rank, process_index);
            MPI_Send(sub_array, elements_in_sub_array, MPI_INT, process_index, 0, MPI_COMM_WORLD);
        }

        int occures_global[100];
        for (int i = 0; i < 100; i++) {
            occures_global[i] = 0;
        }
        for (int process_index = 1; process_index < world_size; process_index++) {
            printf("Proces %d - Odebral obliczenia od procesu: %d\n", world_rank, process_index);
            MPI_Recv(occures, 100, MPI_INT, process_index, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int i = 0; i < 100; i++) {
                occures_global[i] += occures[i];
            }
        }
        for (int i = 0; i < 100; i++) {
            printf("%d wystapilo: %d\n",i ,occures_global[i]);
        }
    }
    
    else if (world_rank > 0 && world_rank < world_size) {
        MPI_Recv(sub_array, elements_in_sub_array, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proces %d - Odebral dane i rozpoczyna obliczanie\n", world_rank);
        for (int i = 0; i < 100; i++) {
            occures[i] = 0;
        }
        for (int i = 0; i < elements_in_sub_array; i++) {
            occures[sub_array[i]]++;
        }
        MPI_Send(occures, 100, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    



    double stop = MPI_Wtime();
    printf("Czas wykonania wyniosl %f sekund\n", stop - start);
    MPI_Finalize();
}