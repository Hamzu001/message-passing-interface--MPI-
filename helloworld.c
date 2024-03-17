// MPI_Send, MPI_Recv data between processes.
  #include <mpi.h>
  #include <stdio.h>
  #include <stdlib.h>

  int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    // Find out rank ==> process_index/id
    int process_id; /* get current process id */
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    // Find out size ==> total_processes
    int total_process; /* get number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &total_process);
    // print 
    printf("Current process id %d or total number of processes %d\n", process_id, total_process);
    // We are assuming at least 2 processes for this task, if not then return this if ↓
    if (total_process < 2) {
      fprintf(stderr, "Number of process must be greater than 1 for %s\n", argv[0]);
      MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int number;
    if (process_id == 0) {
      // If we are rank 0, set the data and send it to process
      number = 10;
      MPI_Send(
        /* data         = */ &number,               //Address for the message you are sending.
        /* count        = */ 1,                     //Number of elements being sent through the address.
        /* datatype     = */ MPI_INT,               //The MPI specific data type being passed through the address.
        /* destination  = */ 1,                     //Rank of destination process.
        /* tag          = */ 0,                     //Message tag.
        /* communicator = */ MPI_COMM_WORLD);       //The MPI Communicator handle.
    } else if (process_id == 1) {
      MPI_Recv(
        /* data         = */ &number,                //Address to the message you are receiving.
        /* count        = */ 1,                      //Number of elements being sent through the address.
        /* datatype     = */ MPI_INT,                //The MPI specific data type being passed through the address.
        /* source       = */ 0,                      //Process rank of sending process.
        /* tag          = */ 0,                      //Message tag.
        /* communicator = */ MPI_COMM_WORLD,         //The MPI Communicator handle.
        /* status       = */ MPI_STATUS_IGNORE);     //Status object.
      // print received data & process_id 
      printf("In process %d received data %d from process 0\n", process_id, number);
    }
  // This function cleans up the MPI environment and ends MPI communications.
  MPI_Finalize();
  
}