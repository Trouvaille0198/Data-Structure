#include "LinkList.h"
int main(void)
{
    int a[5] = {1, 3, 5, 7, 9};
    int b[5] = {2, 4, 6, 8, 10};
    LinkList<int> la(a, 5);
    LinkList<int> lb(b, 5);
    la.Show();
    lb.Show();
    LinkList<int> lc;
    lc = Merge(la, lb);
    lc.Show();
    system("pause");
    return 0;
}