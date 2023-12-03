#include "Game.h"

void Game::Update()
{
	sf::Time deltatime = this->gameClock_.restart();
	this->flock_->updateBoids(deltatime.asSeconds());
}

void Game::Draw()
{
	this->flock_->drawBoids(this->window_);
	this->window_.display();

}

Game::Game(int screen_width, int screen_height,std::unique_ptr<NeighborSearchStrategy>&& searchStrategy):window_(sf::RenderWindow(sf::VideoMode(screen_width, screen_height), "SFML works!"))
{
	this->gameBoundary_ = sf::FloatRect(BORDER_SIZE, BORDER_SIZE, screen_width - BORDER_SIZE, screen_height - BORDER_SIZE);

	this->flock_ = std::make_unique<Flock>(std::move(searchStrategy), SIGHT_RADIUS, this->gameBoundary_);

	for (int i = 0; i < STARTING_BOIDS; i++) {
		this->flock_->addBoid();
	}
}

void Game::start()
{
	//std::cout.precision(15);

	while (this->window_.isOpen())
	{
		sf::Event event;
		while (this->window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				this->window_.close();
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					this->flock_->addBoid(sf::Vector2f(this->gameBoundary_.width / 2 + this->gameBoundary_.left, this->gameBoundary_.height / 2 + this->gameBoundary_.top));
				}
			}

		}

		this->window_.clear();

		this->Update();

		this->Draw();

		/*std::cout << 1/deltaTime.asSeconds() << " fps" << std::endl;*/

	}
}
