#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct level {
    int level;
    char question[100];
    int answer;
    struct level* next;
};
typedef struct level Node;
Node *head = NULL;

Node *create_Node(int lev, char *ques, int ans) {
    Node *temp;
    temp = malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Memory not allocated");
        exit(0);
    } else {
        temp->level = lev;
        snprintf(temp->question, sizeof(temp->question), "%s", ques);
        temp->answer = ans;
        temp->next = temp; // Circular reference
    }
    return temp;
}

void add_Node(int lev, char *ques, int ans) {
    Node* new = create_Node(lev, ques, ans);
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

void play_game(Node *head) {
    int user_ans = 0;
    Node *current = head;
    int ctr2=0,ctr3=0;

    while (1) {
        printf("LEVEL %d\n", current->level);
        printf("%s\n", current->question);
        printf("ANS = ");
        scanf("%d", &user_ans);

        if (user_ans == current->answer) {
            printf("Good, you have passed level %d\n\n", current->level);

            if (current->level == 1) {
                if(ctr2==0)
                add_Node(2, "Question 2 (Level 2)", 2);
                ctr2=1;

                current = current->next;
            } 
            else if (current->level == 2) 
            {
                if(ctr3==0)
                add_Node(3, "Question 3 (Level 3)", 3);
                ctr3=1;
                
                current = current->next;
            } 
            else if (current->level == 3) 
            {
                printf("Congratulations, you have won the game!\n");
                break;
            }
        } 
        else 
        {
            printf("\nWrong answer. You'll return to Level 1.\n");
            current = current->next;
        }
    }
}

int main() {
    add_Node(1, "Question 1 (Level 1)", 1);
    play_game(head);
    return 0;
}
