/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:31:16 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/29 18:04:10 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_threads(t_data *data)
{
	pthread_t	*philosophers;
	int			i;

	i = 0;
	philosophers = malloc(sizeof(pthread_t) * data->num_of_philo);
	if  (!philosophers)
		return (0);
	while (i++ < data->num_of_philo)
	{
		if (pthread_create(&philosophers[i], NULL, philo_lifes, (void *)&data) != 0)
			return (0);
	}
	i = 0;
	while (i++ < data->num_of_philo)
	{
		if (pthread_join(philosophers[i], NULL) != 0)
			return (0);
	}
	free(philosophers);
	return (1);
}

void	safe_exit(t_data *data)
{
	pthread_mutex_destroy(data->print_mutex);
	pthread_mutex_destroy(data->death_mutex);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	// data = (t_data *) malloc(sizeof(t_data));
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments!");
		return(0);
	}
	if (init_philo(argc, argv, data))
	{
		printf("poshel nahui");
		return (0);
	}
	make_threads(data);
	safe_exit(data);
	return (0);
}