//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include <iostream>
#include "mySystem_GraphSystem.h"
#include <time.h>

#include "myBasicTools.h"
#define PI 3.1415926

using namespace std;

int Param::GRAPH_MAX_NUM_NODES = 1000;
int Param::GRAPH_MAX_NUM_EDGES = 1000;

GRAPH_SYSTEM::GRAPH_SYSTEM()
{
	mFlgAutoNodeDeletion = false;
	createDefaultGraph();
	//
	// Implement your own stuff
	//

}

void GRAPH_SYSTEM::reset()
{
	stopAutoNodeDeletion();
	mPassiveSelectedNode = 0;
	mSelectedNode = 0;
	//
	// Implement your own stuff
	//
	initMemoryPool();
	mCurNumOfActiveNodes = 0;
	mCurNumOfActiveEdges = 0;

	mCurNumOfFreeNodes = Param::GRAPH_MAX_NUM_NODES;
	mCurNumOfFreeEdges = Param::GRAPH_MAX_NUM_EDGES;

	for (int i = 0; i < mCurNumOfFreeNodes; ++i) {
		mFreeNodeArr[i] = i; // index is not used
	}
	for (int i = 0; i < mCurNumOfFreeEdges; ++i) {
		mFreeEdgeArr[i] = i; // index is not used
	}



}

void GRAPH_SYSTEM::createDefaultGraph()
{

	reset();
	//
	// Implement your own stuff
	//
	int default_node_id[3];
	default_node_id[0] = addNode(0, 0, 0, 1);
	default_node_id[1] = addNode(10, 0, 0, 1);
	default_node_id[2] = addNode(0, 0, 10, 1);
	addEdge(default_node_id[0], default_node_id[1]);
	addEdge(default_node_id[1], default_node_id[2]);

	/*
	for(int i=0;i<3;i++){
		//cout<<"FN_id_"<<i<<": "<<mFreeNodeArr[i]<<endl;
		cout<<"x: "<<mNodeArr_Pool[i].p.x<<" z: "<<mNodeArr_Pool[i].p.z<<endl;
	}
	*/
}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
	reset();
	float dx = 5.0;
	float dz = 5.0;
	float r = 15; // radius
	float d = 10; // layer distance
	float offset_x = 15.;
	float offset_z = 15.;
	//
	// Implement your own stuff
	//
	float radius = r;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			addNode(offset_x + r * cos(j * 360 / n * PI / 180), 0, offset_z + r * sin(j * 360 / n * PI / 180), 1);
		}
		r += d;
	}


	for (int i = 0; i < n; i++) {

		while (1) {
			int OutterNodeIndex = getRandDouble(n, 2 * n);
			if (OutterNodeIndex == 2 * n) OutterNodeIndex = 2 * n - 1;
			double distance_2 = 0;
			double x_d = mNodeArr_Pool[mActiveNodeArr[i]].p.x - mNodeArr_Pool[mActiveNodeArr[OutterNodeIndex]].p.x;
			double z_d = mNodeArr_Pool[mActiveNodeArr[i]].p.z - mNodeArr_Pool[mActiveNodeArr[OutterNodeIndex]].p.z;
			distance_2 = (x_d * x_d + z_d * z_d);

			if (distance_2 + radius * radius < ((radius + d) * (radius + d))) {
				addEdge(mActiveNodeArr[i], mActiveNodeArr[OutterNodeIndex]);
				break;
			}
		}

	}

}

