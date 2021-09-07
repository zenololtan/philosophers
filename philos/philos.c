/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:55:57 by ztan          #+#    #+#                 */
/*   Updated: 2021/09/07 12:30:22 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->data->n_philos % 2 && philo->philo % 2)
		usleep(100);
	while (philo->data->status != dead && philo->data->mutex_status != dead)
	{
		if (eat_(philo) || sleep_(philo))
		{
			// printf("philo %i stop --\n", philo->philo);
			return (NULL);
		}
			
	}
	// printf("philo %i stop\n", philo->philo);
	return (NULL);
}
