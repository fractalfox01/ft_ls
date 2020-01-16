NAME= ft_ls

TEST= test

SRC := $(addsuffix .c, src/verify_options src/set_options src/init_utils \
	src/option_utils src/verify_args src/set_arguments src/ls_utils \
	src/ls_stack_utils src/sort_utils src/time_sort_forward src/time_sort_reverse \
	src/sort_stack_utils)

INC := $(addsuffix .h, includes/ft_ls includes/ft_printf includes/get_next_line \
	includes/libft)

FLAGS= -Wall -Werror -Wextra

$(NAME):
	gcc -g $(FLAGS) libft.a $(SRC) src/main.c -o ft_ls

$(TEST):
	gcc $(FLAGS) -g $(SRC) src/recurse_example.c libft.a -o test

all: $(NAME)

clean:
	rm ft_ls 2>/dev/null | echo "Gone"
	rm -rf ft_ls.dSYM/ 2>/dev/null | echo "Gone"
	rm test 2>/dev/null | echo "Gone"
	rm -rf test.dSYM/ 2>/dev/null | echo "Gone"

fclean: clean

fc: fclean

re: fclean all

add:
	git add makefile $(SRC) $(INC)
	git status

push:
	git commit -m "auto push"
	git push
