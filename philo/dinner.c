/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:01:37 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/30 14:40:14 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_desync(t_philo *philo)
{
	long	eating_time;
	long	thinking_time;
	long	sleeping_time;

	eating_time = philo->data->t_eat;
	sleeping_time = philo->data->t_sleep;
	if (philo->data->n_philo % 2 == 0)
		return ;
	else
	{
		thinking_time = 2 * eating_time - sleeping_time;
		if (thinking_time < 0)
			thinking_time = 0;
		ft_usleep(thinking_time * 0.42, philo->data);
	}
}

void	ft_philo_think(t_philo *philo)
{
	ft_write_status(philo, THINKING);
	ft_desync(philo);
}

void	ft_philo_eat(t_philo *philo)
{
	ft_safe_mutex(&philo->first_fork->fork_m, LOCK);
	ft_write_status(philo, TAKES_FORK_1);
	ft_safe_mutex(&philo->second_fork->fork_m, LOCK);
	ft_write_status(philo, TAKES_FORK_2);
	ft_set_long(&philo->philo_mutex, ft_get_time(MILSEC),
		&philo->last_meal_time);
	philo->meals_counter++;
	ft_write_status(philo, EATING);
	ft_usleep(philo->data->t_eat, philo->data);
	if (philo->data->n_times_eat > 0
		&& philo->meals_counter == philo->data->n_times_eat)
		ft_set_bool(&philo->philo_mutex, true, &philo->full);
	ft_safe_mutex(&philo->first_fork->fork_m, UNLOCK);
	ft_safe_mutex(&philo->second_fork->fork_m, UNLOCK);
}

void	*ft_philo_dinner(void *dataa)
{
	t_philo	*philo;

	philo = (t_philo *)dataa;
	wait4allthreads(philo->data);
	ft_set_long(&philo->philo_mutex, ft_get_time(MILSEC),
		&philo->last_meal_time);
	ft_increase_long(&philo->data->data_mutex, 1,
		&philo->data->threads_running);
	if (philo->id % 2 == 0)
		ft_usleep(50, philo->data);
	while (ft_simulation_end(philo->data) == false)
	{
		if (philo->full == true)
			break ;
		ft_philo_eat(philo);
		ft_write_status(philo, SLEEPING);
		ft_usleep(philo->data->t_sleep, philo->data);
		ft_philo_think(philo);
		if (philo->full == true && ft_simulation_end(philo->data) == false)
			break ;
	}
	return (NULL);
}

void	*ft_monitor_dinner(void	*dataa)
{
	t_data	*data;
	int		i;

	data = (t_data *)dataa;
	while (all_threads_running(data) == false)
		;
	while (ft_simulation_end(data) == false)
	{
		i = 0;
		while (i < data->n_philo && ft_simulation_end(data) == false)
		{
			if (ft_philo_died(&data->philos[i]) == true)
			{
				ft_write_status(&data->philos[i], DIED);
				ft_set_bool(&data->data_mutex, true, &data->end_simulation);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
