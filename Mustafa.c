#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MATRIX_SIZE 4

struct level {
    int level;
    char question[MATRIX_SIZE][MATRIX_SIZE];
    int answer_x[5];
    int answer_y[5];
    struct level* next;
};
typedef struct level Node;
Node *head = NULL;

Node *create_Node(int lev, char ques[MATRIX_SIZE][MATRIX_SIZE]) {
    Node *temp;
    temp = malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Memory not allocated");
        exit(0);
    } else {
        temp->level = lev;
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                temp->question[i][j] = ques[i][j];
            }
        }
        
        temp->next = temp; // Circular reference
    }
    return temp;
}

void add_Node(int lev, char ques[MATRIX_SIZE][MATRIX_SIZE]) {
    Node* new = create_Node(lev, ques);
    if (head == NULL) {
        head = new;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = new;
        new->next = head;
    }
}

void print_matrix(Node *current) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (current->question[i][j] == 'x') {
                if (current->level == 1 || current->level == 2 || current->level == 3) {
                    printf("* "); // Hide the mines
                }
            } else {
                printf("%c ", current->question[i][j]);
            }
        }
        printf("\n");
    }
}

bool allUncovered(Node *current,int lev) {
    int ctr=0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (current->question[i][j] != 'o') {
                ctr++;
            }
        }
    }
    if(ctr==lev)
    return true;
    else
    return false;
}

void play_game(Node *head) {
    int user_x, user_y;
    Node *current = head;
    int ctr2 = 0, ctr3 = 0;
    
    while (1) {
        printf("LEVEL %d\n", current->level);
        print_matrix(current);

        printf("Enter the x and y coordinates: ");
        scanf("%d %d", &user_x, &user_y);
        
        if (user_x < 0 || user_x >= MATRIX_SIZE || user_y < 0 || user_y >= MATRIX_SIZE) {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }
        
        if (current->question[user_x][user_y] == 'x') {
            printf("You hit a mine! You'll return to Level 1.\n");
            current = head;
        } else if (current->question[user_x][user_y] == 'o') {
            printf("You've already uncovered that cell. Try again.\n");
        } else {
            current->question[user_x][user_y] = 'o'; // Mark the cell as uncovered
            
            if (allUncovered(current,current->level)) {
                printf("Good, you have passed level %d\n", current->level);
                
                if (current->level == 1) {
                    if (ctr2 == 0) {
                        char ques[4][4] = {{'*', '*', '*', '*'},
                                          {'*', 'x', '*', 'x'},
                                          {'*', '*', '*', '*'},
                                          {'*', '*', '*', '*'}};
                        int ans_x[2] = {1, 1};
                        int ans_y[2] = {1, 3};
                        add_Node(2, ques);
                    }
                    ctr2 = 1;
                    current = current->next;
                } else if (current->level == 2) {
                    if (ctr3 == 0) {
                        char ques[4][4] = {{'*', '*', '*', '*'},
                                          {'*', 'x', '*', 'x'},
                                          {'*', 'x', '*', '*'},
                                          {'*', '*', '*', '*'}};
                        int ans_x[3] = {1, 1, 2};
                        int ans_y[3] = {1, 3, 1};
                        add_Node(3, ques);
                        ctr3 = 1;
                    }
                    current = current->next;
                } else if (current->level == 3) {
                    printf("Congratulations, you have won the game!\n");
                    break;
                }
            }
        }
    }
}

int main() {
    char ques[4][4] = {{'*', '*'},
                      {'*', 'x'}};

    add_Node(1, ques);
    play_game(head);
    return 0;
}
