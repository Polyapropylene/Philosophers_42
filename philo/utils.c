/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:31:25 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/27 19:30:58 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_time(void)
{
    static struct timeval	tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	message(t_data *data, int philo_id, char *msg)
{
    pthread_mutex_lock(&data->print_mutex);
    printf("%ld ms: %d Philosopher %s\n", get_current_time() - data->start_time,
           philo_id + 1, msg);
    if (msg[0] != 'd')
        pthread_mutex_unlock(&data->print_mutex);
}

void	myusleep(uint64_t time)
{
    uint64_t	start_time;

    start_time = 0;
    start_time = get_current_time();
    while ((get_current_time() - start_time) < time)
        usleep(time / 10);
}

int	ft_str_is_number(char *string)
{
    int	i;

    i = 0;
    while (string[i] != '\0')
    {
        if (string[i] < '0' || string[i] > '9')
            return (1);
        i++;
    }
    return (0);
}
