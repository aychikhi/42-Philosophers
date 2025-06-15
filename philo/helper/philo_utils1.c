/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:40:55 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/22 09:38:19 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	error_mess(void)
{
	ft_putendl_fd("Error: invalid arguments", 2);
}

void	clear_fun(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_num)
	{
		pthread_mutex_destroy(&philo[i].left_fork);
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->data->print_mutex);
	pthread_mutex_destroy(&philo->data->flag_mutex);
	pthread_mutex_destroy(&philo->data->simulation_mutex);
	free(philo->data);
	free(philo);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

size_t	read_last_meal_time(t_philo *philo)
{
	size_t	read;

	pthread_mutex_lock(&philo->last_meal_mutex);
	read = philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (read);
}

void	change_last_meal_time(t_philo *philo, size_t new_last_meal_time)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = new_last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}
