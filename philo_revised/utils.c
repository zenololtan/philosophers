/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 22:01:22 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/14 23:59:13 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_err(t_philo *philo)
{
	philo->data->mutex_status = DEAD;
	return (str_error(MUTEX_ERR));
}

int	str_error(char *str)
{
	if (str)
		printf("ERROR: %s", str);
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
	int	i;

	i = 0;
	if (data->mutex_status == ALIVE)
	{
		while (i > data->n_philos)
		{
			if (data->forks)
				pthread_mutex_destroy(&data->forks[i]);
			if (philos)
				pthread_mutex_destroy(&philos[i].p_status);
			i++;
		}
		pthread_mutex_destroy(&data->m_print);
	}
	free_data(data, philos);
	if (str)
		str_error(str);
	return (1);
}
