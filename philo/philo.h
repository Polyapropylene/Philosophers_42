/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:31:20 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/29 18:25:04 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
    pthread_t		philo_thread;
    pthread_t		death_thread;
    int				id;
    int				right_fork;
    int				left_fork;
    int				times_has_eaten;
    long			ate_last_time;
    int				is_eating_rn;
    pthread_mutex_t	death_mutex;
    struct s_data	*data;
}	t_philo;

typedef struct s_data
{
    int				num_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				times_philos_must_eat;
    long			start_time;
    t_philo			**philo;
    pthread_mutex_t	print_mutex;
    pthread_mutex_t	*fork_mutex;
    int				finish;
}	t_data;

int				check_args(char **argv, int argc);
t_data			*init_all(int argc, char **argv);
pthread_mutex_t	*fork_init(t_data *data);
t_philo			**philo_init(t_data *data);

void			*philo_lifes(void *arg);
void			philo_eating(t_philo *philo);

void			myusleep(uint64_t time);
int				ft_str_is_number(char *string);
void			message(t_data *table, int philo_id, char *msg);
int				get_current_time(void);
int				ft_atoi(const char *str);
#endif