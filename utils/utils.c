/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 15:03:09 by ztan          #+#    #+#                 */
/*   Updated: 2021/07/26 23:50:48 by zenotan       ########   odam.nl         */
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

void	free_array(pthread_mutex_t **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	*free_data(t_data *data)
{
	if (data->forks)
		free_array(data->forks);
	free(data);
	return (NULL);
}

void	*free_philos(t_philo **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
	return (NULL);
}

int	clear_all(t_data *data, char *str)
{
	if (data)
		free_data(data);
	if (str)
		str_error(str);
	return (1);
}
