/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:14:12 by ztan          #+#    #+#                 */
/*   Updated: 2021/06/24 15:44:31 by ztan          ########   odam.nl         */
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
	create_philo_threads(data);
	// test_threads(data);
	// printf("ended\n");
	return (0);
}
