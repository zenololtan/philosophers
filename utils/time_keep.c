/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_keep.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 11:40:54 by ztan          #+#    #+#                 */
/*   Updated: 2021/09/07 16:46:43 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long int	current_time_mili(void)
{	
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long int	passed_time_mili(struct timeval start, struct timeval current)
{
	return ((current.tv_sec * 1000 + current.tv_usec / 1000) - \
		(start.tv_sec * 1000 + start.tv_usec / 1000));
}

void	sleeper_func(t_philo *philo, long int t_sleep)
{
	long int		start_t;

	start_t = current_time_mili();
	while (current_time_mili() - start_t < t_sleep && philo->data->status
		 && philo->data->mutex_status)
		usleep(100);
}
