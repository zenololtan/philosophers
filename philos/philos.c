/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:55:57 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/03 20:41:05 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	test(struct timeval *time)
{
	printf("this is a test function, current time: %ld.%d\n", time->tv_sec, time->tv_usec);
}

void	*philo(void *ptr)
{
	t_philo	*philo;
	philo = (t_philo*)ptr;
	while (philo->data->status)
	{
		if (eat_(philo) || sleep_(philo))
			return (NULL);
	}
	return (NULL);
}
