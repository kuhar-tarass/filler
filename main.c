#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "visual.h"
#include "libft/libft.h"
#include <time.h>

t_area	*writespace()
{
	t_area	*n;
	int i;
	int j;

	char *s;
	n = malloc(sizeof(t_area));
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
	printf("   ");
	j = n->x + 1;
	while(j-- > -1)
		printf("#");
	printf("\n");

	i = n->y + 1;
	while(i-- > 1)
	{
		printf("%03d#", ((n->y) - i));
		set_display_atrib(F_BLACK);
		j = n->x + 1;
		while(j-- > 1)
			printf(".");
		resetcolor();
		printf("#\n");
	}
	printf("   ");
	j = n->x + 1;
	while(j-- > -1)
		printf("#");
	printf("\n");
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
				if (*s == 'X')
					set_display_atrib(F_RED);
				if (*s == 'O')
					set_display_atrib(F_GREEN);
				if (*s == 'o' || *s == 'x')
				{
					set_display_atrib(BRIGHT);
					set_display_atrib(B_RED);
				}
				if (*s != '.')
					printf("%c", *s);
				s++;
				resetcolor();
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
	i = 6;
	while (ft_isdigit(s[i]))
		pice->y = pice->y * 10 + s[i++] - 48;
	i++;
	while (ft_isdigit(s[i]))
		pice->x = pice->x * 10 + s[i++] - 48;
	return (pice);
}

void	printpice(t_area *n, t_f *pice)
{
	int i;
	char *s;

	i = pice->y;
	while (i > 0)
	{
		gotoxy(n->x + 10,  (pice->y - i) + 2);
		get_next_line(0, &s);
		while(*s)
		{
			if (*s == '*')
				set_display_atrib(F_YELLOW);
			if (*s != '.')
				set_display_atrib(F_BLACK);
			printf("%c", *s);
			s++;
		}
		printf("\n");
		i--;
	}
	resetcolor();
	gotoxy(n->x + 1, n->y + 1)
}

int main (int ac, char **av)
{
	char *s;
	t_area	*n;
	t_f		*pice;

	visible_cursor(0);
	home();
	n = writespace();
	while(get_next_line(0, &s))
	{
		if (ft_strstr(s, "0123456789"))
			printmap(n);
		/*if (ft_strstr(s, "Piece"))
		{
			pice = readpice(s);
			printpice(n,pice);
		}*/
	}
	visible_cursor(1);

	return (0);
}
