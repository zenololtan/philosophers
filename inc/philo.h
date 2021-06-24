/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:57:24 by ztan          #+#    #+#                 */
/*   Updated: 2021/06/24 16:26:18 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <libft.h>

typedef struct	s_data
{
	int		n_philos;
	pthread_mutex_t	*lock;
	int		t_die;
	int		t_eat;
	int		t_sleep;
}				t_data;

typedef struct	s_philo
{
	int		philo;
	bool	left;
	bool	right;
	t_data	*data;
}				t_philo;

//parser
t_data	*get_args(char **argv);

//utils
int	str_error(char *str);
int	clear_all(t_data *data, char *str);

//philos
int	create_philo_threads(t_data *data);

//test
void	print_args(t_data *data);

#endif

