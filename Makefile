# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 19:15:24 by oroy              #+#    #+#              #
#    Updated: 2023/11/20 15:54:29 by oroy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

INCDIR		:= inc
OBJDIR		:= obj
SRCDIR		:= src

SRC			:= $(wildcard $(SRCDIR)/*.c)
OBJ			:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

AR			:= ar rcs
CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra
RM			:= rm -rf

COLOR_GREEN	:= \033[0;32m
COLOR_RED	:= \033[0;31m
COLOR_BLUE	:= \033[0;34m
COLOR_END	:= \033[0m

SPACE		:= space

# ********************************** RULES *********************************** #

all: $(SPACE) $(NAME)
	@$(MAKE) ready

$(NAME): $(OBJDIR) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Compiled: ./$(NAME)"
	@echo
	@echo

$(OBJDIR):
	@mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@echo "Compiled: $@"

clean:
	@$(RM) $(OBJDIR)
	@echo
	@echo "$(COLOR_RED)-> Object files cleaned$(COLOR_END)"
	@echo

fclean: clean
	@$(RM) $(NAME)
	@echo "$(COLOR_RED)-> Exec file cleaned$(COLOR_END)"
	@echo

re: fclean all

.PHONY: all clean fclean re ready

# ********************************* VISUAL ********************************** #

$(SPACE):
	@echo

ready:
	@echo "-------------------------------------------"
	@echo
	@echo "█▀█ █░█ █ █░░ █▀█   █▀█ █▀▀ ▄▀█ █▀▄ █▄█   █"
	@echo "█▀▀ █▀█ █ █▄▄ █▄█   █▀▄ ██▄ █▀█ █▄▀ ░█░   ▄"
	@echo
	@echo "-------------------------------------------"
	@echo

# ******************************** VALGRIND ********************************* #

PARAM = 4 410 200 200

val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes -s \
	./$(NAME) $(PARAM)