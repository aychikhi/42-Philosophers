/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:56:13 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/22 09:39:08 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	*data_init(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start_time = get_current_time();
	data->simulation_flag = 0;
	data->flag = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->flag_mutex, NULL);
	pthread_mutex_init(&data->simulation_mutex, NULL);
	if (ac == 6)
		data->must_eat_num = ft_atoi(av[5]);
	else
		data->must_eat_num = -1;
	return (data);
}

void	philo_init(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		philo[i].philo_id = i + 1;
		philo[i].meal_count = 0;
		philo[i].data = data;
		philo[i].last_meal_time = get_current_time();
		pthread_mutex_init(&philo[i].left_fork, NULL);
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		if (i == data->philo_num - 1)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
	}
}

void	thread_create(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->philo_num)
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
	check_death(philo);
	if (philo->data->philo_num > 1)
	{
		i = -1;
		while (++i < philo->data->philo_num)
			if (pthread_join(philo[i].thread, NULL))
				break ;
	}
	i = -1;
	while (++i < philo->data->philo_num)
		pthread_detach(philo[i].thread);
}
