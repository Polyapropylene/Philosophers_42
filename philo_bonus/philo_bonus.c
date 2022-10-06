/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:07:54 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/07/01 18:24:12 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_meal(void *args)
{
	t_data	*data;
	int		eat_counter;
	int		i;

	data = (t_data *)args;
	eat_counter = 0;
	while (eat_counter < data->times_philos_must_eat)
	{
		i = 0;
		while (i <= data->num_of_philos)
		{
			sem_wait(data->meal_sem);
			i++;
		}
		eat_counter++;
	}
	sem_wait(data->write_sem);
	i = 0;
	while (i < data->num_of_philos)
		kill(data->philo[i++]->pid, SIGKILL);
	return (NULL);
}

void	*monitor_die(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	while (1)
	{
		sem_wait(ph->eat_sem);
		if (get_current_time() - ph->ate_last_time >= ph->data->time_to_die)
		{
			message(ph->data, ph->id, "died");
			exit(1);
		}
		sem_post(ph->eat_sem);
		usleep(100);
	}
	return (NULL);
}

void	start_philo(t_data	*data)
{
	int	i;

	i = 0;
	if (data->times_philos_must_eat)
		pthread_create(&data->meal_thread, NULL, monitor_meal,
			(void *)data);
	while (i < data->num_of_philos)
	{
		data->philo[i]->pid = fork();
		data->philo[i]->ate_last_time = get_current_time();
		if (data->philo[i]->pid == 0)
		{
			pthread_create(&data->philo[i]->death_thread, NULL, monitor_die,
				(void *)data->philo[i]);
			routine(data->philo[i]);
			exit(1);
		}
		i++;
		usleep(100);
	}
	close_processes(data);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (check_args(argv, argc))
		return (1);
	data = init(argc, argv);
	if (!data)
		return (1);
	data->start_time = get_current_time();
	start_philo(data);
	return (0);
}
