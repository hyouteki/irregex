#ifndef IRREGEX_H_
#define IRREGEX_H_

#include <stdio.h>
#include <stdlib.h>

#define u32 unsigned int 

typedef struct Vec2 {
	u32 n1;
	u32 n2;
} Vec2;

typedef struct Option {
	Vec2 vec2;
	u32 valid: 1;
} Option;

static inline Vec2 Vec2_Init(u32, u32);

static inline Option Option_Valid(u32, u32);
static inline Option Option_Invalid();

static u32 Irregex_StrLen(char *);
static Option Irregex_MatchH(char *, char *);
static Option Irregex_MatchHere(char *, char *, u32);

char *Irregex_Match(char *, char *);

static u32 Irregex_StrLen(char *str) {
	u32 len = 0;
	while (*str) {
		len++;
		str++;
	}
	return len;
}

static inline Vec2 Vec2_Init(u32 n1, u32 n2) {
	return (Vec2){.n1=n1, .n2=n2};
}

static inline Option Option_Valid(u32 n1, u32 n2) {
	return (Option){.vec2=Vec2_Init(n1, n2), .valid=1};
}

static inline Option Option_Invalid() {
	return (Option){.vec2=Vec2_Init(0, 0), .valid=0};
}

static Option Irregex_MatchH(char *irregex, char *query) {
	if (irregex[0] == '^') return Irregex_MatchHere(irregex+1, query, 0);
	for (char *text = query; *text; text++) {
		Option option = Irregex_MatchHere(irregex, text, 0);
		if (option.valid) return option;
	}
	return Option_Invalid();
}

static Option Irregex_MatchHere(char *irregex, char *query, u32 len) {
	switch (irregex[0]) {
	case '\0': return Option_Valid(0, len);
	case '.': {
		if (irregex[1] != '*') return (query[0] == '\0')? Option_Invalid():
								   Irregex_MatchHere(irregex+1, query+1, len+1);
		u32 i = 0;
		for (; i < Irregex_StrLen(query) && query[i] != irregex[2]; ++i);
		return Irregex_MatchHere(irregex+2, query+i, len+i);
	} 
	case '$': {
		if (irregex[1] != '\0') {
			printf("(Irregex) Error: Invalid token `$` in middle of regex\n");
			exit(1);
		}
		return (query[0] == '\0')? Option_Valid(0, len): Option_Invalid(); 
	}
	case '*': {
		if (irregex[1] == '\0')
			return Option_Valid(Irregex_StrLen(query)-len, Irregex_StrLen(query));
		u32 i = 0;
		for (; i < Irregex_StrLen(query) && query[i] != irregex[1]; ++i);
		return Irregex_MatchHere(irregex+1, query+i, len+i);
	}
	case '^':
		printf("(Irregex) Error: Invalid token `^` in middle of regex\n");
		exit(1);
	}
	if (irregex[1] == '*') {
		u32 i = 0;
		for (; i < Irregex_StrLen(query) && query[i] == irregex[0]; ++i);
		return Irregex_MatchHere(irregex+2, query+i, len+i);
	}
	if (query[0] == '\0' || query[0] != irregex[0]) return Option_Invalid();
	return Irregex_MatchHere(irregex+1, query+1, len+1); 
}

char *Irregex_Match(char *irregex, char *query) {
	Option option = Irregex_MatchH(irregex, query);
	if (option.valid) {
		u32 len = option.vec2.n2-option.vec2.n1;
		char *str = (char *)malloc(sizeof(char)*(len+1));
		for (int i = 0; i < len; ++i) str[i] = query[i+option.vec2.n1];
		str[len] = 0;
		return str;
	}
	return "";
}

#endif // IRREGEX_H_
