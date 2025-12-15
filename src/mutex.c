/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:29:20 by aloimusa          #+#    #+#             */
/*   Updated: 2025/12/15 15:29:20 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_long(t_mutex *mutex, long *val)
{
	long	ret;

	pthread_mutex_lock(&mutex->lock);
	ret = *val;
	pthread_mutex_unlock(&mutex->lock);
	return (ret);
}

void	set_long(t_mutex *mutex, long *val, long new_val)
{
	pthread_mutex_lock(&mutex->lock);
	*val = new_val;
	pthread_mutex_unlock(&mutex->lock);
}

bool	get_bool(t_mutex *mutex, bool *val)
{
	bool	ret;

	pthread_mutex_lock(&mutex->lock);
	ret = *val;
	pthread_mutex_unlock(&mutex->lock);
	return (ret);
}

void	set_bool(t_mutex *mutex, bool *val, bool new_val)
{
	pthread_mutex_lock(&mutex->lock);
	*val = new_val;
	pthread_mutex_unlock(&mutex->lock);
}
