#include <iostream>

#include <unistd.h>

#include <sys/wait.h>

#include <fcntl.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <iostream>

#include <pthread.h>

#include <semaphore.h>

#include <sys/types.h>

#include <unistd.h>

#include <sys/wait.h>

#include <fcntl.h>

#include <sys/stat.h>

#include <iostream>
#include <sstream>
using namespace std;

const int num_processes = 7;
const int max_num_threads = 8;
///////////////////////////////////
double input[] = {0.1, 0.2};

    double input_weight_1[][8] = {
        {0.1, -0.2, 0.3, 0.1, -0.2, 0.3, 0.1, -0.2},
        {-0.4, 0.5, 0.6, -0.4, 0.5, 0.6, -0.4, 0.5}
    };
    double hidden_layer_1_weights[][8] = {
        {-0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9},
        {0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8},
        {-0.7, 0.5, 0.8, -0.2, -0.3, -0.6, 0.1, 0.4},
        {-0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9},
        {0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8},
        {-0.7, 0.5, 0.8, -0.2, -0.3, -0.6, 0.1, 0.4},
        {-0.2, 0.3, -0.4, 0.5, 0.6, -0.7, 0.8, -0.9},
        {0.1, 0.9, -0.3, 0.2, -0.5, 0.4, 0.6, -0.8}
    };

    double hidden_layer_2_weights[][8] = {
        {0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9},
        {-0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8},
        {0.7, -0.5, -0.8, 0.2, 0.3, 0.6, -0.1, -0.4},
        {0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9},
        {-0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8},
        {0.7, -0.5, -0.8, 0.2, 0.3, 0.6, -0.1, -0.4},
        {0.2, -0.3, 0.4, -0.5, -0.6, 0.7, -0.8, 0.9},
        {-0.1, -0.9, 0.3, -0.2, 0.5, -0.4, -0.6, 0.8}
    };


 double hidden_layer_3_weights[][8] = {
        {0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1},
        {-0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1},
        {0.6, -0.5, -0.7, 0.2, 0.4, 0.8, -0.1, -0.3},
        {0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1},
        {-0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1},
        {0.6, -0.5, -0.7, 0.2, 0.4, 0.8, -0.1, -0.3},
        {0.3, -0.4, 0.5, -0.6, -0.7, 0.8, -0.9, 0.1},
        {-0.2, -0.9, 0.4, -0.3, 0.5, -0.6, -0.8, 0.1}
    };

 double hidden_layer_4_weights[][8] = {
        {0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2},
        {-0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2},
        {0.5, -0.4, -0.6, 0.3, 0.2, 0.8, -0.2, -0.1},
        {0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2},
        {-0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2},
        {0.5, -0.4, -0.6, 0.3, 0.2, 0.8, -0.2, -0.1},
        {0.4, -0.5, 0.6, -0.7, -0.8, 0.9, -0.1, 0.2},
        {-0.3, -0.8, 0.5, -0.4, 0.6, -0.7, -0.9, 0.2}
    };

 double hidden_layer_5_weights[][8] = {
        {0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3},
        {-0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1},
        {0.4, -0.3, -0.5, 0.1, 0.6, 0.7, -0.3, -0.2},
        {0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3},
        {-0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1},
        {0.4, -0.3, -0.5, 0.1, 0.6, 0.7, -0.3, -0.2},
        {0.5, -0.6, 0.7, -0.8, -0.9, 0.1, -0.2, 0.3},
        {-0.4, -0.7, 0.6, -0.5, 0.8, -0.6, -0.2, 0.1}
    };

    double output_layer[] = {-0.1, 0.2, 0.3, 0.4, 0.5, -0.6, -0.7, 0.8};

double output_1[8] = {
    0};
double result[8] = {
    0.0};
double final = 0.0;

double next_input[2] = {
    0.0};

double new_main[2] = {
    0.613101, -0.0769727};

sem_t sem[max_num_threads];
sem_t sem_all_threads_done;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t process_sem[num_processes];
sem_t sem_all_process_done;

struct thread_arg
{
   int thread_id;
   int process_id;
};

