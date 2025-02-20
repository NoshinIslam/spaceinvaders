#include<stdio.h>
int main()
{
    // position of A (spaceship) and | (bullet):

    int rowA=15,colA=15;


    //i used ANSI code to specify the location of A. A is the spaceship.
    printf("\033[%d;%dH",rowA,colA);
    printf("A");


     int rowB=14,colB=15;
    char E; //E for 'enter'. Assigning 'Enter' as to trigger bullets. '|' is a bullet.
    scanf("%c",&E);
    printf("\033[%d;%dH",rowB,colB);
    printf("|");

    int i;
    for(i=0;i<4;i++)
    {
            printf("\n");

    }  
    
    return 0;
}
