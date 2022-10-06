/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:53:24 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/29 19:22:30 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->fork_mutex[philo->left_fork]);
    pthread_mutex_lock(&philo->data->fork_mutex[philo->right_fork]);
    pthread_mutex_lock(&philo->death_mutex);
    philo->ate_last_time = get_current_time();
    philo->is_eating_rn = 1;
    message(philo->data, philo->id, "is eating");
    myusleep(philo->data->time_to_eat);
    philo->is_eating_rn = 0;
    philo->times_has_eaten++;
    pthread_mutex_unlock(&philo->death_mutex);
}

void	*philo_lifes(void *arg)
{
    t_philo	*philo;

    philo = ((t_philo *)arg);
    while (philo->data->finish)
    {
        philo_eating(philo);
        pthread_mutex_unlock(&philo->data->fork_mutex[philo->left_fork]);
        pthread_mutex_unlock(&philo->data->fork_mutex[philo->right_fork]);
        message(philo->data, philo->id, "is sleeping");
        myusleep(philo->data->time_to_sleep);
        message(philo->data, philo->id, "is thinking");
    }
    return (NULL);
}
