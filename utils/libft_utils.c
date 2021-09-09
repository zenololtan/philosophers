/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 11:20:31 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/07 18:14:31 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdint.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		int_min;
	char	c;

	int_min = -2147483648;
	c = n % 10 + '0';
	if (n == int_min)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		write(fd, &c, 1);
	}
	else if (n >= 0 && n <= 9)
		write(fd, &c, 1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n != 0 && (*s1 != '\0' || *s2 != '\0'))
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			return ((unsigned char)*s1 - (unsigned char)*s2);
		n--;
	}
	return (0);
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
