/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_funcs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 20:16:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/03 21:37:46 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	init_philo_threads(t_philo **philos, t_data *data)
{
	int			i;
	pthread_t	tids[data->n_philos - 1];
	pthread_t	ctids[data->n_philos - 1];

	i = 0;
	if (gettimeofday(&data->start_time, NULL))
		return (str_error(STRUCT_ERR));
	while (i < data->n_philos)
	{
		(*philos)[i].last_diner = data->start_time;
		if (pthread_create(&(tids[i]), NULL, &philo, (void*)&(*philos)[i]))
			return (str_error(THREAD_ERR));
		if (pthread_create(&(ctids[i]), NULL, &checker_func, (void*)&(*philos)[i]))
			return (str_error(THREAD_ERR));
		i++;
	}
	// CLOSING THREADS
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(tids[i], NULL);
		usleep(100);
		pthread_join(ctids[i], NULL);
		i++;
	}
	printf("amount of philos created = %i\n", i);
	return (0);
}

int		init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		philos[i].philo = i + 1;
		philos[i].data = data;
		philos[i].n_eaten = 0;
		i++;
	}
	return (0);
}

int		init_mutexes(t_data **struct_address)
{
	t_data	*data;
	int		i;
	
	i = 0;
	data = *struct_address;
	data->forks = (pthread_mutex_t*)malloc(sizeof(*data->forks) * (data->n_philos));
	if (!data->forks)
		return (str_error(MALLOC_ERR));
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (str_error(MUTEX_ERR));
		i++;
	}
	if (pthread_mutex_init(&data->m_status, NULL))
			return (str_error(MUTEX_ERR));
	if (pthread_mutex_init(&data->m_print, NULL))
		return (str_error(MUTEX_ERR));
	return (0);
}

int		init_data(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (str_error(ARG_ERR));
	data->n_eat = 0;
	data->status = alive;
	data->mutex_status = alive;
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = -1;
	data->forks = NULL;
	if (init_mutexes(&data))
		return (1);
	return (0);
}