void GRAPH_SYSTEM::createNet_Circular(int n, int num_layers)
{
	reset();

	float dx = 5.0;
	float dz = 5.0;
	float r = 5; // radius
	float d = 5; // layer distance 
	float offset_x = 15.;
	float offset_z = 15.;
	//
	// Implement your own stuff
	//
	for (int i = 0; i < num_layers + 1; i++) {
		for (int j = 0; j < n; j++) {
			addNode(offset_x + r * cos(j * 360 / n * PI / 180), 0, offset_z + r * sin(j * 360 / n * PI / 180), 1);
		}
		r += d;
	}

	for (int i = 0; i < num_layers; i++) {
		for (int j = 0; j < n; j++) {
			addEdge(mActiveNodeArr[i * n + j % n], mActiveNodeArr[i * n + (j + 1) % n]);
			addEdge(mActiveNodeArr[i * n + j % n], mActiveNodeArr[(i + 1) * n + j % n]);
		}
		r += d;
	}


}
void GRAPH_SYSTEM::createNet_Square(int n, int num_layers)
{
	reset();

	float dx = 5.0;
	float dz = 5.0;
	float r = 5; // radius
	float d = 5; // layer distance 
	float offset_x = 5.;
	float offset_z = 5.;
	//
	// Implement your own stuff
	//
	float now_x = offset_x + (n - 1) * r;
	float now_z = offset_z + (n - 1) * r;
	int pLayersCap = 0;
	int OneLayerCap = (n + 1) * 4;
	for (int i = 0; i < (num_layers - n) / 2; i++) {
		for (int j = pLayersCap; j < pLayersCap + OneLayerCap; j++) {
			int flg = (j - pLayersCap) / (n + 2 * i + 1);

			if (flg == 0) {
				now_z -= dz;
			}
			else if (flg == 1) {
				now_x -= dx;
			}
			else if (flg == 2) {
				now_z += dz;
			}
			else {
				now_x += dx;
			}
			addNode(now_x, 0, now_z);

		}
		now_x += d;
		now_z += d;
		pLayersCap += OneLayerCap;
		OneLayerCap += 8;
	}

	pLayersCap = 0;
	OneLayerCap = (n + 1) * 4;
	int node_0 = 0, node_1 = 0;
	for (int i = 0; i < (num_layers - n) / 2 - 1; i++) {
		for (int j = pLayersCap; j < pLayersCap + OneLayerCap; j++) {
			node_0 = j;
			node_1 = j + 1;
			if (node_1 == pLayersCap + OneLayerCap) node_1 = pLayersCap;
			addEdge(mActiveNodeArr[node_0], mActiveNodeArr[node_1]);

			int flg = (j - pLayersCap) / (n + 2 * i + 1);

			if (flg == 0) {
				node_1 = OneLayerCap + j + 1;
			}
			else if (flg == 1) {
				node_1 = OneLayerCap + j + 3;
			}
			else if (flg == 2) {
				node_1 = OneLayerCap + j + 5;
			}
			else {
				node_1 = OneLayerCap + j + 7;
			}

			addEdge(mActiveNodeArr[node_0], mActiveNodeArr[node_1]);
			if ((j - pLayersCap + 1) % (n + 2 * i + 1) == 0) {
				if ((j - pLayersCap + 1) % OneLayerCap == 0) {
					addEdge(mActiveNodeArr[node_0], mActiveNodeArr[node_0 + 1]);
				}
				else	addEdge(mActiveNodeArr[node_0], mActiveNodeArr[node_1 + 2]);
			}
		}
		pLayersCap += OneLayerCap;
		OneLayerCap += 8;
	}

	for (int j = pLayersCap; j < pLayersCap + OneLayerCap; j++) {
		node_0 = j;
		node_1 = j + 1;
		if (node_1 == pLayersCap + OneLayerCap) node_1 = pLayersCap;
		addEdge(mActiveNodeArr[node_0], mActiveNodeArr[node_1]);
	}




}

void GRAPH_SYSTEM::createNet_RadialCircular(int n) {

	reset();

	float offset_x = 15.0;
	float offset_z = 15.0;

	float r = 15; // radius
	//
	// Implement your own stuff
	//    
	addNode(offset_x, 0, offset_z, 1);
	for (int j = 0; j < n; j++) {
		addNode(offset_x + r * cos(j * 360 / n * PI / 180), 0, offset_z + r * sin(j * 360 / n * PI / 180), 1);
		addEdge(mActiveNodeArr[0], mActiveNodeArr[1 + j]);
	}

}

// return node id
int GRAPH_SYSTEM::addNode(float x, float y, float z, float r)
{
	//
	// Implement your own stuff
	//  
	GRAPH_NODE* g;
	g = getFreeNode();
	if (g == 0) return -1; // invalid id.
	g->p = vector3(x, y, z);
	g->r = r;
	g->edgeID.clear();

	return g->id;
}

// return edge id
int GRAPH_SYSTEM::addEdge(int nodeID_0, int nodeID_1)
{
	//
	// Implement your own stuff
	//  
	GRAPH_EDGE* e;
	e = getFreeEdge();
	if (e == 0) return -1;
	e->nodeID[0] = nodeID_0;
	e->nodeID[1] = nodeID_1;
	mNodeArr_Pool[nodeID_0].edgeID.push_back(e->id);
	mNodeArr_Pool[nodeID_1].edgeID.push_back(e->id);
	return e->id;


}

