/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:31:08 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/29 19:17:34 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
    while (i < data->num_of_philos)
    {
        philo[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
        if (!philo[i])
            return (NULL);
        if (pthread_mutex_init(&philo[i]->death_mutex, NULL))
            return (NULL);
        philo[i]->id = i;
        philo[i]->data = data;
        philo[i]->is_eating_rn = 0;
        philo[i]->times_has_eaten = 0;
        philo[i]->left_fork = i;
        philo[i]->right_fork = (i + 1) % data->num_of_philos;
        i++;
    }
    return (philo);
}

pthread_mutex_t	*fork_init(t_data *data)
{
    pthread_mutex_t	*fork_mutex;
    int				i;

    i = 0;
    if (data->num_of_philos == -1 || data->time_to_die == -1
        || data->time_to_eat == -1 || data->time_to_sleep == -1
        || data->times_philos_must_eat == -1)
    {
        printf("Error: Invalid Arguments\n");
        return (NULL);
    }
    fork_mutex = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
    if (!fork_mutex)
        return (NULL);
    while (i < data->num_of_philos)
    {
        pthread_mutex_init(&fork_mutex[i], NULL);
        i++;
    }
    return (fork_mutex);
}

t_data	*init_all(int argc, char **argv)
{
    t_data	*data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    data->num_of_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->times_philos_must_eat = 0;
    if (argc == 6)
        data->times_philos_must_eat = ft_atoi(argv[5]);
    pthread_mutex_init(&data->print_mutex, NULL);
    data->start_time = get_current_time();
    data->fork_mutex = fork_init(data);
    data->philo = philo_init(data);
    if (!data->philo || !data->fork_mutex)
        return (NULL);
    return (data);
}
