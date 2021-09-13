/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_funcs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 20:16:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/09/13 13:55:25 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	init_philo_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	if (gettimeofday(&data->start_time, NULL))
		return (str_error(STRUCT_ERR));
	while (i < data->n_philos && data->n_eat != 0)
	{
		philos[i].last_diner = data->start_time;
		if (pthread_create(&philos[i].ptid, NULL, &philo, &philos[i]))
			return (str_error(THREAD_ERR));
		if (pthread_create(&philos[i].ctid, NULL, &checker, &philos[i]))
			return (str_error(THREAD_ERR));
		i++;
	}
	i = 0;
	while (i < data->n_philos && data->n_eat != 0)
	{
		pthread_join(philos[i].ptid, NULL);
		usleep(100);
		pthread_join(philos[i].ctid, NULL);
		i++;
	}
	return (0);
}

int	init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		philos[i].philo = i + 1;
		philos[i].data = data;
		philos[i].n_eaten = 0;
		pthread_mutex_init(&philos[i].p_status, NULL);
		i++;
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	data->mutex_status = alive;
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	amount;

	data->n_eat = 0;
	data->status = alive;
	data->mutex_status = dead;
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = -1;
	if (data->n_philos == 1)
		amount = 2;
	else
		amount = data->n_philos;
	data->forks = (pthread_mutex_t *)malloc(sizeof(*data->forks) * (amount));
	if (!data->forks)
		return (str_error(MALLOC_ERR));
	if (init_mutexes(data))
		return (clear_all(data, NULL, MUTEX_ERR));
	return (0);
}
