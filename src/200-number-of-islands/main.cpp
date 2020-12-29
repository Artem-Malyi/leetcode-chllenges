// https://leetcode.com/problems/number-of-islands/
// 200. Number of Islands

// Given an m x n 2d grid map of '1's(land) and '0's(water), return the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
// You may assume all four edges of the grid are all surrounded by water.

// Time:  O(n^2)
// Space: O(n)
// Pattern: BFS

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int numIslands(vector<vector<char>>& grid) {
    // init visited matrix
    // init empty queue
    // for each element i,j:
    //     if the element is 1:
    //         mark element in visited matrix
    //         if the queue goes from empty to non empty state:
    //             increase island counter by 1
    //             add element coordinates to the queue
    //         remove first element from the queue
    //         check each of surrounding elements and add them to the queue if their value is 1 and if it's not visited yet
    //
    //  ["1","1","0","0","0"],   [ 1 1 0 0 0 ]
    //
    //  ["1","1","0","0","0"],   [ 1 0 0 0 0 ]
    //    ^
    //  ["0","0","1","0","0"],   [ 0 0 0 0 0 ]
    //
    //  ["0","0","0","1","1"]    [ 0 0 0 0 0 ]
    //
    if (grid.empty() || grid[0].empty())
        return 0;
    int islands = 0, width = grid[0].size(), height = grid.size();
    vector<vector<bool>> v(height, vector<bool>(width));
    auto inside = [&](int row, int col) {
        return 0 <= row && row < height && 0 <= col && col < width;
    };
    queue<pair<int, int>> q;
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} };
    for (int row = 0; row < height; row++) { // 1 < 4
        for (int col = 0; col < width; col++) { // 0 < 5
            if (!v[row][col] && grid[row][col] == '1') { // grid[1,0]
                islands++; // 1
                q.push({ row, col }); // [1,1 1,1]
                v[row][col] = true;
                while (!q.empty()) {
                    pair<int, int> p = q.front(); // 0,1
                    q.pop();
                    for (auto dir : directions) {
                        int newRow = p.first + dir.first;
                        int newCol = p.second + dir.second;
                        if (inside(newRow, newCol) && !v[newRow][newCol] && grid[newRow][newCol] == '1') {
                            q.push({ newRow, newCol });
                            v[newRow][newCol] = true;
                        }
                    }
                }
            }
        }
    }
    return islands;
}

void testNumIslands() {
    vector<vector<char>> m1(4, vector<char>(5));
    m1[0] = { '1', '1', '0', '0', '0' };
    m1[1] = { '1', '1', '0', '0', '0' };
    m1[2] = { '0', '0', '1', '0', '0' };
    m1[3] = { '0', '0', '0', '1', '1' };
    assert(3 == numIslands(m1));

    vector<vector<char>> m2(4, vector<char>(5));
    m2[0] = { '1', '1', '1', '1', '0' };
    m2[1] = { '1', '1', '0', '1', '0' };
    m2[2] = { '1', '1', '0', '0', '0' };
    m2[3] = { '0', '0', '0', '0', '0' };
    assert(1 == numIslands(m2));
}

int main() {

    testNumIslands();

	return 0;
}
