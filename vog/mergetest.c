#include <stdio.h>

typedef struct  s_ms
{
    int         i;
    int         j;
    int         k;
    int         n1;
    int         n2;
}               t_ms;

void    ms_init(t_ms *ms, int i, int j)
{
    ms->i = -1;
    ms->j = -1;
    ms->n1 = i;
    ms->n2 = j;
}

void    s_merge(int  *tab, int l, int m, int r)
{
    t_ms    ms;
    int     left[(m - l + 1)];
    int     right[(r - m)];

    ms_init(&ms, (m - l + 1), (r - m));
    while (++ms.i < ms.n1)
        left[ms.i] = tab[(l + ms.i)];
    while (++ms.j < ms.n2)
        right[ms.j] = tab[(m + 1 + ms.j)];
    ms.i = 0;
    ms.j = 0;
    ms.k = l;
    while (ms.i < ms.n1 && ms.j < ms.n2)
    {
        if (left[ms.i] <= right[ms.j])
            tab[ms.k] = left[ms.i++];
        else
            tab[ms.k] = right[ms.j++];
        ms.k++;
    }
    while (ms.i < ms.n1)
        tab[ms.k++] = left[ms.i++];
    while (ms.j < ms.n2)
        tab[ms.k++] = right[ms.j++];
}

void    sort_merge(int  *tab, int l, int r)
{
    int m;

    if (l < r)
    {
        m = l + (r - l) / 2;
        sort_merge(tab, l, m);
        sort_merge(tab, m + 1, r);
        s_merge(tab, l, m, r);
    }
}

int main(void)
{
    int i = 0;
    int tab[] = {4563, -75, 11, 9, 254364, 4, -5787610, 5, 8, 1657, 6};

    sort_merge(tab, 0, 10);
    while (i < 11)
        printf("%d ", tab[i++]);
    printf("\n");
    return (0);
}