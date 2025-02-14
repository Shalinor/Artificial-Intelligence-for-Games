#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <fstream>

#include "Graph.h"

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	srand(time(NULL));

	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);

	input = Input::GetSingleton();

	LoadMenu();			//Loads menuText from text file
	//menuFont = new Font("./Fonts/calibri_24px.fnt");
	//menuFont = new Font("./Fonts/arial_20px.fnt");
	menuFont				= new Font("./Fonts/CourierNew_11px.fnt");
	menuPos					= vec2(0.f, 0.f);


	defaultTexture			= new Texture("./Images/circle_blue.png");
	startTexture			= new Texture("./Images/circle_red.png");
	endTexture				= new Texture("./Images/circle_orange.png");
	traversedTexture		= new Texture("./Images/circle_yellow.png");
	pathTexture				= new Texture("./Images/circle_green.png");
	nonTraversableTexture	= new Texture("./Images/circle_grey.png");

	graph					= new Graph(false, 5.f);	//true == directed == oneway only ... detection radius == half image dimension being used
	pathfinder				= new Pathfinder();

	startNode				= NULL;
	potEndNodes.clear();

	randomCosts				= true;
	diagonals			    = false;

	chosenSearch			= DIJKSTRAS;
	newSearch				= false;
	continueSearch			= false;
	spaceReleased			= true;
	rReleased				= true;
	pReleased				= true;
	sReleased				= true;
	eReleased				= true;
	iReleased				= true;
	cReleased				= true;
	dReleased				= true;
	tReleased				= true;
	oneReleased				= true;
	twoReleased				= true;
	threeReleased			= true;
	fourReleased			= true;

	mouseLeftReleased		= true;
	//mouseRightReleased		= true;

	displayIDs				= false;
	displayCosts			= false;
	displayDirections		= false;

	//Now to create a grid of nodes...

	gridSize = 46;//11;
	gridSpacing = 10.f;//45.f;

	for (int y = 1; y < gridSize; ++y)
	{
		for (int x = 1; x < gridSize; ++x)
		{
			graph->AddNode(new Node(vec3(float(windowWidth - (x * gridSpacing)), float(windowHeight - (y * gridSpacing)), 0.f), defaultTexture, traversedTexture, nonTraversableTexture));
		}
	}

	graph->FillAllEdges(gridSize, gridSpacing, diagonals, randomCosts, 1.f);

	Node*	temp = graph->GetFirstNode();
	
	if (temp != NULL)
	{
		startNode = temp;
	}

	temp = graph->GetLastNode();

	if (temp != NULL)
	{
		potEndNodes.push_back(temp);
	}
	
	temp = NULL;
	delete temp;

	//Attempting to duplicate the slide's 6 node graph
	/*Node* node1 = new Node(vec3(100, 50, 0), defaultTexture, traversedTexture);	//0
	Node* node2 = new Node(vec3(200, 50, 0), defaultTexture, traversedTexture);	//1
	Node* node3 = new Node(vec3(200, 100, 0), defaultTexture, traversedTexture);	//2
	Node* node4 = new Node(vec3(200, 150, 0), defaultTexture, traversedTexture);	//3
	Node* node5 = new Node(vec3(150, 200, 0), defaultTexture, traversedTexture);	//4
	Node* node6 = new Node(vec3(100, 150, 0), defaultTexture, traversedTexture);	//5

	graph->AddNode(node1);
	graph->AddNode(node2);
	graph->AddNode(node3);
	graph->AddNode(node4);
	graph->AddNode(node5);
	graph->AddNode(node6);

	graph->AddEdge(node1, node2, 200.f);
	graph->AddEdge(node2, node3, 300.f);
	graph->AddEdge(node3, node1, 300.f);
	graph->AddEdge(node3, node4, 100.f);
	graph->AddEdge(node4, node5, 400.f);
	graph->AddEdge(node4, node6, 400.f);
	graph->AddEdge(node1, node6, 500.f);
	graph->AddEdge(node6, node5, 600.f);*/

//	graph->DisplayToConsole();	//This chugs with the grid...
}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(m_spritebatch);
	
	delete graph;
	//delete pathfinder;
}


