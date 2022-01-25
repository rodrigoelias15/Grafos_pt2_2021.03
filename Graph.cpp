/*#include "Graph.h"
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
#include <algorithm>
#include <string.h>
#include <float.h>
#include <iomanip>
#include <cstring>
#include <vector>
*/
#define MAX_INT 999999

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
#include <algorithm>
#include <string.h>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
 **************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node){

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = NULL;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph(){

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
    Node *node, *targetNode;
    node = getNode(id);
    if (node != NULL)
    {
        targetNode = getNode(target_id);
        if (targetNode != NULL)
        {
            node->insertEdge(target_id, weight);
            if (this->getDirected())
            {
                node->incrementOutDegree();
                targetNode->incrementInDegree();
            }
            else
            {
                node->incrementInDegree();
                targetNode->insertEdge(id, weight);
                targetNode->incrementOutDegree();
            }
        }
    }
}

bool Graph::removeNode(int id)
{
    if (searchNode(id))
    {
        Node *excluded = this->last_node;


        if (this->later_node_of_search == this->first_node)
        {
            this->first_node = this->first_node->getNextNode();
        }
        else
        {
            this->previous_node_of_search = this->later_node_of_search->getNextNode();
        }

        this->later_node_of_search = this->first_node;

        while (this->later_node_of_search != NULL)
        {
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


void Graph::breadthFirstSearch(ofstream &output_file){

}

int** Graph::aux_build_matrix(Node *node, int order, int **dist_nodes) {
    int i,j,z;
    Edge *aux_edge;

    for(i = 0; i < order; i++){
        dist_nodes[i] = new int [order];
        for(j = 0; j < order; j++){
            if(i == j)
                dist_nodes[i][j] = 0;
            else
                dist_nodes[i][j] = -1;
        }
    }

    this->printer << endl;

    while(node != NULL){
        aux_edge = node->getFirstEdge();
        while(aux_edge != NULL){
            dist_nodes[node->getId()-1][aux_edge->getTargetId()-1] = aux_edge->getWeight();
            aux_edge = aux_edge->getNextEdge();
        }
        node = node->getNextNode();
    }

    for (i = 0; i < this->order; i++ ) {
        for (j = 0; j < this->order; j++ ) {
            if ( j != i ) {
                for (z = 0; z < this->order; z++ ) {
                    if (dist_nodes[j][i] != -1 && dist_nodes[i][z] != -1) {
                        if (dist_nodes[j][z] > dist_nodes[j][i] + dist_nodes[i][z]
                        || dist_nodes[j][z] == -1)
                            dist_nodes[j][z] = dist_nodes[j][i] + dist_nodes[i][z];
                    }
                }
            }
        }
    }
    return dist_nodes;
}

string Graph::floydWarshall(int idOrigin, int idDestiny){
    this->printer.str(string());
    this->printer << "Running Floyd Marshall algorithm!";
    Node *aux_node = this->first_node;
    int** dist_nodes;
    int i,j;

    dist_nodes = aux_build_matrix(aux_node, this->order, dist_nodes);

    this->printer << "The minimum distance between " << idDestiny << " and " << idDestiny  << " costs "
    << dist_nodes[idOrigin - 1][idDestiny - 1] << endl;


    for (i = 0; i < this->order; i++) {
        this->printer << "[ ";
        for (j = 0; j < this->order; j++ ) {
            if (dist_nodes[i][j] != -1)
                this->printer << " " << dist_nodes[i][j] << " | ";
            else {
                this->printer << dist_nodes[i][j] << " | ";
            }
            if ( j == this->order - 1 )
                this->printer << "]\n";
        }
    }
    return this->printer.str();
}

string Graph::dijkstra(int idOrigin, int idDestiny)
{
    this->printer << "-->Dijkstra\n";

    int dist[this->order];
    int visited[this->order];

    //fila de prioridade para alocar a distancia entre os v�rtices
    priority_queue < pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    for(int i = 0; i < this->order; i++){
        dist[i] = -1;
        visited[i] = false;
    }

    dist[idOrigin] = 0;
    pq.push(make_pair(dist[idOrigin], idOrigin));

    while(!pq.empty()) {
        pair<int, int> p = pq.top();
        int u = p.second;
        pq.pop();
        if (visited[u] == false) {
            visited[u] = true;
            list < pair < int, int > > ::iterator
            it;
            for (it = adj[u].begin(); it != adj[u].end(); it++) {
                int v = it->first;
                int custo_aresta = it->second;
                if (dist[v] > (dist[u] + custo_aresta)) {
                    dist[v] = dist[u] + custo_aresta;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }
    this->printer << dist[idDestiny];
    return this->printer.str();
}

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

int buscar(int subset[], int i)
{
    if (subset[i] == -1)
        return i;
    return buscar(subset, subset[i]);
}

void unir(int subset[], int v1, int v2)
{
    int v1_set = buscar(subset, v1);
    int v2_set = buscar(subset, v2);
    subset[v1_set] = v2_set;
}

Graph *Graph::agmKruskal(Graph *graph, ofstream &output_file)
{
    vector<Edge> arvore;
    int size_edges = edges.size();
    sort (edges.begin(), edges.end());
    int V = graph->getOrder();
    int *subset = new int[V + 1];
    memset(subset, -1, sizeof(int) * V);
    for (int i = 0; i < size_edges; i++)
    {
        int v1 = buscar(subset, edges[i].getOriginId());
        int v2 = buscar(subset, edges[i].getTargetId());
        if (v1 != v2)
        {
            arvore.push_back(edges[i]);
            unir(subset, v1, v2);
        }
    }
    int arvoreTam = arvore.size();
    cout << endl;
    cout << "AGM com Kruskal" << endl;
    float pesoTotal = 0;
    for (int i = 0; i < arvoreTam; i++)
    {
        int v1 = arvore[i].getOriginId();
        int v2 = arvore[i].getTargetId();
        int weight = arvore[i].getWeight();
        pesoTotal = weight + pesoTotal;
        cout << "(" << v1 << ", " << v2 << ") - peso = " << weight << endl;
    }
    cout << "Peso total: " << pesoTotal << endl;
    cout << endl;

    output_file << "Kruskal Graph{" << endl;
    for (int i = 0; i < arvoreTam; i++)
    {
        output_file << "\t" << arvore[i].getOriginId() << " -- " << arvore[i].getTargetId() << ";" << endl;
    }
    output_file << "}";
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