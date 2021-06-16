/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:14:12 by ztan          #+#    #+#                 */
/*   Updated: 2021/06/16 16:38:13 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_args(t_data *data)
{
	printf("num_philo[%d], t_die[%d], t_eat[%d], t_sleep[%d]\n", data->n_philo, data->time_die, data->time_eat, data->time_sleep);
}

int	str_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

int		clear_all(t_data *data, char *str)
{
	if (data)
		free(data);
	if (str)
		str_error(str);
	return (1);
}

int	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid(char *str)
{
	if (str[0] == '-' && is_digits(str + 1))
		return (1);
	if (is_digits(str))
		return (1);
	return(0);
}

t_data	*get_args(char **argv)
{
	t_data	*data;
	
	if (!valid(argv[1]) || !valid(argv[2])
		 || !valid(argv[3]) || !valid(argv[4]))
		return (NULL);
	data = (t_data*)malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->n_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = NULL;
	if (argc != 5)
		return (str_error("Error: incorrect arguments\n"));
	if (!(data = get_args(argv)))
		return (str_error("Error: incorrect arguments\n"));
	print_args(data);
	return (0);
}
