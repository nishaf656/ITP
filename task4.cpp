#include <iostream>
#include <vector>
using namespace std;

const int MAX_COLS = 50;

// check if within maze boundaries
bool withinBounds(int r, int c, int totalRows, int totalCols) {
    return (r >= 0 && r < totalRows && c >= 0 && c < totalCols);
}

// recursive maze solver
bool solve_maze(char maze[][MAX_COLS], int totalRows, int totalCols,
                int r, int c, vector<pair<int,int>>& path)
{
    // out of bounds so fail
    if (!withinBounds(r, c, totalRows, totalCols))
        return false;

    // wall hit or visited so fail
    if (maze[r][c] == '#' || maze[r][c] == '*')
        return false;

    // exit reached
    if (maze[r][c] == 'E') {
        path.push_back({r, c});
        return true;
    }

    // mark current as visited, but store if it was S
    bool isStart = (maze[r][c] == 'S');
    if (!isStart)
        maze[r][c] = '*';

    path.push_back({r, c});

    // directions: up, down, left, right
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    // explore all directions
    for (int i = 0; i < 4; i++) {
        int newR = r + dr[i];
        int newC = c + dc[i];

        if (solve_maze(maze, totalRows, totalCols, newR, newC, path))
            return true;
    }

    // remove from path & restore cell
    path.pop_back();

    // eestore only if its not S and not a wall
    if (!isStart)
        maze[r][c] = '.';

    return false;
}


int main() {
    int rows, cols;
    cout << "Enter maze dimensions (rows cols): ";
    cin >> rows >> cols;

    if (rows <= 0 || cols <= 0 || rows > 50 || cols > 50) {
        cout << "Invalid maze size.\n";
        return 0;
    }

    char maze[50][MAX_COLS];

    // Read maze
    cout << "Enter maze row by row (# for walls, . for path, S for start, E for exit):\n";
    int startR = -1, startC = -1;
    int countS = 0, countE = 0;

    for (int r = 0; r < rows; r++) {
        string rowString;
        cout << "Row " << r+1 << ": ";
        cin >> rowString;

        if (rowString.size() != (size_t)cols) {
            cout << "Invalid row length.\n";
            return 0;
        }

        for (int c = 0; c < cols; c++) {
            maze[r][c] = rowString[c];

            if (maze[r][c] == 'S') {
                countS++;
                startR = r;
                startC = c;
            }
            if (maze[r][c] == 'E')
                countE++;
        }
    }

    // edge cases
    if (countS != 1 || countE != 1) {
        cout << "Maze must contain exactly one S and one E.\n";
        return 0;
    }

    cout << "\nSolving maze...\n";

    vector<pair<int,int>> path;
    bool solved = solve_maze(maze, rows, cols, startR, startC, path);

    if (solved) {
        cout << "\nSolution found!\n";
        cout << "Path length: " << path.size() << "\n\n";

        // mark path in maze (except S and E)
        for (auto &p : path) {
            if (maze[p.first][p.second] == '.')
                maze[p.first][p.second] = '*';
        }

        // print maze
        cout << "Final maze with solution path:\n";
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++)
                cout << maze[r][c];
            cout << "\n";
        }

        // print path coords
        cout << "\nPath coordinates:\n";
        for (int i = 0; i < path.size(); i++) {
            cout << "(" << path[i].first << "," << path[i].second << ")";
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\n";

    } else {
        cout << "\nNo solution exists.\n\n";
        cout << "Explored maze:\n";
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++)
                cout << maze[r][c];
            cout << "\n";
        }
    }

    return 0;
}
