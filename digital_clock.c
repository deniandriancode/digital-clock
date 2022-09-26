#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

#define HEIGHT 30
#define WIDTH 90
#define TIME_LENGTH 20
#define DIGIT_ROW 5
#define DIGIT_COL 6

void print_time (WINDOW *);
void print_digit (WINDOW *, int, int, char);
void print_colon (WINDOW *, int, int);
void display_digit (WINDOW *, int, int, int (*)[6]);
void clear_time (WINDOW *, int, int, int);
int get_digit (char);

int
main (int argc, char *argv[])
{
        WINDOW *main_win;
        int starty, startx;

        initscr ();
        if (has_colors () != TRUE) {
                printf ("Your terminal does not support colors\n");
                exit (0);
        }
        start_color ();
        init_pair (1, COLOR_BLUE, COLOR_BLACK);
        init_pair (2, COLOR_BLACK, COLOR_BLUE);

        mousemask (ALL_MOUSE_EVENTS, NULL);

        cbreak ();
        noecho ();
        curs_set (0);

        starty = (LINES - HEIGHT) / 2;
        startx = (COLS - WIDTH) / 2;
        refresh ();

        main_win = newwin (HEIGHT, WIDTH, starty, startx);
        box (main_win, 0, 0);
        keypad (main_win, TRUE);
        wrefresh (main_win);

        print_time (main_win);

        /*int ch = getchar ();*/
        /*wprintw (main_win, "%d", ch);*/
        /*wrefresh (main_win);*/
        getchar ();

        endwin ();
        return 0;
}

void
print_time (WINDOW *win)
{
        char time_value[TIME_LENGTH];
        char date[TIME_LENGTH];
        time_t current_time;
        int max_y, max_x;
        int starty, startx;
        int i;
        int ch;

        while (1) {
                current_time = time (NULL);
                struct tm *detailed_time = localtime (&current_time);

                strftime (time_value, TIME_LENGTH, "%X", detailed_time);
                strftime (date, TIME_LENGTH, "%Y-%m-%d", detailed_time);

                getmaxyx (win, max_y, max_x);
                starty = 2;
                startx = (max_x - (6 * (strlen (time_value) + 1))) / 2;

                int spacer = 0;
                clear_time (win, starty, startx, strlen (time_value));
                wattron (win, COLOR_PAIR (2));
                for (i = 0; i < strlen (time_value); i++) {
                        if (time_value[i] != ':')
                                print_digit (win, starty, startx + i + spacer, time_value[i]);
                        else
                                print_colon (win, starty, startx + i + spacer);
                        spacer += 6;
                }
                wattroff (win, COLOR_PAIR (2));

                wrefresh (win);
                sleep (1);
        }
}

void
print_digit (WINDOW *win,
                int starty,
                int startx,
                char c_time)
{
        int i, j;
        int digit = get_digit (c_time);

        if (digit == 0) {
                int digit_arr[5][6] = {
                        {1,1,1,1,1,1},
                        {1,1,0,0,1,1},
                        {1,1,0,0,1,1},
                        {1,1,0,0,1,1},
                        {1,1,1,1,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 1) {
                int digit_arr[5][6] = {
                        {0,0,0,0,1,1},
                        {0,0,0,0,1,1},
                        {0,0,0,0,1,1},
                        {0,0,0,0,1,1},
                        {0,0,0,0,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 2) {
                int digit_arr[5][6] = {
                        {1,1,1,1,1,1},
                        {0,0,0,0,1,1},
                        {1,1,1,1,1,1},
                        {1,1,0,0,0,0},
                        {1,1,1,1,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 3) {
                int digit_arr[5][6] = {
                        {1,1,1,1,1,1},
                        {0,0,0,0,1,1},
                        {1,1,1,1,1,1},
                        {0,0,0,0,1,1},
                        {1,1,1,1,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 4) {
                int digit_arr[5][6] = {
                        {1,1,0,0,1,1},
                        {1,1,0,0,1,1},
                        {1,1,1,1,1,1},
                        {0,0,0,0,1,1},
                        {0,0,0,0,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 5) {
                int digit_arr[5][6] = {
                        {1,1,1,1,1,1},
                        {1,1,0,0,0,0},
                        {1,1,1,1,1,1},
                        {0,0,0,0,1,1},
                        {1,1,1,1,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 6) {
                int digit_arr[5][6] = {
                        {1,1,1,1,1,1},
                        {1,1,0,0,0,0},
                        {1,1,1,1,1,1},
                        {1,1,0,0,1,1},
                        {1,1,1,1,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 7) {
                int digit_arr[5][6] = {
                        {1,1,1,1,1,1},
                        {0,0,0,0,1,1},
                        {0,0,0,0,1,1},
                        {0,0,0,0,1,1},
                        {0,0,0,0,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 8) {
                int digit_arr[5][6] = {
                        {1,1,1,1,1,1},
                        {1,1,0,0,1,1},
                        {1,1,1,1,1,1},
                        {1,1,0,0,1,1},
                        {1,1,1,1,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        } else if (digit == 9) {
                int digit_arr[5][6] = {
                        {1,1,1,1,1,1},
                        {1,1,0,0,1,1},
                        {1,1,1,1,1,1},
                        {0,0,0,0,1,1},
                        {1,1,1,1,1,1}
                };
                display_digit (win, starty, startx, digit_arr);
        }
}

void
display_digit (WINDOW *win,
                int y_pos,
                int x_pos,
                int (*arr)[6])
{
        for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                        if (arr[i][j] == 1)
                                mvwprintw (win, y_pos + i, x_pos + j, " ");
                }
        }
}

void
print_colon (WINDOW *win,
                int starty,
                int startx)
{
        int i, j;
        int colon[5][6] = {
                {0,0,0,0,0,0},
                {0,0,1,1,0,0},
                {0,0,0,0,0,0},
                {0,0,1,1,0,0},
                {0,0,0,0,0,0}
        };
        for (i = 0; i < 5; i++) {
                for (j = 0; j < 6; j++) {
                        if (colon[i][j] == 1)
                                mvwprintw (win, starty + i, startx + j, " ");
                }
        }
}

int
get_digit (char ch)
{
        char c_digit[] = {'0','1','2','3','4','5','6','7','8','9'};
        int i;
        for (i = 0; i < sizeof (c_digit); i++) {
                if (ch == c_digit[i])
                        return i;
        }
}

void
clear_time (WINDOW *win,
                int starty,
                int startx,
                int time_size)
{
        int i, j, s;
        int spacer = 0;

        for (s = 0; s < time_size; s++) {
                for (i = 0; i < DIGIT_ROW; i++) {
                        for (j = 0; j < DIGIT_COL; j++) {
                                mvwprintw (win, starty + i, startx + j + spacer, " ");
                        }
                }
                spacer += 7;
        }
}
