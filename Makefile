# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 19:15:24 by oroy              #+#    #+#              #
#    Updated: 2023/11/15 17:14:40 by oroy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

INCDIR	:= inc
OBJDIR	:= obj
SRCDIR	:= src

SRC		:= $(wildcard $(SRCDIR)/*.c)
OBJ		:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# ITERATION 	:= 10
# TOTAL 		:= $(words $(SRC))
# STEP		:= $(TOTAL) / $(ITERATION)
# CURRENT		:= 0

AR		:= ar rcs
CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
RM		:= rm -rf

# ********************************** RULES *********************************** #

# all: progress $(NAME)
all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
# @$(MAKE) ready

$(OBJDIR):
	@mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -c $(CFLAGS) $< -o $@
# @$(MAKE) update_progress

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

# ******************************** Animation ********************************* #

# progress:
# 	@echo -n "Loading... ["

# update_progress:
# 	@$(eval CURRENT=$(shell expr $(CURRENT) + 1))
# 	@if [ $(CURRENT) -ge $(STEP) ]; then \
# 		$(eval CURRENT=0); \
# 		echo -n "/"; \
# 	fi

# ready:
# 	@echo "]"
# 	@echo
# 	@echo "█▀█ █░█ █ █░░ █▀█   █▀█ █▀▀ ▄▀█ █▀▄ █▄█   █"
# 	@echo "█▀▀ █▀█ █ █▄▄ █▄█   █▀▄ ██▄ █▀█ █▄▀ ░█░   ▄"

# ******************************** VALGRIND ********************************* #

PARAM = 4 410 200 200

val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes -s \
	./$(NAME) $(PARAM)