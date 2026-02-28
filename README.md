# 🍝 Philosophers - 42 Project 🍝

This project has been created as part of the 42 curriculum by [tu_login].
## 📝 Description

This project is a simulation based on the classic Dining Philosophers problem. It explores the fundamentals of concurrent programming, specifically how to create and manage threads, and how to use mutexes to protect shared resources and avoid data races.

The goal is to keep a set of philosophers alive by ensuring they can eat, sleep, and think without dying from starvation or causing a deadlock.
## ⚙️ Instructions
## 🛠️ Compilation

The project must be compiled with the flags -Wall -Wextra -Werror. To compile the mandatory part, navigate to the philo/ directory and run:
Bash

make

## 🚀 Execution

Run the program with the following arguments in order:
Bash

    ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

## 📌 Variables Explained

  * 👥 number_of_philosophers: The total number of philosophers and also the number of forks.

  * ⌛ time_to_die (ms): If a philosopher doesn't start eating time_to_die milliseconds after starting their last meal (or the start of the simulation), they die.
  * 🍝 time_to_eat (ms): The time it takes for a philosopher to eat. During this time, they must hold two forks.

  * 💤 time_to_sleep (ms): The time a philosopher spends sleeping.

  * 🔢 number_of_times_each_philosopher_must_eat (optional): If all philosophers have eaten at least this many times, the simulation stops.

## 💡 Example
Bash

./philo 5 800 200 200

    Note: In this case, there are 5 philosophers. They will die if they don't eat for 800ms. Each eating and sleeping action lasts 200ms.

## 📚 Resources

The implementation relies on the POSIX threads library (pthread) and authorized standard C functions:

  * pthread_create, pthread_join, pthread_mutex_init, pthread_mutex_lock, etc.

  * gettimeofday and usleep for high-precision time management.

## 🤖 AI Usage Disclosure

As per the requirements in Chapter VII of the 42 subject, here is the description of AI usage in this project:

  * <u>Code Formatting</u>: Assistance in ensuring Norminette compliance for variable alignments and function structures.

  * <u>Debugging</u>: Identifying potential data races and memory leaks during the development of thread synchronization.

  * <u>Makefile Generation</u>: Structuring the build system to handle subdirectories and prevent relinking.

  * <u>Documentation</u>: Drafting the required README file in English as per the subject's requirements.

## ⚠️ Important Rules

  * 🚫 No Global Variables: All shared data is passed via structures to avoid forbidden globals.

  * 🔒 Thread Safety: Each fork is protected by a mutex to prevent duplication.

  * ⏱️ Precision: The system monitor ensures death is reported within 10ms of the actual event.

  * 🧹 Clean Exit: All memory allocated on the heap is properly freed, and all mutexes are destroyed before the program exits.
