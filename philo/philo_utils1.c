/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:35:14 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/01 16:45:23 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	error_mess(void)
{
	ft_putendl_fd("Error: invalid arguments", 2);
	exit(1);
}

void	flag_change(t_philosopher *philo, int flag1)
{
	pthread_mutex_lock(&philo->data->mutex);
	philo->data->flag = flag1;
	pthread_mutex_unlock(&philo->data->mutex);
}

int	flag_read(t_philosopher *philo)
{
	int	flag1;

	pthread_mutex_lock(&philo->data->mutex);
	flag1 = philo->data->flag;
	pthread_mutex_unlock(&philo->data->mutex);
	return (flag1);
}
