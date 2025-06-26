#include <ncurses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
int main() {
 ITEM *items[3]; //2 OPTIONS + 1 NULL TERMINATOR
 MENU *menu;
 int c;

  //Option labels
  char *choices[] = {
    "Restore Power",
    "Exit",
    NULL
  }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);

    //Create items
    for (int i = 0; choices[i]; i++) {
        items[i] = new_item(choices[i], "");
    }
    items[2] = (ITEM *)NULL;

    //Create menu
    menu = new_menu((ITEM **)items);
    post_menu(menu);
    refresh();

    while ((c = getch()) != '\n') {
    switch (c) {
    case KEY_DOWN
      menu_driver(menu,REQ_DOWN_ITEM);
      break;
    case KEY_UP;
      menu_driver(menu,REQ_UP_ITEM);
      break;
      }
    }

  int choice;

    initscr();              // Start ncurses
    noecho();               // Don't echo typed characters
    cbreak();               // React to keys instantly
    keypad(stdscr, TRUE);   // Enable arrow keys

    mvprintw(1,2, "Jurassic Park: Systems online AUCILARY POWER ONLY \n");
    mvprintw(2,2, "WARNING: Security systems DISABLED");
    mvprintw(3, 4, "1. Restore Power");
    mvprintw(4, 4, "2. Exit");
    mvprintw(6, 2, "Enter your choice: ");

    echo(); // Turn echo back on so we can type
    scanw("%d", &choice);  // Get input using ncurses

    endwin();               // End ncurses mode

    // Print choice result normally after ncurses
    printf("You chose: %d\n", choice);
    return 0;
}

