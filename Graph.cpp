#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}


Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id)
{
    
}

void Graph::insertEdge(int id, int target_id, float weight)
{

    
}

void Graph::removeNode(int id){ 
    
}

bool Graph::searchNode(int id)
{
    
}

Node *Graph::getNode(int id)
{

    
}


//Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(ofstream &output_file){
    
}



float Graph::floydMarshall(int idSource, int idTarget){
    
}

   

float Graph::dijkstra(int idSource, int idTarget){
    
}

//function that prints a topological sorting
void topologicalSorting(){

}

void breadthFirstSearch(ofstream& output_file){

}

Graph* Graph::getVertexInduced(){
    string answer_user;
    Node* aux_node = this->first_node;
    Edge* aux_edge;

    cout << endl;
    cout << "Enter id_nodes of graph and split with ',' : ";
    cin >> answer_user;

    vector<int> id_nodes;
    id_nodes.clear();

    stringstream ss(answer_user);

    while (getline(ss, answer_user, ',')){
        if(getNode(atoi(answer_user.c_str())))
            id_nodes.push_back(atoi(answer_user.c_str()));
        else
            cout << "Error. Node wasn't found.";
    }

    Graph *subgraph = new Graph(id_nodes.size(), this->directed, this->weighted_edge, this->weighted_node);

    //clean graph
    while(aux_node != NULL){
        aux_node->setIsVisited(false);
        aux_node = aux_node->getNextNode();
    }

    int i,j;
    for(i = 0; i < id_nodes.size(); i++){
        for(j = i+1; j < id_nodes.size(); j++){
            if((!getNode(id_nodes[j])->isNodeVisited() && getNode(id_nodes[i])->searchEdge(id_nodes[j]))){
                aux_edge = getNode(id_nodes[i])->getEdge(id_nodes[j]);
                subgraph->insertEdge(id_nodes[i], id_nodes[j], aux_edge->getWeight());
            }
        }
        getNode(id_nodes[i])->setIsVisited(true);
    }

    cout << "Subgraph was built with success!";

    return subgraph;
}

string Graph::agmKuskal(Graph * sub_graph){
    this->printer << "-->AGM Kuskal\n";
    this->printer << "Will be done" << endl;
    return this->printer.str();
}

Graph* agmPrim(){

}
