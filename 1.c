#include <stdio.h>
#include <string.h>

int main() {
    char S[100]; 
    scanf("%s", S); 

    int length = strlen(S);

    for (int i = 0; i < length; i++) 
    {
        if (S[i] >= 'A' && S[i] <= 'Z') 
        { 
            S[i] = S[i] + ('a' - 'A');
        } 
        else if (S[i] >= 'a' && S[i] <= 'z') 
        { 
            S[i] = S[i] - ('a' - 'A');
        } 
    }

    for (int i = length - 1; i >= 0; i--) 
    {
        printf("%c", S[i]); 
    }

    return 0;
}
