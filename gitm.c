//build 
//gcc -fsanitize=address gitm.c -o gitm.o
#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define SUBSTR_HISTORY 4
#define TURN 2
#define MAX_HISTORY 913 // TOTAL HISTORY DIGIT is 19 * 9 * 2 + 19 * 10 * 3 = 912 and add one for null terminator
#define ROW_NUM 19
#define COL_NUM 19
#define MAX_INPUT 50
#define VIEW_STR_LEN 50 // 49
char centre_mist[4] = "J10";
char view_str[VIEW_STR_LEN];
//once it reaches 19*19 print tie and end game;
int space_occupied = 0;
void rollback_newline(char *usr_input) {
    for (int i = 0; i <strlen(usr_input); i++) {
        if (usr_input[i] == '\0') {
            usr_input[i] = '\n';
            if (i+1 < MAX_INPUT) {
                usr_input[i+1] = '\0';
            }
        }
    }
}
void remove_newline(char *usr_input) {
    for (int i = 0; i < strlen(usr_input); i++) {
        if (usr_input[i] == '\n') {
            usr_input[i] = '\0';
        }
    }
    return;
}
void change_turn(char *turn) {
    if (strncmp(turn,"B",1) == 0) {
        strcpy(turn,"W");
    }else {
        strcpy(turn,"B");
    }
}
int get_centre_mist_x(char stone_x) {
    //? non-ascii value
    //? usuage : printf("%c\n",(char)get_centre_mist_x('A') + 64);
    // printf("%c\n", (char)rst+64);
    return 1 + (5*((int)stone_x -64)*((int)stone_x -64)+3*((int) stone_x-64)+4) % 19;
}
int get_centre_mist_y(int stone_y) {
    //? get int value of y
    return 1 + (4*stone_y*stone_y + 2*stone_y - 4) % 19;
}
int check_win_condition(char map[][COL_NUM], char *turn, int row_idx, int col_idx) {
    //? if win condition satisfies return 1 else 0;
    // check horizontallay
    int cnt = 1;
    for(int i = col_idx + 1; i < COL_NUM; i++) {
        if (map[row_idx][i] == turn[0]) {
            cnt ++;
        } else {
            break;
        }
    }
    for(int i = col_idx - 1; i > -1; i--) {
        if (map[row_idx][i] == turn[0]) {
            cnt ++;
        } else {
            break;
        }
    }
    if (cnt >= 5) {
        return 1;
    }
    // check vertically
    cnt = 1;
    for(int i = row_idx + 1; i < ROW_NUM; i++) {
        if (map[i][col_idx] == turn[0]) {
            cnt ++;
        } else {
            break;
        }
    }
    for(int i = row_idx - 1; i > -1; i--) {
        if (map[i][col_idx] == turn[0]) {
            cnt ++;
        } else {
            break;
        }
    }
    if (cnt >= 5) {
        return 1;
    }
    //check diagonally
    cnt = 1;
    for(int i = row_idx + 1, j = col_idx + 1; i < ROW_NUM && j < COL_NUM; i++, j++) {
        if (map[i][j] == turn[0]) {
            cnt ++;
        } else {
            break;
        }
    }
    for(int i = row_idx - 1, j = col_idx - 1; i > -1 && j > -1 ; i--, j--) {
        if (map[i][j] == turn[0]) {
            cnt ++;
        } else {
            break;
        }
    }
    //opposite direction of diagonally
    cnt = 1;
    for(int i = row_idx - 1, j = col_idx + 1; i > -1 && j < COL_NUM; i--, j++) {
        if (map[i][j] == turn[0]) {
            cnt ++;
        } else {
            break;
        }
    }
    for(int i = row_idx + 1, j = col_idx - 1; i < ROW_NUM && j > -1 ; i++, j--) {
        if (map[i][j] == turn[0]) {
            cnt ++;
        } else {
            break;
        }
    }
    if (cnt >= 5) {
        return 1;
    }
    return 0;
}
void change_view_str(char map[][COL_NUM]) {
    int centre_x = (int)centre_mist[0]-64;
    int centre_y;
    if ((int) strlen(centre_mist) == 2) {
        centre_y = (centre_mist[1]-'0');
    } else {
        centre_y = 10 + (centre_mist[2]-'0');
    }
    int start_x = centre_x - 3;
    int start_y = centre_y + 3;

    int idx = 0;
    for (int i = 0; i < 7; i++) {
        for (; start_x < centre_x+4; start_x++) {
            if (start_x - 1 < 0 || start_x - 1 > ROW_NUM - 1 || start_y - 1 < 0 || start_y - 1 > COL_NUM - 1) {
                view_str[idx] = 'x';
            } else {
                if (map[start_x-1][start_y-1] == 'B') {
                    view_str[idx] = '#';
                }else if (map[start_x-1][start_y-1] == 'W'){
                    view_str[idx] = 'o';
                }else {
                    view_str[idx] = '.';

                }
            }
            idx++;
        }
        start_x = centre_x - 3;
        start_y--;
    }
}
int parse_place(char map[][COL_NUM], char *usr_input, char *turn, char *history) {
    //TODO implement
    // place A1
    // 01234567
    // check number of space
    int space_cnt = 0;    
    for (int i = 0; i < strlen(usr_input); i++) {
        if (usr_input[i] == ' ') {
            space_cnt ++; 
        }
    }
    if (space_cnt > 1) {
        return -3;
    }
    char tmp_usr_input[MAX_INPUT];
    strcpy(tmp_usr_input, usr_input);
    char *token = strtok(tmp_usr_input, " ");
    if ((int) strlen(usr_input) < 7) {
        return -3;
    } else if (strncmp(token, "place", MAX_INPUT) != 0) {
        return -3;
    }else {
        token = strtok(NULL, " ");
        if ((int)strlen(token) == 1) {
            return -3;
        }
        int is_all_numeric = 1;
        int num_cnt = 0;
        for (int idx = 1; idx < strlen(token); idx++) {
            if (!isdigit(token[idx])) {
                is_all_numeric = 0;
                break;
            }
            num_cnt ++;
            if (num_cnt > 2) {
                return -1;
            }
        }
        if (is_all_numeric == 0 || !isupper(token[0])) {
            return -1;
        }
        if (usr_input[6] < 65 || usr_input[6] > 83) {
            // checking whether 6th idx letter is in range of capital A-S
            return -1;
        } else if ((int) strlen(usr_input) == 8) {
            //handle
            if (!isdigit(usr_input[7]) || usr_input[7] == '0' || usr_input[6] < 'A' || usr_input[6] > 'S') {
                return -1;
            }
            //! successful
            int row_idx = (int)usr_input[6]-65;
            int col_idx = (usr_input[7]-'0')-1;
            if (map[row_idx][col_idx] == '.') {
                map[row_idx][col_idx] = turn[0];
                char sub_history[3];
                strncpy(sub_history, usr_input + 6,2);
                sub_history[2] = '\0';
                strcat(history,sub_history);
                space_occupied ++;
                int win_rst = check_win_condition(map, turn, row_idx, col_idx);
                if (win_rst) {
                    //! won game
                    return 1;
                }
                char new_centre_x = (char)get_centre_mist_x(usr_input[6]) + 64;
                int new_centre_y = get_centre_mist_y(col_idx+1);
                snprintf(centre_mist, sizeof(centre_mist), "%c%d", new_centre_x, new_centre_y);
                change_view_str(map);
                change_turn(turn);
                return 0;
            }else{
                return -2;
            }
            return 0;
        } else if ((int) strlen(usr_input) == 9) {
            if (!isdigit(usr_input[7])  || !isdigit(usr_input[8])|| usr_input[7] != '1' || usr_input[6] < 'A' || usr_input[6] > 'S') {
                return -1;
            }
            //! successful
            int row_idx = (int)usr_input[6]-65;
            int col_idx = 10 +(usr_input[8]-'0')-1;
            if (map[row_idx][col_idx] == '.') {
                map[row_idx][col_idx] = turn[0];
                char sub_history[4];
                strncpy(sub_history, usr_input + 6,3);
                sub_history[3] = '\0';
                strcat(history,sub_history);
                space_occupied ++;
                int win_rst = check_win_condition(map, turn, row_idx, col_idx);
                if (win_rst) {
                    //! condition check in parse cmd
                    return 1;
                }
                char new_centre_x = (char)get_centre_mist_x(usr_input[6]) + 64;
                int new_centre_y = get_centre_mist_y(col_idx+1);
                snprintf(centre_mist, sizeof(centre_mist), "%c%d", new_centre_x, new_centre_y);
                change_view_str(map);
                change_turn(turn);
                return 0;
            }else{
                return -2;
            }
            return 0;
        }
    }
    return 0;
}

