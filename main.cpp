#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstdlib> 
#include <ctime>  

using namespace std;

// Функция для нахождения кратчайшего пути от начальной вершины start до всех остальных вершин
vector<int> dijkstra(int n, int start, const vector<vector<int>>& graph) 
{
    vector<int> distance(n, INT_MAX); 
    distance[start] = 0;             

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({ 0, start }); 

    while (!pq.empty()) 
    {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distance[u]) continue;

        for (int v = 0; v < n; v++) 
        {
            int weight = graph[u][v];
            if (weight != 0 && distance[u] + weight < distance[v]) 
            {
                distance[v] = distance[u] + weight;
                pq.push({ distance[v], v });
            }
        }
    }

    return distance;
}

// Функция для генерации случайного графа
vector<vector<int>> generateRandomGraph(int n, int maxWeight) 
{
    vector<vector<int>> graph(n, vector<int>(n, 0));
    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) 
        {
            if (i != j) 
            { // Исключаем петли (рёбра из вершины в саму себя)
                graph[i][j] = rand() % (maxWeight + 1); // Вес от 0 до maxWeight
            }
        }
    }

    return graph;
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    int n = 5;          
    int maxWeight = 100;

    vector<vector<int>> graph = generateRandomGraph(n, maxWeight);

    cout << "Сгенерированный граф (матрица смежности):\n";
    for (const auto& row : graph) 
    {
        for (int weight : row) 
        {
            cout << weight << "\t";
        }
        cout << "\n";
    }

    int start = 0;

    vector<int> distances = dijkstra(n, start, graph);

    cout << "\nКратчайшие расстояния от вершины " << start << ":\n";
    for (int i = 0; i < n; i++) 
    {
        if (distances[i] == INT_MAX) 
        {
            cout << "Вершина " << i << ": недостижима\n";
        }
        else 
        {
            cout << "Вершина " << i << ": " << distances[i] << "\n";
        }
    }

    return 0;
}
