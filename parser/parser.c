/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 14:38:22 by ztan          #+#    #+#                 */
/*   Updated: 2021/06/24 16:29:52 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int	valid(char *str)
{
	if (str[0] == '-' && is_digits(str + 1))
		return (1);
	if (is_digits(str))
		return (1);
	return(0);
}

void	*free_data(t_data *data)
{
	free(data);
	return (NULL);
}

t_data	*get_args(char **argv)
{
	t_data	*data;
	int	err;
	
	if (!valid(argv[1]) || !valid(argv[2])
		 || !valid(argv[3]) || !valid(argv[4]))
		return (NULL);
	data = (t_data*)malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	err = pthread_mutex_init(data->lock, NULL);
	if (err)
		return (free_data(data));
	return (data);
}