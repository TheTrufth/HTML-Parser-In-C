#include <stdio.h>
#include <string.h>
#include "stack.c"


// This method checks if a tag is valid.]
// i.e. it is part of {html, head, body, title, ...}
int checkValidTag(char *newItem){
    char * tags [] = {"html",  "head", "body", "title", "h1", "h2", "h3", "p", "ul", "li", "a", "div", "br", "hr"};
    char searchString[strlen(newItem)];
    char *Ps = strchr(newItem, '/');
    if (Ps){
        for (int i = 2; i < strlen(newItem)-1; i++){
            searchString[i-2] = newItem[i];
        }
    }
    else {
        for (int i=1; i<strlen(newItem)-1; i++){
            searchString[i-1] = newItem[i];
        }
    }

    //printf("  We are checking if %s is a valid tag...", searchString);
    for (int i=0; i<14; i++){
        if (strcmp(tags[i], searchString) == 0){
            //printf("...VERIFIED, IT IS A VALID TAG\n");
            return 0;
        }
    }
    //printf("....IT NOT NOT A VALID TAG\n");
    return 1;

}



int main(){
    // Initialising the stack.
    myStack *s = (myStack *) malloc(sizeof(myStack));
    createEmptyStack(s);


    char text[1000];
    char tags[1000];
    char openTag[1000];

    FILE *fp;
    int c;
    int n = 0;

    int lineNumber = 1;
    int numOfHtmlTag = 0;
    int numOfHeadTags = 0;
    int numOfBodyTags = 0;

    fp = fopen("file.html","r");
    if(fp == NULL) {
        perror("Error in opening file");
        return(-1);
    } do {
        c = fgetc(fp);
        if( feof(fp) ) {
            break ;
        }
        if (c == '<'){
            memset(text,0,sizeof(tags));
            text[0] = c;
            n = 0;
        }
        if (c == '>'){
            text[n] = c;

            char *Ps = strchr(text, ' ');
            if (Ps){
                int index = Ps - text;
                for (int i = 0; i < index; i++){
                    tags[i] = text[i];
                }
                tags[index] = c;
            }
            else {
                strcpy(tags, text);
            }
            //printf("Current Tag = %s\n", tags);

            if (checkValidTag(tags) == 1){
                printf("[ERROR AT LINE %d] %s IS NOT A VALID TAG!", lineNumber, tags);
                return 1;
            }
            else {
                char *closingTag = strchr(tags, '/');
                // If it is closing tag, check if there is a opening tag with the same name.
                memset(openTag,0,sizeof(openTag));
                if (closingTag){
                    openTag[0] = '<';
                    for (int i = 2; i < strlen(tags); i++){
                        openTag[i-1] = tags[i];
                    }
                    //printf("Closing Tag = %s\n", openTag);
                    if (isEmpty(s) == 0 && strcmp(openTag, peek(s)) == 0){
                        pop(s);
                    }
                    else {
                        printf("[ERROR AT LINE %d] INCORRECT NESTING | EXPECTED CLOSING %s BUT GOT CLOSING %s!", lineNumber, peek(s), openTag);
                        return 1;
                    }
                }
                else {
                    //printf("Opening Tag = %s\n", tags);
                    if (strcmp(tags, "<html>") == 0){
                        numOfHtmlTag += 1;
                        if (numOfHtmlTag > 1){
                            printf("[ERROR AT LINE %d] THERE ARE MULTIPLE HTML TAGS!", lineNumber);
                            return 1;
                        }
                    }
                    if (strcmp(tags, "<head>") == 0){
                        numOfHeadTags += 1;
                        if (numOfHeadTags > 1){
                            printf("[ERROR AT LINE %d] THERE ARE MULTIPLE HEAD TAGS!", lineNumber);
                            return 1;
                        }
                    }
                    if (strcmp(tags, "<body>") == 0){
                        numOfBodyTags += 1;
                        if (numOfBodyTags > 1){
                            printf("[ERROR AT LINE %d] THERE ARE MULTIPLE BODY TAGS!", lineNumber);
                            return 1;
                        }
                        if (numOfHeadTags != 1){
                            printf("[ERROR AT LINE %d] BODY TAG DOES NOT COME AFTER HEAD TAG!", lineNumber);
                            return 1;
                        }
                    }
                    if (strcmp(tags, "<title>") == 0){
                        if (isEmpty(s) == 0 && strcmp(peek(s), "<head>") != 0){
                            printf("[ERROR AT LINE %d] TITLE TAG IS NOT NOT HEAD TAG!", lineNumber);
                            return 1;
                        }
                    }
                    if (strcmp(tags, "<div>") == 0){
                        if (isEmpty(s) == 0 && strcmp(peek(s), "<p>") == 0){
                            printf("[ERROR AT LINE %d] DIV CANNOT BE NESTED INSIDE A P TAG!", lineNumber);
                            return 1;
                        }
                    }
                    if (strcmp(tags, "<p>") == 0){
                        if (isEmpty(s) == 0 && strcmp(peek(s), "<p>") == 0){
                            printf("[ERROR AT LINE %d] P CANNOT BE NESTED INSIDE A P TAG!", lineNumber);
                            return 1;
                        }
                    }

                    if (strcmp(tags, "<br>") != 0 && strcmp(tags, "<hr>") != 0){
                        push(s, tags);
                    }
                }
            }

            memset(text,0,sizeof(text));
            memset(tags,0,sizeof(tags));
        }
        if (c != '\n') {
            text[n] = c;
            n++;
        }
        else {
            lineNumber += 1;
        }
        
    } while(1);
    //printf("Text is = %s", text);
    if (numOfHtmlTag == 0){
        printf("[ERROR] THERE ARE NO HTML TAGS!");
        return 1;
    }
    if (numOfHeadTags == 0){
        printf("[ERROR] THERE ARE NO HEAD TAGS!");
        return 1;
    }
    if (numOfBodyTags == 0){
        printf("[ERROR] THERE ARE NO BODY TAGS!");
        return 1;
    }
    if (isEmpty(s) == 1){
        printf("HTML SUCCESSFULLY PARSED!!!");
    }
    else {
        printf("[ERROR] TAGS ARE NOT NESTED CORRECTLY!");
    }
    return 0;
}