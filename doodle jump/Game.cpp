#include "Game.h"

const float screen_width = 1080.f;
const float screen_height = 1080.f;
const int max_platforms = 8;

Menu* currentMenu = nullptr;

Defeat defeat;
WinMenu win;
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

void Game::spawnEnemy(float y, EnemyType type)
{
    const float MIN_DISTANCE_X = 300.f;
    const int MAX_TRIES = 10;

    float x = 0.f;
    bool valid = false;

    for (int i = 0; i < MAX_TRIES; i++)
    {
        x = static_cast<float>(rand() % 900 + 50);
        valid = true;

        for (auto& e : enemies)
        {
            if (std::abs(e->getPosition().x - x) < MIN_DISTANCE_X)
            {
                valid = false;
                break;
            }
        }

        if (valid)
            break;
    }

    enemies.emplace_back(std::make_unique<Enemy>(sf::Vector2f(x, y), type));
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

        scoreText.setCharacterSize(32);
        scoreText.setPosition({ 20,20 });
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setString("Score: 0");


        platforms.clear();
        enemies.clear();

        float spacing = 150.f;
        float startY = screen_height - 50.f;

        for (int i = 0; i < max_platforms; i++)
            spawnPlatform(platforms, startY - i * spacing);

        player.display();
        defeat.display();
        win.display();
        score = 0;

		currentState = GameState::Main_Menu;
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

    switch (currentState)
    {

    case GameState::Main_Menu:

            mainMenu.HandleClick(sf::Vector2f(sf::Mouse::getPosition(window)));

			break;

	case GameState::Game_Over:

            defeat.HandleClick(sf::Vector2f(sf::Mouse::getPosition(window)));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                reset();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
            break;

	case GameState::win:

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                reset();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        break;
    }
 

    if (currentState == GameState::Game_Over || currentState == GameState::win)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            reset();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();
    }
}

void Game::update()
{  
    float deltaTime = clock.restart().asSeconds();

    switch (currentState)
    {
    case GameState::Main_Menu:
            mainMenu.update(sf::Vector2f(sf::Mouse::getPosition(window)));
            break;
       
    case GameState::Play:
    {
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
        {
            currentState = GameState::Game_Over;
        }

        if (score >= 30000)
        {
            currentState = GameState::win;
        }

        if (score - lastEnemyScore >= SCORE_SPAWN_ENEMY)
        {
            lastEnemyScore = score;

            spawnEnemy(-50.f, EnemyType::Static);
            spawnEnemy(-550.f, EnemyType::Moving);
        }

        for (auto& enemy : enemies)
        {
            enemy->update(deltaTime);


            if (enemy->isActive() && player.getBounds().findIntersection(enemy->getBounds()))
            {
                currentState = GameState::Game_Over;

            }
        }

        for (size_t i = 0; i < enemies.size(); )
        {
            if (enemies[i]->getPosition().y > screen_height + 100.f)
                enemies.erase(enemies.begin() + i);
            else
                ++i;
        }

        scoreText.setString("Score: " + std::to_string(score));


        if (wave->isOffScreen(screen_width))
        {
            wave = Wave(waveTexture, { 1200.f, 400.f }, { -250.f, 0.f });
        };

        break;
    }

    case GameState::Game_Over:

        defeat.update(sf::Vector2f(sf::Mouse::getPosition(window)));	
        break;
	}

    scoreText.setString("Score: " + std::to_string(score));
}

void Game::checkEnemyCollisions()
{
    sf::FloatRect playerBounds(
        player.hitbox.getPosition(),
        player.hitbox.getSize()
    );

    for (auto& enemy : enemies)
    {
        if (enemy->isActive() && playerBounds.findIntersection(enemy->getBounds()))
        {
            
            currentState = GameState::Game_Over;
            return;
        }
    }
}

void Game::render()
{
    window.clear();

    switch (currentState)
    {
    case GameState::Main_Menu:

        mainMenu.draw(window);
        break;

    case GameState::Play:

        window.draw(background);

        for (const auto& platform : platforms)
            platform.draw(window);

        for (auto& enemy : enemies)
            enemy->draw(window);

        wave->draw(window);
        player.draw(window);

        window.draw(scoreText);

        break;

    case GameState::Game_Over:
        defeat.draw(window);
        break;

    case GameState::win:

        win.draw(window);
    }

    window.display();
}