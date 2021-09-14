/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 22:01:21 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/15 00:29:00 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (parse_data(&data, argc, argv))
		return (1);
	philos = (t_philo *)malloc(sizeof(*philos) * (data.n_philos));
	if (!philos)
		return (clear_all(&data, NULL, MALLOC_ERR));
	if (init_structs(&data, philos))
		return (clear_all(&data, philos, MUTEX_ERR));
	if (init_philo_threads(philos, &data))
		return (clear_all(&data, philos, NULL));
	clear_all(&data, philos, NULL);
	return (0);
}
