/**************************************************************************************************
 * Implementation of the TAD Graph
 **************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

class Graph
{

    // Atributes
private:
    int order;
    int number_edges;
    bool directed;
    bool weighted_edge;
    bool weighted_node;
    Node *first_node;
    Node *last_node;
    Node *previous_node_of_search;
    Node *later_node_of_search;
    list<pair<int, int> > *adj;
    stringstream printer;

public:
    // Constructor
    Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
    vector<Edge> edges;
    // Destructor
    ~Graph();

    // Getters
    int getOrder();
    int getNumberEdges();
    bool getDirected();
    bool getWeightedEdge();
    bool getWeightedNode();
    Node *getFirstNode();
    Node *getLastNode();

    // Other methods
    void insertEdge(int id, int target_id, float weight);
    Node *getNode(int id);
    int **aux_build_matrix(Node *node, int order, int **dist_nodes);
    Node *insertNode(int id);
    bool removeNode(int id);
    bool removeEdges(int id);
    bool searchNode(int id);

    // methods phase1
    void topologicalSorting();
    void breadthFirstSearch(ofstream &output_file);
    Graph *getVertexInduced();
    Graph *agmKruskal(Graph *graph, ofstream &output_file);
    string agmPrim(Graph *sub_graph);
    string floydWarshall(int idOrigin, int idDestiny);
    string dijkstra(int idOrigin, int idDestiny);

    // methods phase1
    float greed();
    float greedRandom();
    float greedRactiveRandom();
};

#endif // GRAPH_H_INCLUDED
