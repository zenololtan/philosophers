/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:57:24 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/02 20:32:35 by ztan          ########   odam.nl         */
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

# define ARG_ERR "Could not parse arguments\n"
# define STRUCT_ERR "Could not initialise structs\n"
# define MUTEX_ERR "A mutex failed\n"

typedef struct	s_data
{
	int		n_philos;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*m_status; //
	pthread_mutex_t	*m_print; //
}				t_data;

typedef struct	s_philo
{
	int		philo;
	int		n_eaten;
	int		status;
	int		start_time;
	int		cur_time;
	t_data	*data;
}				t_philo;

//parser
int		get_args(t_data *data, int argc, char **argv);

//utils
int		str_error(char *str);
int		clear_all(t_data *data, char *str);
void	*free_data(t_data *data);
void	*free_philos(t_philo **data);

//philos
int		create_philo_threads(t_data *data);

//actions
void	eat_(const int t, const int n);
void	sleep_(const int t, const int n);
void	think_(const int t, const int n);
void	die_(const int n);

//test
void	print_args(t_data *data);

#endif