void GRAPH_SYSTEM::askForInput()
{
	//
	// Implement your own stuff
	// 
	cout << "GRAPH_SYSTEM" << endl;
	cout << "Key usage:" << endl;
	/*
	cout << "1: create a default graph" << endl;
	cout << "2: create a graph with 10x10 nodes. Connect the consecutive nodes horizontally" << endl;
	cout << "3: create a graph with 10x10 nodes. Connect the consecutive nodes vertically" << endl;
	cout << "4: create a graph with 10x10 nodes. Create 10 randomly generated edges" << endl;
	cout << "5: create a graph with 10x10 nodes. Create 10 randomly generated edges attached at a random node" << endl;
	*/
	cout << "1: create a default graph" << endl;
	cout << "2: createNet_Circular mode" << endl;
	cout << "3: createNet_Square mode" << endl;
	cout << "4: createNet_RadialCircular mode" << endl;
	cout << "5: createRandomGraph_DoubleCircles mode" << endl;
	cout << "Delete: delete a node and all the edges attached at it" << endl;
	cout << "Spacebar: unselect the selected node" << endl;
	cout << " " << endl;
	cout << "Use the mouse to select nodes and add edges" << endl;
	cout << "Click the left button to select/unselect or create an edge" << endl;
	cout << " " << endl;
	cout << "A selected node is highlighted as red." << endl;

}

GRAPH_NODE* GRAPH_SYSTEM::findNearestNode(double x, double z, double& cur_distance2) const
{
	GRAPH_NODE* n = 0;
	//
	// Implement your own stuff
	// 
	if (mCurNumOfActiveNodes > 0) {
		double x_d = mNodeArr_Pool[mActiveNodeArr[0]].p.x - x;
		double z_d = mNodeArr_Pool[mActiveNodeArr[0]].p.z - z;
		double LongerDistance2 = 0;
		double ShorterDistance2 = x_d * x_d + z_d * z_d;
		cur_distance2 = ShorterDistance2;
		n = &(mNodeArr_Pool[mActiveNodeArr[0]]);

		for (int i = 1; i < mCurNumOfActiveNodes; i++) {
			x_d = mNodeArr_Pool[mActiveNodeArr[i]].p.x - x;
			z_d = mNodeArr_Pool[mActiveNodeArr[i]].p.z - z;
			LongerDistance2 = (x_d * x_d) + (z_d * z_d);
			if (LongerDistance2 < ShorterDistance2) {
				ShorterDistance2 = LongerDistance2;
				n = &(mNodeArr_Pool[mActiveNodeArr[i]]);
				cur_distance2 = ShorterDistance2;
			}
		}
	}
	return n;
}

//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z)
{
	//
	// Implement your own stuff
	// 
	//尚未排除已經有edge的兩個節點重複建立edge的狀況(但運行上沒差)
	handlePassiveMouseEvent(x, z);
	if (mSelectedNode != mPassiveSelectedNode) {
		if (mSelectedNode != 0 && mPassiveSelectedNode != 0) {
			addEdge(mSelectedNode->id, mPassiveSelectedNode->id);
			mSelectedNode = 0;
		}
		else {
			mSelectedNode = mPassiveSelectedNode;
		}

	}
	else mSelectedNode = 0;
	/*
	for(int i=0;i<mCurNumOfActiveNodes;i++){
		if(mNodeArr_Pool[mActiveNodeArr[i]].p.x==x && mNodeArr_Pool[mActiveNodeArr[i]].p.z==z){
			mSelectedNode = &(mNodeArr_Pool[mActiveNodeArr[i]]);
		}
	}*/

	//handlePassiveMouseEvent( x, z );
	// mSelectedNode = n;
}

void GRAPH_SYSTEM::deleteNode(int nodeID) {
	//
	// Implement your own stuff
	// 
	//cout<<"debug"<<endl;
	//cout<<"edgeID_vector_size:"<<mNodeArr_Pool[nodeID].edgeID.size()<<endl;
	while (!mNodeArr_Pool[nodeID].edgeID.empty()) {
		deleteEdge(mNodeArr_Pool[nodeID].edgeID[0]);
	}
	//cout<<"num of AN:"<<mCurNumOfActiveNodes<<endl;
	/*for(int i=0;i<mCurNumOfActiveNodes;i++){
		cout<<"A_id: "<<mActiveNodeArr[i]<<endl;
	}
	*/
	if (mCurNumOfActiveNodes == 0) { cout << "NONE" << endl; return; }
	/*if(mCurNumOfActiveNodes==1){
		mCurNumOfActiveNodes--;
		mCurNumOfFreeNodes++;
		mSelectedNode=0;
		mPassiveSelectedNode=0;
		return;
	}*/
	mCurNumOfActiveNodes--;
	mNodeArr_Pool[mActiveNodeArr[mCurNumOfActiveNodes]].dynamicID = mNodeArr_Pool[nodeID].dynamicID;
	//cout<<"deletedID: "<<mActiveNodeArr[mNodeArr_Pool[nodeID].dynamicID];
	//cout<<" lastID: "<<mActiveNodeArr[mCurNumOfActiveNodes]<<endl;
	mActiveNodeArr[mNodeArr_Pool[nodeID].dynamicID] = mActiveNodeArr[mCurNumOfActiveNodes];
	mFreeNodeArr[mCurNumOfFreeNodes] = nodeID;
	mCurNumOfFreeNodes++;

	mSelectedNode = 0;
	mPassiveSelectedNode = 0;

}

