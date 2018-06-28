#pragma GCC optimize("O3")
#include <cstdio>

#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;

int read_int() {
	int c, o = 0;
	while ((c = getchar()) < '0');
	do {
		o = (o<<3)+(o<<1) + (c - '0');
	} while ((c = getchar()) >= '0');
	return o;
}

int read_signed_int() {
	int c, o = 0, sign=1;
	while (1) {
        c = getchar(); 
        if (c=='-' || c>='0') break;
    }
    if (c=='-') {
        sign=-1;
        c = getchar();
    }
	do {
		o = (o<<3)+(o<<1) + (c - '0');
	} while ((c = getchar()) >= '0');
	return o*sign;
}