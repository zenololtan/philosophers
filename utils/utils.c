/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 15:03:09 by ztan          #+#    #+#                 */
/*   Updated: 2021/08/03 19:52:10 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_args(t_data *data)
{
	printf("num_philo[%d], t_die[%ld], t_eat[%ld], t_sleep[%ld]", data->n_philos, data->t_die, data->t_eat, data->t_sleep);
	if (data->n_eat)
		printf(", num_eat[%d]", data->n_eat);
	printf("\n");
}

int	str_error(char *str)
{
	if (str)
	{
		write(1, "Error: ", 7);
		write(1, str, ft_strlen(str));
	}
	return (1);
}

void	*free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	free(data);
	return (NULL);
}

void	*free_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		free(philos[i]);
		i++;
	}
	free(philos);
	return (NULL);
}

int	clear_all(t_data *data, char *str)
{
	free_data(data);
	if (str)
		str_error(str);
	return (1);
}
