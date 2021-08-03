/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_keep.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/03 11:40:54 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/03 13:26:17 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//timeval = seconds & micro sec
// micro * 1000 = milisec
// values are in long int

//get current time
struct timeval	*current_time()
{
	struct timeval	*time;
	
	time = (struct timeval*)malloc(sizeof(*time));
	if (!time)
	{
		free(time);
		return (NULL);
	}
	if (gettimeofday(time, NULL))
	{
		free(time);
		return (NULL);
	}
	printf("time: %ld.%d\n", time->tv_sec, time->tv_usec);
	return (time);
}

//compare times
// void	compare_time()
// {
	
// }