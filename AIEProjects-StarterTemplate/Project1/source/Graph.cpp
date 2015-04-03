#include "Graph.h"


Graph::Graph(bool directed_)
{
	directed = directed_;
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

	for (auto iterator = traversal.begin(); iterator != traversal.end(); ++iterator)
	{
		delete (*iterator);
	}

	nodes.clear();
	traversal.clear();
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
		if ((*i)->position == position_)
		{
			return (*i);
		}
	}

	//Not found
	return NULL;
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
		nodes[i]->DisplayEdgeCostToConsole();
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

void	Graph::Update(Texture* t1, Texture* t2)
{
	if (input->IsMouseButtonDown(0) && mouseLeftReleased)
	{
		Node* temp = new Node(vec3(input->GetMouseX(), input->GetMouseY(), 0), t1, t2);

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

void	Graph::TraverseDFS()
{
	/*
	Push first node on stack
	While stack not empty
		Get the top off the stack and remove it
		Process it...
		Mark it as traversed
		Loop through it's edges
			If end node of edge not traversed or on the stack
				Push end node onto the stack
	*/

	/*//This doesn't work for purty step by stepping...
	if (traversed)
	{
	ClearTraversal();
	}
	*/

	if (traversal.empty() && !traversed)
	{
		traversal.push_back(nodes[0]);
		traversed = true;				//This is because of the whole not in a while loop atm
	}


	if (!traversal.empty() && traversed)	//Has already traversed fully...
	{
		//This would normally be within a while(!traversal.empty()) loop, but kept seperate for now for hopeful purtyness
		Node* temp = traversal.back();	//Get reference to top of stack
		traversal.pop_back();			//Remove top of stack

		//Process Node...

		temp->SetTraversed();

		//Get number of linked nodes stored within temp
		int num = temp->GetNumberOfEdges();

		//If there are any, push all linked nodes onto stack
		if (num > 0)
		{
			for (int i = 0; i < num; ++i)
			{
				//traversal.push_back(temp->GetLinkedNode(i));	//Doesn't check if the node is already on the stack...

				Node* returned = temp->GetLinkedNode(i);

				if (!returned->GetTraversed())	//If it hasn't already been traversed, check if it is already in stack
				{
					for (int x = 0; x < traversal.size(); ++x)
					{
						if (traversal[x] == returned)
						{
							break;	//go to next "i"
						}
					}

					//Returned Node not already in stack so add to it
					traversal.push_back(returned);
				}
			}
		}
	}
}

void	Graph::TraverseBFS()
{
	/*
	Push first node on queue
	While queue not empty
		Get the top off the queue and remove it
		Process it...
		Mark it as traversed
		Loop through it's edges
			If end node of edge not traversed or on the queue
				Push end node onto the queue
	*/

	/*//This doesn't work for purty step by stepping...
	if (traversed)
	{
	ClearTraversal();
	}
	*/

	if (traversal.empty() && !traversed)
	{
		traversal.push_back(nodes[0]);
		traversed = true;				//This is because of the whole not in a while loop atm
	}


	if (!traversal.empty() && traversed)	//Has already traversed fully...
	{
		//This would normally be within a while(!traversal.empty()) loop, but kept seperate for now for hopeful purtyness
		Node* temp = traversal.front();	//Get reference to top of stack
		traversal.pop_front();			//Remove top of stack

		//Process Node...

		temp->SetTraversed();

		//Get number of linked nodes stored within temp
		int num = temp->GetNumberOfEdges();

		//If there are any, push all linked nodes onto stack
		if (num > 0)
		{
			for (int i = 0; i < num; ++i)
			{
				//traversal.push_back(temp->GetLinkedNode(i));	//Doesn't check if the node is already on the stack...

				Node* returned = temp->GetLinkedNode(i);

				if (!returned->GetTraversed())	//If it hasn't already been traversed, check if it is already in stack
				{
					for (int x = 0; x < traversal.size(); ++x)
					{
						if (traversal[x] == returned)
						{
							break;	//go to next "i"
						}
					}

					//Returned Node not already in stack so add to it
					traversal.push_back(returned);
				}
			}
		}
	}
}

void	Graph::ClearTraversal()
{
	for (int i = 0; i != nodes.size(); ++i)
	{
		nodes[i]->ClearTraversal();
	}

	traversed = false;
}
