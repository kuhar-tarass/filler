#ifndef VISUAL_H
# define VISUAL_H

# define HOME() 			printf(ESC "[H")
# define CLSCR()			printf(ESC "[2J")
# define GOTOXY(x,y)		printf(ESC "[%d;%dH", y, x);
# define VISIBLE_CURSOR(o)	printf(ESC "[?25%c", (o ? 'h' : 'l'));

# define RESETCOLOR()				printf(ESC "[0m")
# define SET_COLOR(color)	printf(ESC "[%dm",color)
# define ESC "\033"

# define RESET		0
# define BRIGHT		1
# define DIM		2
# define UNDERSCORE	4
# define BLINK		5
# define REVERSE	7
# define HIDDEN		6

# define F_BLACK	30
# define F_RED		31
# define F_GREEN	32
# define F_YELLOW	33
# define F_BLUE		34
# define F_MAGENTA 	35
# define F_CYAN		36
# define F_WHITE	37

# define B_BLACK	40
# define B_RED		41
# define B_GREEN	42
# define B_YELLOW	43
# define B_BLUE		44
# define B_MAGENTA 	45
# define B_CYAN		46
# define B_WHITE	47

typedef struct	s_area
{
	char		player;
	int			x;
	int			y;
}				t_area;

typedef struct	s_f
{
	int			x;
	int			y;
}				t_f;

#endif
