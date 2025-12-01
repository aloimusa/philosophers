/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:54:10 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/26 17:54:31 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_long(pthread_mutex_t *mutex, long *val)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_long(pthread_mutex_t *mutex, long *val, long new_val)
{
	pthread_mutex_lock(mutex);
	*val = new_val;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *val)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_bool(pthread_mutex_t *mutex, bool *val, bool new_val)
{
	pthread_mutex_lock(mutex);
	*val = new_val;
	pthread_mutex_unlock(mutex);
}
