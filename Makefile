CC = gcc

NAME = ft_ls

FT_LS_LIBRARY = ft_ls.a

TESTS_LIBRARY = tests.a

LIBFT = libft/

FLAGS = -Wall -Wextra -Werror

FT_LS_SRCS =  $(shell find ./srcs -type f -name '*.c')

FT_LS_OBJS = $(FT_LS_SRCS:.c=.o)

TESTS_SRCS =  $(shell find ./tests -type f -name '*.c')

TESTS_OBJS = $(TESTS_SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(FT_LS_OBJS) buildlibft buildft_lslib 
	$(CC) main.c -g -fsanitize=address $(FT_LS_LIBRARY) libft/libft.a -o $(NAME)

buildlibft:
	make -C $(LIBFT) all

buildft_lslib:
	@ar rc $(FT_LS_LIBRARY) $(FT_LS_OBJS)
	@ranlib $(FT_LS_LIBRARY)
	@ar -t $(FT_LS_LIBRARY)

tests: $(TESTS_OBJS) all buildft_lstest
	$(CC) tests/main.c $(TESTS_LIBRARY) libft/libft.a ft_ls.a -o ft_tests
	
buildft_lstest:
	@ar rc $(TESTS_LIBRARY) $(TESTS_OBJS)
	@ranlib $(TESTS_LIBRARY)
	@ar -t $(TESTS_LIBRARY)

docker:
	@docker build -t ft_ls_image .
	@docker run -t -i -v /Users/lucasweglarz/ft_ls:/ft_ls ft_ls_image /bin/bash

clean:
	rm -rf $(FT_LS_OBJS) $(FT_LS_LIBRARY)
	rm -rf $(TESTS_OBJS) $(TESTS_LIBRARY)

fclean:	clean
	rm -rf $(NAME) 
	rm -rf ft_tests
	make -C $(LIBFT) fclean
	rm -rf test_ls.log

re: fclean all