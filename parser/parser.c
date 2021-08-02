/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:38:22 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/02 20:29:09 by ztan          ########   odam.nl         */
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
	if (str[0] == '-' && is_digits(str + 1))
		return (1);
	if (is_digits(str))
		return (1);
	return(0);
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

t_data	*init_struct(int n)
{
	t_data	*data;
	int		i;
	int		err;

	i = 0;
	data = (t_data*)malloc(sizeof(*data));
	if (!data)
		return (NULL);
	// printf("Data malloced\n");
	data->forks = (pthread_mutex_t*)malloc(sizeof(*data->forks) * n);
	// printf("Mutex malloced\n");
	if (!data->forks)
		return (free_data(data));
	while (i < n)
	{
		err = pthread_mutex_init(&data->forks[i], NULL);
		if (err)
			return (free_data(data));
		i++;
	}
	// printf("Individual mutexes malloced\n");
	// printf("amount of mutexes/forks = %i\n", i);
	return (data);
}

int		get_args(t_data *data, int argc, char **argv)
{
	int		n_philo;
	int		i;
	
	i = 0;
	if (check_args(argc, argv))
		return (str_error(ARG_ERR));
	n_philo = ft_atoi(argv[1]);
	data->forks = (pthread_mutex_t*)malloc(sizeof(*data->forks) * n_philo);
	if (!data->forks)
		return (clear_all(data, STRUCT_ERR));
	while (i < n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (clear_all(data, MUTEX_ERR));
		i++;
	}
	data->n_philos = n_philo;
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = 0;
	printf("Found args, initiated struct and mutex object\n");
	return (0);
}
