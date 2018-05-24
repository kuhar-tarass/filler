#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "visual.h"
#include "libft.h"
#include <fcntl.h>
#include <locale.h>

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

void	drawline(int j)
{
	char	s[j + 4];
	int		i;
	s[j + 4] = 0;
	s[0] = ' ';
	s[1] = ' ';
	s[2] = ' ';
	i = 2;
	while(i++ < j + 3)
		s[i] = '#';
	printf("%s", s);
}

t_area	*getareasize(t_area *n,char *s)
{
	int i;

	n->x = 0;
	n->y = 0;
	i = 8;
	while (ft_isdigit(s[i]))
		n->y = n->y * 10 + s[i++] - 48;
	i++;
	while (ft_isdigit(s[i]))
		n->x = n->x * 10 + s[i++] - 48;
	return (n);
}

t_area	*writespace(t_area *n)
{
	int i;
	int j;
	
	char *s;
	CLSCR();
	GOTOXY(0,0);
	while (get_next_line(0, &s))
		if (ft_strstr(s, "Plateau"))
		{
			n = getareasize(n, s);
			break ;
		}
		else
			free(s);
	i = n->x + 1;
	printf("    ");
	while(i-- > 1)
		printf("%d", ((n->x) - i)%10);
	printf("\n");
	drawline(n->x + 1);
	printf("\n");
	i = n->y + 1;
	while(i-- > 1)
	{
		printf("%03d#", ((n->y) - i));
		SET_COLOR(DIM);
		j = n->x + 1;
		while(j-- > 1)
			printf("*");
		RESETCOLOR();
		printf("#\n");
	}
	drawline(n->x + 1);
	printf("\n");
	return (n);
}

void	printmap(t_area *n)
{
	int i;
	int j;
	char *s;

	i = n->y + 1;
	while (--i)
	{
		get_next_line(0, &s);
		s += 4;
		j = 5;
		while(*s)
		{
			GOTOXY(j++,(n->y - i) + 3);
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
			s++;
		}
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
		GOTOXY(x, y + sy + 1);
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
		GOTOXY(n->x + 10, (pice->y - i) + 3);
		get_next_line(0, &s);
		while(*s)
		{
			if (*s == '*')
			SET_COLOR(F_YELLOW);
			if (*s == '.')
				SET_COLOR(DIM);
			printf("%c", '*');
			RESETCOLOR();
			s++;
		}
		i--;
	}
	GOTOXY(0 , n->y + 5);
}

void	printstep(char *s, t_area *n)
{
	GOTOXY(n->x + 10, 1);
	if(ft_strchr(s, 'X') && n->player)
		SET_COLOR(F_GREEN);
	else
		SET_COLOR(F_RED);
	printf("%s", ft_strchr(s, '('));
	RESETCOLOR();
	GOTOXY(0 , n->y + 5);
}

int main (int ac, char **av)
{
	char *s;
	t_area	*n;
	t_f		*pice;
	int		o;
	int		x;

	VISIBLE_CURSOR(0);
	HOME();
	n = readplayer();
	n = writespace(n);
	while(get_next_line(0, &s))
	{
		if (ft_strstr(s, "0123456789"))
			printmap(n);
		if (ft_strstr(s, "Piece"))
		{
			pice = readpice(s);
			printpice(n,pice);
		}
		/*if (ft_strstr(s, "<got"))
		{
			printstep(s, n);
		}*/
		if (ft_strstr(s, "== O"))
		{
			o = atoi(&s[9]);
			get_next_line(0, &s);
			free(s);
			x = atoi(&s[9]);
			setlocale(LC_ALL,"");
			SET_COLOR(n->player ? F_RED : F_GREEN);
			o > x ? printf("O: %d %C ***WINNER*** %C\n", o, 127942, 127942) :
				printf("O: %d\n", o);
			SET_COLOR(n->player ? F_GREEN : F_RED);
			x > o ? printf("X: %d %C ***WINNER*** %C\n", x, 127942, 127942) :
				printf("X: %d\n", x);
			RESETCOLOR();
			break ;
		}
		usleep( ac == 2 ? ft_atoi(av[1]): 0);
	}
	VISIBLE_CURSOR(1);
	return (ac * 0);
}
