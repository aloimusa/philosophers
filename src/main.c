/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:29:24 by aloimusa          #+#    #+#             */
/*   Updated: 2025/12/15 15:29:25 by aloimusa         ###   ########.fr       */
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
		|| !table->time_to_sleep || (av[5] && !table->times_must_eat))
		exit(EXIT_SUCCESS);
	if (table->chairs == 1)
		if (printf(ONE_PHILO) && usleep(table->time_to_die * 1000) == 0)
			exit(!(bool)(printf(ONE_PHILO_DEAD, table->time_to_die)));
	table->fork = malloc(table->chairs * sizeof(bool));
	if (!table->fork)
		exit(clean(table));
	table->mutex = malloc((table->chairs * 2 + 2) * sizeof(pthread_mutex_t));
	if (!table->mutex)
		exit(clean(table));
	table->philo = malloc(table->chairs * sizeof(t_philo));
	if (!table->philo)
		exit(clean(table));
	table->alive = true;
	table->finished = 0;
}

static void	sit_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->chairs)
		table->fork[i] = true;
	i = -1;
	while (++i < table->chairs * 2 + 2)
		if (pthread_mutex_init(&table->mutex[i], NULL) == -1)
			exit(clean(table));
	i = -1;
	while (++i < table->chairs)
	{
		table->philo[i].dhand = (bool)(i % 2);
		table->philo[i].table = table;
		table->philo[i].chair = i;
		table->philo[i].ate_at = ms(table);
		table->philo[i].thread = 0;
		if (pthread_create(&table->philo[i].thread, NULL, exist,
				&table->philo[i]) == -1)
			exit(clean(table));
	}
}

static int	clean(t_table *table)
{
	int	i;

	if (table)
	{
		if (table->philo)
		{
			i = -1;
			while (++i < table->chairs && table->philo[i].thread != 0)
				pthread_join(table->philo[i].thread, NULL);
			free(table->philo);
		}
		if (table->mutex)
		{
			i = -1;
			while (++i < table->chairs * 2 + 2)
				pthread_mutex_destroy(&table->mutex[i]);
			free(table->mutex);
		}
		if (table->fork)
			free(table->fork);
	}
	return (EXIT_FAILURE);
}

long	ms(t_table *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit(clean(table));
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - table->start);
}
