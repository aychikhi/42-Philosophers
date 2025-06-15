/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:20:29 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/21 15:21:40 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(t_philo *philo, size_t time_to_sleep)
{
	size_t	end;

	(void)philo;
	end = get_current_time() + time_to_sleep;
	while (get_current_time() < end)
	{
		if (read_simulation(philo))
			break ;
		usleep(200);
	}
}

void	print_status(t_philo *philo, char *status)
{
	size_t	timestamps;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!read_simulation(philo))
	{
		timestamps = get_current_time() - philo->data->start_time;
		printf("%zu %d %s\n", timestamps, philo->philo_id, status);
	}
	if (!ft_strcmp(status, "died"))
		change_simulation(philo, 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	check_death(t_philo *philo)
{
	int		i;
	size_t	time_diff;
	size_t	current_time;

	time_diff = 0;
	while (07)
	{
		i = -1;
		while (philo->data->philo_num > ++i)
		{
			if (read_flag(philo))
				return ;
			current_time = get_current_time();
			time_diff = current_time - read_last_meal_time(&philo[i]);
			if (time_diff > (size_t)philo->data->time_to_die)
			{
				print_status(&philo[i], "died");
				return ;
			}
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		sleep_philo(philo);
	while (!read_simulation(philo))
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
		if (philo->data->must_eat_num != -1
			&& philo->meal_count >= philo->data->must_eat_num)
		{
			change_flag(philo, 1);
			break ;
		}
	}
	return (NULL);
}
