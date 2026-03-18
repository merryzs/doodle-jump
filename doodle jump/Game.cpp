#include "Game.h"
#include "Platform.h"
#include "PlatformType.h"
#include "lib.h"
#include "CollisionManager.h"
#include "Wave.h"

const float screen_width = 1080.f;
const float screen_height = 1080.f;
const int max_platforms = 8;


Menu* currentMenu = nullptr;

Main_Menu mainMenu;

GameState currentState;

float randomPlatformX(float platformWidth)
{
    float halfScreen = screen_width / 2.f;

    if (sideDist(rng) == 0)
    {
        std::uniform_real_distribution<float> dist(0.f, halfScreen - platformWidth);
        return dist(rng);
    }
    else
    {
        std::uniform_real_distribution<float> dist(halfScreen, screen_width - platformWidth);
        return dist(rng);
    }
}

void Game::spawnPlatform(std::vector<Platform>& platforms, float y, float width, float height)
{
    const int MAX_TRIES = 20;
    const float MIN_VERTICAL_GAP = 100.f;
    const float MIN_HORIZONTAL_GAP = 100.f;

    for (int i = 0; i < MAX_TRIES; i++)
    {
        float x = randomPlatformX(width);
        PlatformType type = randomPlatformType();

        Platform newPlat({ x, y }, { width, height }, type);
        sf::FloatRect newBounds = newPlat.getBounds();

        bool overlaps = false;

        for (const auto& p : platforms)
        {
            sf::FloatRect other = p.getBounds();

            if (auto inter = newBounds.findIntersection(other))
            {
                if (inter->size.x > 0 && inter->size.y > 0)
                {
                    overlaps = true;
                    break;
                }
            }

            if (std::abs(p.getPosition().y - y) < MIN_VERTICAL_GAP)
            {
                overlaps = true;
                break;
            }

            if (std::abs(p.getPosition().x - x) < MIN_HORIZONTAL_GAP)
            {
                overlaps = true;
                break;
            }
        }

        if (!overlaps)
        {
            platforms.emplace_back(newPlat);
            return;
        }
    }

    platforms.emplace_back(
        sf::Vector2f(randomPlatformX(width), y),
        sf::Vector2f(width, height),
        randomPlatformType()
    );
}

Game::Game()
    : window(sf::VideoMode({ (int)screen_width,(int)screen_height }), "Doodle Jump"),
    backgroundTexture("images/background.png"),
    background(backgroundTexture),
    scoreText(font)
{
    window.setFramerateLimit(60);

    if (!waveTexture.loadFromFile("images/wave.png"))
        std::cerr << "Impossible de charger la texture de la vague\n";


    wave = Wave(waveTexture, { 1200.f, 400.f }, { -250.f, 0.f });


    auto size = backgroundTexture.getSize();
    background.setTextureRect(sf::IntRect({ 0, (int)size.y - (int)screen_height },
        { (int)screen_width, (int)screen_height }));


    sf::View view;
    view.setSize({ screen_width, screen_height });
    view.setCenter({ screen_width / 2.f, screen_height / 2.f });
    window.setView(view);


    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
        std::cerr << "Impossible de charger la police\n";

    switch (currentState)
    {

        case GameState::Main_Menu:
			mainMenu.display();
			mainMenu.update({ 0,0 });
			mainMenu.HandleClick({ 0,0 });
			mainMenu.draw(window);
			break;

    case GameState::Play:
       



        scoreText.setCharacterSize(32);
        scoreText.setPosition({ 20,20 });
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setString("Score: 0");


        platforms.clear();

        float spacing = 150.f;
        float startY = screen_height - 50.f;

        for (int i = 0; i < max_platforms; i++)
            spawnPlatform(platforms, startY - i * spacing);

        player.display();

        score = 0;

    }
   
    
}

