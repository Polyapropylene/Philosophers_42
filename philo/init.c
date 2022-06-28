/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:31:08 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/27 16:47:20 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (n < argc)
	{
		while (argv[n][i])
		{
			if (ft_isdigit(argv[n][i] == 0))
				return (0);
			i++;
		}
		n++;
	}
	return (1);
}

int	init_philo(int argc, char **argv, t_philo *data)
{
	if (check_args(argc, argv) == 0)
		return (0);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_philo_must_eat = ft_atoi(argv[5]);
	else
		data->times_philo_must_eat = -1;
	return (1);
}