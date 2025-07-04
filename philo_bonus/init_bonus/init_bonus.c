/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:35:02 by aychikhi          #+#    #+#             */
/*   Updated: 2025/07/02 13:53:16 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_data	*data_init(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat_count = -1;
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	data->pid = malloc(data->num_philo * sizeof(pid_t));
	if (!data->pid)
		return (free(data), NULL);
	return (data);
}

void	semaphore_init(t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/death");
	data->fork = sem_open("/fork", O_CREAT, 0644, data->num_philo);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->death = sem_open("/death", O_CREAT, 0644, 1);
	if (data->fork == SEM_FAILED || data->print == SEM_FAILED
		|| data->death == SEM_FAILED)
		exit(1);
}

void	start_process(t_data *data)
{
	int		i;
	t_philo	philo;

	i = -1;
	data->start_time = get_current_time();
	while (++i < data->num_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			philo.id = i + 1;
			philo.meal_count = 0;
			philo.data = data;
			philo.last_meal = get_current_time();
			philo_routine(&philo);
		}
		else if (data->pid[i] < 0)
			break ;
	}
	wait_processes(data);
}
