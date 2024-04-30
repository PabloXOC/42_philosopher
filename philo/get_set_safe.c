/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:22:52 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/21 19:26:22 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	ft_get_bool(t_mtx *mutex, bool	*value)
{
	bool	get_value;

	ft_safe_mutex(mutex, LOCK);
	get_value = *value;
	ft_safe_mutex(mutex, UNLOCK);
	return (get_value);
}

void	ft_set_bool(t_mtx *mutex, bool	value, bool *dest)
{
	ft_safe_mutex(mutex, LOCK);
	*dest = value;
	ft_safe_mutex(mutex, UNLOCK);
}

long	ft_get_long(t_mtx *mutex, long	*value)
{
	long	get_value;

	ft_safe_mutex(mutex, LOCK);
	get_value = *value;
	ft_safe_mutex(mutex, UNLOCK);
	return (get_value);
}

void	ft_set_long(t_mtx *mutex, long value, long *dest)
{
	ft_safe_mutex(mutex, LOCK);
	*dest = value;
	ft_safe_mutex(mutex, UNLOCK);
}

bool	ft_simulation_end(t_data *data)
{
	bool	ret;

	ret = ft_get_bool(&data->data_mutex, &data->end_simulation);
	return (ret);
}
