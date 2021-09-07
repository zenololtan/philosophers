/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:38:22 by ztan          #+#    #+#                 */
/*   Updated: 2021/09/07 18:27:58 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int	valid(char *str)
{
	int val;
	
	if (!is_digits(str) || ft_strlen(str) > 10 || \
		(ft_strlen(str) > 1 && *str == '0'))
		return (0);
	val = ft_atoi(str);
	if (val < 0)
		return (0);
	return (1);
}

int	check_args(int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || (!valid(argv[1]) || !valid(argv[2])
			 || !valid(argv[3]) || !valid(argv[4])))
		return (1);
	if (argc == 6 && !valid(argv[5]))
		return (1);
	return (0);
}
