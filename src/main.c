/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:29:24 by aloimusa          #+#    #+#             */
/*   Updated: 2025/12/15 19:51:29 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_table(char **av, t_table *table);
static void	sit_philos(t_table *table);
static int	clean(t_table *table);

int	main(int ac, char **av)
{
	t_table			table;
	struct timeval	tv;

	if (ac < 5 || ac > 6)
	{
		printf(USAGE_MSG);
		exit(EXIT_SUCCESS);
	}
	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	table.start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	set_table(av, &table);
	sit_philos(&table);
	while (observe(&table))
		usleep(400);
	clean(&table);
	exit(EXIT_SUCCESS);
}

static void	set_table(char **av, t_table *table)
{
	table->chairs = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->times_must_eat = ft_atoi(av[5]);
	else
		table->times_must_eat = -1;
	if (!table->chairs || !table->time_to_die || !table->time_to_eat
		|| !table->time_to_sleep || (av[5] && !table->times_must_eat)
		|| table->chairs > 200)
		exit(EXIT_SUCCESS);
	if (table->chairs == 1)
		if (printf(ONE_PHILO) && usleep(table->time_to_die * 1000) == 0)
			exit(!(bool)(printf(ONE_PHILO_DEAD, table->time_to_die)));
	table->fork = malloc(table->chairs * sizeof(bool));
	table->philo = malloc(table->chairs * sizeof(t_philo));
	table->thread = ft_calloc(table->chairs, sizeof(pthread_t));
	table->mutex = ft_calloc(table->chairs * 2 + 2, sizeof(t_mutex));
	if (!table->fork || !table->philo || !table->thread || !table->mutex)
		exit(clean(table));
	table->finished = 0;
	table->alive = true;
}

static void	sit_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->chairs * 2 + 2)
	{
		if (i < table->chairs)
			table->fork[i] = true;
		if (pthread_mutex_init(&table->mutex[i].lock, NULL) == -1)
			exit(clean(table));
		else
			table->mutex[i].exists = true;
	}
	i = -1;
	while (++i < table->chairs)
	{
		table->philo[i].dhand = (bool)(i % 2);
		table->philo[i].table = table;
		table->philo[i].chair = i;
		table->philo[i].ate_at = ms(table);
		if (pthread_create(&table->thread[i], NULL, exist,
				&table->philo[i]) == -1)
			exit(clean(table));
	}
}

static int	clean(t_table *table)
{
	int	i;

	if (table->thread)
	{
		i = -1;
		while (++i < table->chairs && table->thread[i] != 0)
			pthread_join(table->thread[i], NULL);
		free(table->thread);
	}
	if (table->mutex)
	{
		i = -1;
		while (++i < table->chairs * 2 + 2 && table->mutex[i].exists)
			pthread_mutex_destroy(&table->mutex[i].lock);
		free(table->mutex);
	}
	if (table->fork)
		free(table->fork);
	if (table->philo)
		free(table->philo);
	return (EXIT_FAILURE);
}

long	ms(t_table *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit(clean(table));
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - table->start);
}
