# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/09 19:11:26 by kyork             #+#    #+#              #
#    Updated: 2016/12/29 14:32:18 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap

COMMONSRC	+= input.c do_op.c op_info.c print.c stack.c

SOLVESRC	+= main.c optimize_path.c
SOLVESRC	+= path_step.c path_node.c path_solution.c path_solve.c
SOLVESRC	+= smallsort.c smallsort_3.c smallsort_4.c
SOLVESRC	+= merge_opcombine.c merge_solve.c merge_merge.c
SOLVESRC	+= pick_sort.c

CHECKSRC	+= main.c parse.c opt.c

COMMONOBJS	= $(addprefix build/common-, $(COMMONSRC:.c=.o))
SOLVEOBJS	= $(addprefix build/solve-, $(SOLVESRC:.c=.o))
CHECKOBJS	= $(addprefix build/check-, $(CHECKSRC:.c=.o))

LIBS		= libft/libft.a

CFLAGS		+= -Wall -Wextra -Wmissing-prototypes
#CFLAGS		= -Wall -Wextra -Wfloat-equal -Wundef -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors
CFLAGS		+= -I includes/ -I srcs/
LDFLAGS		+= -Wall -Wextra

ifndef NO_WERROR
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

ifeq ($(SHELL),zsh)
	PRINTF	= printf
else
	PRINTF  = $(shell which printf)
endif

.PHONY: all clean fclean re

all: checker push_swap

push_swap: $(COMMONOBJS) $(SOLVEOBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "\e[32m\e[1m[OK]\e[m $@\n" | tr '\\e' '\e'

checker: $(COMMONOBJS) $(CHECKOBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "\e[32m\e[1m[OK]\e[m $@\n" | tr '\\e' '\e'

libft/libft.a: libft/.git/refs/heads/master
	$(MAKE) -C libft libft.a

libft/.git/refs/heads/master:
	# ignore

clean:
	rm -rf build
	$(MAKE) -C libft clean
	@echo "\e[33m\e[1m[CLEAN]\e[m $$(basename $$(pwd))\n" | tr '\\e' '\e'

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	@echo "\e[33m\e[1m[FCLEAN]\e[m $$(basename $$(pwd))\n" | tr '\\e' '\e'

re: fclean
	$(MAKE) all

build:
	mkdir -p build

build/common-%.o: srcs/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $<

build/solve-%.o: srcs/solve/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $<

build/check-%.o: srcs/check/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $<

