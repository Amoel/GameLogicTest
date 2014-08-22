//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Level class                         //
// File:    Level.cpp                           //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#include "Level.h"

namespace GameLogicTest
{
	Level::Level()
	{
		/* Load assets */
		tileset = al_load_bitmap("Graphics/gfx_tiles.png");
		vignette = al_load_bitmap("Graphics/gfx_vignette.png");
		font = al_load_font("Fonts/ARCADECLASSIC.TTF", 36, NULL);

		for (int y = 0; y < LevelHeight; y++)
		{
			for (int x = 0; x < LevelWidth; x++)
			{
				Tile tile;
				tile.State = ((x + y) % 2 == 0) ? DARK_PENAL : LIGHT_PENAL;
				if (x % 4 == 0 && y % 4 == 0)
				{
					tile.State = TRAP;
				}
				else
				{
					tile.Node = new AStarNode(x, y);
					if (x > 0 && tiles[x - 1][y].Node != NULL)
					{
						tiles[x - 1][y].Node->Neighbors.push_back(tile.Node);
						tile.Node->Neighbors.push_back(tiles[x - 1][y].Node);
					}
					if (y > 0 && tiles[x][y - 1].Node != NULL)
					{
						tiles[x][y - 1].Node->Neighbors.push_back(tile.Node);
						tile.Node->Neighbors.push_back(tiles[x][y - 1].Node);
					}
				}
				tiles[x][y] = tile;
			}
		}

		player = new Player(100);

		/* Add enemies at the specified locations in coordinates. */
		enemies.push_back(new Enemy(22, 10));
		enemies.push_back(new Enemy(26, 10));
		enemies.push_back(new Enemy(22, 14));
		enemies.push_back(new Enemy(26, 14));
		enemies.push_back(new Enemy(22, 18));
		enemies.push_back(new Enemy(26, 18));
		enemies.push_back(new Enemy(22, 22));
		enemies.push_back(new Enemy(26, 22));
		this->levelOffset = FPoint2D{ 0, 0 };
		this->pathfinder = new AStarPathfinder();
	}

	Level::~Level()
	{
		for (int y = 0; y < LevelHeight; ++y)
		{
			for (int x = 0; x < LevelWidth; ++x)
			{
				delete(tiles[x][y].Node);
			}
		}
		delete(this->player);
		delete(this->pathfinder);
		al_destroy_bitmap(tileset);
		al_destroy_bitmap(vignette);
		al_destroy_font(font);
	}

	void Level::MovePlayer(int cursorX, int cursorY)
	{
		/*std::vector<AStarNode*> path = this->pathfinder->FindPath(this->tiles[this->player->GridLocation.X][this->player->GridLocation.Y].Node, this->tiles[(cursorX + (int)levelOffset.X) / 64][(cursorY + (int)levelOffset.Y) / 64].Node);
		std::queue<Point2D> newQueue;
		for (std::vector<AStarNode*>::iterator iter = path.begin(); iter != path.end(); ++iter)
		{
		AStarNode* node = *iter;
		newQueue.push(Point2D{ node->X, node->Y });
		}
		player->WalkingQueue = newQueue;*/
		player->GridLocation = Point2D{ (cursorX + (int)levelOffset.X) / 64, (cursorY + (int)levelOffset.Y) / 64 };
	}

	void Level::Update(float deltaTime)
	{
		player->Update(deltaTime);
		levelOffset.X = min((LevelWidth * TileSize) - 1200, max(0, this->player->Location.X - 640));
		levelOffset.Y = min((LevelHeight * TileSize) - 400, max(0, this->player->Location.Y - 400));

		for each (Enemy* enemy in enemies)
		{
			enemy->Update(deltaTime);
		}
	}

	void Level::Draw()
	{
		for (int y = 0; y < LevelWidth; y++)
		{
			for (int x = 0; x < LevelWidth; x++)
			{
				switch (tiles[x][y].State)
				{
				case TileState::DARK_PENAL:
					al_draw_bitmap_region(tileset, 0, 0, 64, 64, x * TileSize - this->levelOffset.X, y * TileSize - this->levelOffset.Y, NULL); break;
				case TileState::LIGHT_PENAL:
					al_draw_bitmap_region(tileset, 64, 0, 64, 64, x * TileSize - this->levelOffset.X, y * TileSize - this->levelOffset.Y, NULL); break;
				case TileState::TRAP:
					al_draw_bitmap_region(tileset, 64, 64, 64, 64, x * TileSize - this->levelOffset.X, y * TileSize - this->levelOffset.Y, NULL); break;
				}
			}
		}
		player->Draw(levelOffset);
		for each (Enemy* enemy in enemies)
		{
			enemy->Draw(levelOffset);
		}
		al_draw_bitmap(vignette, 0, 0, NULL);

		/* Prints the player's life. */
		al_draw_text(font, al_map_rgb(219, 73, 29), 390, 4, ALLEGRO_ALIGN_LEFT, "Lifes");
		al_draw_text(font, al_map_rgb(247, 27, 27), 510, 4, ALLEGRO_ALIGN_LEFT, "5");

		/* Prints the player's score. */
		al_draw_text(font, al_map_rgb(219, 73, 29), 708, 4, ALLEGRO_ALIGN_LEFT, "Score");
		al_draw_text(font, al_map_rgb(247, 27, 27), 824, 4, ALLEGRO_ALIGN_LEFT, "123");
	}
}