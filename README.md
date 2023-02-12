# Philosophers

Philosophers is a project to teach the basics of threading processes, as how to create threads and mutexes.

## Introduction

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present form. [Read more](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

## General Description

The project requires us to create an algorithm that keeps the philosophers alive as far as possible given the following parameters:
 * `number_of_philosophers`: The number of philosophers, and consecutively the number of forks to be used.
 * `time_to_die`: How long, in milliseconds, a philosopher has to live after a meal. If a philosopher hasn't started eating `time_to_die` after the beginning of his last meal or the beginning of the simulation, he will die.
 * `time_to_eat`: How long, in milliseconds, a philosopher takes to eat his meal. During that time the philosopher keeps his two forks in hand.
 * `time_to_sleep` : How long, in milliseconds, the philosopher spends sleeping.
 * `number_of_times_each_philosopher_must_eat` (Optional argument): When this condition is reached the program ends. If not specified, the simulation stops when a philosopher dies.

Any state change of a philosopher must formatted as follows int the terminal:

```sh
[timestamp_in_ms] [X] has taken a fork
[timestamp_in_ms] [X] is eating
[timestamp_in_ms] [X] is sleeping
[timestamp_in_ms] [X] is thinking
[timestamp_in_ms] [X] died
```

## Usage

Git clone the project and move into its directory.

```sh
git clone https://github.com/humbertoarndt/philosophers.git
cd philosophers
```

Compile the program using `make`

```sh
make
```

Run the program withthe following arguments:

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```

If the arguments are valid, the status change log will be printed on the terminal until one of the stop conditions are meet.

To count how many time a Philosophers does an action use:

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat] | grep <id_and_status> | ec -l
``` 

## References:
* [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
* [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)
* [Unix Threads in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
* [Acelera — Philosophers](https://www.notion.so/Acelera-Philosophers-a82a52edabe24ea4a382393fae6c4531)
* [Difference between pthread_exit, pthread_join and pthread_detach](https://stackoverflow.com/questions/22427007/difference-between-pthread-exit-pthread-join-and-pthread-detach)
* [POSIX : Detached vs Joinable threads](https://thispointer.com/posix-detached-vs-joinable-threads-pthread_join-pthread_detach-examples/)