#include "algorithm.h"

#include <queue>
#include <thread>


using namespace std;


void Algorithm::FindShortestPath(vector<Point>& field, int fieldWidth, int fieldHeight)
{
    shortestPath.clear();

    vector<vector<int>> nodes(field.size());
    int startingNode, endingNode;

    // reserve space
    for (int i = 0; i < nodes.size(); ++i)
        nodes[i].reserve(4);

    // fill adjacency list
    for (int i = 0; i < field.size(); ++i) {
        if (!__FitType(field[i])) continue;

        int x = field[i].x,
            y = field[i].y;

        if (field[i].type == PointType::START) startingNode = y * fieldWidth + x;
        else if (field[i].type == PointType::DESTINATION) endingNode = y * fieldWidth + x;

        int leftPoint = y * fieldWidth + (x - 1);
        int rightPoint = y * fieldWidth + (x + 1);
        int topPoint = (y - 1) * fieldWidth + x;
        int bottomPoint = (y + 1) * fieldWidth + x;

        if (x > 0 && __FitType(field[leftPoint])) nodes[i].push_back(leftPoint);
        if (x < fieldWidth - 1 && __FitType(field[rightPoint])) nodes[i].push_back(rightPoint);
        if (y > 0 && __FitType(field[topPoint])) nodes[i].push_back(topPoint);
        if (y < fieldHeight - 1 && __FitType(field[bottomPoint])) nodes[i].push_back(bottomPoint);
    }

    // find shortest path
    vector<bool> passed(nodes.size(), 0);
    vector<bool> noted(nodes.size(), 0);
    vector<int> minimumLengths(nodes.size(), -1);
    minimumLengths[startingNode] = 0;
    vector<vector<int>> minimumPaths(nodes.size());
    minimumPaths[startingNode] = {startingNode};

    queue<int> traversalOrder;
    traversalOrder.push(startingNode);
    int currentNode;
    int cycle = 1;

    while(!traversalOrder.empty()) {
        currentNode = traversalOrder.front();
        traversalOrder.pop();
        passed[currentNode] = 1;

        for (int i = 0; i < nodes[currentNode].size(); ++i) {
            int nodeToTravelTo = nodes[currentNode][i];
            if (!passed[nodeToTravelTo]) {
                if (!noted[nodeToTravelTo]) {
                    traversalOrder.push(nodeToTravelTo);
                    noted[nodeToTravelTo] = 1;
                }
                if (minimumLengths[nodeToTravelTo] == -1 || minimumLengths[currentNode] + 1 < minimumLengths[nodeToTravelTo]) {
                    minimumLengths[nodeToTravelTo] = minimumLengths[currentNode] + 1;
                    minimumPaths[nodeToTravelTo] = minimumPaths[currentNode];
                    minimumPaths[nodeToTravelTo].push_back(nodeToTravelTo);
                }
            }
        }

        // amination
        if (currentNode == fieldWidth * fieldHeight - 1) continue;
        if (currentNode == startingNode || currentNode == endingNode) {
            __SetColor(Color::BLUE);
            __SetPosition(currentNode % fieldWidth * 2, currentNode / fieldWidth);
            cout << string(2, ' ');
        }
        else {
            __SetColor(Color::BRIGHT_BLUE);
            __SetPosition(currentNode % fieldWidth * 2, currentNode / fieldWidth);
            cout << string(2, ' ');
        }
        __SetColor(Color::SEA_WAVE);
        for (int i = 0; i < nodes[currentNode].size(); ++i) {
            int nodeToTravelTo = nodes[currentNode][i];
            if (!passed[nodeToTravelTo] && nodeToTravelTo != endingNode &&
                    nodeToTravelTo != fieldWidth * fieldHeight - 1) {
                __SetPosition(nodeToTravelTo % fieldWidth * 2, nodeToTravelTo / fieldWidth);
                cout << string(2, ' ');
            }
        }

        // slowdown for cute animation
        if (--cycle == 0) {
            cycle = traversalOrder.size();
            this_thread::sleep_for(10ms);
        }
    }

    if(minimumLengths[endingNode] != -1) {
        shortestPath.reserve(minimumLengths[endingNode]);
        for(auto x : minimumPaths[endingNode]) {
            shortestPath.push_back(field[x]);
        }
    }
}


bool Algorithm::__FitType(Point point)
{
    if (point.type == PointType::DESTINATION ||
        point.type == PointType::PASS ||
        point.type == PointType::START)
        return true;
    return false;
}
