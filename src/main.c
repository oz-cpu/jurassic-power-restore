#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

// Submenu function (takes main menu pointer as argument)
void show_submenu(void *menu_ptr) {
    MENU *main_menu = (MENU *)menu_ptr;

    ITEM *sub_items[3];
    MENU *sub_menu;

    clear();

    sub_items[0] = new_item("Sub Option", "");
    sub_items[1] = new_item("Back", "");
    sub_items[2] = NULL;

    sub_menu = new_menu(sub_items);
    post_menu(sub_menu);
    refresh();

    int ch;
    bool running = true;

    while (running && (ch = getch())) {
        switch (ch) {
            case KEY_DOWN:
                menu_driver(sub_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(sub_menu, REQ_UP_ITEM);
                break;
            case 10: { // ENTER
                ITEM *selected = current_item(sub_menu);
                const char *label = item_name(selected);

                if (strcmp(label, "Back") == 0) {
                    running = false;
                } else if (strcmp(label, "Sub Option") == 0) {
                    mvprintw(10, 0, "Sub Option selected! Press any key...");
                    getch();
                }
                break;
            }
        }
    }

    // Cleanup
    unpost_menu(sub_menu);
    free_menu(sub_menu);
    for (int i = 0; sub_items[i]; i++) {
        free_item(sub_items[i]);
    }
    clear();
    post_menu(main_menu);
    refresh();
}


int main() {
    ITEM *items[3];
    MENU *menu;
    int c;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    items[0] = new_item("Open Submenu", "");
    set_item_userptr(items[0], (void (*)(void *))show_submenu);
    items[1] = new_item("Exit", "");
    items[2] = NULL;

    menu = new_menu(items);
    post_menu(menu);
    refresh();

    while (1) {
        c = getch();
        switch (c) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10: { // ENTER
                ITEM *cur = current_item(menu);
                void (*func)(void *) = item_userptr(cur);

                if (func) {
                    func(menu); // Call submenu handler
                } else if (strcmp(item_name(cur), "Exit") == 0) {
                    unpost_menu(menu);
                    free_menu(menu);
                    for (int i = 0; items[i]; i++) {
                        free_item(items[i]);
                    }
                    endwin();
                    exit(0);
                }
                break;
            }
        }
    }

    return 0;
}

