#ifndef CORE
#define CORE



// maybe use this for menu options?
typedef void (*Consumer)(void** dataStructure);

typedef struct ConsumerMenuOption {
    char* msg;
    Consumer runIfSelected;
} ConsumerMenuOption;

ConsumerMenuOption* newConsumerMenuOption(char* msg, Consumer runIfSelected);
void freeConsumerMenuOption(ConsumerMenuOption** option);
int doConsumerMenu(ConsumerMenuOption** options, int numOptions, void** dataStructure);



/**
A Runnable is a function which
accepts no arguments, and returns
nothing. Used for creating menus.
*/
typedef void (*Runnable)();

/**
An IntSupplier is a function which
accepts an argument, and returns a
status code.
*/
typedef int (*IntSupplier)();

typedef struct MenuOption {
    char* msg;
    Runnable runIfSelected;
} MenuOption;
typedef struct IntMenuOption {
    char* msg;
    IntSupplier runIfSelected;
} IntMenuOption;

MenuOption* newMenuOption(char msg[], Runnable runIfSelected);
int freeMenuOption(MenuOption** menuOption);

IntMenuOption* newIntMenuOption(char msg[], IntSupplier runIfSelected);
int freeIntMenuOption(IntMenuOption** menuOption);

int doMenu(MenuOption** options, int numOptions);
int doIntMenu(IntMenuOption** options, int numOptions);

#endif
