#ifndef CLASSES_H
#define CLASSES_H

const uint16_t DELT_SCREEN = 10;
const uint16_t DELT_BLOCKS = 5;

class Coord
{
private:
	uint8_t x;
	uint16_t y;
public:
	Coord(uint8_t _x, uint8_t _y)
	{
		x = _x;
		y = _y;
	}
	uint8_t getx()
	{
		return x;
	}
	uint8_t gety()
	{
		return y;
	}

	void setCoord(uint8_t _x, uint8_t _y)
	{
		x = _x;
		y = _y;
	}
	friend bool operator== (const Coord& c1,const Coord& c2);
};

bool operator== (const Coord& c1, const Coord& c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}


class Block
{
private:
	Coord c;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Block(Coord cord) : c(cord)
	{
		sf::Vector2f xy;
		xy.x = DELT_SCREEN + c.getx() * 55 + c.getx() * DELT_BLOCKS;
		xy.y = DELT_SCREEN + c.gety() * 55 + c.gety() * DELT_BLOCKS;
		sprite.setPosition(xy);
	}

	void setTexture(std::string path)
	{
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}
	sf::Sprite getSprite()
	{
		return sprite;
	}


};

class Stone
{
private:
	Coord c;
	sf::Texture texture;
	sf::Sprite sprite;
	uint8_t color_pos;
	bool check_pos()
	{
		uint8_t x = c.getx();
		if (x == color_pos) return true;
		else return false;
	}

public:
	bool fin;
	Stone(Coord cord, uint8_t cl_pos) : c(cord)
	{
		setPosition(c.getx(),c.gety());
		color_pos = cl_pos;
		fin = check_pos();
	}


	void setTexture(std::string path)
	{
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}

	void setPosition(uint8_t x, uint8_t y)
	{
		c = Coord(x, y);
		sf::Vector2f xy;
		xy.x = DELT_SCREEN + c.getx() * 55 + c.getx() * DELT_BLOCKS;
		xy.y = DELT_SCREEN + c.gety() * 55 + c.gety() * DELT_BLOCKS;
		sprite.setPosition(xy);
		fin = check_pos();
	}

	sf::Sprite getSprite()
	{
		return sprite;
	}
};

class Curs
{
private:
	Coord c;
	sf::Texture texture;
	sf::Sprite sprite;
	std::vector<Coord>* stones;
	std::vector<Coord>* all;
	std::vector<Stone*>* stones_s;
	bool choice;
	uint8_t choiced;

	bool can_movie(Coord cc)
	{
		uint8_t x, y;
		x = cc.getx();
		y = cc.gety();
		if (x > 4) return false;
		if (y > 4) return false;
		return true;
	}

	bool can_drag(Coord cc)
	{
		uint8_t x, y;
		x = cc.getx();
		y = cc.gety();
		if (x > 4) return false;
		if (y > 4) return false;
		if (std::find(all->begin(), all->end(), cc) != all->end()) return false;

		return true;
	}

	void setCoord()
	{
		sf::Vector2f xy;
		xy.x = DELT_SCREEN + c.getx() * 55 + c.getx() * DELT_BLOCKS;
		xy.y = DELT_SCREEN + c.gety() * 55 + c.gety() * DELT_BLOCKS;
		sprite.setPosition(xy);
	}

public:
	Curs(Coord cord, std::vector<Coord>* st, std::vector<Coord>* _all, std::vector<Stone*>* sts) : c(cord)
	{
		stones_s = sts;
		stones = st;
		all = _all;
		choice = false;
		texture.loadFromFile("graphics\\cursor.png");
		sprite.setTexture(texture);
		setCoord();
	}