void Game::reset()
{
    score = 0;
	currentState = GameState::Play;
    player.reset();

    platforms.clear();

    float spacing = 150.f;
    float startY = screen_height - 50.f;

    for (int i = 0; i < max_platforms; i++)
        spawnPlatform(platforms, startY - i * spacing);

    auto size = backgroundTexture.getSize();
    background.setTextureRect(sf::IntRect({ 0, (int)size.y - (int)screen_height },
        { (int)screen_width, (int)screen_height }));

    scoreText.setString("Score: 0");

   
    wave = Wave(waveTexture, { 1200.f, 400.f }, { -250.f, 0.f });
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();

        
        for (size_t i = 0; i < platforms.size();)
        {
            if (platforms[i].getPosition().y > screen_height)
            {
                platforms.erase(platforms.begin() + i);

                if (platforms.size() < max_platforms)
                    spawnPlatform(platforms, -10.f);
            }
            else
            {
                ++i;
            }
        }

        collisionManager.handle(player, platforms);
        render();
    }
}

void Game::processEvents()
{
    while (auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    if (currentState == GameState::Game_Over)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            reset();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

    }
}

void Game::update()
{
  
    
    switch (currentState)
    {
    case GameState::Main_Menu:
            mainMenu.update(sf::Vector2f(sf::Mouse::getPosition(window)));
            break;
       
    case GameState::Play:
            float deltaTime = clock.restart().asSeconds();


            if (player.isGrabbed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                {
                    player.resistance += 1.5f;
                }
                else
                {
                    player.resistance -= 0.5f;
                }

                player.resistance = std::clamp(player.resistance, 0.f, player.resistanceMax);
            }


            float slow = 1.f - (player.resistance / player.resistanceMax) * player.slowFactor;


            wave->update(deltaTime, slow);


            for (auto& p : platforms)
                p.update(deltaTime);


            player.updates(deltaTime);


            if (!player.isGrabbed)
            {
                if (auto inter = wave->getHitbox().findIntersection(player.getHitbox()))
                {
                    player.isGrabbed = true;
                    player.grabOffset = player.getPose() - wave->getPosition();
                }
            }


            if (player.isGrabbed)
            {
                player.setPose(wave->getPosition() + player.grabOffset);

                if (player.resistance >= player.resistanceMax)
                {
                    player.isGrabbed = false;
                    player.resistance = 0.f;
                }
            }


            float cameraTriggerY = screen_height * 0.4f;

            if (player.getPose().y < cameraTriggerY)
            {
                float offset = cameraTriggerY - player.getPose().y;

                player.setPose({ player.getPose().x, cameraTriggerY });

                for (auto& p : platforms)
                    p.setPosition({ p.getPosition().x, p.getPosition().y + offset });

                sf::IntRect rect = background.getTextureRect();
                rect.position.y -= offset;

                if (rect.position.y < 0)
                    rect.position.y = 0;

                background.setTextureRect(rect);

                score += static_cast<int>(offset);
            }

            player.warp();

            if (player.getPose().y > screen_height)
                currentState = GameState::Game_Over;

            scoreText.setString("Score: " + std::to_string(score));


            if (wave->isOffScreen(screen_width))
            {
                wave = Wave(waveTexture, { 1200.f, 400.f }, { -250.f, 0.f });
            };

            break;
	}
    
   
}

void Game::render()
{
    window.clear();

    switch (currentState)
    {
    


    case GameState::Main_Menu:
        // Afficher le menu principal
			break;

    
    case GameState::Play:
				// Afficher le jeu

                window.draw(background);

                for (const auto& platform : platforms)
                    platform.draw(window);

                wave->draw(window);
                player.draw(window);

                window.draw(scoreText);
				break;  


	case GameState::Game_Over:

                sf::RectangleShape gameoverBackground(sf::Vector2f(1080, 1080));
                gameoverBackground.setFillColor(sf::Color::Black);

                sf::Text gameOverText(font);
                gameOverText.setString("GAME OVER");
                gameOverText.setCharacterSize(80);
                gameOverText.setPosition({ 300,300 });
                gameOverText.setFillColor(sf::Color::Red);

                sf::Text resetText(font);
                resetText.setString("Press Spacebar to reset");
                resetText.setCharacterSize(40);
                resetText.setPosition({ 350,600 });
                resetText.setFillColor(sf::Color::Blue);

                sf::Text closeText(font);
                closeText.setString("Press Escape to quit");
                closeText.setCharacterSize(40);
                closeText.setPosition({ 350,800 });
                closeText.setFillColor(sf::Color::Green);

                window.draw(gameoverBackground);
                window.draw(gameOverText);
                window.draw(resetText);
                window.draw(closeText);
                break;
    }
 


    window.display();
}