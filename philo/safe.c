/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:38:17 by paxoc01           #+#    #+#             */
/*   Updated: 2024/04/21 19:24:43 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_safe_malloc(int n_bytes)
{
	void	*m;

	m = (void *) malloc (n_bytes);
	if (!m)
	{
		ft_pe("Malloc error.");
		return (NULL);
	}
	return (m);
}

int	ft_mutex_error(int result, t_mutex_code m_code)
{
	if (result == 0)
		return (EXIT_SUCCESS);
	else if (result == EINVAL && (m_code == LOCK || m_code == UNLOCK
			|| m_code == DESTROY))
		ft_pe("The value specified by mutex is invalid.");
	else if (result == EINVAL && m_code == INIT)
		ft_pe("The value specified by attr is invalid.");
	else if (result == EPERM && m_code == UNLOCK)
		ft_pe("The current thread does not hold a lock on mutex.");
	else if (result == EDEADLK && m_code == LOCK)
		ft_pe("A deadlock would occur if the thread blocked "
			"waiting for mutex.");
	else if (result == ENOMEM && m_code == INIT)
		ft_pe("The process cannot allocate enough memory to create "
			"another mutex.");
	else if (result == EBUSY && m_code == DESTROY)
		ft_pe("Mutex is locked by another thread.");
	else if (result == EOWNERDEAD && m_code == LOCK)
		ft_pe("The argument mutex points to a robust mutex and the process "
			"containing the previous owning thread terminated while holding"
			" the mutex lock. The lock was granted to the caller and it is up"
			" to the new owner to make the state consistent.");
	else if (result == ENOTRECOVERABLE && m_code == LOCK)
		ft_pe("The state protected by the mutex is not recoverable.");
	return (EXIT_FAILURE);
}

int	ft_safe_mutex(t_mtx *mutex, t_mutex_code m_code)
{
	if (m_code == LOCK)
		return (ft_mutex_error(pthread_mutex_lock(mutex), LOCK));
	else if (m_code == UNLOCK)
		return (ft_mutex_error(pthread_mutex_unlock(mutex), UNLOCK));
	else if (m_code == INIT)
		return (ft_mutex_error(pthread_mutex_init(mutex, NULL), INIT));
	else if (m_code == DESTROY)
		return (ft_mutex_error(pthread_mutex_destroy(mutex), DESTROY));
	else
	{
		ft_pe("Wrong mutex handle\n");
		return (EXIT_FAILURE);
	}
}

int	ft_thread_error(int result, t_mutex_code t_code)
{
	if (result == 0)
		return (EXIT_SUCCESS);
	else if (result == EAGAIN && t_code == CREATE)
		ft_pe("Not enough system resources to create a process for the new thre"
			"ad, or more than PTHREAD_THREADS_MAX threads are already active.");
	else if (result == ESRCH && (t_code == DETACH || t_code == JOIN))
		ft_pe("No thread could be found corresponding to that specified by the"
			" given thread ID.");
	else if (result == EINVAL && t_code == DETACH)
		ft_pe("the thread th is already in the detached state");
	else if (result == EINVAL && t_code == JOIN)
		ft_pe("The value specified by thread does not refer to a joinable "
			"thread.");
	else if (result == EDEADLK && t_code == JOIN)
		ft_pe("A deadlock was detected or the value of thread specifies the "
			"calling thread.");
	return (EXIT_FAILURE);
}

int	ft_safe_thread(pthread_t *thread, void *(*foo)(void *),
		void *data, t_mutex_code t_code)
{
	if (t_code == CREATE)
		return (ft_thread_error(pthread_create(thread, NULL, foo, data),
				CREATE));
	else if (t_code == DETACH)
		return (ft_thread_error(pthread_detach(*thread), DETACH));
	else if (t_code == JOIN)
		return (ft_thread_error(pthread_join(*thread, NULL), JOIN));
	else
	{
		ft_pe("Wrong thread handle\n");
		return (EXIT_FAILURE);
	}
}
