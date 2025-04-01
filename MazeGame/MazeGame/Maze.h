#pragma once
#include <vector>
#include <fstream>
#include <stack>
#include "LinkedStack.h"
using namespace std;
class Maze {
public:
    Maze(int rows, int cols); // 构造函数
    void generateRandomMaze(); // 生成随机迷宫
    bool findPathNonRecursive(int startRow, int startCol, int endRow, int endCol); // 非递归求解
    void findAllPathsRecursive(int startRow, int startCol, int endRow, int endCol); // 递归求所有路径
   // void printMazeWithPath() const; // 输出非递归迷宫及通路
   // void printMazeWithPath(const vector<pair<int, int>>& path) const;//输出递归迷宫及通路
    const vector<vector<pair<int, int>>>& getAllPaths() const { return allPaths_; }
    void printPathTriplets() const;
    int getRows() const { return rows_; }
    int getCols() const { return cols_; }
    const vector<vector<int>>& getMaze() const { return maze_; }
    vector<tuple<int, int, int>> getPathTriplets() const {
        vector<tuple<int, int, int>> triplets;
        int currentRow = 0, currentCol = 0;
        while (true) {
            int dir = pathDirections_[currentRow][currentCol];
            if (dir == -1) break;
            triplets.emplace_back(currentRow, currentCol, dir);
            currentRow += dirs[dir][0];
            currentCol += dirs[dir][1];
        }
        return triplets;
    }

private:
    int rows_, cols_;
    vector<vector<int>> maze_;                // 迷宫数据（0:通路，1:障碍）
    vector<vector<int>> path_;                // 当前路径标记
    vector<vector<pair<int, int>>> allPaths_; // 存储递归找到的所有路径坐标序列
    vector<vector<int>> pathDirections_;     // 记录非递归算法中每个节点的移动方向

    // 方向数组
    const int dirs[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };//定义四个移动方向（下、右、上、左），对应方向值 0-3

    // 递归辅助函数
    void dfs(int row, int col, int endRow, int endCol, vector<pair<int, int>>& currentPath);
};
