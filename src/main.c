#include <ncurses.h>

int main() {
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