void Game1::Update(float deltaTime)
{
	if (!sReleased || !eReleased || !tReleased)						//If either setting Start or End node or Traversability
	{
		if (input->IsMouseButtonDown(0) && mouseLeftReleased)
		{
			mousePosition = vec3(input->GetMouseX(), input->GetMouseY(), 0.f);
			mouseLeftReleased = false;
						

			Node* temp = graph->FindNode(mousePosition);			//Get node under mouse pointer

			if (temp != NULL)										//Test if a node was found
			{
				if (!sReleased && eReleased && tReleased)			//Setting Start node
				{
					if (startNode == temp)							//If selecting existing Start node, clear it
					{
						startNode = NULL;
					}
					else
					{
						startNode = temp;
					}
				}
				else if (sReleased && !eReleased && tReleased)		//Setting End node
				{
					bool alreadyInPotEndList = false;

					for (std::list<Node*>::iterator i = potEndNodes.begin(); i != potEndNodes.end(); ++i)
					{
						if ((*i) == temp)
						{
							alreadyInPotEndList = true;
							potEndNodes.erase(i);
							break;
						}
					}

					if (!alreadyInPotEndList)
					{
						potEndNodes.push_back(temp);
					}
				}
				else if (sReleased && eReleased && !tReleased)		//Setting node Traversability
				{
					temp->SetTraversable(!temp->GetTraversable());
				}
			}

			temp = NULL;
			delete temp;
		}
		/*else if (input->IsMouseButtonDown(1) && mouseRightReleased)
		{
		mousePosition = vec3(input->GetMouseX(), input->GetMouseY(), 0.f);

		mouseRightReleased = false;
		}*/
	}
	else/* if (sReleased && eReleased)*/						//Not setting Start or End node
	{
		graph->Update(defaultTexture, traversedTexture, nonTraversableTexture, randomCosts, 1.0f);	//Only use graph's LMB/RMB input if setting Start/End nodes...
		//	NEED TO PUT SOMETHING IN TO COVER REMOVING A START/END NODE AS THEY ARE STORED EXTERNALLY TO GRAPH...
		//		MAYBE WHEN I REMOVE IT, SET IT TO NULL??
	}


	//Reset LMB down when released
	if (input->IsMouseButtonUp(0) && !mouseLeftReleased)
	{
		mouseLeftReleased = true;
	}

	/*if (input->IsMouseButtonUp(1) && !mouseRightReleased)
	{
		mouseRightReleased = true;
	}*/


	if (input->IsKeyDown(GLFW_KEY_L))
	{
		LoadMenu();
	}

	if (input->IsKeyDown(GLFW_KEY_S) && sReleased)
	{
		//Set Start Node
		sReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_S))
	{
		sReleased = true;
	}

	if (input->IsKeyDown(GLFW_KEY_E) && eReleased)
	{
		//Set End Node
		eReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_E))
	{
		eReleased = true;
	}

	if (input->IsKeyDown(GLFW_KEY_I) && iReleased)
	{
		//Set Display IDs
		displayIDs = !displayIDs;
		iReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_I))
	{
		iReleased = true;
	}

	if (input->IsKeyDown(GLFW_KEY_C) && cReleased)
	{
		//Set Display Costs
		displayCosts = !displayCosts;
		cReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_C))
	{
		cReleased = true;
	}
	
	if (input->IsKeyDown(GLFW_KEY_D) && dReleased)
	{
		//Set Display Directions
		displayDirections = !displayDirections;
		dReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_D))
	{
		dReleased = true;
	}

	if (input->IsKeyDown(GLFW_KEY_T) && tReleased)
	{
		//Set node Traversability
		tReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_T))
	{
		tReleased = true;
	}

	///Choosing Search Option - BFS, DFS, DIJKSTRAS
	if (input->IsKeyDown(GLFW_KEY_1) && oneReleased)
	{
		if (chosenSearch != BFS)
		{
			//Set BFS as chosen search and reset
			chosenSearch = BFS;
			ResetSearches();
			oneReleased = false;
		}
	}
	else if (input->IsKeyUp(GLFW_KEY_1))
	{
		oneReleased = true;
	}


	if (input->IsKeyDown(GLFW_KEY_2) && twoReleased)
	{
		if (chosenSearch != DFS)
		{
			//Set DFS as chosen search and reset
			chosenSearch = DFS;
			ResetSearches();
			twoReleased = false;
		}
	}
	else if (input->IsKeyUp(GLFW_KEY_2))
	{
		twoReleased = true;
	}


	if (input->IsKeyDown(GLFW_KEY_3) && threeReleased)
	{
		if (chosenSearch != DIJKSTRAS)
		{
			//Set Dijkstra's as chosen search and reset
			chosenSearch = DIJKSTRAS;
			ResetSearches();
			threeReleased = false;
		}
	}
	else if (input->IsKeyUp(GLFW_KEY_3))
	{
		threeReleased = true;
	}

	if (input->IsKeyDown(GLFW_KEY_4) && fourReleased)
	{
		if (chosenSearch != ASTAR)
		{
			//Set A* as chosen search and reset
			chosenSearch = ASTAR;
			ResetSearches();
			fourReleased = false;
		}
	}
	else if (input->IsKeyUp(GLFW_KEY_4))
	{
		fourReleased = true;
	}


	///Searching - Reset, Step-thru, Run-thru...
	if (input->IsKeyDown(GLFW_KEY_R) && rReleased)
	{
		ResetSearches();
		rReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_R))
	{
		rReleased = true;
	}


	//Step-thru / Run-thru	<space/p>
	if (input->IsKeyDown(GLFW_KEY_SPACE) && spaceReleased)
	{
		continueSearch = true;
		spaceReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_SPACE))
	{
		spaceReleased = true;
	}

	if (input->IsKeyDown(GLFW_KEY_P))
	{
		if (pReleased && newSearch)
		{
			ResetSearches();
			newSearch = false;
		}

		if (newSearch)
		{
			continueSearch = false;
		}
		else
		{
			continueSearch = true;
		}

		pReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_P))
	{
		pReleased = true;
	}

	if (continueSearch)
	{
		if (newSearch)
		{
			ResetSearches();
			newSearch = false;
		}

		Search();
		continueSearch = false;
	}

	if (input->IsKeyDown(GLFW_KEY_ESCAPE))
	{
		Game1::Application::Quit();
	}
}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	m_spritebatch->Begin();

	// TODO: draw stuff.

	//Draw menu
	m_spritebatch->DrawString(menuFont, menuText, menuPos.x, menuPos.y);

    //Display search type
	switch (chosenSearch)
	{
	case BFS:
		m_spritebatch->DrawString(menuFont, "Search Type: Breadth First", 10.f, (GetWindowHeight() - 20.f));
		break;
	case DFS:
		m_spritebatch->DrawString(menuFont, "Search Type: Depth First", 10.f, (GetWindowHeight() - 20.f));
		break;
	case DIJKSTRAS:
		m_spritebatch->DrawString(menuFont, "Search Type: Dijkstra's", 10.f, (GetWindowHeight() - 20.f));
		break;
	case ASTAR:
		m_spritebatch->DrawString(menuFont, "Search Type: A*", 10.f, (GetWindowHeight() - 20.f));
		break;
	default:
		//Shouldn't get here
		std::cout << "\n\nError: Reached default in Game1::Draw() Switch(chosenSearch) statement...\n\n";
		break;
	}

	//Draw graph
	graph->DisplayToScreen(m_spritebatch, displayIDs, displayCosts, displayDirections, menuFont);

	//Draw Start/End nodes <over the existing traversed/non-traversed ... these will then be overridden by outpath once done>
	if (startNode)
	{
		m_spritebatch->DrawSprite(startTexture, startNode->position.x, startNode->position.y, 10.f, 10.f);
	}

	if (!potEndNodes.empty())
	{
		for (std::list<Node*>::iterator i = potEndNodes.begin(); i != potEndNodes.end(); ++i)
		{
			m_spritebatch->DrawSprite(endTexture, (*i)->position.x, (*i)->position.y, 10.f, 10.f);
		}
	}


	if (!outPath.empty())
	{
		for (auto iterator = outPath.begin(); iterator != outPath.end(); ++iterator)
		{
			m_spritebatch->DrawSprite(pathTexture, (*iterator)->position.x, (*iterator)->position.y, 10.f, 10.f);
		}

		newSearch = true;
	}

	m_spritebatch->End();
}

