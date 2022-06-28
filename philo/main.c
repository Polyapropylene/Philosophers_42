/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:31:16 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/27 19:24:01 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_threads(t_philo *data)
{
	pthread_t	*philosophers;
	int			i;

	i = 0;
	philosophers = malloc(sizeof(pthread_t) * data->num_of_philo);
	if  (!philosophers)
		return (0);
	while (i++ < data->num_of_philo)
		if (pthread_create(philosophers[i], NULL, philo_lifes, ) != 0);
			return (0);
	i = 0;
	while (i++ < data->num_of_philo)
		if (pthread_join(philosophers[i], NULL) != 0)
			return (0);
	free(philosophers);
	return (1);
}

/*void	print_message()
{
	printf();
}*/

void	safe_exit(t_philo *data)
{
	free(data);
}

int	main(int argc, char **argv)
{
	t_philo	*data;

	data = (t_philo *) malloc(sizeof(t_philo));
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments!");
		exit(0);
	}
	if (!init_philo(argc, argv, data))
	{
		printf("poshel nahui");
		exit(0);
	}
	// printf("%d %d %d %d %d", data->num_of_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->times_philo_must_eat);
	safe_exit(data);
	return (0);
}