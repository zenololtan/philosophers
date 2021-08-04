/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 15:03:09 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/03 21:36:25 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_args(t_data *data)
{
	printf("num_philo[%d], t_die[%ld], t_eat[%ld], t_sleep[%ld]", data->n_philos, data->t_die, data->t_eat, data->t_sleep);
	if (data->n_eat)
		printf(", num_eat[%d]", data->n_eat);
	printf("\n");
}

int		mutex_error(t_data *data)
{
	printf("SHIT\n");
	data->mutex_status = dead;
	return (1);
}

int		str_error(char *str)
{
	if (str)
	{
		write(1, "Error: ", 7);
		write(1, str, ft_strlen(str));
	}
	return (1);
}

void	*free_data(t_data *data, t_philo *philos)
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
		free(data->forks);
	}
	pthread_mutex_destroy(&data->m_status);
	pthread_mutex_destroy(&data->m_print);
	if (philos)
		free(philos);
	return (NULL);
}

int	clear_all(t_data *data, t_philo *philos, char *str)
{
	free_data(data, philos);
	if (str)
		str_error(str);
	return (1);
}
