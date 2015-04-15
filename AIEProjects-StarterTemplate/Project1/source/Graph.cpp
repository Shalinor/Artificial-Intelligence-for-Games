#include "Graph.h"

Graph::Graph(bool directed_, float detectionRadius_)
{
	directed = directed_;
	detectionRadius = detectionRadius_;
	input = Input::GetSingleton();

	mouseLeftReleased = true;
	mouseRightReleased = true;
	traversed = false;
}

Graph::~Graph()
{
	for (auto iterator = nodes.begin(); iterator != nodes.end(); ++iterator)
	{
		delete (*iterator);
	}

	/*for (auto iterator = traversal.begin(); iterator != traversal.end(); ++iterator)
	{
		delete (*iterator);
	}*/

	nodes.clear();
//	traversal.clear();
}


void Graph::AddNode(Node* node_)
{
	//Do we need to check for pre-existing node???
	nodes.push_back(node_);
}

/*NEEDS TO BE WORKED*/
void Graph::RemoveNode(Node* node_)
{
	std::vector<Node*>::iterator temp;

	//iterate through nodes and call removeEdge on each passing in (*i) as start_ and node_ as end_
	for (std::vector<Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
	{
		(*i)->RemoveEdge((*i), node_);

		if ((*i) == node_)
		{
			temp = i;
		}
	}

	nodes.erase(temp);
}

Node* Graph::FindNode(vec3 position_)
{
	for (std::vector<Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
	{
		if (((*i)->position.x >= position_.x - detectionRadius) &&
			((*i)->position.x <= position_.x + detectionRadius) &&
			((*i)->position.y >= position_.y - detectionRadius) &&
			((*i)->position.y <= position_.y + detectionRadius))
		{
			return (*i);
		}
	}

	//Not found
	return NULL;
}

Node*	Graph::GetFirstNode()
{
	if (nodes.empty())
	{
		return NULL;
	}

	return nodes.front();
}

Node*	Graph::GetLastNode()
{
	if (nodes.empty())
	{
		return NULL;
	}

	return nodes.back();
}

void Graph::AddEdge(Node* nodeAlpha_, Node* nodeBeta_, float cost_)
{
	nodeAlpha_->AddEdge(nodeAlpha_, nodeBeta_, cost_);

	//directed_ assumes nodeAlpha -> nodeBeta only
	if (!directed)
	{
		nodeBeta_->AddEdge(nodeBeta_, nodeAlpha_, cost_);
	}
}

void Graph::FillAllEdges(int gridSize_, float range_, bool diagonals_, bool randomCosts_, float cost_)
{
	if (diagonals_)		//This cross connects the whole grid (upto 8 for a fully surrounded node)
	{
		//If nodes are within "range_" pixels (units?) of another node, connect them
		for (int i = 0; i != nodes.size(); ++i)
		{
			for (int j = 0; j != nodes.size(); ++j)
			{
				if (nodes[i] != nodes[j])	//Don't want to connect to self
				{
					if ((nodes[i]->position.x >= nodes[j]->position.x - range_) &&
						(nodes[i]->position.x <= nodes[j]->position.x + range_) &&
						(nodes[i]->position.y >= nodes[j]->position.y - range_) &&
						(nodes[i]->position.y <= nodes[j]->position.y + range_))
					{
						if (randomCosts_)
						{
							AddEdge(nodes[i], nodes[j], glm::linearRand(1.f, 10.f));
						}
						else
						{
							AddEdge(nodes[i], nodes[j], cost_);
						}
					}
				}
			}
		}
	}	
	else				//This orthogonally connects the whole grid (upto 4 for a fully surrounded node)
	{
		//If nodes are within "range_" pixels (units?) of another node, connect them
		for (int i = 0; i != nodes.size(); ++i)
		{
			//This cross connects the whole grid (upto 8 for a fully surrounded node)
			for (int j = 0; j != nodes.size(); ++j)
			{
				if (nodes[i] != nodes[j])	//Don't want to connect to self
				{
					if ((((nodes[i]->position.x >= nodes[j]->position.x - range_) && (nodes[i]->position.y == nodes[j]->position.y)) &&
						((nodes[i]->position.x <= nodes[j]->position.x + range_) && (nodes[i]->position.y == nodes[j]->position.y))) ||
						(((nodes[i]->position.x == nodes[j]->position.x) && (nodes[i]->position.y >= nodes[j]->position.y - range_)) &&
						((nodes[i]->position.x == nodes[j]->position.x) && (nodes[i]->position.y <= nodes[j]->position.y + range_))))
					{
						if (randomCosts_)
						{
							AddEdge(nodes[i], nodes[j], glm::linearRand(1.f, 10.f));
						}
						else
						{
							AddEdge(nodes[i], nodes[j], cost_);
						}
					}
				}
			}
		}
	}
}

void Graph::RemoveEdge(Node* nodeAlpha_, Node* nodeBeta_)
{
	nodeAlpha_->RemoveEdge(nodeAlpha_, nodeBeta_);

	//directed_ assumes nodeAlpha -> nodeBeta only
	if (!directed)
	{
		nodeBeta_->RemoveEdge(nodeBeta_, nodeAlpha_);
	}
}

void	Graph::DisplayToConsole()
{
	for (int i = 0; i != nodes.size(); ++i)
	{
		std::cout << "Node ";
//		nodes[i]->DisplayPosition();
		nodes[i]->DisplayIDToConsole();
		std::cout << "\n";

//		nodes[i]->DisplayEdgesToConsole();
		nodes[i]->DisplayEdgeIDToConsole();
	}
}

void	Graph::DisplayToScreen(SpriteBatch* spriteBatch_, Texture* texture_)
{
	for (int i = 0; i != nodes.size(); ++i)
	{
		nodes[i]->DisplayEdgesToScreen(spriteBatch_); 
		spriteBatch_->DrawSprite(texture_, nodes[i]->position.x, nodes[i]->position.y, 10.f, 10.f);
	}
}

void	Graph::DisplayToScreen(SpriteBatch* spriteBatch_)
{
	for (int i = 0; i != nodes.size(); ++i)
	{
		nodes[i]->DisplayEdgesToScreen(spriteBatch_);
		//nodes[i]->DisplayNodeToScreen(spriteBatch_);
	}

	//Split to allow all edges to be drawn before any nodes to ensure ALL nodes are on top of ALL edges
	for (int i = 0; i != nodes.size(); ++i)
	{
		nodes[i]->DisplayNodeToScreen(spriteBatch_);
	}
}

void	Graph::DisplayToScreen(SpriteBatch* spriteBatch_, bool displayIDs_, bool displayCosts_, bool displayDirections_, Font* font_)
{
	for (int i = 0; i != nodes.size(); ++i)
	{
		nodes[i]->DisplayEdgesToScreen(spriteBatch_, displayCosts_, displayDirections_, font_);
	}

	//Split to allow all edges to be drawn before any nodes to ensure ALL nodes are on top of ALL edges
	for (int i = 0; i != nodes.size(); ++i)
	{
		nodes[i]->DisplayNodeToScreen(spriteBatch_, displayIDs_, font_);
	}
}

void	Graph::Update()
{
	if (input->IsMouseButtonDown(0) && mouseLeftReleased)
	{
		Node* temp = new Node(vec3(input->GetMouseX(), input->GetMouseY(), 0));

		mouseLeftReleased = false;
		AddNode(temp);

		//If new node (temp) is within 50 pixels (units?) of another node, connect them
		for (int i = 0; i != nodes.size(); ++i)
		{
			if ((nodes[i]->position.x >= temp->position.x - 50.f) &&
				(nodes[i]->position.x <= temp->position.x + 50.f) &&
				(nodes[i]->position.y >= temp->position.y - 50.f) &&
				(nodes[i]->position.y <= temp->position.y + 50.f))
			{
				AddEdge(temp, nodes[i]);
			}
		}
	}
	else if (input->IsMouseButtonDown(1) && mouseRightReleased)
	{
		mouseRightReleased = false;

		int x = input->GetMouseX();
		int y = input->GetMouseY();

		for (int i = 0; i != nodes.size(); ++i)
		{
			if ((nodes[i]->position.x >= ((float)x - 10.f)) &&
				(nodes[i]->position.x <= ((float)x + 10.f)) &&
				(nodes[i]->position.y >= ((float)y - 10.f)) &&
				(nodes[i]->position.y <= ((float)y + 10.f)))
			{
				RemoveNode(nodes[i]);
				break;
			}
		}
	}

	if (input->IsMouseButtonUp(0) && !mouseLeftReleased)
	{
		mouseLeftReleased = true;
	}

	if (input->IsMouseButtonUp(1) && !mouseRightReleased)
	{
		mouseRightReleased = true;
	}
}

void	Graph::Update(Texture* t1_, Texture* t2_, bool randomCosts_, float cost_)
{
	////TEST IF A NODE IS WITHIN DETECTION RADIUS OF THE CLICK (10px??) AND DO NOT ADD IF THERE IS - OR REMOVE IF RMB

	if (input->IsMouseButtonDown(0) && mouseLeftReleased)
	{
		Node* temp = new Node(vec3(input->GetMouseX(), input->GetMouseY(), 0), t1_, t2_);

		mouseLeftReleased = false;
		AddNode(temp);

		//If new node (temp) is within 50 pixels (units?) of another node, connect them
		for (int i = 0; i != nodes.size(); ++i)
		{
			if (nodes[i]->position != temp->position) // or could just if(nodes[i] != temp)...
			{
				if ((nodes[i]->position.x >= temp->position.x - 50.f) &&
					(nodes[i]->position.x <= temp->position.x + 50.f) &&
					(nodes[i]->position.y >= temp->position.y - 50.f) &&
					(nodes[i]->position.y <= temp->position.y + 50.f))
				{
					if (randomCosts_)
					{
						AddEdge(temp, nodes[i], glm::linearRand(1.f, 10.f));
					}
					else
					{
						AddEdge(temp, nodes[i], cost_);
					}
				}
			}
		}
	}
	else if (input->IsMouseButtonDown(1) && mouseRightReleased)
	{
		mouseRightReleased = false;

		int x = input->GetMouseX();
		int y = input->GetMouseY();

		for (int i = 0; i != nodes.size(); ++i)
		{
			if ((nodes[i]->position.x >= ((float)x - 8.f)) &&
				(nodes[i]->position.x <= ((float)x + 8.f)) &&
				(nodes[i]->position.y >= ((float)y - 8.f)) &&
				(nodes[i]->position.y <= ((float)y + 8.f)))
			{
				RemoveNode(nodes[i]);
				break;
			}
		}
	}

	if (input->IsMouseButtonUp(0) && !mouseLeftReleased)
	{
		mouseLeftReleased = true;
	}

	if (input->IsMouseButtonUp(1) && !mouseRightReleased)
	{
		mouseRightReleased = true;
	}
}

//void	Graph::TraverseDFS()
//{
//	/*
//	Push first node on stack
//	While stack not empty
//		Get the top off the stack and remove it
//		Process it...
//		Mark it as traversed
//		Loop through it's edges
//			If end node of edge not traversed or on the stack
//				Push end node onto the stack
//	*/
//
//	/*//This doesn't work for purty step by stepping...
//	if (traversed)
//	{
//	ClearTraversal();
//	}
//	*/
//
//	if (traversal.empty() && !traversed)
//	{
//		traversal.push_back(nodes[0]);
//		traversed = true;				//This is because of the whole not in a while loop atm
//	}
//
//
//	if (!traversal.empty() && traversed)	//Has already traversed fully...
//	{
//		//This would normally be within a while(!traversal.empty()) loop, but kept seperate for now for hopeful purtyness
//		Node* temp = traversal.back();	//Get reference to top of stack
//		traversal.pop_back();			//Remove top of stack
//
//		//Process Node...
//
//		temp->SetTraversed();
//
//		//Get number of linked nodes stored within temp
//		int num = temp->GetNumberOfEdges();
//
//		//If there are any, push all linked nodes onto stack
//		if (num > 0)
//		{
//			for (int i = 0; i < num; ++i)
//			{
//				//traversal.push_back(temp->GetLinkedNode(i));	//Doesn't check if the node is already on the stack...
//
//				Node* returned = temp->GetLinkedNode(i);
//
//				if (!returned->GetTraversed())	//If it hasn't already been traversed, check if it is already in stack
//				{
//					for (int x = 0; x < traversal.size(); ++x)
//					{
//						if (traversal[x] == returned)
//						{
//							break;	//go to next "i"
//						}
//					}
//
//					//Returned Node not already in stack so add to it
//					traversal.push_back(returned);
//				}
//			}
//		}
//	}
//}
//
//void	Graph::TraverseBFS()
//{
//	/*
//	Push first node on queue
//	While queue not empty
//		Get the top off the queue and remove it
//		Process it...
//		Mark it as traversed
//		Loop through it's edges
//			If end node of edge not traversed or on the queue
//				Push end node onto the queue
//	*/
//
//	/*//This doesn't work for purty step by stepping...
//	if (traversed)
//	{
//	ClearTraversal();
//	}
//	*/
//
//	if (traversal.empty() && !traversed)
//	{
//		traversal.push_back(nodes[0]);
//		traversed = true;				//This is because of the whole not in a while loop atm
//	}
//
//
//	if (!traversal.empty() && traversed)	//Has already traversed fully...
//	{
//		//This would normally be within a while(!traversal.empty()) loop, but kept seperate for now for hopeful purtyness
//		Node* temp = traversal.front();	//Get reference to top of stack
//		traversal.pop_front();			//Remove top of stack
//
//		//Process Node...
//
//		temp->SetTraversed();
//
//		//Get number of linked nodes stored within temp
//		int num = temp->GetNumberOfEdges();
//
//		//If there are any, push all linked nodes onto stack
//		if (num > 0)
//		{
//			for (int i = 0; i < num; ++i)
//			{
//				//traversal.push_back(temp->GetLinkedNode(i));	//Doesn't check if the node is already on the stack...
//
//				Node* returned = temp->GetLinkedNode(i);
//
//				if (!returned->GetTraversed())	//If it hasn't already been traversed, check if it is already in stack
//				{
//					for (int x = 0; x < traversal.size(); ++x)
//					{
//						if (traversal[x] == returned)
//						{
//							break;	//go to next "i"
//						}
//					}
//
//					//Returned Node not already in stack so add to it
//					traversal.push_back(returned);
//				}
//			}
//		}
//	}
//}

void	Graph::ClearTraversal()
{
	for (int i = 0; i != nodes.size(); ++i)
	{
		nodes[i]->ClearTraversal();
	}

	traversed = false;
}
