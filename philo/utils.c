/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:26:27 by paxoc01           #+#    #+#             */
/*   Updated: 2024/04/29 15:14:58 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_free(t_data *data)
{
	int	i;

	if (data == NULL)
		return ;
	ft_safe_mutex(&data->data_mutex, DESTROY);
	ft_safe_mutex(&data->write_mutex, DESTROY);
	i = 0;
	while (i < data->threads_running)
	{
		ft_safe_mutex(&data->philos[i].philo_mutex, DESTROY);
		ft_safe_mutex(&data->forks[i].fork_m, DESTROY);
		i++;
	}
	if (data->philos != NULL)
		free(data->philos);
	if (data->forks != NULL)
		free(data->forks);
	free(data);
}

void	ft_increase_long(t_mtx *mutex, long amount, long *dest)
{
	ft_safe_mutex(mutex, LOCK);
	*dest += amount;
	ft_safe_mutex(mutex, UNLOCK);
}
