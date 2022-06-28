/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:53:24 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/27 16:59:57 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_philo *data)
{
	int	i;

	i = -1;
	while (i < data->num_of_philo)
	{
		if(pthread_mutex_init(&(data->fork_mutex[i]), NULL) != 0)
			return (0);
	}
	
}