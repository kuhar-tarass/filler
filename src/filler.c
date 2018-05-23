/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:48:21 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/23 19:45:11 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static short		minf(short t1, short t2, short t3, short t4)
{
	int m11;
	int m22;

	t1 = t1 >= 0 ? t1 : 255;
	t2 = t2 >= 0 ? t2 : 255;
	t3 = t3 >= 0 ? t3 : 255;
	t4 = t4 >= 0 ? t4 : 255;
	m11 = t1 > t2 ? t2 : t1;
	m22 = t3 > t4 ? t4 : t3;
	m11 = m22 < m11 ? m22 : m11;
	if (m11 == 255)
		return (-3);
	return (m11);
}

static t_map		*fillmap(t_map *p)
{
	int		i;
	int		j;
	short	m;

	m = (p->x + p->y);
	while (m-- > 0 && (i = -1))
		while (++i < p->y && (j = -1))
			while (++j < p->x)
				if (p->map[i][j] != 0 && p->map[i][j] != -1)
					p->map[i][j] = 1 + minf(
						(i - 1 > 0 ? p->map[i - 1][j] : -2),
						(j - 1 > 0 ? p->map[i][j - 1] : -2),
						(i + 1 < p->y ? p->map[i + 1][j] : -2),
						(j + 1 < p->x ? p->map[i][j + 1] : -2));
	return (p);
}

static int			count(t_pice *p, t_map *m, int x, int y)
{
	int i;
	int j;
	int sum;
	int dots;

	dots = 0;
	sum = 0;
	i = -1;
	while (++i < p->y && (j = -1))
		while (++j < p->x)
			if ((p->pice)[i][j])
			{
				if (i + y < 0 || i + y >= m->y || j + x < 0 || j + x >= m->x)
					return (0);
				if ((m->map)[i + y][j + x] == 0)
					return (0);
				if ((m->map)[i + y][j + x] == -1)
					dots++;
				else
					sum = sum + (m->map)[i + y][j + x];
			}
	sum = sum > 0 ? sum : 999999;
	return (dots == 1 ? sum : 0);
}

static t_pice		*placepice(t_pice *p, t_map *m)
{
	int i;
	int j;
	int min;
	int tmp;

	min = 1000000;
	i = -p->y;
	while (++i < (m->y) && (j = -p->x))
		while (++j < m->x)
		{
			tmp = count(p, m, j, i);
			if (tmp && min > tmp)
			{
				min = tmp;
				p->x_ins = j;
				p->y_ins = i;
			}
		}
	return (min != 1000000 ? p : 0);
}

int			main(int argc, char *argv[])
{
	char		*s;
	t_map		*m;
	t_pice		*pc;

	m = readplayer();
	while (1)
	{
		m = readparam(m);
		get_next_line(0, &s);
		m = readmap(m);
		m = fillmap(m);
		pc = readpiceparam();
		pc = readpice(pc);
		if ((pc = placepice(pc, m)))
			ft_printf("%d %d\n", pc->y_ins, pc->x_ins);
		else
		{
			ft_printf("0 0\n");
			break ;
		}
		free(m->map);
		free(pc);
	}
	return (0);
}
