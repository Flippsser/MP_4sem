#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct AMatrix {
    int n;
    vector<vector<int>> data;
    AMatrix(int size) : n(size), data(size, vector<int>(size, 0)) {}
};

struct AList {
    int n;
    vector<vector<int>> data;
    AList(int size) : n(size), data(size) {}
};

AList matrixToList(const AMatrix& m) {
    AList lst(m.n);
    for (int i = 0; i < m.n; ++i)
        for (int j = 0; j < m.n; ++j)
            if (m.data[i][j] == 1)
                lst.data[i].push_back(j);
    return lst;
}

AMatrix listToMatrix(const AList& lst) {
    AMatrix mat(lst.n);
    for (int i = 0; i < lst.n; ++i)
        for (int v : lst.data[i])
            mat.data[i][v] = 1;
    return mat;
}

void printMatrix(const AMatrix& m) {
    for (auto& row : m.data) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
}

void printList(const AList& lst) {
    for (int i = 0; i < lst.n; ++i) {
        cout << i << ": ";
        if (lst.data[i].empty()) cout << "-";
        else for (int v : lst.data[i]) cout << v << " ";
        cout << "\n";
    }
}

void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << "\n";
}

vector<int> BFS(const AList& g, int start) {
    vector<int> visited(g.n, 0), order;
    queue<int> q;
    visited[start] = 1;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : g.data[u])
            if (!visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
    }
    return order;
}

vector<int> DFS(const AList& g, int start) {
    vector<int> visited(g.n, 0), order;
    vector<int> stack = { start };
    while (!stack.empty()) {
        int u = stack.back(); stack.pop_back();
        if (visited[u]) continue;
        visited[u] = 1;
        order.push_back(u);
        for (auto it = g.data[u].rbegin(); it != g.data[u].rend(); ++it)
            if (!visited[*it]) stack.push_back(*it);
    }
    return order;
}

void topoDFS(const AList& g, int u, vector<int>& visited, vector<int>& res) {
    visited[u] = 1;
    for (int v : g.data[u])
        if (!visited[v]) topoDFS(g, v, visited, res);
    res.push_back(u);
}

vector<int> topologicalSort(const AList& g) {
    vector<int> visited(g.n, 0), res;
    for (int i = 0; i < g.n; ++i)
        if (!visited[i]) topoDFS(g, i, visited, res);
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<vector<int>> dirMatrixData = {
        {0,1,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,1,0},
        {0,0,0,0,0,1},
        {0,0,0,0,0,1},
        {0,0,0,0,0,0}
    };
    AMatrix dirMat(6);
    dirMat.data = dirMatrixData;

    cout << "Матрица смежности:\n"; printMatrix(dirMat);
    AList dirList = matrixToList(dirMat);
    cout << "\nСписок смежных вершин:\n"; printList(dirList);
    cout << "\nПреобразование обратно в матрицу:\n"; printMatrix(listToMatrix(dirList));

    cout << "\nBFS от вершины 0: "; printVector(BFS(dirList, 0));
    cout << "DFS от вершины 0: "; printVector(DFS(dirList, 0));
    cout << "Топологическая сортировка: "; printVector(topologicalSort(dirList));

    return 0;
}