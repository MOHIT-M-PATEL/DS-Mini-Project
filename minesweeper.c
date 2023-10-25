#include <stdio.h>
#include <stdlib.h>

// Define cell structure
struct Cell {
    char content;  // '-' for unrevealed, '1' for one mine nearby, '*' for mine
    struct Cell* next;
};

// Function prototypes
void printGrid(struct Cell* grid[], int rows, int cols);
void revealCell(struct Cell* grid[], int row, int col, int rows, int cols);

// Function to create a new cell
struct Cell* createCell(char content) {
    struct Cell* newCell = (struct Cell*)malloc(sizeof(struct Cell));
    newCell->content = content;
    newCell->next = NULL;
    return newCell;
}

// Function to print the Minesweeper grid
void printGrid(struct Cell* grid[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        struct Cell* current = grid[i];
        while (current != NULL) {
            printf("%c ", current->content);
            current = current->next;
        }
        printf("\n");
    }
}

// Function to reveal a cell
void revealCell(struct Cell* grid[], int row, int col, int rows, int cols) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        struct Cell* cell = grid[row];
        for (int i = 0; i < col; i++) {
            cell = cell->next;
        }

        if (cell->content == '-') {
            // TODO: Implement logic for revealing the cell based on game rules
            // For now, just mark it as revealed
            cell->content = 'R';
        }
    }
}

int main() {
    // Example Minesweeper grid using linked list
    const int rows = 10;
    const int cols = 10;

    struct Cell* minesweeperGrid[rows];

    // Initialize the grid with unrevealed cells
    for (int i = 0; i < rows; i++) {
        minesweeperGrid[i] = createCell('-');
        struct Cell* current = minesweeperGrid[i];
        for (int j = 1; j < cols; j++) {
            current->next = createCell('-');
            current = current->next;
        }
    }

    // Set a mine in the middle for testing
    minesweeperGrid[rows / 2][cols / 2].content = '*';

    // Game loop
    int row, col;
    do {
        // Print the Minesweeper grid
        printGrid(minesweeperGrid, rows, cols);

        // Get user input
        printf("Enter row and column to reveal (e.g., 2 3): ");
        scanf("%d %d", &row, &col);

        // Reveal the selected cell
        revealCell(minesweeperGrid, row, col, rows, cols);

        // TODO: Add game logic for revealing cells and checking for game over/win conditions

    } while (1);  // Change the loop condition based on game logic

    return 0;
}
