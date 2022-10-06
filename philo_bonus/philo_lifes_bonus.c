/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:13:44 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/07/01 18:22:33 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->data->fork_sem);
	message(philo->data, philo->id, "has taken the left fork");
	sem_wait(philo->data->fork_sem);
	message(philo->data, philo->id, "has taken the right fork");
	message(philo->data, philo->id, "is eating");
	sem_wait(philo->eat_sem);
	sem_post(philo->data->meal_sem);
	philo->ate_last_time = get_current_time();
	myusleep(philo->data->time_to_eat);
	sem_post(philo->eat_sem);
}

void	*routine(t_philo	*ph)
{
	while (1)
	{
		take_fork(ph);
		sem_post(ph->data->fork_sem);
		sem_post(ph->data->fork_sem);
		message(ph->data, ph->id, "is sleeping");
		myusleep(ph->data->time_to_sleep);
		message(ph->data, ph->id, "is thinking");
		usleep(100);
	}
	return (NULL);
}
