// Maximize the number of cores within the largest connected component using at most K violations

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<int>> color(n, vector<int>(m, -1));
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    int maximum_cores = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] != '.' || visited[i][j])
                continue;
            queue<pair<int, int>> q;
            q.push({i, j});
            visited[i][j] = true;
            color[i][j] = 0;
            int count_black = 0;
            int count_white = 0;
            while (!q.empty())
            {
                auto [x, y] = q.front();
                q.pop();
                if (color[x][y] == 0)
                    count_black++;
                else
                    count_white++;
                for (int d = 0; d < 4; d++)
                {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                        continue;
                    if (grid[nx][ny] == 'X')
                        continue;
                    if (!visited[nx][ny])
                    {
                        visited[nx][ny] = true;
                        color[nx][ny] = color[x][y] ^ 1;
                        q.push({nx, ny});
                    }
                }
            }
            int component_size = count_black + count_white;
            int best_independent = max(count_black, count_white);
            int result = min(component_size, best_independent + k);
            maximum_cores = max(maximum_cores, result);
        }
    }
    cout << maximum_cores << endl;
    return 0;
}