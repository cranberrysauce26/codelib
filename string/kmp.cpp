#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char s[1000003], t[1000003]; int N, M, i, j, nxt[1000003];
int KMP(){ // returns index of first occurence of t
    N = strlen(s), M = strlen(t);
    nxt[0] = -1;
    for(j=-1, i=0; i<M; ){
        if(j==-1 || t[j]==t[i]) { j++; i++; nxt[i]=j;}
        else j = nxt[j];
    }
    for(i=0, j=0; i<N; ){
        if(j==-1 || s[i]==t[j]){
            if(j==M-1) return i-M+1;
            i++; j++;
        }else j = nxt[j];
    }
    return -1;
}
int main(){
    scanf("%s %s", s, t);
    printf("%d\n", KMP());
}