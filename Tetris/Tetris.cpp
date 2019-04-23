#include "pch.h"
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int hight = 30; 
const int width = 20;

int ground[hight][width] = { 0 };

// the shape of the blocks
struct Point
{
	int x, y;
}
a[4], b[4];


int blocks[7][4] =
{
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,5,4,7,
	2,3,5,7,
	3,5,7,6,
	2,3,4,5,
};

bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x<0 || a[i].x>width || a[i].y >= hight) return 0;
		else if (ground[a[i].y][a[i].x])return 0;
	return 1;
}





int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(602, 902), "Titres", Style::Close | Style::Titlebar);
	Texture bg;
	bg.loadFromFile("pic/blocks.png");

	Sprite s(bg);
	s.setTextureRect(IntRect(0, 0, 30, 30));

	int dx = 0; bool rotate = 0; int colorNum = 1;
	float timer=0, delay=0.3;
	Clock clk;


	while (window.isOpen())
	{
		float time = clk.getElapsedTime().asSeconds();
		clk.restart();
		timer += time;
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}
			if (evnt.type == Event::KeyPressed)
				if (evnt.key.code == Keyboard::Up) rotate = true;
				else if (evnt.key.code == Keyboard::Left) dx = -1;
				else if (evnt.key.code == Keyboard::Right) dx = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;



		//// <- Move -> ///
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];




		//////Rotate//////
		if (rotate)
		{
			Point p = a[1];
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
		}


		///////Tick//////
		if (timer > delay)
		{
			
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1;
			}
			if (!check())
			{
				for (int i = 0; i < 4; i++) ground[b[i].y][b[i].x] = colorNum;
				colorNum = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = blocks[n][i] % 2;
					a[i].y = blocks[n][i] / 2;
				}
			}
			timer =0 ;
		}
		//////// Lines delete//////

		int k = hight - 1;
		for (int i = hight - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < width; j++)
			{
				if (ground[i][j]) count++;
				ground[k][j] = ground[i][j];
			}
			if (count < width) k--;
		}
		

		//int n = 3;
		//if(a[0].x==0)
		//for (int i = 0; i < 4; i++)
		//{
		//	a[i].x = blocks[n][i] % 2;
		//	a[i].y = blocks[n][i] / 2;
		//}

		dx = 0; rotate = 0; delay = 0.3;
		/////// Draw////////
		window.clear(Color::White);


		for (int i = 0; i <hight ; i++)
			for (int j = 0; j < width; j++)
			{
				if (ground[i][j] == 0) continue;
				s.setTextureRect(IntRect(ground[i][j] * 30, 0, 30, 30));
				s.setPosition(j * 30, i * 30);
				s.move(28, 31);
				window.draw(s);
			}



		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 30, 0, 30, 30));
			s.setPosition(a[i].x * 30, a[i].y * 30);
			s.move(28, 31);
			window.draw(s);
		}

		window.display();
		


	}
	return 0;
}