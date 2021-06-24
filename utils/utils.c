/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 15:03:09 by ztan          #+#    #+#                 */
/*   Updated: 2021/06/24 15:45:50 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_args(t_data *data)
{
	printf("num_philo[%d], t_die[%d], t_eat[%d], t_sleep[%d]\n", data->n_philos, data->t_die, data->t_eat, data->t_sleep);
}

int	str_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

int	clear_all(t_data *data, char *str)
{
	if (data)
		free(data);
	if (str)
		str_error(str);
	return (1);
}