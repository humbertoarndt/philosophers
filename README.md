# Philosophers

## Table of contents
* [Function](#functions)
* [References](#references)

## Functions
| Function Name | Description | Lib | Mandatory |
| :--- | :--- | :---: | :---: |
| memset() |
| printf() |
| malloc() |
| free() |
| write() |
| usleep() |
| gettimeofday() |
| pthread_create() |
| pthread_detach() | Imediatelly detaches a thread when you don't want its return value, or don't need wait it to finish.
| pthread_join(pthread_t thread, void **retval) | Waits for the specified thread to terminate and obtains its return value.
| pthread_mutex_init() |
| pthread_mutex_destroy() |
| pthread_mutex_lock() |
| pthread_mutex_unlock() |
| fork() |
| kill() |
| exit() |
| waitpid() |
| sem_open() |
| sem_close() |
| sem_post() |
| sem_wait() |
| sem_unlink() |


## References:
* [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
* [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)
* [Unix Threads in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
* [Acelera — Philosophers](https://www.notion.so/Acelera-Philosophers-a82a52edabe24ea4a382393fae6c4531)
* [Difference between pthread_exit, pthread_join and pthread_detach](https://stackoverflow.com/questions/22427007/difference-between-pthread-exit-pthread-join-and-pthread-detach)
* [POSIX : Detached vs Joinable threads](https://thispointer.com/posix-detached-vs-joinable-threads-pthread_join-pthread_detach-examples/)