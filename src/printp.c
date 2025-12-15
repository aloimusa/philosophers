/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:29:35 by aloimusa          #+#    #+#             */
/*   Updated: 2025/12/15 15:29:36 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	printf_flush(t_fprintf *f)
{
	ssize_t	wrote;

	if (f->len > 0)
	{
		wrote = write(f->fd, f->buffer, f->len);
		if (wrote == -1)
			f->ret = -1;
		else
			f->ret += wrote;
		f->len = 0;
	}
}

static void	printf_putchar(t_fprintf *f, char c)
{
	if (f->ret == -1)
		return ;
	if (f->len >= PIPE_BUF)
		printf_flush(f);
	f->buffer[f->len++] = c;
}

static void	printf_putnbr(t_fprintf *f, unsigned long long n, int is_signed)
{
	if (is_signed && (long long)n < 0)
	{
		printf_putchar(f, '-');
		n = -(long long)n;
	}
	if (n >= 10)
		printf_putnbr(f, n / 10, 0);
	printf_putchar(f, (n % 10) + '0');
}

static void	printf_putstr(t_fprintf *f, char *s)
{
	char	*str;
	size_t	i;

	if (s)
		str = s;
	else
		str = "(null)";
	i = -1;
	while (str[++i])
		printf_putchar(f, str[i]);
}

long	printp(const char *msg, const char *msg2, int chair, t_table *table)
{
	t_fprintf	f;
	long long	time;

	f.fd = STDOUT_FILENO;
	f.len = 0;
	f.ret = 0;
	time = ms(table);
	printf_putnbr(&f, time, false);
	printf_putchar(&f, ' ');
	printf_putnbr(&f, chair + 1, false);
	printf_putchar(&f, ' ');
	printf_putstr(&f, (char *)msg);
	if (msg2)
	{
		printf_putnbr(&f, time, false);
		printf_putchar(&f, ' ');
		printf_putnbr(&f, chair + 1, false);
		printf_putchar(&f, ' ');
		printf_putstr(&f, (char *)msg2);
	}
	if (f.ret != -1)
		printf_flush(&f);
	return (time);
}
