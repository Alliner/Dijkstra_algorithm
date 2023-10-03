#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
//#include <queue>
//#include <unordered_set>

using namespace std;

int main() {
    const int someMax = 1000000000;
    //���� ������
    unordered_map<string, unordered_map<string, int>> graph;
    graph.insert({ "A", {{"B",2},{"C",5}} });
    graph.insert({ "B", {{"C",8},{"D",7}} });
    graph.insert({ "C", {{"D",2},{"E",4}} });
    graph.insert({ "D", {{"F",1}} });
    graph.insert({ "E", {{"D",6},{"F",3}} });
    graph.insert({ "F", {} });

    //������� ���������
    unordered_map<string, int> costs;
    costs.insert({ "A", 0 });
    costs.insert({ "B", someMax });
    costs.insert({ "C", someMax });
    costs.insert({ "D", someMax });
    costs.insert({ "E", someMax });
    costs.insert({ "F", someMax });


    unordered_map<string, string> parent;
    parent.insert({ "B", "A" });
    parent.insert({ "C", "A" });

    vector<string> processed;
    string firstNode = "A", lastNode = "F";

    for (const auto& n : costs)
        cout << n.first << " = " << n.second << "; \n";

    for (const auto& n : graph) {
        const auto neighbours = n.second;
        cout << n.first << ": \n";
        for (const auto& k : neighbours)
            cout << k.first << " = " << k.second << "; \n";
    }

    while (true) {
        int lowCost = someMax;
        string node = "NotNode";
        for (const auto& n : costs)
            //���� ������� � ����������� ���������� � �� ���������� - �������� ��
            if (n.second < lowCost)
                if (find(processed.cbegin(), processed.cend(), n.first) == processed.cend()) {
                    node = n.first;
                    lowCost = n.second;
                }
        //���� ������ ����� �� ������� - �����
        if (node == "NotNode")break;
        const auto neighbours = graph[node];
        //������������ ������� � ����������� ����������
        for (const auto& k : neighbours) {
            if (costs[k.first] > lowCost + k.second) {
                costs[k.first] = lowCost + k.second;
                parent[k.first] = node;
            }
        }
        processed.push_back(node);

    }
    
    //����� ������� ���� ����� �� ������ �������
    cout << "\nOut lenght path:\n";
    for (const auto& n : costs)
        cout << n.first << " = " << n.second << "; \n";
    //����� ������������ ������
    cout << "\nOut parent:\n";
    for (const auto& n : parent)
        cout << n.first << " = " << n.second << "; \n";
    //����� �������� �� � �� F
    cout << "\nPath:\n";
    while (true) {
        cout << lastNode;
        if (lastNode == firstNode) break;
        lastNode = parent[lastNode];

    }

}