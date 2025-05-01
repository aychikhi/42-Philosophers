/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:31:52 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/01 17:20:50 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_count;
	size_t	start_time;
	sem_t	*fork;
	sem_t	*print;
	sem_t	*death;
	pid_t	*pid;
}			t_data;

typedef struct s_philo
{
	int		id;
	int		meal_count;
	size_t	last_meal;
	t_data	*data;
}			t_philo;

void	error_mess(void);
void	check(char *ptr);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_atoi(char *str);
void	is_empty(char *str);
void	check_max_int(char *str);
void	check_args(char **av, int l);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
t_data	*data_init(int ac, char **av);
void	ft_putendl_fd(char *s, int fd);

#endif