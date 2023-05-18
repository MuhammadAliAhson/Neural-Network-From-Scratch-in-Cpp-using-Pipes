## Neural Network Code

The provided code is an implementation of a neural network. It consists of multiple processes and threads working together to perform the calculations. Below is a step-by-step guide explaining the code functionality:




<img width="960" alt="Neural1" src="https://github.com/MuhammadAliAhson/Neural-Network-From-Scratch-in-Cpp-using-Pipes/assets/105967134/8f94044b-06f6-4b87-bf4d-b946bdfd8124">
<img width="960" alt="Neural2" src="https://github.com/MuhammadAliAhson/Neural-Network-From-Scratch-in-Cpp-using-Pipes/assets/105967134/9f190e04-09e5-4635-8c95-40942e722de8">
<img width="960" alt="Neural3" src="https://github.com/MuhammadAliAhson/Neural-Network-From-Scratch-in-Cpp-using-Pipes/assets/105967134/e70a3a9f-a4c1-4aff-88ca-c08f53fac6a1">
<img width="960" alt="Neural4" src="https://github.com/MuhammadAliAhson/Neural-Network-From-Scratch-in-Cpp-using-Pipes/assets/105967134/eba86c42-92dc-4efe-871e-800ab38de612">






1. Include the necessary libraries:
```cpp
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
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
```

2. Define constants and variables:
```cpp
const int num_processes = 7;
const int max_num_threads = 8;
double input[] = {0.1, 0.2};
// Neural network weights
double input_weight_1[][8] = { ... };
double hidden_layer_1_weights[][8] = { ... };
double hidden_layer_2_weights[][8] = { ... };
double hidden_layer_3_weights[][8] = { ... };
double hidden_layer_4_weights[][8] = { ... };
double hidden_layer_5_weights[][8] = { ... };
double output_layer[] = { ... };
double output_1[8] = { ... };
double result[8] = { ... };
double final = 0.0;
double next_input[2] = { ... };

sem_t sem[max_num_threads];
sem_t sem_all_threads_done;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t process_sem[num_processes];
sem_t sem_all_process_done;

struct thread_arg {
    int thread_id;
    int process_id;
};
```

3. Define a helper function to perform the neural network calculations:
```cpp
void *thread_process(void *arg) {
    struct thread_arg *ta = (struct thread_arg *)arg;

    sem_wait(&sem[ta->thread_id - 1]);

    // Perform calculations based on the process and thread ID
    // Update the result array with the calculated values

    sem_post(&sem[ta->thread_id % max_num_threads]);
    sem_post(&sem_all_threads_done);

    return nullptr;
}
```

4. Define a function to process a specific layer of the neural network:
```cpp
void process(int id, int num_threads) {
    pthread_t threads[max_num_threads];
    struct thread_arg args[max_num_threads];

    // Launch the threads
    for (int i = 0; i < num_threads; ++i) {
        args[i].thread_id = i + 1;
        args[i].process_id = id;
        pthread_create(&threads[i], nullptr, thread_process, (void *)&args[i]);
    }

    // Wait for all the threads to finish without using pthread_join()
    for (int i = 0; i < num_threads; ++i) {
        sem_wait(&sem_all_threads_done);
    }

    // Print the process ID and the calculated result
    std::cout << "Process " << id << " calculated result: " << result[0] << std::endl;
}
```

5. Define a helper function to calculate the values for the next input:
```cpp
void final_next(double x) {
    // Perform calculations to get the values for the next input
    next_input[0] = value_1;
    next_input[1] = value_2;
    cout << endl;
    cout << "Values for next input are  " << next_input[0] << " and  " << next_input[1] << endl;
}
```

6. Implement the main function

```cpp
int main() {
    // Initialize the semaphores
    for (int i = 0; i < max_num_threads; ++i) {
        sem_init(&sem[i], 0, 0);
    }
    sem_init(&sem_all_threads_done, 0, 0);

    for (int i = 0; i < num_processes; ++i) {
        sem_init(&process_sem[i], 0, 0);
    }
    sem_init(&sem_all_process_done, 0, 0);

    // Create child processes
    pid_t pid;
    for (int i = 0; i < num_processes; ++i) {
        pid = fork();
        if (pid < 0) {
            cout << "Fork error!" << endl;
            return 1;
        } else if (pid == 0) {
            // Child process
            process(i);
            sem_post(&sem_all_process_done);
            return 0;
        }
    }

    // Parent process
    // Wait for all child processes to finish
    for (int i = 0; i < num_processes; ++i) {
        sem_wait(&sem_all_process_done);
    }

    // Calculate values for the next input
    final_next(final);

    // Close the semaphores
    sem_destroy(&sem_all_threads_done);
    for (int i = 0; i < max_num_threads; ++i) {
        sem_destroy(&sem[i]);
    }
    for (int i = 0; i < num_processes; ++i) {
        sem_destroy(&process_sem[i]);
    }
    sem_destroy(&sem_all_process_done);

    return 0;
}
```

 

7. Use helper function to calculate the values for the next input:
```cpp
void final_next(double x) {
    // Perform calculations to get the values for the next input
    next_input[0] = value_1;
    next_input[1] = value_2;
    cout << endl;
    cout << "Values for next input are  " << next_input[0] << " and  " << next_input[1] << endl;
}
```


8. Pass the updated values of the output to the next cpp file whose comiplationed file is named ./q2 using:

# You can change the ./q2 to whatever you like to just named it exactly the compiled file you make

## For Example
```bash
 g++ -pthread forward_backward_propagation_1.cpp -o q1
  g++ -pthread forward_propagation_2.cpp -o q2
  
  # in the End you need to run the q1 

./q1

# this will also exexcute your q2 file.
```

## For Sending Values to the next file forward_propagation_2.cpp

```cpp
 execlp("./q2", "./q2", oss.str().c_str(), (char *)NULL);
```



9. Recieve the data in the argumentd of the main of the next file and put it into another array

```cpp
int main(int argc, char *argv[])
{
   std::istringstream iss(argv[1]);

   // Parse the string back into double values
   iss >> input[0] >> input[1];

   std::cout << "Values: " << input[0] << ", " << input[1] << '\n';
```



