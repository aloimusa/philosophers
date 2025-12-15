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

int	ft_atoi(const char *str)
{
	long long	number;
	short		pm;
	int			i;

	number = 0;
	pm = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pm *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - '0');
	if (number > INT_MAX || number < INT_MIN)
		errno = ERANGE;
	i = (int)number;
	return (i *= pm);
}
