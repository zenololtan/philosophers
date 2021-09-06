/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/16 13:57:24 by ztan          #+#    #+#                 */
/*   Updated: 2021/09/06 15:17:34 by ztan          ########   odam.nl         */
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

# define RESET			"\033[0m"
# define RED			"\033[31m"

# define ARG_ERR		"Could not parse arguments\n"
# define MALLOC_ERR		"Could not allocate a variable\n"
# define STRUCT_ERR		"Could not initialise structs\n"
# define MUTEX_ERR		"A mutex failed\n"
# define THREAD_ERR		"Could not initialise a thread\n"
# define TIME_ERR		"Could not get the time\n"

enum e_values
{
	dead = 0,
	alive = 1
};

typedef struct s_data
{
	int					n_philos;
	long int			t_die;
	long int			t_eat;
	long int			t_sleep;
	int					n_eat;
	int					status;
	int					mutex_status;
	struct timeval		start_time;	
	pthread_mutex_t		*forks;
	pthread_mutex_t		m_status;
	pthread_mutex_t		m_print;
}				t_data;

typedef struct s_philo
{
	int					philo;
	int					n_eaten;
	pthread_t			ptid;
	pthread_t			ctid;
	struct timeval		last_diner;
	t_data				*data;
}				t_philo;

/*-----------------------------------PARSER-----------------------------------*/
/* init_funcs.c */
int			init_data(t_data *data, int argc, char **argv);
int			init_mutexes(t_data *data);
int			init_philos(t_philo *philos, t_data *data);
int			init_philo_threads(t_philo *philos, t_data *data);

/* parser.c */
int			check_args(int argc, char **argv);

/*-----------------------------------UTILS------------------------------------*/
/* libft_utils.c */
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void		ft_putnbr_fd(int n, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/* utils.c */
int			str_error(char *str);
void		*str_error_null(char *str);
int			mutex_error(t_data *data);
int			clear_all(t_data *data, t_philo *philos, char *str);
void		*free_data(t_data *data, t_philo *philos);

/* time_keep.c */
long int	expired_time_mili(struct timeval start, struct timeval current);
void		sleeper_func(long int t_sleep);

/* print_func.c */
int			print_func(t_philo *philo, char *str);

/* check_func.c */
void		*checker(t_philo *philo);

/*-----------------------------------PHILOS-----------------------------------*/
/* philos.C */
void		*philo(void *ptr);

/* actions.c */
int			eat_(t_philo *philo);
int			sleep_(t_philo *philo);

#endif
