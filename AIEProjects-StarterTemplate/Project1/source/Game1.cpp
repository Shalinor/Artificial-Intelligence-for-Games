#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "Graph.h"

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);

	input = Input::GetSingleton();

	defaultTexture = new Texture("./Images/circle_blue.png");
	startTexture = new Texture("./Images/circle_red.png");
	endTexture = new Texture("./Images/circle_orange.png");
	traversedTexture = new Texture("./Images/circle_yellow.png");
	pathTexture = new Texture("./Images/circle_green.png");

	graph = new Graph(true, 10.f);	//true == directed == oneway only

	pathfinder = new Pathfinder();
	newSearch = false;
	continueSearch = false;
	spaceReleased = true;

	rReleased = true;

	pReleased = true;

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
	///*Node* */node1 = new Node(vec3(100, 50, 0), defaultTexture, traversedTexture);	//0
	//Node* node2 = new Node(vec3(200, 50, 0), defaultTexture, traversedTexture);	//1
	//Node* node3 = new Node(vec3(200, 100, 0), defaultTexture, traversedTexture);	//2
	//Node* node4 = new Node(vec3(200, 150, 0), defaultTexture, traversedTexture);	//3
	//Node* node5 = new Node(vec3(150, 200, 0), defaultTexture, traversedTexture);	//4
	//Node* node6 = new Node(vec3(100, 150, 0), defaultTexture, traversedTexture);	//5

	//graph->AddNode(node1);
	//graph->AddNode(node2);
	//graph->AddNode(node3);
	//graph->AddNode(node4);
	//graph->AddNode(node5);
	//graph->AddNode(node6);

	//graph->AddEdge(node1, node2, 200.f);
	//graph->AddEdge(node2, node3, 300.f);
	//graph->AddEdge(node3, node1, 300.f);
	//graph->AddEdge(node3, node4, 100.f);
	//graph->AddEdge(node4, node5, 400.f);
	//graph->AddEdge(node4, node6, 400.f);
	//graph->AddEdge(node1, node6, 500.f);
	//graph->AddEdge(node6, node5, 600.f);

	graph->DisplayToConsole();

	////std::list<Node*>	potEndNodes;
	//potEndNodes.push_back(node5);
	
}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(m_spritebatch);
	
	delete graph;
	//delete pathfinder;
}


void Game1::Update(float deltaTime)
{
	graph->Update(defaultTexture, traversedTexture, 1.0f);


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

	graph->DisplayToScreen(m_spritebatch);

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
