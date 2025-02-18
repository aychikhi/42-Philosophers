/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:05:05 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/18 18:38:28 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(t_philosopher *philo, size_t n)
{
	size_t	end;

	end = get_current_time() + n;
	while (get_current_time() < end)
	{
		if (simulation_read(philo))
			break ;
		usleep(100);
	}
}

void	print_status(t_philosopher *philo, char *status)
{
	size_t	timestamps;

	if (!simulation_read(philo))
	{
		timestamps = get_current_time() - philo->data->start_time;
		printf("%zu %d %s\n", timestamps, philo->id, status);
	}
	if (!ft_strcmp(status, "died"))
		simulation_change(philo, 1);
}

void	check_death(t_philosopher *philo)
{
	int		i;
	size_t	time_diff;
	size_t	ctime;

	time_diff = 0;
	while (1337)
	{
		i = 0;
		while (philo->data->num_philo > i)
		{
			ctime = get_current_time();
			time_diff = ctime - last_meal_read(&philo[i]);
			if (time_diff > (size_t)philo->data->time_to_die)
			{
				if (!simulation_read(philo))
				{
					print_status(&philo[i], "died");
					break ;
				}
				return ;
			}
			i++;
		}
	}
	ft_usleep(philo, 10);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
	{
		sleep_philo(philo);
	}
	while (1337)
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_fork(philo);
		sleep_philo(philo);
		if (philo->data->must_eat_count != -1
			&& philo->meal_count >= philo->data->must_eat_count)
			break ;
		if (philo->data->stop_simulation)
			break ;
	}
	return (NULL);
}
