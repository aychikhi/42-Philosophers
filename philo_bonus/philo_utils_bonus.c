/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:56:40 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/02 12:58:18 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_mess(void)
{
	ft_putendl_fd("Error: invalid arguments", 2);
	exit(1);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	clean_fun(t_data *data)
{
	sem_close(data->fork);
	sem_close(data->print);
	sem_close(data->death);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/death");
	free(data->pid);
	free(data);
}

void	kill_processes(t_data *data)
{
	int	i;

	i = 0;
	while (data->num_philo > i)
	{
		kill(data->pid[i], SIGTERM);
		i++;
	}
}

void	wait_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (data->num_philo > i)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			kill_processes(data);
			break ;
		}
		i++;
	}
}
