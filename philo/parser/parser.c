/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aychikhi <aychikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:20:08 by aychikhi          #+#    #+#             */
/*   Updated: 2025/05/20 15:11:25 by aychikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check(char *ptr)
{
	while (*ptr)
	{
		if (ft_isspace(*ptr))
			return (1);
		if ((*ptr == '+') && *(ptr + 1) && ft_isdigit(*(ptr + 1)))
			ptr++;
		if (ft_isdigit(*ptr))
		{
			while (ft_isdigit(*ptr))
				ptr++;
			if (*ptr == '+' || *ptr == '-')
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

int	check_max_int(char *str)
{
	if (ft_atoi(str) > 2147483647 || ft_atoi(str) < -2147483648)
		return (1);
	return (0);
}

int	check_args(char **av, int l)
{
	int	i;

	i = 0;
	while (i++ < l - 1)
	{
		if (!av[i][0] || ft_atoi(av[i]) == 0)
			return (1);
		if (is_empty(av[i]))
			return (1);
		if (check(av[i]))
			return (1);
		if (check_max_int(av[i]))
			return (1);
	}
	return (0);
}
