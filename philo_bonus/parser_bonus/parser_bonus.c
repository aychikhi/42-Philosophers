/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:02:48 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/18 11:28:47 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return ;
		i++;
	}
	error_mess();
}

void	check(char *ptr)
{
	while (*ptr)
	{
		if (ft_isspace(*ptr))
			error_mess();
		if ((*ptr == '+') && *(ptr + 1) && ft_isdigit(*(ptr
					+ 1)))
			ptr++;
		if (ft_isdigit(*ptr))
		{
			while (ft_isdigit(*ptr))
				ptr++;
			if (*ptr == '+' || *ptr == '-')
				error_mess();
		}
		else
			error_mess();
	}
}

void	check_max_int(char *str)
{
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) < -2147483648)
		error_mess();
}

void	check_args(char **av, int l)
{
	int	i;

	i = 0;
	if (ft_atoi(av[1]) > 200)
		error_mess();
	while (i++ < l - 1)
	{
		if (!av[i][0] || ft_atoi(av[i]) == 0)
			error_mess();
		is_empty(av[i]);
		check(av[i]);
		check_max_int(av[i]);
	}
}
