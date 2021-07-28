/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:55:57 by ztan          #+#    #+#                 */
/*   Updated: 2021/07/26 23:55:50 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	test(void)
{
	printf("this is a test function\n");
}

void	*philo(void *ptr)
{
	t_philo	*philo;
	philo = (t_philo*)ptr;
	printf("PHILO[%i]\n", philo->philo);
	test();
	return (NULL);
}

t_philo	**init_philos(t_data *data, int n)
{
	t_philo **philos;
	int	i;

	i = 0;
	philos = (t_philo**)malloc(sizeof(*philos) * (n + 1));
	if (!philos)
		return (NULL);
	philos[n] = NULL;
	while (i < n)
	{
		philos[i] = (t_philo*)malloc(sizeof(**philo));
		if (!philos[i])
			return (free_philos(philos));
		philos[i]->philo = i + 1;
		philos[i]->data = data;
		i++;
	}
	return (philos);
}

int	create_philo_threads(t_data *data)
{
	int			i;
	int			err;
	pthread_t	tids[data->n_philos - 1];
	t_philo		**philos;

	philos = init_philos(data, data->n_philos);
	if (!philos)
		return (str_error("Error: couldnt create philos\n"));
	i = 0;
	while (i < data->n_philos)
	{
		err = pthread_create(&(tids[i]), NULL, &philo, (void*)philos[i]);
		if (err != 0)
			return (str_error("Error: couldnt create a thread\n"));
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(tids[i], NULL);
		i++;
	}
	printf("amount of philos created = %i\n", i);
	free_philos(philos);
	return (0);
}
