#ifndef GRAPH_H
#define GRAPH_H

#include<string>

/*
Overall:
-Generalized graph
-room for expansion
-cost saving measures at the base

Nodes:
-multiple nodes with the same data allowed
-easy to add
-easy to remove
-easy to find

Vertecies:
-room for cost
-all of the 4 possible connections between nodes available
-multiple vertecies between nodes allowed
-easy to add
-easy to remove
-easy to find

Data output:
-vertex matrix
-cost matrix
-list of vertecies connected to a node
-list of vertecies /w "value"
-list of nodes /w "cost"
*/

template<typename T>
class graph {
private:
	class node{
	public:
		T value;
		bool available;

		node() {}
		node(const node&) {}
		~node() {}
	};
	class vertex{
	public:
		int node1, node2, cost;
		bool end1, end2, available;
		void setDirection(bool end1, bool end2) { this->end1 = end1; this->end2 = end2; }
		void setEnds(int node1, int node2) { this->node1 = node1; this->node2 = node2; }
		void getDirection(bool, bool) {}
		void getEnds(int, int) {}

		vertex() {}
		vertex(const vertex&) {}
		~vertex() {}
	};
	node*nodeList;
	vertex*vertexList;
	int nodeAmount, maxNodes, nodeProbe, vertexAmount, maxVertex, vertexProbe;
	void probeNode();
	void expandNode();
	void probeVertex();
	void expandVertex();
public:
	//nodefunctions
	void addNode(T&);
	bool removeNode(int);
	std::string findNode(T&)const;
	//vertexfunctions
	void addVertex(int,int,int,bool,bool);
	bool removeVertex(int);
	std::string findVertex(int)const;
	//data output
	std::string getVertexList()const;
	std::string getNodeList()const;
	std::string getConnectedVertex(int)const;

	int getNodeAmount()const;
	int getMaxNodeAmount()const;
	int getVertexAmount()const;
	int getMaxVertexAmount()const;
	//spanning tree functions

	graph();
	graph(int);
	graph(const graph&);
	~graph();
};

#endif

//private functions
template<typename T>
void graph<T>::probeNode() {
	int i = 0;
	while (!this->nodeList[this->nodeProbe].available && i < this->maxNodes) {
		this->nodeProbe = (this->nodeProbe == this->maxNodes - 1) ? 0 : this->nodeProbe + 1;
		i++;
	}
}

template<typename T>
void graph<T>::expandNode() {
	this->nodeProbe = this->maxNodes;
	this->maxNodes *= 2;
	node*temp = new node[this->maxNodes];
	for (int i = 0; i < this->nodeProbe; i++) {
		temp[i].available = this->nodeList[i].available;
		temp[i].value = this->nodeList[i].value;
	}
	delete[]this->nodeList;
	this->nodeList = temp;
}

template<typename T>
void graph<T>::probeVertex() {
	int i = 0;
	while (!this->vertexList[this->vertexProbe].available && i < this->maxVertex) {
		this->vertexProbe = (this->vertexProbe == this->maxVertex - 1) ? 0 : this->vertexProbe + 1;
		i++;
	}
}

template<typename T>
void graph<T>::expandVertex() {
	this->vertexProbe = this->maxVertex;
	this->maxVertex *= 2;
	vertex*temp = new vertex[this->maxVertex];
	for (int i = 0; i < this->vertexProbe; i++) {
		temp[i].available = this->vertexList[i].available;
		temp[i].cost = this->vertexList[i].cost;
		temp[i].node1 = this->vertexList[i].node1;
		temp[i].node2 = this->vertexList[i].node2;
		temp[i].end1 = this->vertexList[i].end1;
		temp[i].end2 = this->vertexList[i].end2;
	}
	delete[]this->vertexList;
	this->vertexList = temp;
}

//data output
template<typename T>
std::string graph<T>::getVertexList()const {
	std::string returnString = "";

	for (int i = 0; i < this->maxVertex; i++)
		if (this->vertexList[i].available == false) {
			returnString += 'A' + this->vertexList[i].node1;

			if (this->vertexList[i].end1 == 1 && this->vertexList[i].end2 == 0)
				returnString += "-->";
			else if (this->vertexList[i].end1 == 0 && this->vertexList[i].end2 == 1)
				returnString += "<--";
			else if (this->vertexList[i].end1 == 1 && this->vertexList[i].end2 == 1)
				returnString += "<->";
			else
				returnString += "ERR";

			returnString += 'A' + this->vertexList[i].node2;
			returnString += ", cost = " + std::to_string(this->vertexList[i].cost) + "\n";
		}

	return returnString;
}

template<typename T>
std::string graph<T>::getNodeList()const {
	std::string returnString = "";

	for (int i = 0; i < this->maxNodes; i++)
		if (this->nodeList[i].available == false) {
			returnString += 'A' + i;
			returnString += ", value = " + std::to_string(this->nodeList[i].value) + "\n";
		}

	return returnString;
}

