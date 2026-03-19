#include "Game.h"


const int max_platforms = 10;
GameState currentState = GameState::Main_Menu;

void Game::spawnPlatform(std::vector<Platform>& platforms, float y, float width, float height)
{
    const int Max_tries = 20;
    const float Min_Vertical_gap = 200.f;
    const float Min_Horizontal_gap = 200.f;

    for (int i = 0; i < Max_tries; i++)
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

            if (std::abs(p.getPosition().y - y) < Min_Vertical_gap)
            {
                overlaps = true;
                break;
            }

            if (std::abs(p.getPosition().x - x) < Min_Horizontal_gap)
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

void Game::spawnWave()
{
    float x = RandomXWave(0.f, screen_width);

    wave = std::make_unique<Wave>(waveTexture, x, 0.f, sf::Vector2f{ 0.f, 250.f });

    wave->setRotation(90.f);

    waveActive = true;

    nextWaveScore += waveScoreGap;
}

Game::Game()

    : window(sf::VideoMode({ (unsigned int)screen_width,(unsigned int)screen_height }), "Doodle Jump"),
    backgroundTexture("images/background.png"),
    background(backgroundTexture),
    scoreText(font)
{
    window.setFramerateLimit(60);

    if (!waveTexture.loadFromFile("images/wave.png"))
        std::cerr << "Impossible de charger la texture de la vague\n";

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

    platforms.clear();
    enemies.clear();

    float spacing = 150.f;
    float startY = screen_height - 50.f;

    for (int i = 0; i < max_platforms; i++)
        spawnPlatform(platforms, startY - i * spacing);

    player.display();

    score = 0;


    waveActive = false;
    player.display();
    defeat.display();
    win.display();
    score = 0;

    currentState = GameState::Main_Menu;
}

void Game::reset()
{
    score = 0;

    player.reset();
    player.isGrabbed = false;
    player.resistance = 0.f;
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

    waveActive = false;
    nextWaveScore = 1500;
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

    if (currentState == GameState::Main_Menu)
    {
        mainMenu.HandleClick(sf::Vector2f(sf::Mouse::getPosition(window)));
    }

    switch (currentState)
    {
    case GameState::Main_Menu:

        //permet de reset quand on clic sur play
        mainMenu.HandleClick(mousePose);
        if (mainMenu.clickedrestart)
        {
            reset();
            mainMenu.clickedrestart = false;
            currentState = GameState::Play;
        }
        break;

    case GameState::Game_Over:
        //la same que juste au dessus mais pour le menu de d�faite

        defeat.HandleClick(mousePose);
        if (defeat.clickedrestart)
        {
            reset();
            defeat.clickedrestart = false;
            currentState = GameState::Play;
        }
        break;

    case GameState::win:

        //de même pour le menu de victoire
        win.HandleClick(mousePose);
        if (win.clickedrestart)
        {
            reset();
            win.clickedrestart = false;
            currentState = GameState::Play;
        }
        break;
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))

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

        for (auto& p : platforms)
            p.update(deltaTime);

        player.updates(deltaTime);

        std::cout << "score=" << score
            << " nextWaveScore=" << nextWaveScore
            << " gap=" << waveScoreGap
            << " waveActive=" << waveActive << "\n";

        if (!player.isGrabbed && waveActive)
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

        if (score >= 25000)
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

        if (!waveActive && score >= nextWaveScore)
        {
            spawnWave();
        }

        if (waveActive)
        {
            wave->update(deltaTime, slow);
        }

        break;
    }

    case GameState::Game_Over:     
            
    {
        defeat.update(sf::Vector2f(sf::Mouse::getPosition(window)));
        break;
    }
    case GameState::win:
    {
        win.update(sf::Vector2f(sf::Mouse::getPosition(window)));
        break;
    }

    }
}

        
void Game::checkEnemyCollisions()       
{
    sf::FloatRect playerBounds(player.hitbox.getPosition(), player.hitbox.getSize());
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
    {
        window.draw(background);

        for (const auto& platform : platforms)
            platform.draw(window);

        if (waveActive)
            wave->draw(window);

        for (auto& enemy : enemies)
            enemy->draw(window);
        player.draw(window);
        window.draw(scoreText);
        break;
    }

    case GameState::Game_Over:
        defeat.draw(window);
        break;
    
    case GameState::win:
        
        win.draw(window);
        break;
    }
    window.display();
}