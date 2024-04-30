/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:06:57 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/24 14:36:20 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_init(t_data *data)
{
	data->end_simulation = false;
	data->all_ready_to_start = false;
	data->threads_running = 0;
	data->philos = ft_safe_malloc(data->n_philo * sizeof(t_philo));
	if (data->philos == NULL)
		return (EXIT_FAILURE);
	data->forks = ft_safe_malloc(data->n_philo * sizeof(t_fork));
	if (data->forks == NULL)
		return (EXIT_FAILURE);
	ft_safe_mutex(&data->data_mutex, INIT);
	ft_safe_mutex(&data->write_mutex, INIT);
	if (ft_init_philos(data) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (ft_safe_mutex(&data->forks[i].fork_m, INIT) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		data->forks[i].fork_id = i;
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_counter = 0;
		data->philos[i].full = false;
		data->philos[i].data = data;
		ft_safe_mutex(&data->philos[i].philo_mutex, INIT);
		ft_assign_forks(&data->philos[i], data->forks, i, data->n_philo);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_assign_forks(t_philo *philo, t_fork *forks, int i, int n_philo)
{
	if ((i + 1) % 2 == 1)
	{
		philo->first_fork = &forks[i % n_philo];
		philo->second_fork = &forks[(i + 1) % n_philo];
	}
	else
	{
		philo->first_fork = &forks[(i + 1) % n_philo];
		philo->second_fork = &forks[i % n_philo];
	}
}

t_data	*get_data(char **argv, int argc)
{
	t_data	*data;

	if (ft_valid_str(argv[0]) == 1 || ft_valid_str(argv[1]) == 1
		|| ft_valid_str(argv[2]) == 1 || ft_valid_str(argv[3]) == 1)
		return (NULL);
	if (argc == 5)
	{
		if (ft_valid_str(argv[4]) == EXIT_FAILURE)
			return (NULL);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!(data))
		return (NULL);
	if (get_data2(data, argv, argc) == EXIT_FAILURE)
		return (NULL);
	return (data);
}

int	get_data2(t_data *data, char **argv, int argc)
{
	data->n_philo = ft_atoi(argv[0]);
	data->t_die = ft_atoi(argv[1]);
	data->t_eat = ft_atoi(argv[2]);
	data->t_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		data->n_times_eat = ft_atoi(argv[4]);
	if (data->n_philo < 1 || data->t_die <= 60 || data->t_eat <= 60
		|| data->t_sleep <= 60 || (data->n_times_eat <= 0 && argc == 5))
	{
		ft_free(data);
		return (EXIT_FAILURE);
	}
	if (argc == 4)
		data->n_times_eat = -1;
	return (EXIT_SUCCESS);
}
