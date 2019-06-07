#include "ft_ls.h"

void print_useage(void)
{
    ft_putstr(FT_GREEN);
    ft_putstr("useage function working!\n");
}

int main(int ac, char **av)
{
    if (ac == 1)
        print_useage();
    else
    {
        // do LS stuff here...!?!
    }
    return (0);
}