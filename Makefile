# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 19:15:24 by oroy              #+#    #+#              #
#    Updated: 2023/11/17 16:48:23 by oroy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

INCDIR		:= inc
OBJDIR		:= obj
SRCDIR		:= src

SRC			:= $(wildcard $(SRCDIR)/*.c)
OBJ			:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

PROGRESS	:= progress

AR			:= ar rcs
CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra
RM			:= rm -rf

COLOR_GREEN	:= \033[0;32m
COLOR_RED	:= \033[0;31m
COLOR_BLUE	:= \033[0;34m
COLOR_END	:= \033[0m

# SRC_TOTAL	:= $(words $(SRC))
# PROGRESS	:= 0

# ********************************** RULES *********************************** #

all: $(NAME)
	@$(MAKE) ready

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR):
	@mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
# @$(MAKE) progress_update

clean:
	@$(RM) $(OBJDIR)
	@echo
	@echo "$(COLOR_RED)-> Object files deleted$(COLOR_END)"
	@echo

fclean: clean
	@$(RM) $(NAME)
	@echo "$(COLOR_RED)-> EXEC file deleted$(COLOR_END)"
	@echo

re: fclean all
	
# ******************************** Progress ********************************* #

# progress_update:
# 	$(eval PROGRESS=$(shell echo $$(($(PROGRESS) + 1))))
# 	@echo -ne "Compiling... $(PROGRESS)/$(SRC_TOTAL) files ($(shell echo $$((($(PROGRESS)*100)/$(SRC_TOTAL))))%) \r"

ready:
	@echo
	@echo "█▀█ █░█ █ █░░ █▀█   █▀█ █▀▀ ▄▀█ █▀▄ █▄█   █"
	@echo "█▀▀ █▀█ █ █▄▄ █▄█   █▀▄ ██▄ █▀█ █▄▀ ░█░   ▄"
	@echo

# ******************************** VALGRIND ********************************* #

PARAM = 4 410 200 200

val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes -s \
	./$(NAME) $(PARAM)