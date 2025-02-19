/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:26:14 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/19 11:35:40 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	just_one(t_philosopher *philo)
{
	printf("0 1 is thinking\n");
	printf("0 1 has taken a fork\n");
	ft_usleep(philo, philo->data->time_to_die);
	printf("%d 1 died\n", philo->data->time_to_die);
	free(philo->data);
	exit(0);
}

void	simulation_change(t_philosopher *philo, int simulation)
{
	pthread_mutex_lock(&philo->data->stop_mutex);
	philo->data->stop_simulation = simulation;
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

int	simulation_read(t_philosopher *philo)
{
	int	simulation;

	pthread_mutex_lock(&philo->data->stop_mutex);
	simulation = philo->data->stop_simulation;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (simulation);
}

void	last_meal_change(t_philosopher *philo, size_t last_meal)
{
	(void)last_meal;
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
}

size_t	last_meal_read(t_philosopher *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(&philo->meal_time_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_time_mutex);
	return (last_meal);
}
