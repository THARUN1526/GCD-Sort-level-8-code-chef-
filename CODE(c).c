#include<stdio.h>
int main()
{
    int p,i;
    scanf("%d",&p);
    while(p>0)
    {
        int k;
        scanf("%d",&k);
        int a[k];
        for(i=0;i<k;i++)
    {
        scanf("%d",&a[i]);
    }
    if(a[i]%2==0)
    printf("YES\n");
    else
    printf("NO\n");
    p--;
  }
}