void *thread_process(void *arg)
{
   struct thread_arg *ta = (struct thread_arg *)arg;

   sem_wait(&sem[ta->thread_id - 1]);

   pthread_mutex_lock(&count_mutex);
   if (ta->process_id == 1)
   {
      std::cout << "Process " << ta->process_id << ", Thread " << ta->thread_id << " 1st layer calculation is running in process " << getpid() << std::endl;
      result[ta->thread_id - 1] = (input[0] * input_weight_1[0][ta->thread_id - 1]) + (input[1] * input_weight_1[1][ta->thread_id - 1]);
   }
   else if (ta->process_id == 2)
   {
      std::cout << "Process " << ta->process_id << ", Thread " << ta->thread_id << " 2nd layer is running in process " << getpid() << std::endl;
      for (int j = 0; j < 8; j++)
      {
         result[ta->thread_id - 1] += output_1[j] * hidden_layer_1_weights[j][ta->thread_id - 1];
      }
   }
   else if (ta->process_id == 3)
   {
      std::cout << "Process " << ta->process_id << ", Thread " << ta->thread_id << " 3rd layer is running in process " << getpid() << std::endl;
      for (int j = 0; j < 8; j++)
      {
         result[ta->thread_id - 1] += output_1[j] * hidden_layer_2_weights[j][ta->thread_id - 1];
      }
   }
   else if (ta->process_id == 4)
   {
      std::cout << "Process " << ta->process_id << ", Thread " << ta->thread_id << " 4th layer is running in process " << getpid() << std::endl;
      for (int j = 0; j < 8; j++)
      {
         result[ta->thread_id - 1] += output_1[j] * hidden_layer_3_weights[j][ta->thread_id - 1];
      }
   }
   else if (ta->process_id == 5)
   {
      std::cout << "Process " << ta->process_id << ", Thread " << ta->thread_id << " 5th layer is running in process " << getpid() << std::endl;
      for (int j = 0; j < 8; j++)
      {
         result[ta->thread_id - 1] += output_1[j] * hidden_layer_4_weights[j][ta->thread_id - 1];
      }
   }
   else if (ta->process_id == 6)
   {
      std::cout << "Process " << ta->process_id << ", Thread " << ta->thread_id << " 6th layer is running in process " << getpid() << std::endl;
      for (int j = 0; j < 8; j++)
      {
         result[ta->thread_id - 1] += output_1[j] * hidden_layer_5_weights[j][ta->thread_id - 1];
      }
   }
   else if (ta->process_id == 7)
   {
      std::cout << "Process " << ta->process_id << ", Thread " << ta->thread_id << " 7th layer is running in process " << getpid() << std::endl;

      final += output_1[ta->thread_id - 1] * output_layer[ta->thread_id - 1];
   }
   pthread_mutex_unlock(&count_mutex);

   sem_post(&sem[ta->thread_id % max_num_threads]);

   // Signal that the thread has finished its work
   sem_post(&sem_all_threads_done);

   return nullptr;
}

void final_next(double x)
{
   double value_1 = (x * x) + (x + 1);
   double value_2 = (x * x) - x;
   value_1 = value_1 / 2;
   value_2 = value_2 / 2;
   next_input[0] = value_1;
   next_input[1] = value_2;
   cout << endl;
   cout << "Values for next input are  " << next_input[0] << " and  " << next_input[1] << endl;
}

void process(int id, int num_threads)
{
   pthread_t threads[max_num_threads];
   struct thread_arg args[max_num_threads];

   // Launch the threads
   for (int i = 0; i < num_threads; ++i)
   {
      args[i].thread_id = i + 1;
      args[i].process_id = id;

      pthread_create(&threads[i], nullptr, thread_process, (void *)&args[i]);
   }

   // Wait for all the threads to finish without using pthread_join()
   for (int i = 0; i < num_threads; ++i)
   {
      sem_wait(&sem_all_threads_done);
   }

   std::cout << "Process " << id << " is done." << std::endl;

   std::cout << "=================================================================================" << std::endl;
   if (id == 7)
   {
      std::cout << "Output of neuron  in the final  " << id << " hidden layer: " << final << std::endl;
   }
   else
   {
      for (int i = 0; i < 8; i++)
      {
         std::cout << "Output of neuron " << i + 1 << " in the " << id << " hidden layer: " << result[i] << std::endl;
      }
   }
   std::cout << "=================================================================================" << std::endl;

   // Delete the threads
   for (int i = 0; i < num_threads; ++i)
   {
      pthread_detach(threads[i]);
   }
   cout << "lest " << endl;
}