int resign_game(char *history, char *turn) {
    if (strncmp(turn,"B",1)== 0) {
        printf("White wins!\n");
    }else {
        printf("Black wins!\n");
    }
    if (!(strncmp(history, "", MAX_HISTORY) == 0)) {
        //checking if hisotry is not empty string
        printf("%s\n", history);
    }
    printf("Thank you for playing!\n");
    return -1;
}
void print_who(char *turn) {
    printf("%s\n",turn);
}
void print_map(char map[][COL_NUM]) {
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
}
void print_history(char *history) {
    printf("%s\n",history);
}
void print_view() {
    printf("%s,%s\n",centre_mist, view_str);
}
int parse_cmd(char map[][COL_NUM], char *usr_input, char *history, char *turn) {
    int rst = 0;
    if (strncmp(usr_input, "term", MAX_INPUT) == 0) {
        return -5;
    } else if (strncmp(usr_input, "resign", MAX_INPUT) == 0) {
        rst = resign_game(history, turn);
    } else if (strncmp(usr_input, "who", MAX_INPUT) == 0) {
        print_who(turn);
    } else if (strncmp(usr_input, "place", 5) == 0) {
        rst = parse_place(map, usr_input, turn, history);
        if (rst == -1) {
            printf("Invalid coordinate\n");
        }else if (rst == -2) {
            printf("Occupied coordinate\n");
        }else if (rst == 1) {
            //! win condition
            return 1;
        }else if (rst == -3) {
            printf("Invalid!\n");
        }
        rst = 0;
    } else if (strncmp(usr_input, "history", MAX_INPUT) == 0) {
        print_history(history);
    } else if (strncmp(usr_input, "view", 5) == 0) {
        print_view();
    } else {
        printf("Invalid!\n");
    }
    return rst;
}

