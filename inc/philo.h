/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:57:24 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/03 19:47:13 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>

# define ARG_ERR "Could not parse arguments\n"
# define STRUCT_ERR "Could not initialise structs\n"
# define MUTEX_ERR "A mutex failed\n"

enum e_values
{
	dead = 0,
	alive = 1
};

typedef struct	s_data
{
	int					n_philos;
	long int			t_die;
	long int			t_eat;
	long int			t_sleep;
	int					n_eat;
	struct timeval		start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		m_status; //
	pthread_mutex_t		m_print; //
}				t_data;

typedef struct	s_philo
{
	int					philo;
	int					n_eaten;
	int					status;
	long int			last_diner;
	struct timeval		cur_time;
	t_data				*data;
}				t_philo;

//parser
int		get_args(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);

//utils
int		str_error(char *str);
int		clear_all(t_data *data, char *str);
void	*free_data(t_data *data);
void	*free_philos(t_philo **data);
// libft utils
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// time_keep
// void	current_time(t_philo *philo);
struct timeval	*current_time();

//philos
int		create_philo_threads(t_data *data);

//actions
void	eat_(t_philo *philo);
void	sleep_(t_philo *philo);
void	die_(int n);

//test
void	print_args(t_data *data);

#endif

