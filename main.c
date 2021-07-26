/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:14:12 by ztan          #+#    #+#                 */
/*   Updated: 2021/07/26 23:52:28 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = NULL;
	if (argc != 5)
		return (str_error("Error: incorrect arguments\n"));
	if (!(data = get_args(argv)))
		return (str_error("Error: incorrect arguments\n"));
	print_args(data);
	// create_philo_threads(data);
	// test_threads(data);
	clear_all(data, NULL);
	printf("ended\n");
	// while(1) {}
	return (0);
}
