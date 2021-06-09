#include "parser.h"
#include "common.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
/*
Private function prototypes
*/

typedef struct TreeStack {
    PostfixTree* value;
    struct TreeStack* next;
} TreeStack;

PostFixTree* newPostfixTree(char* token);

TreeStack* newTreeStack(PostfixTree* value);
void deleteTreeStack(TreeStack** top);
void pushTreeStack(TreeStack** top, PostfixTree* tree);
PostfixTree* popTreeStack(TreeStack** top);


// need these?
typedef struct OperatorStack {
    struct OperatorStack* next;
    char operator;
} OperatorStack;

OperatorStack* newOperatorStack(char operator);
void deleteOperatorStack(OperatorStack** stack);
void push(OperatorStack** stack, char operator);
char popOperatorStack(OperatorStack** stack);


/*
Public functions
*/
PostfixTree* toPostfixTree(char* infix){
    PostfixTree* root = 0;
    // todo all this
    OperatorStack* ops = 0;

    char token;
    bool inNumber = false;
    for(int offset = 0; offset < strlen(infix); ++offset){
        token = infix[offset];
        if(isdigit(token)){
            inNumber = true;
            appendStringBuilderChar(sb, token);
        } else {
            if(inNumber){
                appendStringBuilderChar(sb, END_OF_NUMBER);
                // mark end of current number
                inNumber = false;
            }
            if(token == '('){
                push(&ops, token);
            } else if(token == ')'){
                // pop until it finds the matching '('
                while(token != '('){
                    token = popOperatorStack(&ops);
                    if(token != '('){
                        appendStringBuilderChar(sb, token);
                    }
                }
            }
            //if the token is an operator, pop until the top is LESS precedence than the token,
            //then push to token.
            else if(token == '+' || token == '-'){
                while(ops && ops->operator != '('){
                    appendStringBuilderChar(sb, popOperatorStack(&ops));
                }
                push(&ops, token);
            } else if(token == '*' || token == '/'){
                while(
                    ops &&
                    ops->operator != '(' &&
                    ops->operator != '+' &&
                    ops->operator != '-'
                ){
                    appendStringBuilderChar(sb, popOperatorStack(&ops));
                }
                push(&ops, token);
            } else if(token == ' '){
                // do nothing
            } else {
                printf("Unsupported token: '%c'\n", token);
            }
        }
    }

    if(inNumber){
        appendStringBuilderChar(sb, END_OF_NUMBER);
        // mark end of current number
        inNumber = false;
    }
    while(ops){
        appendStringBuilderChar(sb, popOperatorStack(&ops));
    }

    return root;
}



/*
Private function implementations
*/



PostFixTree* newPostfixTree(char* token){
    PostfixTree* tree = (PostfixTree*)malloc(sizeof(PostfixTree));
    int n = strlen(token);
    tree->token = (char*)malloc(sizeof(char) * (n + 1));
    strncpy(tree->token, token, n);
    tree->token[n] = '\0';
    tree->left = 0;
    tree->right = 0;
    return tree;
}

TreeStack* newTreeStack(PostfixTree* value){
    TreeStack* frame = (TreeStack*)malloc(sizeof(TreeStack));
    frame->value = value;
    frame->next = 0;
    return frame;
}

void deleteTreeStack(TreeStack** top){
    if(top){
        PostfixTree* tree = 0;
        while(*top){
            tree = popTreeStack(top);
            deletePostfixTree(&tree);
        }
    }
}

void pushTreeStack(TreeStack** top, PostfixTree* tree){
    if(top){
        TreeStack* newTop = newTreeStack(tree);
        newTop->next = *top;
        *top = newTop;
    }
}

PostfixTree* popTreeStack(TreeStack** top){
    PostFixTree* value = 0;
    if(top && *top){
        TreeStack* oldTop = *top;
        *top = oldTop->next;
        value = oldTop->value;
        free(oldTop);
    }
    return value;
}


// need these?


OperatorStack* newOperatorStack(char operator){
    OperatorStack* newFrame = (OperatorStack*)malloc(sizeof(OperatorStack));
    newFrame->next = 0;
    newFrame->operator = operator;
    return newFrame;
}

void deleteOperatorStack(OperatorStack** stack){
    while(stack && *stack){
        popOperatorStack(stack);
    }
}

void push(OperatorStack** stack, char operator){
    if(stack){
        OperatorStack* newTop = newOperatorStack(operator);
        newTop->next = *stack;
        *stack = newTop;
    }
}

char popOperatorStack(OperatorStack** stack){
    char value = ERROR;
    if(stack && *stack){
        OperatorStack* oldTop = *stack;
        value = oldTop->operator;
        *stack = oldTop->next;
        free(oldTop);
        oldTop = 0;
    }
    return value;
}