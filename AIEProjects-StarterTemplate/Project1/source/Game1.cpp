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

	//t = new Texture("./Images/nodeTexture.png");//box0_256.png");
	//t1 = new Texture("./Images/yellowBox_16.png");
	//t2 = new Texture("./Images/redBox_16.png");
	//t3 = new Texture("./Images/greenBox_16.png");

	defaultTexture = new Texture("./Images/circle_blue.png");
	startTexture = new Texture("./Images/circle_red.png");
	endTexture = new Texture("./Images/circle_orange.png");
	traversedTexture = new Texture("./Images/circle_yellow.png");
	pathTexture = new Texture("./Images/circle_green.png");

	graph = new Graph(true);	//true == directed == oneway only
	pathfinder = new Pathfinder();
	continueSearch = false;
	spaceReleased = true;

	/*
	Node* node1 = new Node(vec3(10, 100, 0), t1, t2);	//Jason has each node having an int id
	Node* node2 = new Node(vec3(50, 50, 0), t1, t2);
	Node* node3 = new Node(vec3(100, 230, 0), t1, t2);
	Node* node4 = new Node(vec3(150, 150, 0), t1, t2);

	graph->AddNode(node1);
	graph->AddNode(node2);
	graph->AddNode(node3);
	graph->AddNode(node4);

	graph->AddEdge(node1, node3);
	graph->AddEdge(node1, node4);
	graph->AddEdge(node3, node2);
	*/

	//Attempting to duplicate the slide's 6 node graph

	/*Node* */node1 = new Node(vec3(100, 50, 0), defaultTexture, traversedTexture);	//0
	Node* node2 = new Node(vec3(200, 50, 0), defaultTexture, traversedTexture);	//1
	Node* node3 = new Node(vec3(200, 100, 0), defaultTexture, traversedTexture);	//2
	Node* node4 = new Node(vec3(200, 150, 0), defaultTexture, traversedTexture);	//3
	Node* node5 = new Node(vec3(150, 200, 0), defaultTexture, traversedTexture);	//4
	Node* node6 = new Node(vec3(100, 150, 0), defaultTexture, traversedTexture);	//5

	//Node* node1 = new Node(vec3(10, 10, 0), defaultTexture, traversedTexture);	//0
	//Node* node2 = new Node(vec3(12, 10, 0), defaultTexture, traversedTexture);	//1
	//Node* node3 = new Node(vec3(12, 13, 0), defaultTexture, traversedTexture);	//2
	//Node* node4 = new Node(vec3(12, 14, 0), defaultTexture, traversedTexture);	//3
	//Node* node5 = new Node(vec3(11, 17, 0), defaultTexture, traversedTexture);	//4
	//Node* node6 = new Node(vec3(10, 15, 0), defaultTexture, traversedTexture);	//5

	graph->AddNode(node1);
	graph->AddNode(node2);
	graph->AddNode(node3);
	graph->AddNode(node4);
	graph->AddNode(node5);
	graph->AddNode(node6);

	/*graph->AddEdge(node1, node2);
	graph->AddEdge(node2, node3);
	graph->AddEdge(node3, node1);
	graph->AddEdge(node3, node4);
	graph->AddEdge(node4, node5);
	graph->AddEdge(node4, node6);
	graph->AddEdge(node1, node6);
	graph->AddEdge(node6, node5);*/

	/*graph->AddEdge(node1, node2, 2.f);
	graph->AddEdge(node2, node3, 3.f);
	graph->AddEdge(node3, node1, 3.f);
	graph->AddEdge(node3, node4, 1.f);
	graph->AddEdge(node4, node5, 4.f);
	graph->AddEdge(node4, node6, 4.f);
	graph->AddEdge(node1, node6, 5.f);
	graph->AddEdge(node6, node5, 6.f);*/

	graph->AddEdge(node1, node2, 200.f);
	graph->AddEdge(node2, node3, 300.f);
	graph->AddEdge(node3, node1, 300.f);
	graph->AddEdge(node3, node4, 100.f);
	graph->AddEdge(node4, node5, 400.f);
	graph->AddEdge(node4, node6, 400.f);
	graph->AddEdge(node1, node6, 500.f);
	graph->AddEdge(node6, node5, 600.f);

	graph->DisplayToConsole();

	//std::list<Node*>	potEndNodes;
	potEndNodes.push_back(node5);

//	graph->FindDijkstrasPath(node1, potEndNodes, outPath);
	
//	pathfinder->Dijkstras(node1, potEndNodes, outPath);


	//graph->RemoveNode(node1);

	//graph->RemoveEdge(node1, node2);

	//std::cout << "\n\n";

	//graph->DisplayToConsole();
	
}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(m_spritebatch);
	
	delete graph;
	//delete pathfinder;
}


void Game1::Update(float deltaTime)
{
	graph->Update(defaultTexture, traversedTexture);

//	graph->FindDijkstrasPathIncremental(node1, potEndNodes, outPath);

//	graph->FindDijkstrasPath(node1, potEndNodes, outPath);

	if (input->IsKeyDown(GLFW_KEY_SPACE) && spaceReleased)
	{
		continueSearch = true;
		spaceReleased = false;
	}
	else if (input->IsKeyUp(GLFW_KEY_SPACE))
	{
		spaceReleased = true;
	}

	if (continueSearch)
	{
		pathfinder->Dijkstras(node1, potEndNodes, outPath);
		continueSearch = false;
	}
//	_sleep(100);

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

//	graph->DisplayToScreen(m_spritebatch, t);
	graph->DisplayToScreen(m_spritebatch);

	/*static int temp = -1;

	if (temp < outPath.size() - 1)
	{
		++temp;
	}*/

	if (!outPath.empty())
	{
		for (auto iterator = outPath.begin(); iterator != outPath.end(); ++iterator)
		{
			m_spritebatch->DrawSprite(pathTexture, (*iterator)->position.x, (*iterator)->position.y, 10.f, 10.f);
		}
	}

//	system("cls");
//	graph->DisplayToConsole();

	//graph->TraverseDFS();
	//graph->TraverseBFS();

/*	m_spritebatch->DrawSprite(t, 300.f, 300.f, 64.f, 64.f, 3.14f);

	m_spritebatch->SetRenderColor(255, 0, 0, 255);
	m_spritebatch->DrawLine(30.f, 30.f, 300.f, 200.f, 1.f);
*/
	m_spritebatch->End();

}