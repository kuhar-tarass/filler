/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:42:43 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/23 19:42:45 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "visual.h"
#include "libft/libft.h"
#include <fcntl.h>

t_area	*readplayer()
{
	t_area	*n;
	int i;
	char *s;

	n = malloc(sizeof(t_area));
	i = 6;
	while (i-- && get_next_line(0,&s))
		free(s);
	get_next_line(0,&s);
	if (strstr(s, "tkuhar.filler"))
		n->player = 0;
	else
		n->player = 1;
	return (n);
}


t_area	*writespace(t_area *n)
{
	int i;
	int j;

	char *s;
	clrscr();
	while (get_next_line(0, &s))
		if (ft_strstr(s, "Plateau"))
		{
			n->x = 0;
			n->y = 0;
			clrscr();
			gotoxy(0,0);
			i = 8;
			while (ft_isdigit(s[i]))
				n->y = n->y * 10 + s[i++] - 48;
			i++;
			while (ft_isdigit(s[i]))
				n->x = n->x * 10 + s[i++] - 48;
			break ;
		}
	i = n->x + 1;
	printf("    ");
	while(i-- > 1)
		printf("%d", ((n->x) - i)%10);
	printf("\n");
	{	printf("   ");
		j = n->x + 1;
		while(j-- > -1)
			printf("#");
	}
	printf("\n");
	i = n->y + 1;
	while(i-- > 1)
	{
		printf("%03d#", ((n->y) - i));
		set_display_atrib(DIM);
		j = n->x + 1;
		while(j-- > 1)
			printf("*");
		resetcolor();
		printf("#\n");
	}
	{	printf("   ");
		j = n->x + 1;
		while(j-- > -1)
			printf("#");
		printf("\n");
	}
	return (n);
}

void	printmap(t_area *n)
{
	int i;
	int j;
	char *s;

		i = n->y;
		while (i)
		{
			get_next_line(0, &s);
			s += 4;
			j = 5;
			while(*s)
			{
				gotoxy(j++,(n->y - i) + 3);
				if (*s != '.')
				{
					if (*s == 'X')
						set_display_atrib(n->player ? F_GREEN : F_RED);
					else if (*s == 'O')
						set_display_atrib(n->player ? F_RED : F_GREEN);
					else if (*s == 'o' || *s == 'x')
					{
						set_display_atrib(BRIGHT);
						set_display_atrib(F_WHITE);
						set_display_atrib(B_YELLOW);
					}
					printf("%c", *s);
					resetcolor();
				}
				s++;
			}
			printf("\n");
			printf("\n");
			i--;
		}
}

t_f		*readpice(char *s)
{
	t_f  *pice;
	int i;

	pice = malloc (sizeof (pice));
	pice->x = 0;
	pice->y = 0;
	i = 6;
	while (ft_isdigit(s[i]))
		pice->y = pice->y * 10 + s[i++] - 48;
	i++;
	while (ft_isdigit(s[i]))
		pice->x = pice->x * 10 + s[i++] - 48;
	return (pice);
}

void	cleararea(int x, int y, int sx, int sy)
{
	int i;

	while (sy--)
	{
		gotoxy(x, y + sy);
		i = sx;
		while (i--)
			printf("%c", ' ');
	}
}

void	printpice(t_area *n, t_f *pice)
{
	int i;
	char *s;

	i = pice->y;
	cleararea(n->x + 10, 0, n->x, n->y);
	while (i > 0)
	{
		gotoxy(n->x + 10, i + 2);
		get_next_line(0, &s);
		while(*s)
		{
			if (*s == '*')
			set_display_atrib(F_YELLOW);
			if (*s == '.')
				set_display_atrib(DIM);
			printf("%c", '*');
			resetcolor();
			s++;
		}
		i--;
	}
}

int main (int ac, char **av)
{
	char *s;
	t_area	*n;
	t_f		*pice;

	visible_cursor(0);
	home();
	n = readplayer();
	n = writespace(n);
	int fd = open("./1.txt", O_RDWR);
	while(get_next_line(0, &s))
	{
		if (ft_strstr(s, "0123456789"))
			printmap(n);
		else if (ft_strstr(s, "Piece"))
		{
			pice = readpice(s);
			printpice(n,pice);
			gotoxy(0 , n->y + 5)
		}
		else if (ft_strstr(s, "== O"))
		{
			printf("%s\n", s);
			get_next_line(0, &s);
			printf("%s\n", s);
			break ;
		}
	}
	visible_cursor(1);

	return (0);
}
