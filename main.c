/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:14:12 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/03 21:38:47 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (init_data(&data, argc, argv))
		return (1);
	philos = (t_philo*)malloc(sizeof(*philos) * (data.n_philos));
	if (!philos)
		return (clear_all(&data, NULL, MALLOC_ERR));
	if (init_philos(philos, &data))
		return (clear_all(&data, NULL, NULL));
	print_args(&data);
	if (init_philo_threads(&philos, &data))
		return (clear_all(&data, philos, NULL));
	free_data(&data, philos);
	wait(NULL);
	return (0);
}
