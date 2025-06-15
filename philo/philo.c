/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:52 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/22 09:35:44 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	*data;

	if (ac < 5 || ac > 6 || check_args(av, ac))
		return (error_mess(), 1);
	data = data_init(ac, av);
	if (!data)
		return (1);
	philo = malloc(data->philo_num * sizeof(t_philo));
	if (!philo)
		return (free(data), 1);
	philo_init(philo, data);
	thread_create(philo);
	clear_fun(philo);
	return (0);
}
