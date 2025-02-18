/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:20:49 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/18 18:25:13 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	think(t_philosopher *philo)
{
	print_status(philo, "is thinking");
}

void	pick_up_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	eat(t_philosopher *philo)
{
	print_status(philo, "is eating");
	last_meal_change(philo, get_current_time());
	philo->meal_count++;
	ft_usleep(philo, philo->data->time_to_eat);
}

void	put_down_fork(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	sleep_philo(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo, philo->data->time_to_sleep);
}
