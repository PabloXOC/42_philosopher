/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:04:34 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/23 17:58:08 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_write_status(t_philo *philo, t_philo_status status)
{
	long	time;
	int		id;
	t_data	*data;

	id = philo->id;
	data = philo->data;
	time = ft_get_time(MILSEC) - philo->data->start_time_simulation;
	ft_safe_mutex(&philo->data->write_mutex, LOCK);
	if (status == TAKES_FORK_1 && ft_simulation_end(data) == false)
		printf(G"%-6ld"RST""YE"%d"RST" has taken a fork\n", time, id);
	else if (status == TAKES_FORK_2 && ft_simulation_end(data) == false)
		printf(G"%-6ld"RST""YE"%d"RST" has taken a fork\n", time, id);
	else if (status == EATING && ft_simulation_end(data) == false)
		printf(G"%-6ld"RST""YE"%d"RST" is eating\n", time, id);
	else if (status == SLEEPING && ft_simulation_end(data) == false)
		printf(G"%-6ld"RST""YE"%d"RST" is sleeping\n", time, id);
	else if (status == THINKING && ft_simulation_end(data) == false)
		printf(G"%-6ld"RST""YE"%d"RST" is thinking\n", time, id);
	else if (status == DIED && ft_simulation_end(data) == false)
		printf(G"%-6ld"RST""YE"%d"RST" died\n", time, id);
	ft_safe_mutex(&philo->data->write_mutex, UNLOCK);
}

void	ft_pe(char *str)
{
	printf("Error: %s\n", str);
}
