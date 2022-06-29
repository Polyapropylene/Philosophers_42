/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:17:06 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/29 18:00:45 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_data *data, size_t start_time)
{
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d is sleeping", get_current_time() - start_time, data->philo.id);
	pthread_mutex_unlock(data->print_mutex);
	my_usleep(data->time_to_sleep);
}

void	philo_eat(t_data *data, size_t start_time)
{
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d is eating", get_current_time() - start_time, data->philo.id);
	pthread_mutex_unlock(data->print_mutex);
	data->philo.times_has_eaten++;
	my_usleep(data->time_to_eat);
}

int	check_is_alive(t_data *data, size_t start_time)
{
	pthread_mutex_lock(data->death_mutex);
	if((get_current_time() - start_time) > (data->time_to_die))
	{
		pthread_mutex_lock(data->print_mutex);
		printf("%ld %d has died", get_current_time() - start_time, data->philo.id);
		pthread_mutex_unlock(data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->death_mutex);
	return (0);
}

void	*philo_lifes(t_data *data)
{
	size_t	start_time;

	start_time = get_current_time();
	data->philo.times_has_eaten = 0;
	while (!check_is_alive(data, start_time))
	{
		philo_eat(data, start_time);
		if (data->times_philo_must_eat != -1 && data->philo.times_has_eaten == data->times_philo_must_eat)
			break;
		philo_sleep(data, start_time);
		pthread_mutex_lock(data->print_mutex);
		printf("%ld %d is thinking", get_current_time() - start_time, data->philo.id);
	}
}