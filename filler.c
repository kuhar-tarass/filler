/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:48:21 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/16 22:22:33 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include "filler.h"


int	gnl(int	fd, char **s)
{
	//if(*s)
	//	free(*s);
	return(get_next_line(fd, s));
}

t_params	*readparam(void)
{
	t_params	*p;
	char		*s;
	int			i;

	s = 0;
	p = malloc(sizeof(t_params));
	//gnl(0,&s);
	//p->player = s[10];
	gnl(0, &s);
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
		gnl(0, &s);
		j = -1;
		while (++j < p->x)
		if (s[j + 4] != '.')
			map[i][j] = (s[j + 4] == 'X' || s[j + 4] == 'x') ? -1 : -2;
		else
			map[i][j] = 0;
	}
	return (map);
}

short		**fillmap(t_params *p, short **map)
{
	int	i;
	int	j;
	int	c;
	c = p->x + p->y ;
	while(c--)
	{
		i = -1;
		while(++i < p->y)
		{
			j = -1;
			while(++j < p->x)
				if (map[i][j] == -1)
					map[i][j]
		}
	}
}

void printarr(short **map, t_params *p, int fd)
{
	int	i;
	int	j;
	
	i = -1;
	while(++i < p->y)
	{
		j = -1;
		while(++j < p->x)
			printf( "%d	", map[i][j]);
		printf( "\n");
	}
	return ;
}


int		main(int argc, char *argv[])
{
	char		*s;
	int			d;
	t_params	*p;
	short		**map;

	p = readparam();
	gnl(0,&s);
	map = readmap (p);
	d = open("./1.txt", O_RDWR);
	printarr(map, p, d);
	dprintf(d, "x:%d	y:%d", p->x, p->y);
	close(d);

	return 0;
}
