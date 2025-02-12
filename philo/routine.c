/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:05:05 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/11 20:23:01 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philosopher *philo, char *status)
{
	long	timestamps;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!philo->data->stop_simulation)
	{
		timestamps = get_current_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamps, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	check_death(t_philosopher *philo)
{
	int		i;
	long	current_time;
	long	time_diff;

	i = 0;
	while (!philo->data->stop_simulation)
	{
		while (i < philo->data->num_philo)
		{
			pthread_mutex_lock(&philo[i].meal_time_mutex);
			current_time = get_current_time();
			time_diff = current_time - philo[i].last_meal_time;
			if (time_diff > philo->data->time_to_die)
			{
				pthread_mutex_lock(&philo->data->stop_mutex);
				if (!philo->data->stop_simulation)
				{
					print_status(&philo[i], "died");
					philo->data->stop_simulation = 1;
				}
				pthread_mutex_unlock(&philo->data->stop_mutex);
				pthread_mutex_unlock(&philo[i].meal_time_mutex);
				return;
			}
			pthread_mutex_unlock(&philo[i].meal_time_mutex);
			i++;
		}
		usleep(100);
	}
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!philo->data->stop_simulation)
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_fork(philo);
		sleep_philo(philo);
		if (philo->data->must_eat_count != -1 && philo->meal_count >= philo->data->must_eat_count)
		{
			pthread_mutex_lock(&philo->data->stop_mutex);
            philo->data->stop_simulation = 1;
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break;	
		}
	}
	return (NULL);
}