int main()
{

   // Initialize the semaphores
   for (int i = 0; i < max_num_threads; ++i)
   {
      sem_init(&sem[i], 0, i == 0 ? 1 : 0);
   }

   sem_init(&sem_all_threads_done, 0, 0); // Initialize this semaphore

   sem_init(&sem_all_process_done, 0, 0); // Initialize this semaphore

   for (int i = 0; i < num_processes; ++i)
   {
      sem_init(&process_sem[i], 0, 1); // initialize all process semaphores to 0, except the first one
   }

   pid_t p[num_processes];
   char *pipe_final[num_processes];
   char *pipe[num_processes];

   for (int i = 0; i < num_processes; i++)
   {
      pipe[i] = new char[20];
      sprintf(pipe[i], "/tmp/pipe%d", i + 1);
      mkfifo(pipe[i], 0666);
   }

   // Launch the processes using fork() and wait for them to finish one by one
   for (int i = 0; i < num_processes; ++i)
   {
      p[i] = fork();

      if (p[i] < 0)
      {
         std::cerr << "Fork failed for process " << i + 1 << std::endl;
         return 1;
      }
      else if (p[i] == 0)
      {
         // Child process

         for (int i = 0; i < num_processes; i++)
         {
            pipe[i] = new char[20];
            sprintf(pipe[i], "/tmp/pipe%d", i + 1);
            mkfifo(pipe[i], 0666);
         }
         if (i != 0)
         {
            int fd_in = open(pipe[i - 1], O_RDONLY);
            read(fd_in, &output_1, sizeof(double) * 8);
            close(fd_in);
         }

         process(i + 1, 8);

         if (i != num_processes - 1)
         {
            int fd_out = open(pipe[i], O_WRONLY);
            write(fd_out, &result, sizeof(double) * 8);
            close(fd_out);
         }
         if (i == 6)
         {
            std::cerr << "process war gia " << i + 1 << std::endl;

            final_next(final);
         }

         exit(0);
      }
      else
      {
         // Parent process
         int status;
         // waitpid(p[i], &status, 0);
      }
   }

   for (int i = 0; i < num_processes; i++)
   {

      int status;

      waitpid(p[i], &status, 0); // Wait for specific child process to finish
   }

   for (int i = num_processes - 1, j = 0; i >= 0; j++, i--)
   {

      cout << "Values for next input are back tracking " << new_main[0] << " and  " << new_main[1] << endl;
      cout << "The Process Id is " << p[i] << "  value of i is " << i << " Presenting the value  " << endl;
   }

   // Clean up the semaphores
   std::cout << "All processes have completed." << std::endl;
   for (int i = 0; i < max_num_threads; ++i)
   {
      sem_destroy(&sem[i]);
   }
   // std::cout << "All processes have completed." << std::endl;
   for (int i = 0; i < num_processes; ++i)
   {
      sem_destroy(&process_sem[i]);
   }

   sem_destroy(&sem_all_threads_done); // Destroy this semaphore

   // std::cout << "All processes have completed." << std::endl;

   // Clean up
   for (int i = 0; i < num_processes; i++)
   {
      delete[] pipe[i];
      unlink(pipe[i]);
      // unlink(pipe_final[i]);
   }

   std::ostringstream oss;

   // Convert double values to string
   oss << new_main[0] << " " << new_main[1];

   cout << oss.str().c_str() << endl
        << endl;
   // Pass the string as an argument to the second program
   execlp("./q2", "./q2", oss.str().c_str(), (char *)NULL);

   return 0;
}
