# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 19:15:24 by oroy              #+#    #+#              #
#    Updated: 2023/11/17 01:02:25 by olivierroy       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

INCDIR		:= inc
OBJDIR		:= obj
SRCDIR		:= src

SRC			:= $(wildcard $(SRCDIR)/*.c)
OBJ			:= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

OBJ_COUNT	:= $(wildcard $(OBJDIR)/*.o)
SRC_TOTAL 	:= $(words $(SRC))
OBJ_TOTAL 	:= $(words $(OBJ_COUNT))

AR			:= ar rcs
CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra
RM			:= rm -rf

# ********************************** RULES *********************************** #

all: $(NAME)
	@$(MAKE) ready

$(NAME): progress_check
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR):
	@mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@$(MAKE) progress_update

clean:
	@$(RM) $(OBJDIR)
	@echo
	@echo -\> OBJ files cleaned up
	@echo

fclean: clean
	@$(RM) $(NAME)
	$(eval OBJ_TOTAL=0)
	@echo -\> EXEC file cleaned up
	@echo

re: fclean all

# ******************************** Progress ********************************* #

progress_check:
	@if [ $(OBJ_TOTAL) != $(SRC_TOTAL) ]; then \
		$(MAKE) progress; \
	fi

progress: progress_start $(OBJDIR) $(OBJ) progress_done

progress_start: 
	@echo
	@echo -n Compiling \[

progress_update:
	@echo -n .

progress_done:
	@echo \]

ready:
	@echo
	@echo █▀█ █░█ █ █░░ █▀█   █▀█ █▀▀ ▄▀█ █▀▄ █▄█   █
	@echo █▀▀ █▀█ █ █▄▄ █▄█   █▀▄ ██▄ █▀█ █▄▀ ░█░   ▄
	@echo

# ******************************** VALGRIND ********************************* #

PARAM = 4 410 200 200

val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes -s \
	./$(NAME) $(PARAM)