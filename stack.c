//
// Created by Dinesh on 18/05/2021.
// Referenced: https://www.programiz.com/dsa/stack but modified to support strings.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 150
int count = 0;

struct Stack {
    char items[MAX][MAX];
    int top;
};

typedef struct Stack myStack;

void createEmptyStack(myStack *s){
    s -> top = -1;
}

int isFull(myStack *s){
    return s ->top == MAX - 1 ? 1 : 0;
}

int isEmpty(myStack *s){
    return s ->top == -1 ? 1 : 0;
}

void push(myStack *s, char *newItem){
    if (isFull(s)){
        printf("Stack full");
    }
    else {
        s -> top++;
        strcpy(s -> items[s->top], newItem);
    }
    count++;
}

void pop(myStack *s){
    if (isEmpty(s)){
        printf("STACK EMPTY");
    }
    else {
        //printf("ITEM POOPED= %s", s->items[s->top]);
        s->items[s->top];
        s->top--;
    }
    count--;
}

char * peek(myStack *s){
    if (isEmpty(s)){
        printf("STACK EMPTY");
    }
    else {
        //printf("ITEM PEEK= %s", s->items[s->top]);
        return s->items[s->top];
    }
}


void printStack(myStack *s){
    printf("Stack: ");
    for (int i=0; i<count; i++){
        printf("%s ", s->items[i]);
    }
}
