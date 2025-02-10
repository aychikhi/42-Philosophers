/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:05:05 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/09 20:54:32 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = philo->data;
	while (!data->stop_simulation)
	{
		print_status(philo, "is thinking");
		pthread_mutex_lock(&data->fork[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&data->fork[philo->left_fork]);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal_time = get_current_time();
		usleep(data->time_to_eat * 1000);
		philo->meal_count++;
		print_status(philo, "is sleeping");
		usleep(data->time_to_sleep * 1000);
	}
	return NULL;
}
