/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 15:03:09 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/07 17:57:46 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	mutex_error(t_data *data)
{
	data->mutex_status = dead;
	return (1);
}

int	str_error(char *str)
{
	if (str)
	{
		write(1, "Error: ", 7);
		write(1, str, ft_strlen(str));
	}
	return (1);
}

void	*str_error_null(char *str)
{
	if (str)
	{
		write(1, "Error: ", 7);
		write(1, str, ft_strlen(str));
	}
	return (NULL);
}

int	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i > data->n_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->m_status);
	pthread_mutex_destroy(&data->m_print);
	return (1);
}

void	*free_data(t_data *data, t_philo *philos)
{
	if (data->forks)
		free(data->forks);
	if (philos)
		free(philos);
	return (NULL);
}

int	clear_all(t_data *data, t_philo *philos, char *str)
{
	if (data->mutex_status == alive)
		destroy_mutexes(data);
	free_data(data, philos);
	if (str)
		str_error(str);
	return (1);
}