template<typename T>
std::string graph<T>::getConnectedVertex(int node)const {
	std::string returnString = "";

	for(int i = 0; i < this->maxVertex;i++)
		if ((this->vertexList[i].node1 == node || this->vertexList[i].node2 == node) && this->vertexList[i].available == false) {
			returnString += 'A' + this->vertexList[i].node1;

			if (this->vertexList[i].end1 == 1 && this->vertexList[i].end2 == 0)
				returnString += "-->";
			else if (this->vertexList[i].end1 == 0 && this->vertexList[i].end2 == 1)
				returnString += "<--";
			else if (this->vertexList[i].end1 == 1 && this->vertexList[i].end2 == 1)
				returnString += "<->";
			else
				returnString += "ERR";

			returnString += 'A' + this->vertexList[i].node2;
			returnString += ", cost = " + std::to_string(this->vertexList[i].cost) + "\n";
		}

	return returnString;
}

template<typename T>
int graph<T>::getNodeAmount()const {
	return this->nodeAmount;
}

template<typename T>
int graph<T>::getMaxNodeAmount()const {
	return this->maxNodes;
}

template<typename T>
int graph<T>::getVertexAmount()const {
	return this->vertexAmount;
}

template<typename T>
int graph<T>::getMaxVertexAmount()const {
	return this->maxVertex;
}

//vertexfunctions
template<typename T>
void graph<T>::addVertex(int nodeA, int nodeB, int cost, bool ab, bool ba) {
	if (this->nodeList[nodeA].available == false && this->nodeList[nodeB].available == false && nodeA != nodeB) {
		if (this->maxVertex == this->vertexAmount)
			this->expandVertex();
		this->probeVertex();
		this->vertexList[this->vertexProbe].cost = cost;
		this->vertexList[this->vertexProbe].setEnds(nodeA, nodeB);
		this->vertexList[this->vertexProbe].setDirection(ab, ba);
		this->vertexList[this->vertexProbe].available = false;
		this->vertexAmount++;
	}
}

template<typename T>
bool graph<T>::removeVertex(int number) {
	if (this->vertexList[number].available == false) {
		this->vertexList[number].available = true;
		this->vertexAmount--;
	}
	return this->vertexList[number].available;
}

template<typename T>
std::string graph<T>::findVertex(int searchValue)const {
	std::string returnString = "";

	for (int i = 0; i < this->maxVertex; i++)
		if (this->vertexList[i].available == false && this->vertexList[i].cost == searchValue) {
			returnString += 'A' + this->vertexList[i].node1;

			if (this->vertexList[i].end1 == 1 && this->vertexList[i].end2 == 0)
				returnString += "-->";
			else if (this->vertexList[i].end1 == 0 && this->vertexList[i].end2 == 1)
				returnString += "<--";
			else if (this->vertexList[i].end1 == 1 && this->vertexList[i].end2 == 1)
				returnString += "<->";
			else
				returnString += "ERR";

			returnString += 'A' + this->vertexList[i].node2;
			returnString += ", cost = " + std::to_string(this->vertexList[i].cost) + "\n";
		}

	return returnString;
}

//nodefunctions
template<typename T>
void graph<T>::addNode(T&value) {
	if (this->maxNodes == this->nodeAmount)
		this->expandNode();
	this->probeNode();
	this->nodeList[this->nodeProbe].value = value;
	this->nodeList[this->nodeProbe].available = false;
	this->nodeAmount++;
}

template<typename T>
bool graph<T>::removeNode(int nodeNumber) {
	if (this->nodeList[nodeNumber].available == false) {
		this->nodeList[nodeNumber].available = true;
		this->nodeAmount--;

		for (int i = 0; i < this->maxVertex; i++)
			if ((this->vertexList[i].node1 == nodeNumber || this->vertexList[i].node2 == nodeNumber) && this->vertexList[i].available == false)
				this->removeVertex(i);
	}
	return this->nodeList[nodeNumber].available;
}

template<typename T>
std::string graph<T>::findNode(T&searchValue)const {
	std::string returnString = "";

	for (int i = 0; i < this->maxNodes; i++)
		if (this->nodeList[i].available == false && this->nodeList[i].value == searchValue) {
			returnString += 'A' + i;
			returnString += ", value = " + std::to_string(this->nodeList[i].value) + "\n";
		}

	return returnString;
}

//constructors destructors
template<typename T>
graph<T>::graph() {
	this->maxNodes = 5;
	this->nodeList = new node[this->maxNodes];
	this->nodeProbe = 0;
	this->nodeAmount = 0;

	this->maxVertex = 2*this->maxNodes;
	this->vertexList = new vertex[this->maxVertex];
	this->vertexProbe = 0;
	this->vertexAmount = 0;
}

template<typename T>
graph<T>::graph(int maxNodes) {
	this->maxNodes = maxNodes;
	this->nodeList = new node[this->maxNodes];
	this->nodeProbe = 0;
	this->nodeAmount = 0;

	this->maxVertex = 2 * this->maxNodes;
	this->vertexList = new vertex[this->maxVertex];
	this->vertexProbe = 0;
	this->vertexAmount = 0;
}

template<typename T>
graph<T>::graph(const graph&) {}

template<typename T>
graph<T>::~graph() {
	delete[]this->nodeList;
	delete[]this->vertexList;
}