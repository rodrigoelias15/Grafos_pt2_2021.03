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




string Graph::floydWarshall(int idOrigin, int idDestiny){
    this->printer.str(string());
    this->printer << "Running Floyd Marshall algorithm!";
    Node *aux_node = this->first_node;
    int** dist_nodes;
    int i,j;

    dist_nodes = aux_build_matrix(aux_node, this->order, dist_nodes);

    this->printer << "The minimum distance between " << idSource << " and " << int idDestiny << " costs "
    << dist_nodes[idOrigin-1][int idDestiny-1] << endl;


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



string Graph::dijkstra(int idOrigin, int idDestiny){
    this->printer << "-->Dijkstra Algorimth\n";

    int dist[this->order];
    int visited[this->order];

    //fila de prioridade para alocar a distancia entre os vértices
    priority_queue < pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    for(int i = 0; i < this->order; i++){
        dist[i] = -1;
        visited[i] = false;
    }

    dist[idOrigin] = 0;
    pq.push(make_pair(dist[idOrigin], idOrigin));

    while(!pq.empty()){
        pair<int, int> p = pq.top(); // extrai o pair do topo
        int u = p.second; // obtém o vértice do pair
        pq.pop(); // remove da fila

        // verifica se o vértice não foi expandido
        if(visited[u] == false){
            // marca como visitado
            visited[u] = true;

            list<pair<int, int> >::iterator it;

            // percorre os vértices "v" adjacentes de "u"
            for(it = adj[u].begin(); it != adj[u].end(); it++){
                // obtém o vértice adjacente e o custo da aresta
                int v = it->first;
                int custo_aresta = it->second;

                // relaxamento (u, v)
                if(dist[v] > (dist[u] + custo_aresta)){
                    // atualiza a distância de "v" e insere na fila
                    dist[v] = dist[u] + custo_aresta;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }

    // retorna a distância mínima até o destino
    this->printer << dist[idDestiny];

    return this->printer.str();
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
