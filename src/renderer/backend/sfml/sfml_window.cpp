#include "../../renderer_config.h"
#ifdef USE_SFML_BACKEND

#include "sfml_window.h"
#include "../../../base/cordinate.h"

#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

using namespace std;
using namespace renderer::api;

namespace renderer::backend::sfml {

    IWindow::RegistrationToken Window::registerKeyboardEvent(KeyboardEventCallback callback)
    {
        std::size_t index = _keyboardEventMethods.size();
        _keyboardEventMethods.push_back(callback);
        return index;
    }
    IWindow::RegistrationToken Window::registerPointerEvent(PointerEventCallback callback)
    {
        std::size_t index = _pointerEventMethods.size();
        _pointerEventMethods.push_back(callback);
        return index;
    }
    IWindow::RegistrationToken Window::registerSystemEvents(SystemEventsCallback callback)
    {
        std::size_t index = _systemEventsCallbacks.size();
        _systemEventsCallbacks.push_back(callback);
        return index;
    }

    bool Window::updateWindowProps(WindowOptions& options)
    {
        return false;
    }

    bool Window::initGUI()
    {
        return ImGui::SFML::Init(_window);
    }

    bool Window::startEventLoop()
    {
        sf::Clock deltaClock;
        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(_window, event);

                _redirectEventToListeners(event);

                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
            }

            ImGui::SFML::Update(_window, deltaClock.restart());

            _imGuiDrawer();

            _window.clear();
            ImGui::SFML::Render(_window);
            _window.display();

            if (_isCloseWindow)
            {
                ImGui::SFML::Shutdown(_window);
                _window.close();
            }
        }
        return true;
    }

    template <class T>
    static bool interateOverCallbacks(vector <function<bool(T)>> _functionList, T param)
    {
        for (function<bool(T)> &callback : _functionList)
        {
            callback(param);
        }

        return true;
    }

    static renderer::api::KeyboardEvent toKeyboardEvent(sf::Event event)
    {
        KeyboardEvent kbEvent;
        kbEvent.alt = event.key.alt;
        kbEvent.ctrl = event.key.control;
        kbEvent.shift = event.key.shift;
        kbEvent.shift = event.key.system;
        kbEvent.key = static_cast<Key>(event.key.code);
        return kbEvent;
    }

    static renderer::api::PointerEvent toPointerEvent(sf::Event event)
    {
        PointerEvent pEvent;
        pEvent.x = event.mouseButton.x;
        pEvent.y = event.mouseButton.y;
        pEvent.keyUp = event.type == sf::Event::EventType::MouseButtonReleased;
        pEvent.keyDown = event.type == sf::Event::EventType::MouseButtonPressed;
        pEvent.type = PointerType::MouseLeftClick;
        // Todo handle other types as well
        return pEvent;
    }

    bool Window::_redirectEventToListeners(sf::Event event)
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed: __fallthrough;
            case sf::Event::KeyReleased:
                return interateOverCallbacks<renderer::api::KeyboardEvent>(_keyboardEventMethods, {});
            case sf::Event::MouseButtonPressed:
            case sf::Event::EventType::MouseButtonReleased:
            case sf::Event::EventType::TouchBegan:
            case sf::Event::EventType::TouchEnded:
                return interateOverCallbacks<renderer::api::PointerEvent>(_pointerEventMethods, {});
            default: return interateOverCallbacks<renderer::api::EventType>(_systemEventsCallbacks, {});
        }
    }


    bool Window::setImGuiLoop(std::function<void(void)> method)
    {
        _imGuiDrawer = method;
        return true;
    }
    bool Window::destroyWindow()
    {
        _isCloseWindow = true;
        return true;
    }
}

#endif // USE_SFML_BACKEND