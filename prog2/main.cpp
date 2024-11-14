#include <iostream>
#include <windows.h>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct vertex{
    size_t number;
    vector<vertex*> destinations;
};

int bfs(vector<vertex*> graphs, int start, int destination) {
    vector<int> dists(graphs.size(), INT_MAX);
    dists[start] = 0;

    vertex* now_graph;
    unordered_set<int> visited;
    queue<vertex*> graph_queue;
    graph_queue.push(graphs[start]);

    while (!graph_queue.empty()) {
        now_graph = graph_queue.front();
        graph_queue.pop();

        for (auto dest : now_graph->destinations) {
            if (visited.find(dest->number) == visited.end()) {
                graph_queue.push(dest);
            }

            if (dists[now_graph->number] + 1 < dists[dest->number]) {
                dists[dest->number] = dists[now_graph->number] + 1;
            }
        }
        visited.insert(now_graph->number);
    }
    return dists[destination];
}

int main(int argc,char* argv[]) {
    if (argc != 2) {
        cerr << "Error: not valid usage of prog (./prog.exe count)";
        return 1;
    }
    int res, etalon_res = 3;


    vertex v1 = {0};
    vertex v2 = {1};
    vertex v3 = {2};
    vertex v4 = {3};
    vertex v5 = {4};
    vertex v6 = {5};
    vertex v7 = {6};

    v1.destinations = {&v2, &v4};
    v2.destinations = {&v1, &v3};
    v3.destinations = {&v2, &v4, &v6};
    v4.destinations = {&v1, &v3, &v6};
    v5.destinations = {&v3, &v7};
    v6.destinations = {&v3, &v4, &v7};
    v7.destinations = {&v5, &v6};

    vector<vertex*> graph = {&v1, &v2, &v3, &v4, &v5, &v6, &v7};
    for (int i = 0; i < atoi(argv[1]); i++) {
        res = bfs(graph, 0, 6);
        if (res != etalon_res) {
            cerr << "Error: wrong answer!\n";
            return 1;
        }
    }
    return 0;
}