void Game1::ResetSearches()
{
	graph->ClearTraversal();
	pathfinder->ResetSearch();
	outPath.clear();
}

void Game1::Search()
{
	switch (chosenSearch)
	{
	case BFS:
		if (startNode)								//Ensure that the requisite values are in place
		{
			//pathfinder->BreadthFirstSearch(startNode);
			pathfinder->BFS_DFS(startNode, false);
		}
		break;
	case DFS:
		if (startNode)								//Ensure that the requisite values are in place
		{
			//pathfinder->DepthFirstSearch(startNode);
			pathfinder->BFS_DFS(startNode, true);
		}
		break;
	case DIJKSTRAS:
		if (startNode && !potEndNodes.empty())		//Ensure that the requisite values are in place
		{
//			while (outPath.empty())
			pathfinder->Dijkstras(startNode, potEndNodes, outPath);
		}
		break;
	case ASTAR:
		if (startNode && !potEndNodes.empty() && (potEndNodes.size() == 1))		//Ensure that the requisite values are in place
		{
//			while (outPath.empty())
			//pathfinder->AStarTutorial(startNode, potEndNodes.front(), outPath);
			//pathfinder->AStarLecture(startNode, potEndNodes.front(), outPath);
			pathfinder->AStarWiki(startNode, potEndNodes.front(), outPath);
		}
		break;
	default:
		//Shouldn't get here
		std::cout << "\n\nError: Reached default in Game1::Search() Switch(chosenSearch) statement...\n\n";
		break;
	}
}

void Game1::LoadMenu()
{
	std::ifstream file("menu.txt", std::ios_base::in | std::ios_base::binary);

	if (file)
	{
		//Get length of file
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		//+1 added to allow for addition of '\0' after read to clear superflouous memory content
		menuText = new char[length + 1];

		std::cout << "Reading " << length << " characters... ";

		//Read file into menuText
		file.read(menuText, length);

		menuText[length] = '\0';	//clears the supurflouous byte of rubbish at the end.

		if (file)
			std::cout << "All characters read successfully.";
		else
			std::cout << "Error: only " << file.gcount() << " could be read.";

		std::cout << std::endl;

		file.close();
	}
}
