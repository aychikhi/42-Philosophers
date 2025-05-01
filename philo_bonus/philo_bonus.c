/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:14:38 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/01 12:25:16 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

// Name of our semaphore
#define SEM_NAME "/forks_semaphore"

void philosopher(int id, sem_t *forks_sem, int num_forks)
{
    printf("Philosopher %d is thinking\n", id);
    sleep(1);
    
    printf("Philosopher %d is hungry and wants to eat\n", id);
    
    // Try to take 2 forks
    printf("Philosopher %d is waiting for forks\n", id);
    sem_wait(forks_sem);  // Take first fork
    sem_wait(forks_sem);  // Take second fork
    
    printf("Philosopher %d took 2 forks and is eating\n", id);
    sleep(2);
    printf("Philosopher %d finished eating\n", id);
    
    // Return the forks
    sem_post(forks_sem);  // Return first fork
    sem_post(forks_sem);  // Return second fork
    
    printf("Philosopher %d returned the forks and is thinking again\n", id);
}

int main()
{
    int num_philosophers = 5;
    int i;
    pid_t pid;
    
    // Create semaphore with value = number of forks
    sem_t *forks_sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, num_philosophers);
    if (forks_sem == SEM_FAILED)
    {
        perror("sem_open failed");
        // If semaphore already exists, unlink it and try again
        sem_unlink(SEM_NAME);
        forks_sem = sem_open(SEM_NAME, O_CREAT, 0644, num_philosophers);
        if (forks_sem == SEM_FAILED)
        {
            perror("sem_open failed again");
            exit(1);
        }
    }
    
    // Create philosopher processes
    for (i = 1; i <= num_philosophers; i++)
    {
        pid = fork();
        
        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process (philosopher)
            philosopher(i, forks_sem, num_philosophers);
            exit(0);
        }
    }
    
    // Wait for all philosophers to finish
    for (i = 0; i < num_philosophers; i++)
    {
        wait(NULL);
    }
    
    // Clean up semaphore
    sem_close(forks_sem);
    sem_unlink(SEM_NAME);
    
    return 0;
}

