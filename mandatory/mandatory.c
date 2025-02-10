/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:45:27 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/09 20:04:10 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_fun(t_data **data)
{
	free((*data)->fork);
	free(*data);
}

t_data	*data_init(char **av)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->num_philo = ft_atoi(av[1]);
	data->fork = (pthread_mutex_t *)malloc(data->num_philo
			* sizeof(pthread_mutex_t));
	if (!data->fork)
		return (0);
	pthread_mutex_init(&data->print_mutex, NULL);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return (data);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_init(t_philosopher *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo->id = i + 1;
		philo->left_fork = i;
		philo->right_fork = (i + 1) % data->num_philo;
		philo->last_meal_time = get_current_time();
		philo->meal_count = 0;
		philo->data = data;
		pthread_create(&philo[i].thread, NULL, philosopher_routine, &philo[i]);
	}
}

int	main(int ac, char **av)
{
	t_philosopher	philo;
	t_data			*data;

	if (ac < 5 || ac > 6)
		error_mess();
	check_args(av, ac);
	data = data_init(av);
	philo_init(&philo, data);
	free_fun(&data);
	return (0);
}
