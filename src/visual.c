/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:37:26 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/25 16:13:44 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

t_area	*readplayer(void)
{
	t_area	*n;
	int		i;
	char	*s;

	n = malloc(sizeof(t_area));
	i = 6;
	while (i-- && get_next_line(0, &s))
		free(s);
	get_next_line(0, &s);
	if (strstr(s, "tkuhar.filler"))
		n->player = 0;
	else
		n->player = 1;
	return (n);
}

t_area	*getareasize(t_area *n)
{
	int		i;
	char	*s;

	while (get_next_line(0, &s))
		if (ft_strstr(s, "Plateau"))
			break ;
		else
			free(s);
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

void	drawresult(t_area *n, char *s)
{
	int		o;
	int		x;

	o = atoi(&s[9]);
	get_next_line(0, &s);
	free(s);
	x = atoi(&s[9]);
	setlocale(LC_ALL, "");
	SET_COLOR(n->player ? F_RED : F_GREEN);
	o > x ? printf("O: %d %C ***WINNER*** %C\n", o, 127942, 127942) :
		printf("O: %d\n", o);
	SET_COLOR(n->player ? F_GREEN : F_RED);
	x > o ? printf("X: %d %C ***WINNER*** %C\n", x, 127942, 127942) :
		printf("X: %d\n", x);
	RESETCOLOR();
}

int		main(int ac, char **av)
{
	char	*s;
	t_area	*n;

	VISIBLE_CURSOR(0);
	HOME();
	n = readplayer();
	n = getareasize(n);
	writespace(n);
	while (get_next_line(0, &s))
	{
		if (ft_strstr(s, "0123456789"))
		{
			printmap(n);
			usleep(ac == 2 && ft_atoi(av[1]) ? 10000 : 0);
		}
		if (ft_strstr(s, "== O"))
		{
			drawresult(n, s);
			break ;
		}
		GOTOXY(0, n->y + 5);
	}
	VISIBLE_CURSOR(1);
	return (0);
}
