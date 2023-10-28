#include <stdio.h>
#include <stdlib.h>

// Define cell structure
struct Cell {
    char content;  // '-' for unrevealed, '1' for one mine nearby, '*' for mine
    int hasBomb;   // 1 if the cell has a bomb, 0 otherwise
    int bombHit;   // 1 if a bomb has been hit, 0 otherwise
    struct Cell* next;
};

// Function prototypes
void printGrid(struct Cell* grid[], int rows, int cols);
void revealCell(struct Cell* grid[], int row, int col, int rows, int cols, int* gameOver, int* bombRevealed);
void placeBombs(struct Cell* grid[], int rows, int cols, int bombPositions[][2], int numBombs);
int allNonBombCellsRevealed(struct Cell* grid[], int rows, int cols);
void cleanup(struct Cell* grid[], int rows);

// Function to create a new cell
struct Cell* createCell(char content, int hasBomb) {
    struct Cell* newCell = (struct Cell*)malloc(sizeof(struct Cell));
    newCell->content = content;
    newCell->hasBomb = hasBomb;
    newCell->bombHit = 0;
    newCell->next = NULL;
    return newCell;
}

// Function to print the Minesweeper grid
void printGrid(struct Cell* grid[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        struct Cell* current = grid[i];
        while (current != NULL) {
            if (current->content == '-' || current->content == 'R' || current->content == 'X') {
                printf("%c ", current->content);
            } else {
                if (current->bombHit) {
                    printf("* ");  // Reveal bombs
                } else {
                    printf("- ");  // Hide the bombs
                }
            }
            current = current->next;
        }
        printf("\n");
    }
}

// Function to reveal a cell
void revealCell(struct Cell* grid[], int row, int col, int rows, int cols, int* gameOver, int* bombRevealed) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        struct Cell* cell = grid[row];
        for (int i = 0; i < col; i++) {
            cell = cell->next;
        }

        if (cell->content == '-') {
            // Reveal the cell
            if (cell->hasBomb) {
                // Bomb exploded
                cell->content = 'X';
                cell->bombHit = 1;  // Mark the bomb as hit
                *gameOver = 1;      // Set the game over flag
                *bombRevealed = 1;  // Set the bomb revealed flag
            } else {
                // TODO: Implement logic for revealing the cell based on game rules
                // For now, just mark it as revealed
                cell->content = 'R';
            }
        }
    }
}

// Function to place bombs on the grid
void placeBombs(struct Cell* grid[], int rows, int cols, int bombPositions[][2], int numBombs) {
    for (int k = 0; k < numBombs; k++) {
        int row = bombPositions[k][0];
        int col = bombPositions[k][1];

        struct Cell* cell = grid[row];
        for (int i = 0; i < col; i++) {
            cell = cell->next;
        }

        // Place bomb
        if (!cell->hasBomb) {
            cell->hasBomb = 1;
        } else {
            k--; // Try placing bomb again
        }
    }
}

// Function to check if all non-bomb cells are revealed
int allNonBombCellsRevealed(struct Cell* grid[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        struct Cell* current = grid[i];
        while (current != NULL) {
            if (!current->hasBomb && current->content == '-') {
                return 0;  // Not all non-bomb cells are revealed
            }
            current = current->next;
        }
    }
    return 1;  // All non-bomb cells are revealed
}

// Function to clean up memory
void cleanup(struct Cell* grid[], int rows) {
    for (int i = 0; i < rows; i++) {
        struct Cell* current = grid[i];
        while (current != NULL) {
            struct Cell* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    // Initialize game parameters
    int level = 1;
    const int maxLevel = 5;
    int rows = 2;
    int cols = 2;
    const int numBombs = 1;  // Adjust the number of bombs as needed
    struct Cell* minesweeperGrid[rows];

    // Bomb positions for each level
    int bombPositions[][2] = {
        {1, 1}
    };

    do {
        // Example Minesweeper grid using linked list
        struct Cell* minesweeperGrid[rows];

        // Initialize the grid with unrevealed cells
        for (int i = 0; i < rows; i++) {
            minesweeperGrid[i] = createCell('-', 0);
            struct Cell* current = minesweeperGrid[i];
            for (int j = 1; j < cols; j++) {
                current->next = createCell('-', 0);
                current = current->next;
            }
        }

        // Place bombs on the grid
        placeBombs(minesweeperGrid, rows, cols, bombPositions, numBombs);

        // Game loop
        int row, col;
        int gameOver = 0;        // Game over flag
        int bombRevealed = 0;    // Bomb revealed flag
        do {
            // Print the Minesweeper grid
            printGrid(minesweeperGrid, rows, cols);

            // Get user input
            printf("Enter row and column to reveal (e.g., 0 1) (Min.=0 0 & Max.=%d %d): ", rows - 1, cols - 1);
            scanf("%d %d", &row, &col);

            if (row >= 0 && row < rows && col >= 0 && col < cols) {
                // Reveal the selected cell
                revealCell(minesweeperGrid, row, col, rows, cols, &gameOver, &bombRevealed);

                // Check if the game is over
                if (gameOver) {
                    if (bombRevealed) {
                        printf("Game Over! Bomb revealed.\n");
                    } else {
                        printf("Congratulations! Level %d completed.\n", level);
                    }

                    // Ask the user for options after game over
                    int choice;
                    printf("1. Restart the current level\n");
                    printf("2. Start from the first level\n");
                    printf("3. Exit the game\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            // Restart the current level
                            gameOver = 0;
                            bombRevealed = 0;
                            break;
                        case 2:
                            // Start from the first level
                            level = 1;
                            rows = 2;
                            cols = 2;
                            break;
                        case 3:
                            // Exit the game
                            cleanup(minesweeperGrid, rows);
                            return 0;
                        default:
                            printf("Invalid choice. Exiting the game.\n");
                            cleanup(minesweeperGrid, rows);
                            return 0;
                    }
                }

                // Check if all non-bomb cells are revealed to promote to the next level
                if (allNonBombCellsRevealed(minesweeperGrid, rows, cols)) {
                    printf("Congratulations! All non-bomb cells revealed. Proceeding to the next level.\n");
                    break;
                }

                // TODO: Add game logic for revealing cells and checking for win conditions
            } else {
                printf("\nInvalid Location\n\n");
            }

        } while (1);  // Change the loop condition based on game logic

        // Increase the level and adjust rows and cols
        level++;
        rows += 1;
        cols += 1;

    } while (level <= maxLevel);

    cleanup(minesweeperGrid, rows);

    return 0;
}
