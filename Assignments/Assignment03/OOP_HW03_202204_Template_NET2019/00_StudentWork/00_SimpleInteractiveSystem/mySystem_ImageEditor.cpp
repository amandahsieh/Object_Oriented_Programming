//
// Prof. Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//

#include <iostream>
#include "mySystem_ImageEditor.h"
//
#include <vector>
//
#define IMAGE_FILE_NAME "3d-flower-desktop.jpg"

#define IMAGE_MAX_HIERARCHY_DEPTH 8

IMAGE_SYSTEM::IMAGE_SYSTEM()
{
	m_ImageHierarchy = 0;
	m_Image = new ns_opengl::Image;
	m_Image->readFile(IMAGE_FILE_NAME);

	int wImage, hImage;
	m_Image->getInfo(wImage, hImage);

	int cur_depth = 0;
	int start_x = 0;
	int start_y = 0;

	int w = wImage;
	int h = hImage;
	float sx = 2;
	float sy = 2;

	float radius = wImage / 2.0 * (sx + sy) * 0.5;

	m_ImageHierarchy = new IMAGE_NODE(
		cur_depth,
		start_x,
		start_y,
		w,
		h,
		sx,
		sy,
		radius
	);
	float r, g, b;
	//std::cout<<"oooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<std::endl;
	computeAverageColor(start_x, start_y, w, h, r, g, b);
	//std::cout<<"oooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<std::endl;
	//std::cout<<"r:"<<r<<" g:"<<g<<" b:"<<b<<std::endl;
	m_ImageHierarchy->setColor(r, g, b);
	m_ImageHierarchy->computeDrawPosition(
		wImage, hImage
	);
	originalImageNode = m_ImageHierarchy;
	//
}

void IMAGE_SYSTEM::reset()
{
	//start here
	std::vector <IMAGE_NODE*> NodeQueue;
	NodeQueue.clear();
	NodeQueue.push_back(originalImageNode);
	//std::cout<<"size:"<<NodeQueue.size()<<'\n';
	while (!NodeQueue.empty()) {
		if (NodeQueue[0]->flg_explored == true) {

			for (int i = 0; i < 4; i++) {
				//std::cout<<" i "<<i<<'\n';
				NodeQueue.push_back(NodeQueue[0]->children[i]);
			}
			NodeQueue[0]->flg_explored = false;
			NodeQueue.erase(NodeQueue.begin());
		}
		else {
			//std::cout<<"exexeexxeexe"<<'\n';
			NodeQueue[0]->flg_explored = false;
			NodeQueue.erase(NodeQueue.begin());


		}

	}
}

void IMAGE_SYSTEM::handleKeyPressedEvent(unsigned char key)
{
	switch (key) {
	case ' ':
		break;
	case '.':
	case '<':
		break;
	case ',':
	case '>':
		break;
	case 'r':
		reset();
		break;

	case 'k':
	case 'K':
		break;
	case 'l':
	case 'L':
		break;
	}
}

//
// Compute the node color.
// That is compute the average color of the block of the node
//
void IMAGE_SYSTEM::computeNodeColor(IMAGE_NODE* node)
{
	float nr = 0, ng = 0, nb = 0;
	computeAverageColor(node->start_x, node->start_y, node->w, node->h, nr, ng, nb);
	node->r = nr;
	node->g = ng;
	node->b = nb;
}

