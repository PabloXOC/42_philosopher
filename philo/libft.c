/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:25:27 by paxoc01           #+#    #+#             */
/*   Updated: 2024/04/24 13:50:14 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	loop;
	int	temp;
	int	i;

	temp = 0;
	loop = 0;
	while (is_space(str[loop]))
		loop++;
	if (str[loop] == '+')
		loop++;
	i = 0;
	while (str[loop] >= '0' && str[loop] <= '9')
	{
		temp = 10 * temp + str[loop] - '0';
		loop++;
		i++;
	}
	if (i > 10)
		return (-1);
	if (temp > INT_MAX)
		return (-1);
	return (temp);
}

int	ft_valid_str(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (EXIT_FAILURE);
	if (!(is_digit(str[i])))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	all_threads_running(t_data *data)
{
	if (ft_get_long(&data->data_mutex, &data->threads_running) == data->n_philo)
		return (true);
	else
		return (false);
}
