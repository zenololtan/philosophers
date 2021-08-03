/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:38:22 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/03 19:52:53 by ztan          ########   odam.nl         */
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
	if (!is_digits(str) || ft_strlen(str) > 10)
		return (0);
	if (ft_strlen(str) == 10)
		if (!ft_strncmp(str, "214748364", 9) && str[9] > '7')
			return (0);
	return(1);
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

int		init_mutexes(t_data **data_pointer)
{
	t_data	*data;
	int		i;
	
	i = 0;
	data = *data_pointer;
	data->forks = (pthread_mutex_t*)malloc(sizeof(*data->forks) * data->n_philos);
	if (!data->forks)
		return (clear_all(data, STRUCT_ERR));
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (clear_all(data, MUTEX_ERR));
		i++;
	}
	data->m_status = (pthread_mutex_t*)malloc(sizeof(*data->m_status));
	if (!data->m_status)
		return (clear_all(data, STRUCT_ERR));
	if (pthread_mutex_init(data->m_status, NULL))
			return (clear_all(data, MUTEX_ERR));
	data->m_print = (pthread_mutex_t*)malloc(sizeof(*data->m_print));
	if (!data->m_print)
		return (clear_all(data, STRUCT_ERR));
	if (pthread_mutex_init(data->m_print, NULL))
		return (clear_all(data, MUTEX_ERR));
	return (0);
}

int		get_args(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv))
		return (str_error(ARG_ERR));
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = 0;
	data->start_time = NULL;
	data->forks = NULL;
	data->m_status = NULL;
	data->m_print = NULL;
	if (init_mutexes(&data))
		return (1);
	printf("Found args, initiated struct and mutex object\n");
	return (0);
}
