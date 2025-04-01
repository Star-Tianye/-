#pragma once
#include <vector>
#include <fstream>
#include <stack>
#include "LinkedStack.h"
using namespace std;
class Maze {
public:
    Maze(int rows, int cols); // ���캯��
    void generateRandomMaze(); // ��������Թ�
    bool findPathNonRecursive(int startRow, int startCol, int endRow, int endCol); // �ǵݹ����
    void findAllPathsRecursive(int startRow, int startCol, int endRow, int endCol); // �ݹ�������·��
   // void printMazeWithPath() const; // ����ǵݹ��Թ���ͨ·
   // void printMazeWithPath(const vector<pair<int, int>>& path) const;//����ݹ��Թ���ͨ·
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
    vector<vector<int>> maze_;                // �Թ����ݣ�0:ͨ·��1:�ϰ���
    vector<vector<int>> path_;                // ��ǰ·�����
    vector<vector<pair<int, int>>> allPaths_; // �洢�ݹ��ҵ�������·����������
    vector<vector<int>> pathDirections_;     // ��¼�ǵݹ��㷨��ÿ���ڵ���ƶ�����

    // ��������
    const int dirs[4][2] = { {1,0}, {0,1}, {-1,0}, {0,-1} };//�����ĸ��ƶ������¡��ҡ��ϡ��󣩣���Ӧ����ֵ 0-3

    // �ݹ鸨������
    void dfs(int row, int col, int endRow, int endCol, vector<pair<int, int>>& currentPath);
};
