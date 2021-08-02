/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:14:12 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/02 20:27:43 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <sys/wait.h>
int	main(int argc, char **argv)
{
	t_data	data;

	if (get_args(&data, argc, argv))
		return (1);
	print_args(&data);
	if (create_philo_threads(&data))
		return (1);
	// test_threads(data);
	clear_all(&data, NULL);
	wait(NULL);
	printf("ended\n");
	// while(1) {}
	return (0);
}
