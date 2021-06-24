/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:55:57 by ztan          #+#    #+#                 */
/*   Updated: 2021/06/24 15:54:34 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// int	init_err(int *tids)
// {
	
// }

void	*clear_philos(t_philo **philos, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
	return (NULL);
}

void	*philo(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo*)ptr;
	printf("THEAD[%i]\n", philo->philo);
	return (NULL);
}

t_philo	**init_philos(t_data **data, int n)
{
	t_philo	**philos;
	int i;
	
	philos = (t_philo**)malloc(sizeof(*philo) * n);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < n)
	{
		philos[i] = (t_philo*)malloc(sizeof(**philos));
		if (!philos[i])
			return (clear_philos(philos, n));
		philos[i]->philo = n;
		philos[i]->left = false;
		philos[i]->right = false;
		philos[i]->data = *data;
		i++;
	}
	return (philos);
}

int	create_philo_threads(t_data *data)
{
	int	i;
	int	err;
	pthread_t	tids[data->n_philos];
	t_philo	**philos;

	philos = init_philos(&data, data->n_philos);
	if (!philos)
		return (str_error("Error: couldnt create philos\n"));
	i = 0;
	while (i < data->n_philos)
	{
		err = pthread_create(&(tids[i]), NULL, &philo, (void*)&philos[i]);
		if (err != 0)
			return (str_error("Error: couldnt create a thread\n"));
		i++;
	}
	return (0);
}