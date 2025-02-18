/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:05:05 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/18 13:49:08 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philosopher *philo, char *status)
{
	long	timestamps;
	// pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_read(philo))
	{
		timestamps = get_current_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamps, philo->id, status);
	}
	if (!ft_strcmp(status, "died"))
		simulation_change(philo, 1);
	// pthread_mutex_unlock(&philo->data->print_mutex);
}
void simulation_change(t_philosopher *philo, int simulation)
{
	pthread_mutex_lock(&philo->data->stop_mutex);
	philo->data->stop_simulation = simulation;
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

int simulation_read(t_philosopher *philo)
{
	int simulation;

	pthread_mutex_lock(&philo->data->stop_mutex);
	simulation = philo->data->stop_simulation;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (simulation);
}

void last_meal_change(t_philosopher *philo, int last_meal)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = last_meal;
	pthread_mutex_unlock(&philo->meal_time_mutex);
}

int last_meal_read(t_philosopher *philo)
{
	int last_meal;

	pthread_mutex_lock(&philo->meal_time_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	return (last_meal);
}

void	check_death(t_philosopher *philo)
{
	int		i;
	long	time_diff;

	i = 0;
	time_diff = 0;
	while (1337)
	{
		i = 0;
		while (philo->data->num_philo > i)
		{
			time_diff = get_current_time() - last_meal_read(&philo[i]);
			// printf("time diff = %ld\n",time_diff);
			// printf("time to die = %d\n",philo->data->time_to_die);
			// printf("last meal = %ld\n",philo[i].last_meal_time);
			if (time_diff > philo->data->time_to_die)
			{
				if (!simulation_read(philo))
				{		
					// printf("philo = %d\n", philo->id);
					// printf("i = %d\n", i);
					print_status(&philo[i], "died");
					// printf("philo here1 = %d\n", philo->id);
					break;
				}
				return;
			}
			i++;
		}
	}
	usleep(100);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	// if (philo->id % 2 == 0)
	// {
	// 	usleep(10000);
	// }
	while (1337)
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_fork(philo);
		sleep_philo(philo);
		if (philo->data->must_eat_count != -1 && philo->meal_count >= philo->data->must_eat_count)
			break;
		if (philo->data->stop_simulation)
			break;
	}
	return (NULL);
}