int main() {
    int main_rst = 0;
    
    char turn[2] = "B";
    char map[ROW_NUM][COL_NUM];
    char history[MAX_HISTORY] = "";
    char cmd[MAX_INPUT];
    // initialising map to . 
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++) {
            map[i][j] = '.';
        }
    }
    // initialising view_str
    for (int i = 0; i < VIEW_STR_LEN-1; i++) {
        view_str[i] = '.';
    } 
    view_str[VIEW_STR_LEN-1] = '\0';
    int c;
    while (fgets(cmd, MAX_INPUT, stdin) != NULL) {
        int over_space_cnt = 0;
        if (strlen(cmd) == MAX_INPUT-1 && cmd[MAX_INPUT-1] != '\n') {
            for (int i = 0; i < strlen(cmd); i++) {
                if (cmd[i] == ' ') {
                    over_space_cnt ++;
                }
            }
            while ((c = getchar()) != '\n' && c != EOF) {
                if (c == ' ') {
                    over_space_cnt ++;
                }
            } 
            if (over_space_cnt>1) {
                printf("Invalid!\n");
            }else{
                remove_newline(cmd);
                parse_cmd(map, cmd, history, turn);
            }
            continue; // Restart the loop to read a new input line
        }
        remove_newline(cmd);
        main_rst = parse_cmd(map, cmd, history, turn);
        if (main_rst == -1) {
            break;
        } else if (main_rst == 1) {
            if (turn[0] == 'B') {
                printf("Black wins!\n");
            }else {
                printf("White wins!\n");
            }
            print_history(history);
            printf("Thank you for playing!\n");
            break;
        } else if (main_rst == -5) {
            return -1;
        }
        if ((int) strlen(history) == 912) {
            printf("Wow, a tie!\n");
            print_history(history);
            printf("Thank you for playing!\n");
        }
    }
    return 0;
}