	bool setPosition(sf::Keyboard::Key key)
	{
		Coord _c(c.getx(), c.gety());
		if (!choice)
		{
			if (sf::Keyboard::Left == key)
			{
				_c.setCoord(c.getx() - 1, c.gety());
				if (can_movie(_c)) c.setCoord(c.getx() - 1, c.gety());
			}
			if (sf::Keyboard::Right == key)
			{
				_c.setCoord(c.getx() + 1, c.gety());
				if (can_movie(_c)) c.setCoord(c.getx() + 1, c.gety());
			}
			if (sf::Keyboard::Up == key)
			{
				_c.setCoord(c.getx(), c.gety() - 1);
				if (can_movie(_c)) c.setCoord(c.getx(), c.gety() - 1);
			}
			if (sf::Keyboard::Down == key)
			{
				_c.setCoord(c.getx(), c.gety() + 1);
				if (can_movie(_c)) c.setCoord(c.getx(), c.gety() + 1);
			}
		}
		else
		{
			if (sf::Keyboard::Left == key)
			{
				_c.setCoord(c.getx() - 1, c.gety());
				if (can_movie(_c) && can_drag(_c))
				{
					c.setCoord(c.getx() - 1, c.gety());
					all->at(choiced + 6).setCoord(c.getx(), c.gety());
					stones->at(choiced).setCoord(c.getx(), c.gety());
					stones_s->at(choiced)->setPosition(c.getx(), c.gety());
					sprite.setColor(sf::Color(255, 255, 255, 255));
					choice = false;
				}
			}
			if (sf::Keyboard::Right == key)
			{
				_c.setCoord(c.getx() + 1, c.gety());
				if (can_movie(_c) && can_drag(_c))
				{
					c.setCoord(c.getx() + 1, c.gety());
					all->at(choiced + 6).setCoord(c.getx(), c.gety());
					stones->at(choiced).setCoord(c.getx(), c.gety());
					stones_s->at(choiced)->setPosition(c.getx(), c.gety());
					sprite.setColor(sf::Color(255, 255, 255, 255));
					choice = false;
				}
			}
			if (sf::Keyboard::Up == key)
			{
				_c.setCoord(c.getx(), c.gety() - 1);
				if (can_movie(_c) && can_drag(_c))
				{
					c.setCoord(c.getx(), c.gety() - 1);
					all->at(choiced + 6).setCoord(c.getx(), c.gety());
					stones->at(choiced).setCoord(c.getx(), c.gety());
					stones_s->at(choiced)->setPosition(c.getx(), c.gety());
					sprite.setColor(sf::Color(255, 255, 255, 255));
					choice = false;
				}
			}
			if (sf::Keyboard::Down == key)
			{
				_c.setCoord(c.getx(), c.gety() + 1);
				if (can_movie(_c) && can_drag(_c))
				{
					c.setCoord(c.getx(), c.gety() + 1);
					all->at(choiced + 6).setCoord(c.getx(), c.gety());
					stones->at(choiced).setCoord(c.getx(), c.gety());
					stones_s->at(choiced)->setPosition(c.getx(), c.gety());
					sprite.setColor(sf::Color(255, 255, 255, 255));
					choice = false;
				}
			}
		}
		if (sf::Keyboard::Space == key)
		{
			if (std::find(stones->begin(), stones->end(), c) == stones->end()) return false;
			else choiced = std::distance(stones->begin(), std::find(stones->begin(), stones->end(), c));
			if (!choice)
			{
				choice = true;
				sprite.setColor(sf::Color(255, 0, 0, 255));
			}
			else
			{
				sprite.setColor(sf::Color(255, 255, 255, 255));
				choice = false;
			}
		}

		setCoord();
		return true;
	}

	sf::Sprite getSprite()
	{
		return sprite;
	}
};

class GameBoard
{
private:
	std::vector<Coord> all;
	std::vector<Coord> blocks;
	std::vector<Coord> stones;
	std::vector<Block*> blocks_s;
	std::vector<Stone*> stones_s;
	uint8_t red;
	uint8_t blue;
	uint8_t green;
	uint8_t blocks1;
	uint8_t blocks2;
	sf::RenderWindow* rw_window;
	Curs* curs = new Curs(Coord(0, 0),&stones,&all,&stones_s);

