/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 22:01:19 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/14 23:00:28 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_structs(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	data->mutex_status = DEAD;
	while (i < data->n_philos)
	{
		philos[i].philo = i + 1;
		philos[i].data = data;
		philos[i].n_eaten = 0;
		if (pthread_mutex_init(&data->forks[i], NULL) || \
			pthread_mutex_init(&philos[i].p_status, NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	data->mutex_status = ALIVE;
	return (0);
}

int	valid(char *str)
{
	if (!is_digits(str) || ft_strlen(str) > 10)
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

int	parse_data(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (str_error(ARG_ERR));
	data->n_eat = -1;
	data->status = ALIVE;
	data->mutex_status = DEAD;
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	if (data->n_philos <= 0 || data->t_die <= 0 || data->t_eat <= 0 || \
		 data->t_sleep <= 0)
		 return (str_error(ARG_ERR));
	data->forks = (pthread_mutex_t *)malloc(sizeof(*data->forks) \
		* (data->n_philos));
	if (!data->forks)
		return (str_error(MALLOC_ERR));
	return (0);
}
