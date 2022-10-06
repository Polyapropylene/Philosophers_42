/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:08:07 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/07/01 18:21:51 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_current_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	message(t_data *data, int philo_id, char *msg)
{
	sem_wait(data->write_sem);
	printf("%d ms: %d Philosopher %s\n", get_current_time() - data->start_time,
		philo_id + 1, msg);
	if (msg[0] != 'd')
		sem_post(data->write_sem);
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

void	close_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		while (i < data->num_of_philos)
			kill(data->philo[i++]->pid, SIGKILL);
	}
}
