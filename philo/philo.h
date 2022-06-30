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
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

// struct timeval 
// {
//    time_t      tv_sec;
//    suseconds_t tv_usec;
// };

typedef	struct s_philo
{
	int	id;
	int	times_has_eaten;
} t_philo;

typedef struct s_data
{
	int				num_of_philo;
	long			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_philo_must_eat;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*fork_mutex;
	long			time;
	t_philo			philo;
} t_data;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	my_usleep(size_t time);
int		get_current_time(void);
int		init_philo(int argc, char **argv, t_data *data);
void	*philo_lifes(void *data);
#endif