/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:14:38 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/01 17:17:43 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_mess(void)
{
	ft_putendl_fd("Error: invalid arguments", 2);
	exit(1);
}

t_data	*data_init(int ac, char **av)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat_count = -1;
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	data->pid = malloc (data->num_philo * sizeof(pid_t));
	if (!data->pid)
		return(free(data), NULL);
	return(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac > 6 || ac < 5)
		error_mess();
	check_args(av, ac);
	data = data_init(ac, av);
}
