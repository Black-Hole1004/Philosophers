# Philosophers
This project is a simulation of the classic dining philosophers problem, where a group of philosophers sit around a table and alternate between thinking and eating. The problem involves preventing deadlocks and starvation. It was developed using C.

# Features
- Simulates the dining philosophers problem with multiple threads
- Implements the solution to prevent deadlocks and starvation
- Allows users to customize the number of philosophers and the time they spend thinking/eating
- Displays real-time information about the philosophers' actions
- Getting Started

# Prerequisites
- A C compiler (e.g. GCC)
- Make command installed

# Installation
- Clone the repository:
```git clone https://github.com/Black-Hole1004/philosophers.git```
-Navigate to the project directory:
```cd philosophers```
- Compile the program using the Makefile:
```make```  
- Run the program:

```./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]```  
# Usage
Once you have Philosophers up and running, you can use it to simulate the dining philosophers problem with different parameters. Here's an example command:  

```./philo 5 800 200 200 7```  
This will simulate the problem with 5 philosophers, a time-to-die of 800 milliseconds, a time-to-eat of 200 milliseconds, and a time-to-sleep of 200 milliseconds. Each philosopher must eat 7 times before the simulation ends.

# Contributing
Contributions are always welcome! If you'd like to contribute to Philosophers, please feel free to submit a pull request.  