void GRAPH_SYSTEM::deleteEdge(int edgeID) {

	for (int i = 0; i < mCurNumOfActiveNodes; i++) {
		for (int j = 0; j < mNodeArr_Pool[mActiveNodeArr[i]].edgeID.size(); j++) {
			//cout<<"DEBUG2"<<endl;
			if (mNodeArr_Pool[mActiveNodeArr[i]].edgeID[j] == edgeID) {
				//cout<<"j:"<<j<<endl;
				mNodeArr_Pool[mActiveNodeArr[i]].edgeID.erase(mNodeArr_Pool[mActiveNodeArr[i]].edgeID.begin() + j);
			}
		}
	}

	mCurNumOfActiveEdges--;
	mEdgeArr_Pool[mActiveEdgeArr[mCurNumOfActiveEdges]].dynamicID = mEdgeArr_Pool[edgeID].dynamicID;
	mActiveEdgeArr[mEdgeArr_Pool[edgeID].dynamicID] = mActiveEdgeArr[mCurNumOfActiveEdges];
	mFreeEdgeArr[mCurNumOfFreeEdges] = edgeID;
	mCurNumOfFreeEdges++;



}

void GRAPH_SYSTEM::deleteSelectedNode() {
	//
	// Implement your own stuff
	// 
	if (isSelectedNode())
		deleteNode(mSelectedNode->id);
}

