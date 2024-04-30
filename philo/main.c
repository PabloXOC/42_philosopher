/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:46:59 by paxoc01           #+#    #+#             */
/*   Updated: 2024/04/29 17:19:08 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	argc--;
	argv++;
	if (argc == 4 || argc == 5)
	{
		if (philosopher(argv, argc) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		ft_pe("Wrong number of input");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	philosopher(char **argv, int argc)
{
	t_data	*data;

	data = get_data(argv, argc);
	if (data == NULL)
	{
		ft_pe("Invalid data type. Philosophers "
			"should be > 1, all times should be > 60ms "
			"and all should be smaller than MAX INT");
		return (EXIT_FAILURE);
	}
	if (ft_init(data) == EXIT_FAILURE)
	{
		ft_pe("Init error");
		ft_free(data);
		return (EXIT_FAILURE);
	}
	ft_dinner(data);
	ft_free(data);
	return (EXIT_SUCCESS);
}

void	*ft_lone_philo(void	*dataa)
{
	t_philo	*philo;

	philo = (t_philo *)dataa;
	wait4allthreads(philo->data);
	ft_set_long(&philo->philo_mutex, ft_get_time(MILSEC),
		&philo->last_meal_time);
	ft_increase_long(&philo->data->data_mutex, 1,
		&philo->data->threads_running);
	ft_write_status(philo, TAKES_FORK_1);
	while (ft_simulation_end(philo->data) == false)
		;
	return (NULL);
}

void	ft_dinner_multiple(t_data *data, int i)
{
	while (i < data->n_philo)
	{
		ft_safe_thread(&data->philos[i].thread_id, ft_philo_dinner,
			&data->philos[i], CREATE);
		i++;
	}
	ft_safe_thread(&data->monitor_thread_id, ft_monitor_dinner, data, CREATE);
	data->start_time_simulation = ft_get_time(MILSEC);
	ft_set_bool(&data->data_mutex, true, &data->all_ready_to_start);
	i = 0;
	while (i < data->n_philo)
	{
		ft_safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	ft_set_bool(&data->data_mutex, true, &data->end_simulation);
	ft_safe_thread(&data->monitor_thread_id, NULL, NULL, JOIN);
}

void	ft_dinner(t_data *data)
{
	if (data->n_times_eat == 0)
		return ;
	if (data->n_philo == 1)
	{
		ft_safe_thread(&data->philos[0].thread_id, ft_lone_philo,
			&data->philos[0], CREATE);
		ft_safe_thread(&data->monitor_thread_id, ft_monitor_dinner,
			data, CREATE);
		data->start_time_simulation = ft_get_time(MILSEC);
		ft_set_bool(&data->data_mutex, true, &data->all_ready_to_start);
		ft_safe_thread(&data->philos[0].thread_id, NULL, NULL, JOIN);
		ft_set_bool(&data->data_mutex, true, &data->end_simulation);
		ft_safe_thread(&data->monitor_thread_id, NULL, NULL, JOIN);
	}
	else
		ft_dinner_multiple(data, 0);
}
