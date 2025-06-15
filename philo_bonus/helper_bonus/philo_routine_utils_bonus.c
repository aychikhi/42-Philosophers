/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:44:34 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/18 11:28:54 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	pick_up_forks(t_philo *philo)
{
	sem_wait(philo->data->fork);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->fork);
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	sem_wait(philo->data->death);
	philo->last_meal = get_current_time();
	print_status(philo, "is eating");
	philo->meal_count++;
	sem_post(philo->data->death);
	ft_usleep(philo->data->time_to_eat);
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
}

void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}
