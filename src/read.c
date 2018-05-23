/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:34:38 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/23 19:50:58 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_map		*readplayer(void)
{
	char	*s;
	t_map	*p;

	p = malloc(sizeof(t_map));
	get_next_line(0, &s);
	p->player = s[10] == '1' ? 'O' : 'X';
	free(s);
	return (p);
}

t_map		*readparam(t_map *p)
{
	char		*s;
	int			i;

	s = 0;
	if (!get_next_line(0, &s))
		return (0);
	p->x = 0;
	p->y = 0;
	i = 8;
	while (ft_isdigit(s[i]))
		p->y = p->y * 10 + s[i++] - 48;
	i++;
	while (ft_isdigit(s[i]))
		p->x = p->x * 10 + s[i++] - 48;
	free(s);
	return (p);
}

t_map		*readmap(t_map *p)
{
	int		i;
	int		j;
	char	*s;

	p->map = malloc(sizeof(short *) * (p->y));
	i = -1;
	while (++i < p->y)
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
	return (p);
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
	while (ft_isdigit(s[i]))
		pice->y = pice->y * 10 + s[i++] - 48;
	i++;
	while (ft_isdigit(s[i]))
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
	while (++i < p->y)
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
