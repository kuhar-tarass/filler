/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:51:43 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/25 16:10:40 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	drawline(int j)
{
	char	s[j + 4];
	int		i;

	s[j + 4] = 0;
	s[0] = ' ';
	s[1] = ' ';
	s[2] = ' ';
	i = 2;
	while (i++ < j + 3)
		s[i] = '#';
	printf("%s", s);
}

void	writespace(t_area *n)
{
	int		i;
	char	*s;

	CLSCR();
	GOTOXY(0, 0);
	i = n->x + 1;
	printf("    ");
	while (i-- > 1)
		printf("%d", ((n->x) - i) % 10);
	printf("\n");
	drawline(n->x + 1);
	printf("\n");
	fill(n);
	drawline(n->x + 1);
	printf("\n");
}

void	fill(t_area *n)
{
	int j;
	int i;

	i = n->y + 1;
	while (i-- > 1)
	{
		printf("%03d#", ((n->y) - i));
		SET_COLOR(DIM);
		j = n->x + 1;
		while (j-- > 1)
			printf("*");
		RESETCOLOR();
		printf("#\n");
	}
}

void	printsymb(t_area *n, char *s)
{
	if (*s != '.')
	{
		if (*s == 'X')
			SET_COLOR(n->player ? F_GREEN : F_RED);
		else if (*s == 'O')
			SET_COLOR(n->player ? F_RED : F_GREEN);
		else if (*s == 'o' || *s == 'x')
		{
			SET_COLOR(BRIGHT);
			SET_COLOR(F_WHITE);
			SET_COLOR(B_YELLOW);
		}
		printf("%c", *s);
		RESETCOLOR();
	}
}

void	printmap(t_area *n)
{
	int		i;
	int		j;
	char	*s;

	i = n->y + 1;
	while (--i)
	{
		get_next_line(0, &s);
		s += 4;
		j = 5;
		while (*s)
		{
			GOTOXY(j++, (n->y - i) + 3);
			printsymb(n, s);
			s++;
		}
	}
}
