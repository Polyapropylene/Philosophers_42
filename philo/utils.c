/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhyhorn <rrhyhorn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:31:25 by rrhyhorn          #+#    #+#             */
/*   Updated: 2022/06/27 19:30:58 by rrhyhorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	t;
	int			minus;

	i = 0;
	t = 0;
	minus = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		t = (t * 10) + ((str[i]) - '0');
		if (minus * t > 2147483647)
			return (-1);
		if (minus * t < -2147483648)
			return (0);
		i++;
	}
	return (t * minus);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	my_usleep(size_t time)
{
	size_t	start;
	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(50);
}

int	get_current_time(void)
{
	struct timeval	cur_time;
	size_t	time;
	gettimeofday(&cur_time, NULL);
	time = (cur_time.tv_sec * 1000) + (cur_time.tv_usec / 1000);
	return (time);
}