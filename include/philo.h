/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:25:10 by aloimusa          #+#    #+#             */
/*   Updated: 2025/10/23 00:25:36 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "libft.h"
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define THINK "%l %d is thinking\n"
# define SLEEP "%l %d is sleeping\n"
# define EAT "%l %d is eating\n"
# define FORK_ONE "%l %d has taken a fork\n"
# define FORK_TWO "%l %d has taken a fork\n%l %d is eating\n"
# define ONE_PHILO "0 1 is thinking\n0 1 has taken a fork\n"
# define DEAD "%l %d died\n"
# define USAGE_MSG \
	"./philo <philos> <die_time> <eat_time> \
<sleep_time> [times_to_eat]\n"

typedef struct s_table	t_table;

typedef struct s_philo
{
	long				ate_at;
	pthread_t			thread;
	t_table				*table;
	bool				dhand;
	short				chair;
}						t_philo;

typedef struct s_table
{
	bool				*fork;
	bool				alive;
	short				finished;
	pthread_mutex_t		*mutex;
	t_philo				*philo;
	short				chairs;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_must_eat;
	long				start;
}						t_table;

long					get_long(pthread_mutex_t *mutex, long *val);
void					set_long(pthread_mutex_t *mutex, long *val,
							long new_val);
bool					get_bool(pthread_mutex_t *mutex, bool *val);
void					set_bool(pthread_mutex_t *mutex, bool *val,
							bool new_val);
long					ms(t_table *table);
void					*exist(void *arg);
bool					observe(t_table *table);

#endif
