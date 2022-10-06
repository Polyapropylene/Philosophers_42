/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:17:06 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/29 18:26:04 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checking_meal(t_philo	*philo)
{
    int	i;

    i = 0;
    pthread_mutex_lock(&philo->death_mutex);
    while (i < philo->data->num_of_philos)
    {
        if (philo->data->philo[i]->times_has_eaten
            >= philo->data->times_philos_must_eat)
        {
            if (i == philo->data->num_of_philos - 1)
            {
                pthread_mutex_lock(&philo->data->print_mutex);
                philo->data->finish = 0;
            }
            i++;
        }
        else
            break ;
    }
    pthread_mutex_unlock(&philo->death_mutex);
}

void	*monitor(void *arg)
{
    t_philo	*philo;

    philo = ((t_philo *)arg);
    while (philo->data->finish)
    {
        if (!philo->is_eating_rn
            && get_current_time() - philo->ate_last_time
               >= philo->data->time_to_die)
        {
            pthread_mutex_lock(&philo->death_mutex);
            message(philo->data, philo->id, "died");
            philo->data->finish = 0;
            pthread_mutex_unlock(&philo->death_mutex);
        }
        if (philo->data->times_philos_must_eat
            && philo->times_has_eaten >= philo->data->times_philos_must_eat)
            checking_meal(philo);
        usleep(100);
    }
    return (NULL);
}

void	start_philo(t_data *data)
{
    int	i;

    i = 0;
    while (i < data->num_of_philos)
    {
        data->philo[i]->ate_last_time = get_current_time();
        pthread_create(&data->philo[i]->philo_thread, NULL, philo_lifes,
                       (void *)data->philo[i]);
        i++;
        usleep(100);
    }
    i = 0;
    while (i < data->num_of_philos)
    {
        pthread_create(&data->philo[i]->death_thread, NULL, monitor,
                       (void *)data->philo[i]);
        i++;
        usleep(100);
    }
}

int	main(int argc, char **argv)
{
    t_data		*data;

    if (check_args(argv, argc))
        return (1);
    data = init_all(argc, argv);
    if (!data)
        return (1);
    data->finish = 1;
    data->start_time = get_current_time();
    start_philo(data);
    while (data->finish)
        continue ;
    return (0);
}