bool GRAPH_SYSTEM::isSelectedNode() const
{
	//
	// mSelectedNode != 0;
	//
	// Implement your own stuff
	// 

	if (mSelectedNode == 0) {
		//cout<<"not selected"<<endl;
		return false;

	}
	//cout<<"selected"<<endl;
	return true;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint(double& r, vector3& p) const
{
	// r = mSelectedNode->r;
	// p = mSelectedNode->p;
	//
	// Implement your own stuff
	// 
	if (isSelectedNode()) {
		r = mSelectedNode->r;
		p = mSelectedNode->p;
	}
}



void GRAPH_SYSTEM::handleKeyPressedEvent(unsigned char key)
{

	switch (key) {
	case 127: // delete
		mFlgAutoNodeDeletion = false;
		deleteSelectedNode();
		break;
	case '1':
		mFlgAutoNodeDeletion = false;
		//
		IFDoubleCirclesNodesMode = false;
		//
		createDefaultGraph();
		mSelectedNode = 0;
		break;
	case '2':
		mFlgAutoNodeDeletion = false;
		//
		IFDoubleCirclesNodesMode = false;
		//
		createNet_Circular(12, 3);
		mSelectedNode = 0;

		break;
	case '3':
		mFlgAutoNodeDeletion = false;
		//
		IFDoubleCirclesNodesMode = false;
		//
		createNet_Square(3, 11); // you can modify this
		mSelectedNode = 0;

		break;
	case '4':
		mFlgAutoNodeDeletion = false;
		//
		IFDoubleCirclesNodesMode = false;
		//
		createNet_RadialCircular(24);
		mSelectedNode = 0;

		break;
	case '5':
		mFlgAutoNodeDeletion = false;
		//
		IFDoubleCirclesNodesMode = true;
		curNumOfDoubleCirclesNodes = 24;
		//
		createRandomGraph_DoubleCircles(24);
		mSelectedNode = 0;

		break;

	case ' ':
		mFlgAutoNodeDeletion = false;
		mSelectedNode = 0;
		break;
	case 'g':
		mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
		break;
	case '>':
		if (IFDoubleCirclesNodesMode) {
			curNumOfDoubleCirclesNodes += 1;
			if (curNumOfDoubleCirclesNodes > 36) curNumOfDoubleCirclesNodes = 36;
			createRandomGraph_DoubleCircles(curNumOfDoubleCirclesNodes);
		}
		break;
	case '<':
		if (IFDoubleCirclesNodesMode) {
			curNumOfDoubleCirclesNodes -= 1;
			if (curNumOfDoubleCirclesNodes < 3) curNumOfDoubleCirclesNodes = 3;
			createRandomGraph_DoubleCircles(curNumOfDoubleCirclesNodes);
		}
		break;

	}
}

void GRAPH_SYSTEM::handlePassiveMouseEvent(double x, double z)
{//is it
	double cur_d2;
	GRAPH_NODE* n = findNearestNode(x, z, cur_d2);
	if (n == 0) return;
	if (cur_d2 > n->r * n->r) {
		mPassiveSelectedNode = 0;
		return;
	}
	/*
	if(mSelectedNode!=0){
		addEdge(mSelectedNode->id,n->id);
	}*/
	mPassiveSelectedNode = n;
}

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes() const
{
	//
	// Implement your own stuff
	// 
	return mCurNumOfActiveNodes;
}

void GRAPH_SYSTEM::getNodeInfo(int nodeIndex, double& r, vector3& p) const
{
	//
	// Implement your own stuff
	// 
	int node_id = mActiveNodeArr[nodeIndex];
	r = mNodeArr_Pool[node_id].r;
	p = mNodeArr_Pool[node_id].p;
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges() const
{
	//
	// Implement your own stuff
	// 
	return mCurNumOfActiveEdges;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge(int edgeIndex, int nodeIndex) const
{
	vector3 p;
	//
	// Implement your own stuff
	// 
	int edge_id = mActiveEdgeArr[edgeIndex];
	int node_id = mEdgeArr_Pool[edge_id].nodeID[nodeIndex];
	p = mNodeArr_Pool[node_id].p;
	return p;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
	mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
// 
//
void GRAPH_SYSTEM::update()
{
	if (!mFlgAutoNodeDeletion) {

		return;
	}
	mSelectedNode = 0;
	mPassiveSelectedNode = 0;

	Sleep(250);
	//
	//
	// Implement your own stuff
	// 


}


/////////////////////////以下
void GRAPH_SYSTEM::initMemoryPool()
{
	mNodeArr_Pool = new GRAPH_NODE[Param::GRAPH_MAX_NUM_NODES];
	mEdgeArr_Pool = new GRAPH_EDGE[Param::GRAPH_MAX_NUM_EDGES];

	mCurNumOfActiveNodes = 0;
	mCurNumOfActiveEdges = 0;
	mCurNumOfFreeNodes = Param::GRAPH_MAX_NUM_NODES;
	mCurNumOfFreeEdges = Param::GRAPH_MAX_NUM_EDGES;
	mActiveNodeArr = new int[Param::GRAPH_MAX_NUM_NODES];
	mActiveEdgeArr = new int[Param::GRAPH_MAX_NUM_EDGES];

	mFreeNodeArr = new int[Param::GRAPH_MAX_NUM_NODES];
	mFreeEdgeArr = new int[Param::GRAPH_MAX_NUM_EDGES];
	//
	for (int i = 0; i < Param::GRAPH_MAX_NUM_NODES; ++i) {
		mNodeArr_Pool[i].id = i; // assign a unique id
	}
	for (int i = 0; i < Param::GRAPH_MAX_NUM_EDGES; ++i) {
		mEdgeArr_Pool[i].id = i; // assign a unique id
	}
	//reset( );
}

GRAPH_NODE* GRAPH_SYSTEM::getFreeNode() {
	if (mCurNumOfFreeNodes == 0) return 0;
	--mCurNumOfFreeNodes;
	int id = mFreeNodeArr[mCurNumOfFreeNodes];
	GRAPH_NODE* n = &mNodeArr_Pool[id];
	mActiveNodeArr[mCurNumOfActiveNodes] = id;
	n->dynamicID = mCurNumOfActiveNodes;
	++mCurNumOfActiveNodes;
	return n;
}

GRAPH_EDGE* GRAPH_SYSTEM::getFreeEdge() {
	if (mCurNumOfFreeEdges == 0) return 0;
	--mCurNumOfFreeEdges;
	int id = mFreeEdgeArr[mCurNumOfFreeEdges];
	GRAPH_EDGE* e = &mEdgeArr_Pool[id];
	mActiveEdgeArr[mCurNumOfActiveEdges] = id;
	e->dynamicID = mCurNumOfActiveEdges;
	++mCurNumOfActiveEdges;
	return e;
}


/////////////////////////////////以上