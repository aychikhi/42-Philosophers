/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:46:31 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/21 15:45:39 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	change_last_meal_time(philo, get_current_time());
	philo->meal_count++;
	ft_usleep(philo, philo->data->time_to_eat);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo, philo->data->time_to_sleep);
}
