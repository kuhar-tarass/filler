# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 16:30:15 by tkuhar            #+#    #+#              #
#    Updated: 2018/05/24 22:10:48 by tkuhar           ###   ########.fr        #
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

FLAGS=	-Wall -Wextra -Werror

NAME=	tkuhar.filler

SRC=	filler.c \
		read.c

INCLD=	./include

OBJ= $(SRC:%.c=%.o)


OK_STRING    =***	$(NAME) created		***

all: $(NAME)
	
$(NAME):
	@$(MAKE) -C ./src/libft
	gcc $(FLAGS) $(addprefix ./src/, $(SRC)) -o $(NAME) ./src/libft/libft.a ./src/libft/libftprintf.a -I ./include
	@printf "\n$(GREEN)$(OK_STRING)\n\n"
clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C ./src/libft
	@printf  "$(YELLOW)remove OBJ"
fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./src/libft
	@printf "$(YELLOW)remove OBJ$(COLOR_OFF)\n"
	@printf "$(RED)remove $(NAME)$(COLOR_OFF)\n"

visual:
	@gcc  $(addprefix ./src/, visual.c) -o visual ./src/libft/libft.a ./src/libft/libftprintf.a -I ./include
	@printf "\n$(GREEN)DONE$(COLOR_OFF)\n\n"

rmvisual:
	@rm -f visual

revisual: rmvisual visual

re: fclean all