// #pragma GCC optimize("O3")
#include <cstdio>

// #define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1,
// 1048576, stdin)] = 0, *_pbuf++)) char _buf[1048577], *_pbuf = _buf;

int read_int() {
    int c, o = 0;
    while ((c = getchar()) < '0')
        ;
    do {
        o = (o << 3) + (o << 1) + (c - '0');
    } while ((c = getchar()) >= '0');
    return o;
}

// int read_signed_int() {
// 	int c, o = 0, sign=1;
// 	while (1) {
//         c = getchar();
//         if (c=='-' || c>='0') break;
//     }
//     if (c=='-') {
//         sign=-1;
//         c = getchar();
//     }
// 	do {
// 		o = (o<<3)+(o<<1) + (c - '0');
// 	} while ((c = getchar()) >= '0');
// 	return o*sign;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
    clock_t begin = clock();
    printf("*********Starting program*********\n\n");
    freopen("data.txt", "r", stdin);
    // freopen("data.txt", "w", stdout);
    // int n = 1e7;
    // printf("%d\n", n);
    // while (n--) {
    //     printf("%d\n", rand());
    // }
    // cin.tie(0);
    // cin.sync_with_stdio(0);
    int n, x;
    // cin >> n;
    // scanf("%d", &n);
    n = read_int();
    while (n--) {
        // cin >> x;
        // scanf("%d", &x);
        x = read_int();
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime taken: %lf\n", elapsed_secs);
}