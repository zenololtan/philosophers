/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 22:28:37 by zenotan       #+#    #+#                 */
/*   Updated: 2021/07/26 23:34:36 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// take_fork
// put fork
// eat
void	eat_(const int t, const int n)
{
	printf("philosopher %i is eating\n", n);
	wait(t);
}
// sleep
void	sleep_(const int t, const int n)
{
	printf("philosopher %i is sleeping\n", n);
	wait(t);
}
// think
void	think_(const int t, const int n)
{
	printf("philosopher %i is thinking\n", n);
	wait(t);
}
// die
void	die(const int n)
{
	printf("philosopher %i died\n", n);
}