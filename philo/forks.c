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

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->fork_mutex)
		return (1);
	while (i < data->num_of_philo)
	{
		if(pthread_mutex_init(&(data->fork_mutex[i]), NULL) != 0)
			return (1);
	}
	return (0);
}