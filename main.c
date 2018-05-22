#include <stdio.h>
#include <stdlib.h>
#include "visual.h"
#include "libft/libft.h"
#include "printf/ft_printf.h"
int main (int ac, char **av)
{
	char *s;
	int i;
	int y;
	int x;

	home();
	while (get_next_line(0, &s))
		if (ft_strstr(s, "Plateau"))
		{
			x = 0;
			y = 0;
			clrscr();
			gotoxy(0,0);
			i = 8;
			while (ft_isdigit(s[i]))
				y = y * 10 + s[i++] - 48;
			i++;
			while (ft_isdigit(s[i]))
				x = x * 10 + s[i++] - 48;
			get_next_line(0, &s);
			printf ("%s\n", s);
			while (y--)
			{
				get_next_line(0, &s);
				while(*s++)
				{
					if (*s == 'X')
						set_display_atrib(F_RED);
					if (*s == 'O')
						set_display_atrib(F_GREEN);
					if (*s == 'o' || *s == 'x')
						set_display_atrib(F_YELLOW);
					if (*s == '.')
						set_display_atrib(F_BLACK);
					printf("%c", *s);
					//write(1, s, 1);
					resetcolor();
				}
				printf("\n");
			}
		}
	return 0;
}
