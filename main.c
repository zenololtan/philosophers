/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:14:12 by ztan          #+#    #+#                 */
/*   Updated: 2021/09/10 17:05:13 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <sys/wait.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (check_args(argc, argv))
		return (str_error(ARG_ERR));
	if (init_data(&data, argc, argv))
		return (1);
	philos = (t_philo *)malloc(sizeof(*philos) * (data.n_philos));
	if (!philos)
		return (clear_all(&data, NULL, MALLOC_ERR));
	if (init_philos(philos, &data))
		return (clear_all(&data, NULL, NULL));
	if (init_philo_threads(philos, &data))
		return (clear_all(&data, philos, NULL));
	free_data(&data, philos);
	wait(NULL);
	return (0);
}
