#include "Maze.h"
using namespace std;
Maze::Maze(int rows, int cols) : rows_(rows), cols_(cols), maze_(rows, vector<int>(cols, 0)) {}
void Maze::generateRandomMaze() {
    maze_.clear(); // ���֮ǰ���Թ�
    maze_.resize(rows_, vector<int>(cols_, 1)); // ��ʼ��Ϊȫ�ϰ�
    // �������ͨ·��0: ͨ·, 1: �ϰ���
    srand(time(0)); // �����������
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            // ��������ϰ����ͨ·
            if (rand() % 3 == 0) { // ����֮һ�ĸ���Ϊ�ϰ�
                maze_[i][j] = 1;
            }
            else {
                maze_[i][j] = 0;
            }
        }
    }
    // ȷ����ںͳ�����ͨ·
    maze_[0][0] = 0; // ���
    maze_[rows_ - 1][cols_ - 1] = 0; // �յ�

    path_.clear();
    path_.resize(rows_, vector<int>(cols_, 0));
}

bool Maze::findPathNonRecursive(int startRow, int startCol, int endRow, int endCol) {
    LinkedStack stack;
    vector<vector<bool>> visited(rows_, vector<bool>(cols_, false));
    path_ = maze_; // �Թ�·�����
    pathDirections_.clear(); // ��շ����¼
    pathDirections_.resize(rows_, vector<int>(cols_, -1)); // ��ʼ��Ϊ-1

    stack.push(startRow, startCol, -1); // ��ʼ����Ϊ-1
    visited[startRow][startCol] = true;

    while (!stack.isEmpty()) {
        int row, col, dir;
        stack.pop(row, col, dir);
        dir++; // ��һ������

        while (dir < 4) {
            int nextRow = row + dirs[dir][0];
            int nextCol = col + dirs[dir][1];

            // �ҵ�����
            if (nextRow == endRow && nextCol == endCol) {
                path_[row][col] = 2;       // ��ǵ�ǰ����
                path_[endRow][endCol] = 2; // ��ǳ���
                pathDirections_[row][col] = dir; // ��¼����
                return true;
            }

            if (nextRow >= 0 && nextRow < rows_ &&
                nextCol >= 0 && nextCol < cols_ &&
                maze_[nextRow][nextCol] == 0 &&
                !visited[nextRow][nextCol]) {

                // ��¼��ǰ����ķ���
                pathDirections_[row][col] = dir;

                // ѹջ���ƶ�
                stack.push(row, col, dir);
                visited[nextRow][nextCol] = true;
                path_[row][col] = 2; // ���·��
                row = nextRow;
                col = nextCol;
                dir = -1; // ���÷���
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
    path_ = maze_; // ����·�����
    allPaths_.clear();
    dfs(startRow, startCol, endRow, endCol, currentPath);
}

void Maze::dfs(int row, int col, int endRow, int endCol, vector<pair<int, int>>& currentPath) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || maze_[row][col] != 0 || path_[row][col] == 2) {
        return; // Խ����ϰ����ѷ���
    }

    currentPath.push_back({ row, col });
    path_[row][col] = 2; // ���Ϊ·��

    if (row == endRow && col == endCol) {
        allPaths_.push_back(currentPath); // �ҵ�һ��·��
    }
    else {
        // �����ĸ�����
        for (int i = 0; i < 4; ++i) {
            dfs(row + dirs[i][0], col + dirs[i][1], endRow, endCol, currentPath);
        }
    }

    path_[row][col] = 0; // ����
    currentPath.pop_back();
}

void Maze::printPathTriplets() const {
    // �ҵ���㣨���Ϊ2�ĵ�һ�����꣩
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

    // ����㿪ʼ׷�ٷ���
    int currentRow = startRow, currentCol = startCol;
    while (true) {
        int dir = pathDirections_[currentRow][currentCol];
        if (dir == -1) break; // �յ��޷���
        cout << "(" << currentRow << "," << currentCol << "," << dir << ")" << endl;
        currentRow += dirs[dir][0];
        currentCol += dirs[dir][1];
    }
}