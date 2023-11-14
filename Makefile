# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 19:15:24 by oroy              #+#    #+#              #
#    Updated: 2023/11/14 17:21:31 by oroy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

INCDIR	:= inc
OBJDIR	:= obj
SRCDIR	:= src

SRC		:= $(wildcard $(SRCDIR)/*.c)
OBJ		:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

AR		:= ar rcs
CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra -g
RM		:= rm -rf

# ********************************** RULES *********************************** #

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# ******************************** VALGRIND ********************************* #

PARAM = 4 410 200 200

val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes -s \
	./$(NAME) $(PARAM)