/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:38:22 by ztan          #+#    #+#                 */
/*   Updated: 2021/07/26 23:54:39 by zenotan       ########   odam.nl         */
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

t_data	*init_struct(int n)
{
	t_data	*data;
	int		i;
	int		err;

	i = 0;
	data = (t_data*)malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->forks = (pthread_mutex_t**)malloc(sizeof(*data->forks) * n);
	data->forks[n] = NULL;
	if (!data->forks)
		return (free_data(data));
	while (i < n)
	{
		data->forks[i] = (pthread_mutex_t*)malloc(sizeof(**data->forks));
		if (!data->forks[i])
			return (free_data(data));
		err = pthread_mutex_init(data->forks[i], NULL);
		if (err)
			return (free_data(data));
		i++;
	}
	return (data);
}

t_data	*get_args(char **argv)
{
	t_data	*data;
	int n_philo;
	
	if (!valid(argv[1]) || !valid(argv[2])
		 || !valid(argv[3]) || !valid(argv[4]))
		return (NULL);
	n_philo = ft_atoi(argv[1]);
	data = init_struct(n_philo);
	if (!data)
		return (NULL);
	data->n_philos = n_philo;
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	printf("Found args, initiated struct and mutex object\n");
	return (data);
}