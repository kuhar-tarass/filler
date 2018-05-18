/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:48:21 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/18 18:40:02 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include "filler.h"

void		printarr(short **map, t_map *p, int fd)
{
	int	i;
	int	j;
	
	i = -1;
	while(++i < p->y)
	{
		j = -1;
		while(++j < p->x)
			dprintf(fd, "%2d ", map[i][j]);
		//	printf("%2d ", map[i][j]);
		dprintf(fd, "|\n");
		//printf("\n");
	}
	return ;
}
void		printpice(short **map, t_pice *p, int fd)
{
	int	i;
	int	j;
	
	i = -1;
	while(++i < p->y)
	{
		j = -1;
		while(++j < p->x)
			dprintf(fd, "%3d ", map[i][j]);
			//printf( "%3d ", map[i][j]);
		dprintf(fd, "\n");
		//printf( "\n");
	}
	return ;
}

t_map	*readparam(void)
{
	t_map	*p;
	char		*s;
	int			i;

	s = 0;
	p = malloc(sizeof(t_map));
	get_next_line(0,&s);
	p->player = s[10] == '1' ? 'O' : 'X';
	free(s);
	get_next_line(0, &s);
	p->x = 0;
	p->y = 0;
	i = 8;
	while (ft_isdigit(s[i]))
		p->y = p->y * 10 + s[i++] - 48;
	i++;
	while (ft_isdigit(s[i]))
		p->x = p->x * 10 + s[i++] - 48;
	free(s);
	return(p);
}

t_map		**fillmap(t_map *p)
{
	int		i;
	int		j;
	short	m;

	m = (p->x + p->y);
	while(m-- > 0 && (i = -1))
		while(++i < p->y && (j = -1))
			while(++j < p->x)
				if (p->map[i][j] != 0 && p->map[i][j] != -1)
					p->map[i][j] = 1 + minf(
						(i - 1 > 0		? p->map[i - 1][j] : -2),
						(j - 1 > 0		? p->map[i][j - 1] : -2),
						(i + 1 < p->y	? p->map[i + 1][j] : -2),
						(j + 1 < p->x	? p->map[i][j + 1] : -2));
	return (p);
}


t_map		**readmap(t_map *p)
{
	int		i;
	int		j;
	char	*s;

	p->map = malloc(sizeof(short *) * (p->y));
	i = -1;
	while(++i < p->y)
	{
		p->map[i] = malloc(sizeof(short) * (p->x));
		get_next_line(0, &s);
		j = -1;
		while (++j < p->x)
		if (s[j + 4] != '.')
			p->map[i][j] = (ft_toupper(s[j + 4]) == p->player) ? -1 : 0;
		else
			p->map[i][j] = -2;
		free(s);
	}
	return (fillmap(p));
}

short		minf(short t1, short t2, short t3, short t4)
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


t_pice		*readpiceparam(void)
{
	t_pice	*pice;
	int		i;
	char	*s;

	pice = malloc(sizeof(t_pice));
	get_next_line(0, &s);
	i = 6;
	pice->x = 0; 
	pice->y = 0; 
	while( ft_isdigit(s[i]))
		pice->y = pice->y * 10 + s[i++] - 48;
	i++;
	while( ft_isdigit(s[i]))
		pice->x = pice->x * 10 + s[i++] - 48;
	free(s);
	return (pice);
}

t_pice		*readpice(t_pice *p)
{
	short	**pice;
	int		i;
	int		j;
	char	*s;

	pice = malloc(sizeof(short *) * p->y);
	i = -1;
	while(++i < p->y)
	{
		pice[i] = malloc(sizeof(short) * (p->x));
		get_next_line(0, &s);
		j = -1;
		while (++j < p->x)
			pice[i][j] = s[j] == '*' ? 1 : 0;
		free(s);
	}
	p->pice = pice;
	return (p);
}

int			count(t_pice *p, t_map *m, int x, int y)
{
	int i;
	int j;
	int sum;
	int dots;

	dots == 0;
	sum = 0;
	i = -1;
	while (++i < p->y && j == -1)
		while (++j < p->x)
			if ((p->pice)[i][j])
			{
				if ((m->map)[i + y][j + x] == 0)
					return (0);
				if ((m->map)[i + y][j + x] == -1)
					dots++;
				else
					sum  += (m->map)[i + y][j + x];
			}
	return (dots == 1 ? sum : 0);
}

t_pice		*placepice(t_pice *p, t_map *m)
{
	int i;
	int j;
	int max;
	int tmp;

	i = -1;
	while(++i < (m->y - p->y) && (j = -1))
		while(++j < m->x - p->x)
		{
			tmp = count(p, m, j, i);
			if (max > tmp)
			{
				p->
			}
		}
}

int			main(int argc, char *argv[])
{
	char		*s;
	char		buf[100];
	int			d;
	t_map	*p;
	t_pice		*pc;

	d = open("./1.txt", O_RDWR);
	p = readparam();
	get_next_line(0,&s);
	
	{
		while (0 < read(d, buf, 1))
			;
	p = readmap (p);
	pc = readpiceparam();
	pc = readpice(pc);
		printpice(pc->pice, pc, d);
		dprintf(d, "my player: %c \n", p->player);
		dprintf(d, "___________________________________________________________\n\n");
		close(d);
	}
	free(s);
//	system("leaks a.out");
	return 0;
}
