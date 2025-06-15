/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:05:24 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/22 09:37:12 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_num;
	int				flag;
	int				simulation_flag;
	size_t			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	simulation_mutex;
}			t_data;

typedef struct s_philo
{
	int				philo_id;
	int				meal_count;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	size_t			last_meal_time;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		thread;
	t_data			*data;
}			t_philo;

void	error_mess(void);
int		check(char *ptr);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(char *str);
void	eat(t_philo *philo);
int		is_empty(char *str);
void	think(t_philo *philo);
size_t	get_current_time(void);
int		check_max_int(char *str);
void	*philo_routine(void *arg);
void	clear_fun(t_philo *philo);
int		read_flag(t_philo *philo);
void	check_death(t_philo *philo);
void	sleep_philo(t_philo *philo);
int		check_args(char **av, int l);
t_data	*data_init(int ac, char **av);
void	pick_up_forks(t_philo *philo);
void	thread_create(t_philo *philo);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	put_down_forks(t_philo *philo);
void	ft_putendl_fd(char *s, int fd);
int		read_simulation(t_philo *philo);
size_t	read_last_meal_time(t_philo *philo);
void	change_flag(t_philo *philo, int new_flag);
int		ft_strcmp(const char *s1, const char *s2);
void	print_status(t_philo *philo, char *status);
void	philo_init(t_philo	*philo, t_data	*data);
void	ft_usleep(t_philo *philo, size_t time_to_sleep);
void	change_simulation(t_philo *philo, int new_simulation);
void	change_last_meal_time(t_philo *philo, size_t new_last_meal_time);

#endif