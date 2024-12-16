#include "Engine.h"
#include "Particle.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

Engine::Engine()
{
    VideoMode vm = VideoMode::getDesktopMode();
    m_Window.create(vm, "Particle Fireworks");
    srand((unsigned int)time(nullptr));
}

void Engine::run()
{
    Clock clock;

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen()) {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed) {
            m_Window.close();
        }

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
            m_Window.close();
        }


        if (event.type == Event::KeyPressed && event.key.code == Keyboard::G) {
            gravityEnabled = !gravityEnabled;
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 5; i++) {
                int numPoints = 25 + rand() % 26;
                Particle newParticle(m_Window, numPoints, mousePos);
                m_particles.push_back(newParticle);
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    for (auto it = m_particles.begin(); it != m_particles.end(); ) {
        if (it->getTTL() > 0.0f) {
            it->update(dtAsSeconds);
            ++it;
        }
        else {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();
    for (auto& particle : m_particles) {
        m_Window.draw(particle);
    }
    m_Window.display();
}
