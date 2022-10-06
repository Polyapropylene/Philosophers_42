/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_init_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:07:58 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/07/01 18:23:48 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(char **argv, int argc)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong argument number\n");
		return (1);
	}
	while (i < argc)
	{
		if (argv[i][0] == '-' || ft_str_is_number(argv[i])
			|| ft_atoi(argv[i]) == 0)
		{
			printf("Error: Invalid Arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

t_philo	**philo_init(t_data *data)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)malloc(sizeof(t_philo *) * data->num_of_philos);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < (int)data->num_of_philos)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return (0);
		philo[i]->id = i;
		philo[i]->data = data;
		sem_unlink("eatcounter");
		philo[i]->eat_sem = sem_open("eatcounter", O_CREAT, 0644, 1);
		if (philo[i]->eat_sem == SEM_FAILED)
			return (NULL);
		i++;
	}
	return (philo);
}

int	sems_init(t_data *data)
{
	sem_unlink("forking");
	data->fork_sem = sem_open("forking", O_CREAT, 0644,
			data->num_of_philos);
	if (data->fork_sem == SEM_FAILED)
		return (1);
	sem_unlink("writing");
	data->write_sem = sem_open("writing", O_CREAT, 0644, 1);
	if (data->write_sem == SEM_FAILED)
		return (1);
	sem_unlink("meal");
	data->meal_sem = sem_open("meal", O_CREAT, 0644, 1);
	if (data->meal_sem == SEM_FAILED)
		return (1);
	return (0);
}

t_data	*init(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->num_of_philos = (uint64_t)ft_atoi(argv[1]);
	data->time_to_die = (uint64_t)ft_atoi(argv[2]);
	data->time_to_eat = (uint64_t)ft_atoi(argv[3]);
	data->time_to_sleep = (uint64_t)ft_atoi(argv[4]);
	if (data->num_of_philos == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1
		|| data->times_philos_must_eat == -1)
	{
		printf("Error: Invalid Arguments\n");
		return (NULL);
	}
	data->times_philos_must_eat = 0;
	if (argc == 6)
	data->times_philos_must_eat = ft_atoi(argv[5]);
	if (sems_init(data))
		return (NULL);
	data->start_time = get_current_time();
	data->philo = philo_init(data);
	return (data);
}
