#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "Graph.h"

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);
	inputInstance = Input::GetSingleton();

	t = new Texture("./Images/nodeTexture.png");//box0_256.png");

	graph = new Graph(true);

	Node* node1 = new Node(vec3(10, 100, 0));	//Jason has each node having an int id
	Node* node2 = new Node(vec3(50, 50, 0));
	Node* node3 = new Node(vec3(100, 230, 0));
	Node* node4 = new Node(vec3(150, 150, 0));

	graph->AddNode(node1);
	graph->AddNode(node2);
	graph->AddNode(node3);
	graph->AddNode(node4);

	graph->AddEdge(node1, node3);
	graph->AddEdge(node1, node4);
	graph->AddEdge(node3, node2);

	graph->DisplayToConsole();


	//graph->RemoveNode(node1);

	//graph->RemoveEdge(node1, node2);

	//std::cout << "\n\n";

	//graph->DisplayToConsole();
	
}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(m_spritebatch);
	
	delete graph;
}


void Game1::Update(float deltaTime)
{
	if (inputInstance->WasMouseButtonPressed()
}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	m_spritebatch->Begin();

	// TODO: draw stuff.

	graph->DisplayToScreen(m_spritebatch, t);

/*	m_spritebatch->DrawSprite(t, 300.f, 300.f, 64.f, 64.f, 3.14f);

	m_spritebatch->SetRenderColor(255, 0, 0, 255);
	m_spritebatch->DrawLine(30.f, 30.f, 300.f, 200.f, 1.f);
*/
	m_spritebatch->End();

}