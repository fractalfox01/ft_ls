NAME= ft_ls

TEST= test

SRC := $(addsuffix .c, src/verify_options src/set_options src/init_utils1 src/init_utils2\
	src/option_utils src/verify_args src/set_arguments src/ls_utils \
	src/ls_stack_utils src/sort_utils1 src/sort_utils2 src/time_sort_forward src/time_sort_reverse \
	src/sort_stack_utils src/print_utils1 src/print_utils2 src/ls_get_info1 src/ls_get_info2 src/ls_get_info3 \
	src/verify_arg_helpers src/init_utils3 src/ls_padding_utils1 src/ls_padding_utils2 \
	src/time_sort_utils1 src/time_sort_utils2)

INC := $(addsuffix .h, includes/ft_ls includes/libft)

FLAGS= -Wall -Werror -Wextra

$(NAME):
	@make -C libft/ re
	@cp libft/libft.a .
	@gcc -g $(FLAGS) $(SRC) libft.a src/main.c -o ft_ls

$(TEST):
	gcc $(FLAGS) -g $(SRC) libft.a src/recurse_example.c -o test

all: $(NAME)

clean:
	rm ft_ls 2>/dev/null | echo "Gone"
	rm -rf ft_ls.dSYM/ 2>/dev/null | echo "Gone"
	rm test 2>/dev/null | echo "Gone"
	rm -rf test.dSYM/ 2>/dev/null | echo "Gone"
	@make -C libft/ clean

fclean: clean
	@rm libft.a | echo "libft.a gone"
	@make -C libft/ fc

fc: fclean

re: fclean all

add:
	git add makefile $(SRC) $(INC)
	git status

push:
	git commit -m "auto push"
	git push
