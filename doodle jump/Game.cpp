#include "Game.h"
#include "Platform.h"
#include "PlatformType.h"
#include "lib.h"
#include "CollisionManager.h"
#include "Wave.h"
#include "Random.h"

const int max_platforms = 10;

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

void Game::spawnWave()
{
    float x = RandomXWave(0.f, screen_width);

    wave = std::make_unique<Wave>(waveTexture, x, 0.f, sf::Vector2f{ 0.f, 250.f });

    wave->setRotation(90.f);

    waveActive = true;

    nextWaveScore += waveScoreGap;
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

    float spacing = 150.f;
    float startY = screen_height - 50.f;

    for (int i = 0; i < max_platforms; i++)
        spawnPlatform(platforms, startY - i * spacing);

    player.display();

    score = 0;
    gameover = false;

   
    waveActive = false;
}

void Game::reset()
{
    score = 0;
    gameover = false;

    player.reset();
    player.isGrabbed = false;
    player.resistance = 0.f;

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

    if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        reset();

    if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        window.close();
}

void Game::update()
{
    float deltaTime = clock.restart().asSeconds();

    if (player.isGrabbed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            player.resistance += 10.f;
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
        gameover = true;

    scoreText.setString("Score: " + std::to_string(score));

    if (!waveActive && score >= nextWaveScore)
    {
        spawnWave();
    }

    if (waveActive)
    {
        wave->update(deltaTime, slow);

        if (wave->isOffScreen(screen_height))
        {
            waveActive = false;
        }
    }
}

void Game::render()
{
    window.clear();

    window.draw(background);

    for (const auto& platform : platforms)
        platform.draw(window);

    if (waveActive)
        wave->draw(window);

    player.draw(window);

    window.draw(scoreText);

    if (gameover)
    {
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
    }

    window.display();
}