	bool check()
	{
		for (uint8_t i = 0; i < 15; i++)
			if (!stones_s.at(i)->fin) return false;
		return true;
	}
public:
	GameBoard(sf::RenderWindow* window)
	{
		rw_window = window;
	}
	~GameBoard()
	{
		for (uint8_t i = 0; i < 6; i++) delete blocks_s.at(i);
		for (uint8_t i = 0; i < 18; i++) delete stones_s.at(i);
		delete curs;
	}
	void generate()
	{
		uint8_t x=0, y=0;
		Coord c(x, y);
		Stone* s;
		std::srand(std::time(NULL));
		blocks1 = std::rand() % 5;
		blocks2 = (blocks1 + 47) % 5;
		red = (blocks2 + 47) % 5;
		blue = (red + 47) % 5;
		green = (blue + 47) % 5;
		for (uint8_t i = 0; i < 3;)
		{
			y = std::rand() % 5;
			x = blocks1;
			c.setCoord(x, y);
			if (std::find(all.begin(), all.end(), c)!=all.end())
			{
				continue;
			}
			i++;
			blocks.push_back(c);
			all.push_back(c);
			Block* b = new Block(c);
			blocks_s.push_back(b);
			blocks_s.back()->setTexture("graphics\\block.png");
		}
		for (uint8_t i = 0; i < 3;)
		{
			y = std::rand() % 5;
			x = blocks2;
			c.setCoord(x, y);
			if (std::find(all.begin(), all.end(), c) != all.end())
			{
				continue;
			}
			i++;
			blocks.push_back(c);
			all.push_back(c);
			Block* b = new Block(c);
			blocks_s.push_back(b);
			blocks_s.back()->setTexture("graphics\\block.png");
		}

		for (uint8_t i = 0; i < 5;)
		{
			y = std::rand() % 5;
			x = std::rand() % 5;
			c.setCoord(x, y);
			if (std::find(all.begin(), all.end(), c) != all.end())
			{
				continue;
			}
			i++;
			all.push_back(c);
			stones.push_back(c);
			Stone* b = new Stone(c,red);
			stones_s.push_back(b);
			stones_s.back()->setTexture("graphics\\3.png");
		}

		for (uint8_t i = 0; i < 5;)
		{
			y = std::rand() % 5;
			x = std::rand() % 5;
			c.setCoord(x, y);
			if (std::find(all.begin(), all.end(), c) != all.end())
			{
				continue;
			}
			i++;
			all.push_back(c);
			stones.push_back(c);
			Stone* b = new Stone(c, blue);
			stones_s.push_back(b);
			stones_s.back()->setTexture("graphics\\2.png");
		}

		for (uint8_t i = 0; i < 5;)
		{
			y = std::rand() % 5;
			x = std::rand() % 5;
			c.setCoord(x, y);
			if (std::find(all.begin(), all.end(), c) != all.end())
			{
				continue;
			}
			i++;
			all.push_back(c);
			stones.push_back(c);
			Stone* b = new Stone(c, green);
			stones_s.push_back(b);
			stones_s.back()->setTexture("graphics\\1.png");
		}

		x = blue;
		y = 5;
		c.setCoord(x, y);
		s = new Stone(c, blue);
		stones.push_back(c);
		stones_s.push_back(s);
		stones_s.back()->setTexture("graphics\\2.png");


		x = red;
		y = 5;
		c.setCoord(x, y);
		s = new Stone(c, red);
		stones.push_back(c);
		stones_s.push_back(s);
		stones_s.back()->setTexture("graphics\\3.png");

		x = green;
		y = 5;
		c.setCoord(x, y);
		s = new Stone(c, green);
		stones.push_back(c);
		stones_s.push_back(s);
		stones_s.back()->setTexture("graphics\\1.png");
	}

	bool update(sf::Event event)
	{
		if (event.type == event.KeyPressed) curs->setPosition(event.key.code);
		return check();
	}

	void draw()
	{
		for (uint8_t i = 0; i < 6; i++) rw_window->draw(blocks_s.at(i)->getSprite());
		for (uint8_t i = 0; i < 18; i++) rw_window->draw(stones_s.at(i)->getSprite());
		rw_window->draw(curs->getSprite());
	}
};

class Background
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font font;
	sf::Text text;
	sf::RenderWindow* rw_window;
public:
	Background(sf::RenderWindow* window)
	{
		rw_window = window;
		font.loadFromFile("miamanueva.otf");
		text.setFont(font);
		text.setPosition(sf::Vector2f(55,385));
		text.setCharacterSize(14);
		text.setString("Developed by Fyodorov Kirill");
	}
	void setTexture(std::string path)
	{
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}
	void draw()
	{
		rw_window->draw(sprite);
		rw_window->draw(text);
	}
	sf::Sprite get()
	{
		return sprite;
	}
};

class Game 
{
private:
	sf::RenderWindow* rw_window;
	int status;
	Background* bg;
	GameBoard* gb;

	void win()
	{
		rw_window->clear();
		bg->setTexture("graphics\\end.png");
		bg->draw();
		rw_window->display();
		sf::SoundBuffer buffer;
		buffer.loadFromFile("den-pobedy-z_uk-2.wav");
		sf::Sound sound;
		sound.setBuffer(buffer);
		sound.play();
		sf::sleep(sf::Time(sf::seconds(5)));
	}

	void update()
	{
		sf::Event event;
		while (rw_window->isOpen())
		{
			while (rw_window->pollEvent(event))
			{
				bool winner = gb->update(event);
				if ((event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				{
					shutdown();
					return;
				}
				if (winner)
				{
					win();
					shutdown();
					return;
				}
			}
			draw();
		}
	}

	void draw()
	{
		rw_window->clear();
		bg->draw();
		gb->draw();
		rw_window->display();
	}

	void shutdown()
	{
		rw_window->close();
		status = 0;
		delete rw_window;
		delete bg;
		delete gb;
	}

public:
	Game()
	{
		status = 1;
		rw_window = new sf::RenderWindow(sf::VideoMode(315, 410), "15 - Fyodorov Kirill", sf::Style::None);
		rw_window->setFramerateLimit(60);
		gb = new GameBoard(rw_window);
		gb->generate();
		bg = new Background(rw_window);
		bg->setTexture("graphics\\background.png");
	}

	int run()
	{
		update();
		return status;
	}
};
#endif
