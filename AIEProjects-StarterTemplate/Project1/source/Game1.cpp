#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <fstream>
#include <iostream>

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	srand(time(NULL));

	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);

	input = Input::GetSingleton();

	LoadMenu();			//Loads menuText from text file
	menuFont				= new Font("./Fonts/calibri_24px.fnt");
	//menuFont = new Font("./Fonts/arial_20px.fnt");
	//menuFont				= new Font("./Fonts/CourierNew_11px.fnt");
	menuPos					= vec2(0.f, 0.f);


	//defaultTexture			= new Texture("./Images/circle_blue.png");
	defaultTexture = make_shared<Texture>("./Images/Arrow.png");

	agent = make_shared<Agent>(defaultTexture);
}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(m_spritebatch);
}

void Game1::Update(float deltaTime_)
{
	if (input->IsKeyDown(GLFW_KEY_ESCAPE))
	{
		Game1::Application::Quit();
	}

	if (input->IsKeyDown(GLFW_KEY_L))
	{
		LoadMenu();
	}

	agent->Update(deltaTime_);
}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	m_spritebatch->Begin();

	// TODO: draw stuff.
	agent->Draw(m_spritebatch);

	//Draw menu
	m_spritebatch->DrawString(menuFont, menuText, menuPos.x, menuPos.y);

	m_spritebatch->End();
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
