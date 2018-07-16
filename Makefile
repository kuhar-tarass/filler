# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 16:30:15 by tkuhar            #+#    #+#              #
#    Updated: 2018/05/25 15:59:40 by tkuhar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_OFF=\033[0m#			# Text Reset
BLACK	=\033[0;30m#		# Black
RED		=\033[0;31m#		# Red
GREEN	=\033[0;32m#		# Green
YELLOW	=\033[0;33m#		# Yellow
BLUE	=\033[0;34m#		# Blue
PURPLE	=\033[0;35m#		# Purple
CYAN	=\033[0;36m#		# Cyan
WHITE	=\033[0;37m#		# White

CC=		gcc

FLAGS=	#-Wall -Wextra -Werror

NAME=	tkuhar.filler
NAME2=	tkuhar2.filler



SRCNAME=	filler.c \
			read.c

INCLD=	./include

OBJ= $(SRC:%.c=%.o)

SRC=$(addprefix ./src/, $(SRCNAME))

LIBFT= ./src/libft/libft.a
LIBFTPRINTF= ./src/libft/libftprintf.a

OK_STRING    =***	$(NAME) created		***

all: $(NAME)
	
$(NAME): $(LIBFT)
	gcc $(FLAGS) $(SRC) -o $(NAME)  $(LIBFTPRINTF)  $(LIBFT) -I ./include
	@printf "\n$(GREEN)$(OK_STRING)\n\n"

second: $(LIBFT) 
	gcc $(FLAGS) $(SRC) -o $(NAME2) $(LIBFTPRINTF)  $(LIBFT) -I ./include
	@printf "\n$(GREEN)$(OK_STRING)\n\n"

$(LIBFT) $(LIBFTPRINTF): 
	@$(MAKE) -C ./src/libft


clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C ./src/libft
	@printf  "$(YELLOW)remove OBJ"

fclean:
	@printf "$(YELLOW)remove OBJ$(COLOR_OFF)\n"
	@$(MAKE) fclean -C ./src/libft
	@rm -f $(OBJ)
	@printf "$(RED)remove $(NAME)$(COLOR_OFF)\n"
	@rm -f $(NAME)
	@printf "$(RED)remove $(NAME2)$(COLOR_OFF)\n"
	@rm -f $(NAME2)

visual: $(LIBFT) $(LIBFTPRINTF)
	@gcc $(FALGS) ./src/visual.c ./src/visual2.c -o visual ./src/libft/libftprintf.a ./src/libft/libft.a -I ./include
	@printf "\n$(GREEN)DONE$(COLOR_OFF)\n\n"

rmvisual:
	@rm -f visual

revisual: rmvisual visual

re: fclean all