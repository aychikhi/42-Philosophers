/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:20:49 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/11 20:23:21 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	think(t_philosopher *philo)
{
	print_status(philo, "is thinking");
}

void	pick_up_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	eat(t_philosopher *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	philo->meal_count++;
	usleep(philo->data->time_to_eat * 1000);
}

void	put_down_fork(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	sleep_philo(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}
