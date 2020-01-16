#include <fcntl.h>
#include <sys/stat.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <sys/xattr.h>
#include <dirent.h>
#include "../includes/ft_ls.h"

int         is_directory(char *name)
{
    struct stat st;

    lstat(name, &st);
    if (st.st_mode >= S_IFDIR && st.st_mode < S_IFBLK)
        return (1);
    return (0);
}

char        *join_path(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *tmp;
    char    *ret;

    i = ft_strlen(s1);
    j = ft_strlen(s2);
    if (ft_strcmp(s1, "/") != 0)
    {
        tmp = ft_strjoin(s1, "/");
        ret = ft_strjoin(tmp, s2);  
        ft_strdel(&tmp);
        return (ret);
    }
    ret = ft_strjoin(s1, s2);
    return (ret);
}

void    init_obj(t_obj *obj)
{
    obj->sort_total = 0;
    obj->dir = NULL;
    obj->entry = NULL;
    obj->dirs = NULL;
    obj->sort = NULL;
    obj->tmp = NULL;
    obj->i = 0;
    ft_bzero(obj->path2, 1024);
    obj->ptr = NULL;
    obj->merger = NULL;
}

void    save_all(t_opt *opt, t_obj *obj, char *name)
{
    obj->ptr = join_path(name, obj->entry->d_name);
    obj->i = ft_strlen(name) + ft_strlen(obj->entry->d_name) + 1;
    ft_memcpy(obj->path2, obj->ptr, obj->i);
    ft_strdel(&(obj->ptr));
    lstat(obj->path2, &(obj->st));
    if (obj->st.st_mode >= S_IFDIR && obj->st.st_mode < S_IFBLK) {
        if ((ft_strcmp(obj->entry->d_name, ".") == 0 || ft_strcmp(obj->entry->d_name, "..") == 0))
        {
            ft_bzero(obj->path2, 1024);
            obj->st.st_mode = 0;
        }
        else if (opt->f_recurs)
             obj->dirs = stack_push(&obj->dirs, obj->path2);
    }
    if (obj->entry->d_name[0] == '.')
    {
        if (opt->f_all)
        {
            obj->sort_total++;
            obj->sort = stack_push(&obj->sort, obj->entry->d_name);
        }
    }
    else
    {
        obj->sort_total++;
        obj->sort = stack_push(&obj->sort, obj->entry->d_name);
    }
    ft_bzero(obj->path2, 1024);
    obj->st.st_mode = 0;
    obj->i = 0;
}

void    save_table(t_opt *opt, t_obj *obj)
{
    int     i;
    t_stack *list;

    i = 0;
    list = obj->sort;
    if (opt)
    {

    }
    // ft_printf("total: %d\n", obj->sort_total);
    obj->table = (char **)malloc(sizeof(char *) * (obj->sort_total + 1));
    while (i < obj->sort_total)
    {
        // obj->merger = s_stk_push(&obj->merger, list->name);
        obj->table[i] = ft_strdup(list->name);
        list = list->next;
        i++;
    }
    obj->table[i] = NULL;
}

void    print_stack(t_obj *obj)
{
    // char    *ret;

    // ret = NULL;
    // while ((ret = stack_pop(&obj->sort)))
    // {
    //     // ft_printf("%s\n", ret);
    //     ft_strdel(&ret);
    // }
    sort_merge(obj, 0, (obj->sort_total - 1), s_merge_forward);
    int i = 0;
    
    while (i < obj->sort_total)
    {
        ft_printf("%s\n", obj->table[i]);
        ft_strdel(&(obj->table[i]));
        i++;
    }
    free(obj->table);
    obj->table = NULL;
}

void    loopy(t_opt *opt, t_obj *obj, char *name)
{
    // t_stack *stack;
    while ((obj->entry = readdir(obj->dir)) != NULL)
    {
        save_all(opt, obj, name);
        // sort_stack();
    }
}

void listdir(t_opt *opt, char *name)
{
    static int  i;
    t_obj   obj;

    init_obj(&obj);
    if (!(obj.dir = opendir(name)))
        return;
    if (i++)
        ft_printf("\n%s:\n", name);
    loopy(opt, &obj, name);
    save_table(opt, &obj);
    print_stack(&obj);
    obj.sort_total = 0;
    closedir(obj.dir);
    // sort obj.dirs here
    while ((obj.tmp = stack_pop(&obj.dirs)))
    {
        listdir(opt, obj.tmp);
        ft_strdel(&(obj.tmp));
    }
}

int main(int ac, char **av)
{
    t_stack *tmp;
    t_opt   opt;
    char    *str;
    int     i;

    i = 1;
    tmp = NULL;
    init_options(&opt);
    verify_options(ac, av);
    set_options(&opt, ac, av);
    tmp = verify_arguments(av, ac);
    if (ac == 1 || (ac == 2 && opt.set))
    {
        listdir(&opt, ".");
    }
    else if (ac >= 2)
    {
        if (opt.set)
            i++;
        while (is_option(av[i]))
            i++;
        while ((str = stack_pop(&tmp)))
        {
            listdir(&opt, str);
            ft_strdel(&str);
        }
    }
    // system("leaks test");
    return 0;
}