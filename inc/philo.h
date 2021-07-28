/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:57:24 by ztan          #+#    #+#                 */
/*   Updated: 2021/07/26 23:47:58 by zenotan       ########   odam.nl         */
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
	pthread_mutex_t	**forks;
	int		t_die;
	int		t_eat;
	int		t_sleep;
}				t_data;

// need this? a philo is a thread, not data
typedef struct	s_philo
{
	int		philo;
	t_data	*data;
}				t_philo;

//parser
t_data	*get_args(char **argv);

//utils
int	str_error(char *str);
int	clear_all(t_data *data, char *str);
void	*free_data(t_data *data);
void	*free_philos(t_philo **data);

//philos
int	create_philo_threads(t_data *data);
//actions
void	eat_(const int t, const int n);
void	sleep_(const int t, const int n);
void	think_(const int t, const int n);
void	die_(const int n);

//test
void	print_args(t_data *data);

#endif

