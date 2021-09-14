/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 22:16:13 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/14 22:58:11 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int			negative;
	intmax_t	n;

	n = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (!str)
		return (0);
	negative = (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		if (n >= 922337203685477580)
		{
			if (!negative)
				return (-1);
			return (0);
		}
		n = n * 10 + (*str - '0');
		str++;
	}
	if (negative)
		return (n * -1);
	return (n);
}
