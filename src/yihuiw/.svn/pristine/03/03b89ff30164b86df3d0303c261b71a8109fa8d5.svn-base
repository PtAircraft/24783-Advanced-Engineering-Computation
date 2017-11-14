#include "astar.h"

#include <iostream>

std::vector <YsShellExt::VertexHandle> A_Star(const YsShellExt &shl,YsShellExt::VertexHandle startVtHd,YsShellExt::VertexHandle goalVtHd)
{
    //// The set of nodes already evaluated.
    //closedSet := {}
    std::unordered_set <YSHASHKEY> closedSet;
    //// The set of currently discovered nodes that are not evaluated yet.
    //// Initially, only the start node is known.
    //openSet := {start}
    YsAVLTree<double, YsShellExt::VertexHandle> tree;
    std::unordered_map <YSHASHKEY, YsAVLTree<double, YsShellExt::VertexHandle>::NodeHandle> keyNodeMapping;
    tree.Insert(0, startVtHd);
    keyNodeMapping.emplace(shl.GetSearchKey(startVtHd), tree.RootNode());
    //// For each node, which node it can most efficiently be reached from.
    //// If a node can be reached from many nodes, cameFrom will eventually contain the
    //// most efficient previous step.
    //cameFrom := the empty map
    std::unordered_map <YSHASHKEY, YsShellExt::VertexHandle> cameFrom;
    //// For each node, the cost of getting from the start node to that node.
    //gScore := map with default value of Infinity
    std::unordered_map <YSHASHKEY, double> g_score;
    //// The cost of going from start to start is zero.
    //gScore[start] := 0
    g_score.emplace(shl.GetSearchKey(startVtHd), 0);
    //// For each node, the total cost of getting from the start node to the goal
    //// by passing by that node. That value is partly known, partly heuristic.
    //fScore := map with default value of Infinity
    std::unordered_map <YSHASHKEY, double> f_score;
    //// For the first node, that value is completely heuristic.
    //fScore[start] := heuristic_cost_estimate(start, goal)
    f_score.emplace(shl.GetSearchKey(startVtHd), (shl.GetVertexPosition(startVtHd) - shl.GetVertexPosition(goalVtHd)).GetLength());
    //while openSet is not empty
    while (!tree.empty()) {
        //current := the node in openSet having the lowest fScore[] value
        YsShellExt::VertexHandle current = tree.Value(tree.First());
        //if current = goal
        if (current == goalVtHd) {
              //return reconstruct_path(cameFrom, current)
            return A_Star_ReconstructPath(shl, cameFrom, current);
        }
        //openSet.Remove(current)
        tree.Delete(tree.First());
        keyNodeMapping.erase(shl.GetSearchKey(current));
        //closedSet.Add(current)
        closedSet.emplace(shl.GetSearchKey(current));
        //get the neighbor
        auto connVtx = shl.GetConnectedVertex(current);
        //for each neighbor of current
        for (int e = 0; e < connVtx.size(); e++) {
            auto neiVtHd = connVtx[e];
            //if neighbor in closedSet
            if (closedSet.find(shl.GetSearchKey(neiVtHd)) != closedSet.end()) {
                //continue // Ignore the neighbor which is already evaluated.
                continue;
            } else {
                //// The distance from start to a neighbor
                double dis = (shl.GetVertexPosition(current) - shl.GetVertexPosition(neiVtHd)).GetLength();
                double gCurrent = g_score.find(shl.GetSearchKey(current))->second;
                //tentative_gScore := gScore[current] + dist_between(current, neighbor)
                double tentative_gScore = gCurrent + dis;
                double heuristic_cost_estimate = (shl.GetVertexPosition(neiVtHd) - shl.GetVertexPosition(goalVtHd)).GetLength();

                //if neighbor not in openSet // Discover a new node
                if (keyNodeMapping.find(shl.GetSearchKey(neiVtHd)) == keyNodeMapping.end()) {
                    //openSet.Add(neighbor)
                    auto node = tree.Insert(tentative_gScore + heuristic_cost_estimate, neiVtHd);
                    keyNodeMapping.emplace(shl.GetSearchKey(neiVtHd), node);
                    //else if tentative_gScore >= gScore[neighbor]
                } else {
                    if (tentative_gScore < g_score.find(shl.GetSearchKey(neiVtHd))->second) {
                        tree.Delete(keyNodeMapping.find(shl.GetSearchKey(neiVtHd))->second);
                        auto nodeHd = tree.Insert(tentative_gScore + heuristic_cost_estimate, neiVtHd);
                        keyNodeMapping.erase(shl.GetSearchKey(neiVtHd));
                        keyNodeMapping.emplace(shl.GetSearchKey(neiVtHd), nodeHd);
                        // update g f camefrom
                        g_score.erase(shl.GetSearchKey(neiVtHd));
                        g_score.emplace(shl.GetSearchKey(neiVtHd), tentative_gScore);
                        f_score.erase(shl.GetSearchKey(neiVtHd));
                        f_score.emplace(shl.GetSearchKey(neiVtHd), tentative_gScore + heuristic_cost_estimate);
                        cameFrom.erase(shl.GetSearchKey(neiVtHd));
                        cameFrom.emplace(shl.GetSearchKey(neiVtHd), current);
                    }
                }
                //// This path is the best until now. Record it!
                //cameFrom[neighbor] := current
                cameFrom.emplace(shl.GetSearchKey(neiVtHd), current);
                //gScore[neighbor] := tentative_gScore
                g_score.emplace(shl.GetSearchKey(neiVtHd), tentative_gScore);
                //fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
                f_score.emplace(shl.GetSearchKey(neiVtHd), tentative_gScore + heuristic_cost_estimate);
            }
        }
    }
                return std::vector <YsShellExt::VertexHandle>(); // Path not found.
}

std::vector <YsShellExt::VertexHandle> A_Star_ReconstructPath(
    const YsShellExt &shl,const std::unordered_map <YSHASHKEY,YsShellExt::VertexHandle> &cameFrom,YsShellExt::VertexHandle current)
{
	std::vector <YsShellExt::VertexHandle> path;
    path.push_back(current);
    while (true) {
        auto next = cameFrom.find(shl.GetSearchKey(current));
        if (next == cameFrom.end()) {
            break;
        }
        current = next->second;
        path.push_back(current);
    }
	return path;
}
