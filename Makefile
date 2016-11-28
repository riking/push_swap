# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/09 19:11:26 by kyork             #+#    #+#              #
#    Updated: 2016/11/27 17:41:12 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap

COMMONSRC	+= input.c do_op.c print.c
COMMONHDR	= ps_stack.h

SOLVESRC	+= 
SOLVEHDR	=

CHECKSRC	+= main.c parse.c
CHECKHDR	= 

COMMONOBJS	= $(addprefix build/common-, $(COMMONSRC:.c=.o))
SOLVEOBJS	= $(addprefix build/solve-, $(SOLVESRC:.c=.o))
CHECKOBJS	= $(addprefix build/check-, $(CHECKSRC:.c=.o))

COMMONHEAD	= $(addprefix srcs/, $(COMMONHDR))
SOLVEHEAD	= $(addprefix srcs/, $(SOLVEHDR))
CHECKHEAD	= $(addprefix srcs/, $(CHECKHDR))

LIBS		= libft/libft.a

CFLAGS		+= -Wall -Wextra -Wmissing-prototypes
#CFLAGS		= -Wall -Wextra -Wfloat-equal -Wundef -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors
CFLAGS		+= -I includes/ -I srcs/
LDFLAGS		+= -Wall -Wextra

ifneq ($(WERROR), 0)
	CFLAGS += -Werror
	LDFLAGS += -Werror
endif

ifdef DBUG
	CFLAGS += -fsanitize=address -g
	LDFLAGS += -fsanitize=address -g
endif

ifdef RELEASE
	CFLAGS += -O2
	LDFLAGS += -O2
endif

.PHONY: all clean fclean re

all: checker push_swap

push_swap: $(COMMONOBJS) $(SOLVEOBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^
	@printf "\e[32m\e[1m[OK]\e[m $@\n"

checker: $(COMMONOBJS) $(CHECKOBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^
	@printf "\e[32m\e[1m[OK]\e[m $@\n"

libft/libft.a: libft/.git/refs/heads/master
	$(MAKE) -C libft libft.a

libft/.git/refs/heads/master:
	# ignore

clean:
	rm -rf build
	$(MAKE) -C libft clean
	@printf "\e[33m\e[1m[CLEAN]\e[m $$(basename $$(pwd))\n"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	@printf "\e[33m\e[1m[FCLEAN]\e[m $$(basename $$(pwd))\n"

re: fclean
	$(MAKE) all

build:
	mkdir -p build

build/common-%.o: srcs/%.c $(COMMONHEAD) | build
	$(CC) $(CFLAGS) -c -o $@ $<

build/solve-%.o: srcs/solve/%.c $(COMMONHEAD) $(SOLVEHEAD) | build
	$(CC) $(CFLAGS) -c -o $@ $<

build/check-%.o: srcs/check/%.c $(COMMONHEAD) $(CHECKHEAD) | build
	$(CC) $(CFLAGS) -c -o $@ $<

