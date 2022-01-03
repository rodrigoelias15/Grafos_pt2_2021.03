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

#define MAX_INT 999999

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
    this->first_node = this->last_node = NULL;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != NULL)
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
// Function that verifies if the graph is directed
bool Graph::getDirected()
{
    return this->directed;
}
// Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{
    return this->weighted_edge;
}

// Function that verifies if the graph is weighted at the nodes
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
Node *Graph::insertNode(int id)
{
    if (this->first_node == NULL)
    {
        Node *node = new Node(id);
        this->first_node = node;
        this->last_node = node;
    }
    else
    {
        if (!searchNode(id))
        {
            Node *node = new Node(id);
            this->last_node->setNextNode(node);
            this->last_node = node;
        }
        else
        {
            cout << "Node already exists!" << endl;
        }
    }
    return this->last_node;
}

void Graph::insertEdge(int id, int target_id, float weight)
{
}

bool Graph::removeNode(int id)
{
    if (searchNode(id))
    {
        Node *excluded = this->last_node;

        // Se a raiz for o nó a ser excluido, passo a referencia para o prox no
        if (this->later_node_of_search == this->first_node)
        {
            this->first_node = this->first_node->getNextNode();
        }
        else
        { // aponto o proximo no do no a ser removido para o anterior, para nao quebrar os ponteiros
            this->previous_node_of_search = this->later_node_of_search->getNextNode();
        }

        this->later_node_of_search = this->first_node;

        while (this->later_node_of_search != NULL)
        { // continuar o método
            return false;
        }

        this->order--;
        excluded->~Node();
        return true;
    }
    return false;
}

bool Graph::searchNode(int id)
{
    this->later_node_of_search = this->first_node;
    this->previous_node_of_search = NULL;

    while (this->later_node_of_search != NULL)
    {
        if (this->later_node_of_search->getId() == id)
            return true;
        if (this->later_node_of_search->getNextNode() == NULL)
            return false;
        this->previous_node_of_search = this->later_node_of_search;
        this->later_node_of_search = this->later_node_of_search->getNextNode();
    }
    return false;
}

Node *Graph::getNode(int id)
{
    this->later_node_of_search = this->first_node;
    this->previous_node_of_search = NULL;

    while (this->later_node_of_search != NULL)
    {
        if (this->later_node_of_search->getId() == id)
            return this->later_node_of_search;
        if (this->later_node_of_search->getNextNode() == NULL)
            return NULL;
        this->previous_node_of_search = this->later_node_of_search;
        this->later_node_of_search = this->later_node_of_search->getNextNode();
    }
    return NULL;
}

// Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(ofstream &output_file)
{
}

float Graph::floydMarshall(int idSource, int idTarget)
{
}

float Graph::dijkstra(int idSource, int idTarget)
{
}

// function that prints a topological sorting
void topologicalSorting()
{
}

void breadthFirstSearch(ofstream &output_file)
{
}

Graph *Graph::getVertexInduced()
{
    string answer_user;
    Node *aux_node = this->first_node;
    Edge *aux_edge;

    cout << endl;
    cout << "Enter id_nodes of graph and split with ',' : ";
    cin >> answer_user;

    vector<int> id_nodes;
    id_nodes.clear();

    stringstream ss(answer_user);

    while (getline(ss, answer_user, ','))
    {
        if (getNode(atoi(answer_user.c_str())))
            id_nodes.push_back(atoi(answer_user.c_str()));
        else
            cout << "Error. Node wasn't found.";
    }

    Graph *subgraph = new Graph(id_nodes.size(), this->directed, this->weighted_edge, this->weighted_node);

    // clean graph
    while (aux_node != NULL)
    {
        aux_node->setIsVisited(false);
        aux_node = aux_node->getNextNode();
    }

    int i, j;
    for (i = 0; i < id_nodes.size(); i++)
    {
        for (j = i + 1; j < id_nodes.size(); j++)
        {
            if ((!getNode(id_nodes[j])->isNodeVisited() && getNode(id_nodes[i])->searchEdge(id_nodes[j])))
            {
                aux_edge = getNode(id_nodes[i])->getEdge(id_nodes[j]);
                subgraph->insertEdge(id_nodes[i], id_nodes[j], aux_edge->getWeight());
            }
        }
        getNode(id_nodes[i])->setIsVisited(true);
    }

    cout << "Subgraph was built with success!";

    return subgraph;
}

string Graph::agmKruskal(Graph *sub_graph)
{
    this->printer << "-->AGM Kruskal\n";
    this->printer << "Will be done" << endl;
    return this->printer.str();
}

string Graph::agmPrim(Graph *sub_graph)
{
    this->printer << "-->AGM Prim\n";

    int i, j, aux_weight, aux_index_subgraph, aux_number_edges = 0;
    Node *aux_node;
    Edge *aux_edge;
    int **graph = new int *[this->order];
    int *minimal_cost = new int[this->order];
    int *nodes_adj = new int[this->order];
    bool *nodes_visited = new bool[this->order];

    for (i = 0; i < this->order; i++)
    {
        graph[i] = new int[this->order];
        minimal_cost[i] = MAX_INT;
        for (int j = 0; j < this->order; j++)
            graph[i][j] = MAX_INT;
    }

    for (aux_node = sub_graph->getFirstNode(); aux_node != NULL; aux_node = aux_node->getNextNode())
    {
        if (aux_edge->getNextEdge() != NULL)
        {
            for (aux_edge = aux_node->getFirstEdge(); aux_edge != NULL; aux_edge = aux_edge->getNextEdge())
            {
                graph[aux_node->getId()][aux_edge->getTargetId()] = aux_edge->getWeight();
                graph[aux_edge->getTargetId()][aux_node->getId()] = aux_edge->getWeight();
            }
        }
    }
    Node *aux_node_subgraph = sub_graph->getFirstNode();

    for (j = 0; j < this->order; j++)
    {
        minimal_cost[i] = graph[aux_node_subgraph->getId()][i];
        nodes_adj[i] = aux_node_subgraph->getId();
        nodes_visited[i] = false;
    }

    nodes_visited[aux_node_subgraph->getId()] = true;
    aux_index_subgraph = aux_node_subgraph->getId();

    this->printer << "graph {" << endl;

    for (i = 0; i < this->order; i++)
    {
        int min_cost = MAX_INT;
        int aux_index = 0;

        for (j = 0; j < this->order; j++)
        {
            if (minimal_cost[j] < min_cost && !nodes_visited[j])
            {
                min_cost = minimal_cost[j];
                aux_index = j;
            }
        }

        if (aux_index == 0 && min_cost == MAX_INT)
            break;
        else
            aux_weight += min_cost;

        this->printer << " -- " << aux_index_subgraph << " -- " << aux_index;
        this->printer << " [label = " << min_cost << "]" << endl;

        aux_index_subgraph = aux_index;
        nodes_visited[aux_index] = true;
        aux_number_edges++;

        for (j = 0; j < this->order; j++)
        {
            if ((graph[aux_index][j] < minimal_cost[j]) && !nodes_visited[j])
            {
                minimal_cost[j] = graph[aux_index][j];
                nodes_adj[j] = aux_index;
            }
        }
    }

    this->printer << "}" << endl;

    for (i = 0; i < this->order; i++)
    {
        delete[] graph[i];
    }

    delete[] graph;

    return this->printer.str();
}