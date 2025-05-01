/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:45:27 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/01 13:20:13 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_fun(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philo)
	{
		pthread_mutex_destroy(&philo[i].left_fork);
		pthread_mutex_destroy(&philo[i].meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->data->print_mutex);
	pthread_mutex_destroy(&philo->data->mutex);
	pthread_mutex_destroy(&philo->data->stop_mutex);
	free(philo->data);
	free(philo);
}

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
	data->start_time = get_current_time();
	data->stop_simulation = 0;
	data->flag = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	return (data);
}

void	philo_init(t_philosopher *philo, t_data *data)
{
	int	i;

	i = 0;
	while (data->num_philo > i)
	{
		philo[i].id = i + 1;
		philo[i].meal_count = 0;
		philo[i].data = data;
		philo[i].last_meal_time = get_current_time();
		pthread_mutex_init(&philo[i].left_fork, NULL);
		pthread_mutex_init(&philo[i].meal_time_mutex, NULL);
		if (i == data->num_philo - 1)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
		i++;
	}
}

void	create_threads(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philo)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	check_death(philo);
	i = 0;
	while (i < philo->data->num_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			break ;
		i++;
	}
	i = 0;
	while (i < philo->data->num_philo)
	{
		pthread_detach(philo[i].thread);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philosopher	*philo;
	t_data			*data;

	if (ac < 5 || ac > 6)
		error_mess();
	check_args(av, ac);
	data = data_init(ac, av);
	philo = malloc(sizeof(t_philosopher) * data->num_philo);
	if (!philo)
		return (free(data), 1);
	philo_init(philo, data);
	if (data->num_philo == 1)
		just_one(philo);
	else
		create_threads(philo);
	free_fun(philo);
	return (0);
}
