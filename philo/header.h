/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:45:43 by aychikhi          #+#    #+#             */
/*   Updated: 2025/02/18 13:49:19 by aychikhi         ###   ########.fr       */
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
	int						num_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat_count;
	size_t					start_time;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			mutex;
	int						stop_simulation;
	pthread_mutex_t			stop_mutex;
}					t_data;

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	size_t			last_meal_time;
	pthread_mutex_t	meal_time_mutex;
	int				meal_count;
	pthread_t		thread;
	t_data			*data;
}					t_philosopher;

void last_meal_change(t_philosopher *philo, int last_meal);
int last_meal_read(t_philosopher *philo);
void	error_mess(void);
void	check(char *ptr);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(char *str);
void	is_empty(char *str);
void	just_one(t_data *data);
size_t	get_current_time(void);
void	*philo_routine(void *arg);
void	check_max_int(char *str);
void	eat(t_philosopher *philo);
void	think(t_philosopher *philo);
void	check_args(char **av, int l);
t_data	*data_init(int ac, char **av);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	free_fun(t_philosopher *philo);
void	ft_putendl_fd(char *s, int fd);
void	sleep_philo(t_philosopher *philo);
void	check_death(t_philosopher *philo);
void	put_down_fork(t_philosopher *philo);
void	pick_up_forks(t_philosopher *philo);
void	create_threads(t_philosopher *philo);
int		simulation_read(t_philosopher *philo);
int		ft_strcmp(const char *s1, const char *s2);
void	philo_init(t_philosopher *philo, t_data *data);
void	print_status(t_philosopher *philo, char *status);
void	simulation_change(t_philosopher *philo, int simulation);

#endif