#include "Maze.h"
using namespace std;
Maze::Maze(int rows, int cols) : rows_(rows), cols_(cols), maze_(rows, vector<int>(cols, 0)) {}
void Maze::generateRandomMaze() {
    maze_.clear(); // 清空之前的迷宫
    maze_.resize(rows_, vector<int>(cols_, 1)); // 初始化为全障碍
    // 随机生成通路（0: 通路, 1: 障碍）
    srand(time(0)); // 设置随机种子
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            // 随机设置障碍物和通路
            if (rand() % 3 == 0) { // 三分之一的概率为障碍
                maze_[i][j] = 1;
            }
            else {
                maze_[i][j] = 0;
            }
        }
    }
    // 确保入口和出口是通路
    maze_[0][0] = 0; // 起点
    maze_[rows_ - 1][cols_ - 1] = 0; // 终点

    path_.clear();
    path_.resize(rows_, vector<int>(cols_, 0));
}

bool Maze::findPathNonRecursive(int startRow, int startCol, int endRow, int endCol) {
    LinkedStack stack;
    vector<vector<bool>> visited(rows_, vector<bool>(cols_, false));
    path_ = maze_; // 迷宫路径标记
    pathDirections_.clear(); // 清空方向记录
    pathDirections_.resize(rows_, vector<int>(cols_, -1)); // 初始化为-1

    stack.push(startRow, startCol, -1); // 初始方向为-1
    visited[startRow][startCol] = true;

    while (!stack.isEmpty()) {
        int row, col, dir;
        stack.pop(row, col, dir);
        dir++; // 下一个方向

        while (dir < 4) {
            int nextRow = row + dirs[dir][0];
            int nextCol = col + dirs[dir][1];

            // 找到出口
            if (nextRow == endRow && nextCol == endCol) {
                path_[row][col] = 2;       // 标记当前坐标
                path_[endRow][endCol] = 2; // 标记出口
                pathDirections_[row][col] = dir; // 记录方向
                return true;
            }

            if (nextRow >= 0 && nextRow < rows_ &&
                nextCol >= 0 && nextCol < cols_ &&
                maze_[nextRow][nextCol] == 0 &&
                !visited[nextRow][nextCol]) {

                // 记录当前坐标的方向
                pathDirections_[row][col] = dir;

                // 压栈并移动
                stack.push(row, col, dir);
                visited[nextRow][nextCol] = true;
                path_[row][col] = 2; // 标记路径
                row = nextRow;
                col = nextCol;
                dir = -1; // 重置方向
            }
            else {
                dir++;
            }
        }
    }
    return false;
}

void Maze::findAllPathsRecursive(int startRow, int startCol, int endRow, int endCol) {
    vector<pair<int, int>> currentPath;
    path_ = maze_; // 重置路径标记
    allPaths_.clear();
    dfs(startRow, startCol, endRow, endCol, currentPath);
}

void Maze::dfs(int row, int col, int endRow, int endCol, vector<pair<int, int>>& currentPath) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || maze_[row][col] != 0 || path_[row][col] == 2) {
        return; // 越界或障碍或已访问
    }

    currentPath.push_back({ row, col });
    path_[row][col] = 2; // 标记为路径

    if (row == endRow && col == endCol) {
        allPaths_.push_back(currentPath); // 找到一条路径
    }
    else {
        // 尝试四个方向
        for (int i = 0; i < 4; ++i) {
            dfs(row + dirs[i][0], col + dirs[i][1], endRow, endCol, currentPath);
        }
    }

    path_[row][col] = 0; // 回溯
    currentPath.pop_back();
}

void Maze::printPathTriplets() const {
    // 找到起点（标记为2的第一个坐标）
    int startRow = -1, startCol = -1;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (path_[i][j] == 2) {
                startRow = i;
                startCol = j;
                break;
            }
        }
        if (startRow != -1) break;
    }

    // 从起点开始追踪方向
    int currentRow = startRow, currentCol = startCol;
    while (true) {
        int dir = pathDirections_[currentRow][currentCol];
        if (dir == -1) break; // 终点无方向
        cout << "(" << currentRow << "," << currentCol << "," << dir << ")" << endl;
        currentRow += dirs[dir][0];
        currentCol += dirs[dir][1];
    }
}