#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <fstream>

#include "Graph.h"

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);

	input = Input::GetSingleton();

	LoadMenu();			//Loads menuText from text file
	//menuFont = new Font("./Fonts/calibri_24px.fnt");
	//menuFont = new Font("./Fonts/arial_20px.fnt");
	menuFont			= new Font("./Fonts/CourierNew_11px.fnt");
	menuPos				= vec2(0.f, 0.f);


	defaultTexture		= new Texture("./Images/circle_blue.png");
	startTexture		= new Texture("./Images/circle_red.png");
	endTexture			= new Texture("./Images/circle_orange.png");
	traversedTexture	= new Texture("./Images/circle_yellow.png");
	pathTexture			= new Texture("./Images/circle_green.png");

	graph				= new Graph(false, 5.f);	//true == directed == oneway only ... detection radius == half image dimension being used
	pathfinder			= new Pathfinder();

	startNode			= NULL;
	potEndNodes.clear();

	newSearch			= false;
	continueSearch		= false;
	spaceReleased		= true;
	rReleased			= true;
	pReleased			= true;
	sReleased			= true;
	eReleased			= true;
	iReleased			= true;
	cReleased			= true;
	dReleased			= true;
	oneReleased			= true;
	twoReleased			= true;
	threeReleased		= true;

	mouseLeftReleased	= true;
	//mouseRightReleased	= true;

	displayIDs			= false;
	displayCosts		= false;
	displayDirections	= false;

	//Now to create a grid of nodes...

	gridSize = 11;
	gridSpacing = 30.f;

	for (int y = 1; y < gridSize; ++y)
	{
		for (int x = 1; x < gridSize; ++x)
		{
			graph->AddNode(new Node(vec3(float(windowWidth - (x * gridSpacing)), float(windowHeight - (y * gridSpacing)), 0.f), defaultTexture, traversedTexture));
		}
	}

	graph->FillAllEdges(gridSize, gridSpacing, false, 1.f);

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
	if (!sReleased || !eReleased)								//If either setting Start or End node
	{
		if (input->IsMouseButtonDown(0) && mouseLeftReleased)
		{
			mousePosition = vec3(input->GetMouseX(), input->GetMouseY(), 0.f);
			mouseLeftReleased = false;
						

			Node* temp = graph->FindNode(mousePosition);			//Get node under mouse pointer

			if (temp != NULL)										//Test if a node was found
			{
				if (!sReleased && eReleased)						//Setting Start node
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
				else if (sReleased && !eReleased)					//Setting End node
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
			}
		}
		/*else if (input->IsMouseButtonDown(1) && mouseRightReleased)
		{
		mousePosition = vec3(input->GetMouseX(), input->GetMouseY(), 0.f);

		mouseRightReleased = false;
		}*/
	}
	else/* if (sReleased && eReleased)*/						//Not setting Start or End node
	{
		graph->Update(defaultTexture, traversedTexture, 1.0f);	//Only use graph's LMB/RMB input if setting Start/End nodes...
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

	if (input->IsKeyDown(GLFW_KEY_SPACE) && spaceReleased)
	{
		continueSearch = true;
		spaceReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_SPACE))
	{
		spaceReleased = true;
	}

	if (input->IsKeyDown(GLFW_KEY_R) && rReleased)
	{
		ResetSearches();
		rReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_R))
	{
		rReleased = true;
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

		pathfinder->Dijkstras(startNode, potEndNodes, outPath);
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
