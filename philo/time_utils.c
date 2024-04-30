/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:46:57 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/24 14:30:27 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	wait4allthreads(t_data *data)
{
	while (ft_get_bool(&data->data_mutex, &data->all_ready_to_start) == false)
		;
}

long	ft_get_time(t_time_code time_code)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time_code == SEC)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILSEC)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSEC)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (42);
}

void	ft_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rem;

	start = ft_get_time(MILSEC);
	while (ft_get_time(MILSEC) - start < usec)
	{
		if (ft_simulation_end(data) == true)
			break ;
		elapsed = ft_get_time(MILSEC);
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (ft_get_time(MILSEC) - start < usec)
				;
		}
	}
}

bool	ft_philo_died(t_philo *philo)
{
	long	t_last_meal;
	long	elapsed;

	if (ft_get_bool(&philo->philo_mutex, &philo->full) == true)
		return (false);
	t_last_meal = ft_get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = ft_get_time(MILSEC) - t_last_meal;
	if (elapsed >= philo->data->t_die)
		return (true);
	else
		return (false);
}
