/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:29:15 by aloimusa          #+#    #+#             */
/*   Updated: 2025/12/15 15:29:16 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	getfork(bool left, t_table *tbl, int chair);

bool	observe(t_table *table)
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
			printp(DEAD, NULL, i, table);
			return (false);
		}
	}
	if (table->times_must_eat != -1
		&& (short)get_long(&table->mutex[table->chairs * 2 + 1],
			(long *)&table->finished) >= table->chairs)
	{
		set_bool(&table->mutex[0], &table->alive, false);
		return (false);
	}
	return (true);
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
	printp(FORK, NULL, me->chair, table);
	pthread_mutex_lock(&table->mutex[getfork(!me->dhand, table, i)]);
	if (get_bool(&table->mutex[0], &table->alive))
	{
		now = printp(FORK, EAT, me->chair, table);
		set_long(&table->mutex[table->chairs + 1 + i], &me->ate_at, now);
		usleep(table->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&table->mutex[getfork(me->dhand, table, i)]);
	pthread_mutex_unlock(&table->mutex[getfork(!me->dhand, table, i)]);
}

static void	think(t_philo *me, bool ate)
{
	t_table	*table;
	int		think;

	table = me->table;
	printp(THINK, NULL, me->chair, table);
	if (!ate)
	{
		think = ((((bool)me->dhand + 1) * (table->time_to_die
						- table->time_to_eat - table->time_to_sleep)
					* me->chair) / table->chairs / 3);
	}
	else if ((long long)ms(table) - get_long(&table->mutex[table->chairs + 1
				+ me->chair], &me->ate_at) > table->time_to_eat * 4 / 5)
	{
		think = (900 * (table->time_to_die - table->time_to_eat * 2
					- table->time_to_sleep));
	}
	else
		think = 0;
	if (think > 0)
		usleep(think);
}

void	*exist(void *arg)
{
	t_philo			*me;
	unsigned int	ate;

	me = arg;
	ate = 0;
	while (get_bool(&me->table->mutex[0], &me->table->alive))
	{
		think(me, (bool)ate);
		if (!get_bool(&me->table->mutex[0], &me->table->alive))
			break ;
		eat(me);
		if (!get_bool(&me->table->mutex[0], &me->table->alive))
			break ;
		if (++ate == (unsigned int)me->table->times_must_eat)
		{
			pthread_mutex_lock(&me->table->mutex[me->table->chairs * 2 + 1]);
			me->table->finished++;
			pthread_mutex_unlock(&me->table->mutex[me->table->chairs * 2 + 1]);
		}
		printp(SLEEP, NULL, me->chair, me->table);
		usleep(me->table->time_to_sleep * 1000);
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
