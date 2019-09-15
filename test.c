#include <stdio.h>
#include <Windows.h>

int main(){
    int x;
    printf("\x1b[34m" "sss"); 
    scanf("%d", &x);
    printf(1 ? "\x1b[3%xm", (char)x, "Å°" : "Å@");
    printf("%d   %x  %x\n", x, x, (char) x);
    printf("\x1b[3%xm", (char) x);
    scanf("%d",&x);
    printf("aaa\n");
}