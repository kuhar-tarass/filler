/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:48:21 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/17 22:54:22 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include "filler.h"

void		printarr(short **map, t_params *p, int fd)
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

t_params	*readparam(void)
{
	t_params	*p;
	char		*s;
	int			i;

	s = 0;
	p = malloc(sizeof(t_params));
	get_next_line(0,&s);
	p->player = s[10];
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

short		**readmap(t_params *p)
{
	short	**map;
	int		i;
	int		j;
	char	*s;

	map = malloc(sizeof(short *) * (p->y));
	i = -1;
	while(++i < p->y)
	{
		map[i] = malloc(sizeof(short) * (p->x));
		get_next_line(0, &s);
		j = -1;
		while (++j < p->x)
		if (s[j + 4] != '.')
			map[i][j] = (s[j + 4] == 'X' || s[j + 4] == 'x') ? 0 : -1;			//!need to be modified
		else
			map[i][j] = -2;
		free(s);
	}
	return (map);
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

short		**fillmap(t_params *p, short **map)
{
	int		i;
	int		j;
	short	m;

	m = p->x + p->y ;
	while(m-- > 0 && (i = -1))
		while(++i < p->y && (j = -1))
			while(++j < p->x)
				if (map[i][j] != 0 && map[i][j] != -1)
					map[i][j] = 1 + minf(
						map[i - 1 > 0 ? i - 1 : 0][j],
						map[i + 1 < p->y ? i + 1 : 0][j],
						map[i][j - 1 > 0? j - 1 : 0],
						map[i][j + 1 < p->x ? j + 1 : 0]);
	return (map);
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

short		**readpice(t_pice *p)
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
	return (pice);
}

int			main(int argc, char *argv[])
{
	char		*s;
	short		**map;
	short		**pice;
	int			d;
	t_params	*p;
	t_pice		*pc;

	p = readparam();
	get_next_line(0,&s);
	map = readmap (p);
	map = fillmap(p,map);
	pc = readpiceparam();
	pice = readpice(pc);
	
	
	
	d = open("./1.txt", O_RDWR);
	printpice(pice, pc, d);
	printarr(map, p, d);
	//dprintf(d, "x:	y:");
	close(d);
	
	
	free(s);
//	system("leaks a.out");
	return 0;
}