//
// Explore a node if it is not explored.
// Go down the children if the node is explored.
//
void IMAGE_SYSTEM::exploreImageNode(IMAGE_NODE* node, double x, double y)
{
	//std::cout<<"-----------------w:"<<node->w<<"-------h:"<<node->h<<std::endl;
	if (node->flg_explored) {
		// If the node has been explored, 
		// go to check its children
		//¥H¤U
		for (int i = 0; i < 4; i++) {
			computeNodeColor(node->children[i]);

		}

	}
	else {
		// The node is not explored yet.
		// Now, explored it.
		// Do the following steps:
		// Can we explore it? If the dimension is less than 1x1, return.
		// If the dimension is at least 2x2
		//
		//std::cout<<"~here~"<<std::endl;
		if (node->w == 1 || node->h == 1) return;
		// Divide the image block into four children
		// Compute the draw positions of each child.
		//
		//std::cout<<"nonononnononononononononono"<<std::endl;
		//IMAGE_NODE(int cur_depth,int start_x, int start_y,int w, int h,float sx, float sy,float radius)
		float center_x = node->start_x + node->w / 2;
		float center_y = node->start_y + node->h / 2;
		node->children[0] = new IMAGE_NODE(node->cur_depth,
			node->start_x + node->w / 2,
			node->start_y + node->h / 2,
			node->w / 2,
			node->h / 2,
			2,
			2,
			node->radius / 2);
		//std::cout<<"C0 :"<<node->children[0]->w<<std::endl;
		node->children[1] = new IMAGE_NODE(node->cur_depth,
			node->start_x,
			node->start_y + node->h / 2,
			node->w / 2,
			node->h / 2,
			2,
			2,
			node->radius / 2);
		node->children[2] = new IMAGE_NODE(node->cur_depth,
			node->start_x,
			node->start_y,
			node->w / 2,
			node->h / 2,
			2,
			2,
			node->radius / 2);
		//std::cout<<"C2 is done."<<std::endl;
		node->children[3] = new IMAGE_NODE(node->cur_depth,
			node->start_x + node->w / 2,
			node->start_y,
			node->w / 2,
			node->h / 2,
			2,
			2,
			node->radius / 2);
		//std::cout<<"C3 is done."<<std::endl;
		//node->children[0]->cur_depth=(node->cur_depth)+1;
		//std::cout<<"node->cur_depth+1: "<<node->cur_depth+1<<std::endl;
		int wImage, hImage;
		m_Image->getInfo(wImage, hImage);
		for (int i = 0; i < 4; i++) {
			node->children[i]->cur_depth = node->cur_depth + 1;
			//std::cout<<"node->children[i]->cur_depth:"<<node->children[i]->cur_depth<<std::endl;
			node->children[i]->flg_explored = false;
			node->children[i]->computeDrawPosition(wImage, hImage);
			computeNodeColor(node->children[i]);
			//std::cout<<"c"<<i<<": "<<node->children[i]->start_x<<" "<<node->children[i]->start_y<<std::endl;

		}
		node->flg_explored = true;
		//std::cout<<node->draw_x<<" hihihhihihihihihihihihihihih"<<std::endl;
		//if (node->w/2 ==0 || node->h/2 == 0) return;
		//


	}
}

//
// call exploreImageNode(root, mouse_x, mouse_y)
//
void IMAGE_SYSTEM::handlePassiveMouseEvent(double x, double y)
{
	//starth
	//std::cout << "IMAGE_SYSTEM Mouse:" << x << "\t" << y << std::endl;

	IMAGE_NODE* n = findNearestNode(x, y);
	if (n == 0) {
		//std::cout<<"not touched!!"<<std::endl; 
		return;
	}
	//std::cout<<"touched!!"<<std::endl;
   //m_ImageHierarchy=n;

	exploreImageNode(n, x, y);
}


IMAGE_NODE* IMAGE_SYSTEM::findNearestNode(float x, float y) {
	IMAGE_NODE* node = 0;
	//float bigNum=originalImageNode->radius;
	//float dx = bigNum;
	//float dy = bigNum;
	std::vector <IMAGE_NODE*> NodeQueue;
	NodeQueue.clear();
	NodeQueue.push_back(originalImageNode);
	//std::cout<<"size:"<<NodeQueue.size()<<'\n';
	while (!NodeQueue.empty()) {
		if (NodeQueue[0]->flg_explored == true) {

			for (int i = 0; i < 4; i++) {
				//std::cout<<" i "<<i<<'\n';
				NodeQueue.push_back(NodeQueue[0]->children[i]);
			}
			NodeQueue.erase(NodeQueue.begin());
		}
		else {
			//std::cout<<"exexeexxeexe"<<'\n';
			float dx = x - NodeQueue[0]->draw_x;
			float dy = y - NodeQueue[0]->draw_y;
			float d2 = dx * dx + dy * dy;
			float r2 = NodeQueue[0]->radius * NodeQueue[0]->radius;
			if (d2 < r2) {
				return NodeQueue[0];
			}
			else {
				NodeQueue.erase(NodeQueue.begin());
			}

		}

	}
	/*
	float dx = x - node->draw_x;
	float dy = y - node->draw_y;
	float d2 = dx*dx + dy*dy;
	float r2 = node->radius*node->radius;
	*/
	//std::cout<<"return 0"<<std::endl;
	return 0;


}