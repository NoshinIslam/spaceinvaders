#include<stdio.h>
#include<windows.h>
int main()
{
    // position of A (spaceship) and | (bullet):

    int rowA=15,colA=15;
    int rowB=rowA-1, colB=colA;


    //i used ANSI code to specify the location of A. A is the spaceship.
    printf("\033[%d;%dH",rowA,colA);
    printf("A");

    int duration=2;
    char E; //E for 'enter'. Assigning 'Enter' as to trigger bullets. '|' is a bullet.
    scanf("%c",&E);

    while(rowB>0)
    {
        printf("\033[%d;%dH",rowB,colB);
        printf("|\n");
        Sleep(duration*100);

        printf("\033[%d;%dH",rowB,colB);
        printf(" "); //adds a new line to eleminate buffering

        rowB--; //moves the bullet up by one row

    }
    printf("\033[%d;%dH", rowA + 1, 1);




    return 0;
}
