/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 04:51:05 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/07/01 18:28:46 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_philo
{
	pid_t			pid;
	pthread_t		death_thread;
	sem_t			*eat_sem;
	int				id;
	int				ate_last_time;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int			num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_philos_must_eat;
	int			start_time;
	pthread_t	meal_thread;
	sem_t		*write_sem;
	sem_t		*fork_sem;
	sem_t		*meal_sem;
	t_philo		**philo;
}	t_data;

int		ft_atoi(const char *str);
int		get_current_time(void);
void	message(t_data *data, int philo_id, char *msg);
void	myusleep(uint64_t time);
int		ft_str_is_number(char *string);
void	close_processes(t_data *data);
t_data	*init(int argc, char **argv);
int		sems_init(t_data *data);
t_philo	**philo_init(t_data *data);
int		check_args(char **argv, int argc);
void	take_fork(t_philo *philo);
void	start_philo(t_data	*data);
void	*routine(t_philo	*ph);
void	*monitor_die(void *arg);
void	*monitor_meal(void *datat_data);

#endif