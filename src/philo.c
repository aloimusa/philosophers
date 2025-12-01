/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:57:26 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/28 02:57:28 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	getfork(bool left, t_table *tbl, int chair);

void	observe(t_table *table)
{
	int		i;
	long	now;

	i = -1;
	while (++i < table->chairs)
	{
		now = ms(table);
		if (now - get_long(&table->mutex[table->chairs + i + 1],
				&table->philo[i].ate_at) >= table->time_to_die)
		{
			set_bool(&table->mutex[0], &table->alive, false);
			ft_printf(DEAD, (long long)now, i + 1);
			return ;
		}
	}
	if (table->times_must_eat != -1)
	{
		pthread_mutex_lock(&table->mutex[table->chairs * 2 + 1]);
		if (table->finished >= table->chairs)
			set_bool(&table->mutex[0], &table->alive, false);
		pthread_mutex_unlock(&table->mutex[table->chairs * 2 + 1]);
	}
	usleep(420);
}

static void	eat(t_philo *me)
{
	short	i;
	long	now;
	t_table	*table;

	i = me->chair;
	table = me->table;
	pthread_mutex_lock(&table->mutex[getfork(me->dhand, table, i)]);
	if (!get_bool(&table->mutex[0], &table->alive))
	{
		pthread_mutex_unlock(&table->mutex[getfork(me->dhand, table, i)]);
		return ;
	}
	ft_printf(FORK_ONE, (long long)ms(table), i + 1);
	pthread_mutex_lock(&table->mutex[getfork(!me->dhand, table, i)]);
	if (get_bool(&table->mutex[0], &table->alive))
	{
		now = ms(table);
		ft_printf(FORK_TWO, (long long)now, i + 1, (long long)now, i + 1);
		set_long(&table->mutex[table->chairs + 1 + i], &me->ate_at, now);
		usleep(table->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&table->mutex[getfork(me->dhand, table, i)]);
	pthread_mutex_unlock(&table->mutex[getfork(!me->dhand, table, i)]);
	return ;
}

void	*exist(void *arg)
{
	t_philo			*me;
	unsigned int	ate;

	me = arg;
	ate = 0;
	while (get_bool(&me->table->mutex[0], &me->table->alive))
	{
		ft_printf(THINK, (long long)ms(me->table), me->chair + 1);
		if (!ate)
			usleep((42 * me->dhand * me->table->time_to_eat * me->chair)
				/ me->table->chairs);
		eat(me);
		if (!get_bool(&me->table->mutex[0], &me->table->alive)
			|| ++ate >= (unsigned int)me->table->times_must_eat)
			break ;
		ft_printf(SLEEP, (long long)ms(me->table), me->chair + 1);
		usleep(me->table->time_to_sleep * 1000);
	}
	if (ate >= (unsigned int)me->table->times_must_eat)
	{
		pthread_mutex_lock(&me->table->mutex[me->table->chairs * 2 + 1]);
		me->table->finished++;
		pthread_mutex_unlock(&me->table->mutex[me->table->chairs * 2 + 1]);
	}
	return (NULL);
}

static short	getfork(bool left, t_table *tbl, int chair)
{
	short	fork;

	if (left)
		fork = chair + 1;
	else if (chair + 2 > tbl->chairs)
		fork = 1;
	else
		fork = chair + 2;
	return (fork);
}
