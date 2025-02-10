/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:45:43 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/09 20:54:45 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die; // time before a philosopher dies
	int				time_to_eat; // time it takes to eat
	int				time_to_sleep; // time it takes to sleep
	int				must_eat_count; // Number of times each philosopher must eat
	long			start_time; // Start time of the simulation
	pthread_mutex_t	*fork; // Array of mutexes for forks
	pthread_mutex_t	print_mutex; // Mutex for printing logs
	int				stop_simulation; // Flag to stop the simulation
}					t_data;

typedef struct s_philosopher
{
	int			id; //philosopher id 
	int			left_fork;
	int			right_fork;
	long		last_meal_time; //timestamps of the last meal
	int			meal_count; //num of meals eaten
	pthread_t	thread; // thread for philosopher
	t_data		*data;
}					t_philosopher;

void	error_mess(void);
void	check(char *ptr);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(char *str);
void	is_empty(char *str);
t_data	*data_init(char **av);
long	get_current_time(void);
void	check_max_int(char *str);
void	check_args(char **av, int l);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*philosopher_routine(void *arg);
void	philo_init(t_philosopher *philo, t_data *data);

#endif