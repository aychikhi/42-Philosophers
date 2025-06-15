/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:14:38 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/18 12:52:32 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac > 6 || ac < 5)
		error_mess();
	check_args(av, ac);
	data = data_init(ac, av);
	if (!data)
		return (1);
	semaphore_init(data);
	start_process(data);
	clean_fun(data);
	return (0);
}
