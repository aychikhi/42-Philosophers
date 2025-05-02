/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:34:06 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/02 12:55:54 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *status)
{
	size_t	current_time;

	sem_wait(philo->data->print);
	current_time = get_current_time() - philo->data->start_time;
	printf("%zu %d %s\n", current_time, philo->id, status);
	sem_post(philo->data->print);
}

void	ft_usleep(size_t n)
{
	size_t	end;

	end = get_current_time() + n;
	while (get_current_time() < end)
		usleep(100);
}

void	*check_death(void *arg)
{
	t_philo	*philo;
	size_t	current_time;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->death);
		current_time = get_current_time();
		if (current_time - philo->last_meal > (size_t)philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("%zu %d died\n", current_time - philo->data->start_time,
				philo->id);
			exit(1);
		}
		sem_post(philo->data->death);
		ft_usleep(1000);
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	death_thread;

	philo->last_meal = get_current_time();
	if (pthread_create(&death_thread, NULL, check_death, philo) != 0)
		exit(1);
	pthread_detach(death_thread);
	if (philo->id % 2 == 0)
		sleep_philo(philo);
	while (1)
	{
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		if (philo->data->must_eat_count != -1
			&& philo->meal_count >= philo->data->must_eat_count)
			exit(0);
		sleep_philo(philo);
		think(philo);
	}
}
