#include "MenuDrawer.hpp"

const std::string& id_to_string(const int id)
{
    static const std::string convert[16]{"1", "2", "3", "3b", "4", "5", "6", "7", "7b", "8", "9", "10", "11", "12", "13", "14"};
    return convert[id];
}

MenuDrawer::MenuDrawer(sf::RenderWindow& newWindow) : window{newWindow}, currentMode{MenuDrawer::mode::Selection}
{
    source      = nullptr;
    destination = nullptr;

    for (int i = 0; i < 16; i++)
    {
        lineIsDisplayed[id_to_string(i)] = true;
    }
}

MenuDrawer::~MenuDrawer() 
{

}

void MenuDrawer::init()
{
    init_buttons();
}

MenuDrawer::handleRes MenuDrawer::handleEvent(sf::Event& evt)
{
    bool temp = false;
    sf::View v = window.getView();
    if (swapMode.button_pressed(window, evt) && source && destination)
    {
        currentMode = mode::DisplayPath;
        return handleRes::StartDijkstra;
    }
    for (int i = 0; i < 16; i++)
    {
        temp = linesButton[i].button_activated(window, evt);
        if (temp == lineIsDisplayed[id_to_string(i)]) 
        {
            lineIsDisplayed[id_to_string(i)] = !temp;
            return handleRes::None;
        }
    }
    return handleRes::None;
}

void MenuDrawer::render()
{
    //swapMode.refreshText();

    render_background();
    if (currentMode == mode::Selection) 
    {
        render_destsrc();
        render_buttons();
    }
    else
    {
        render_path();
        render_return();
    }
}

bool MenuDrawer::showLine(int id) {return lineIsDisplayed[id_to_string(id)];}


bool MenuDrawer::showLine(std::string line) {return lineIsDisplayed[line];}

void MenuDrawer::setMode(MenuDrawer::mode newMode)
{
    currentMode = newMode;
}

void MenuDrawer::setPathString(const std::list<std::string>&& path)
{
    pathString = path;
}

void MenuDrawer::setFont(const sf::Font& f)
{
    font = f;
}

void MenuDrawer::setSource(const Station* newSource)
{
    source = newSource;
}

void MenuDrawer::setDestination(const Station* newDestination)
{
    destination = newDestination;
}

void MenuDrawer::resetSourceDestination()
{
    source = nullptr;
    destination = nullptr;
}

void MenuDrawer::init_buttons()
{
    std::stringstream stringCreator;
    std::string buffer;

    for (int i = 0; i < 16; i++) {
        stringCreator << "img/ligne_" << id_to_string(i) << ".png";
        linesButton[i].setIdleTexture(stringCreator.str());
        linesButton[i].setActivated(false);
        linesButton[i].setPosition(sf::Vector2f(5 + i * 48, 10));
        linesButton[i].setDimension(sf::Vector2f(32.f, 32.f));
        stringCreator.str("");
    }/*
    for (int i = 0; i < 16; i++) {
        stringCreator << "ligne_" << id_to_string(i) << "a.png";
        linesButton[i].setActiveTexture(stringCreator.str());
        stringCreator.str("");
    }
    for (int i = 0; i < 16; i++) {
        stringCreator << "ligne_" << id_to_string(i) << "h.png";
        linesButton[i].setPressedTexture(stringCreator.str());
        stringCreator.str("");
    }*/
    swapMode.setFont(font);
    swapMode.setColor(sf::Color::White);
    swapMode.setIdleColor(sf::Color(46, 192, 249));
    swapMode.setOutlineColor(sf::Color::Black);
    swapMode.setPressedColor(sf::Color(186, 39, 74));
    swapMode.setActiveColor(sf::Color(186, 39, 74));
    swapMode.setDimension(sf::Vector2f(384, 64));
    swapMode.setString("Calculer le trajet");
    swapMode.setPosition(sf::Vector2f(192, 540));
    swapMode.setCharacterSize(25);
    swapMode.setOutlineThickness(2);
}

void MenuDrawer::render_background()
{
    sf::RectangleShape rec;
    sf::View v = window.getView();

    rec.setPosition(0, 0);
    rec.setFillColor(sf::Color(101, 180, 229));
    rec.setSize(sf::Vector2f(v.getSize().x, v.getSize().y));
    window.draw(rec);

    rec.setPosition(v.getSize().x - 5, 0);
    rec.setSize(sf::Vector2f(5, v.getSize().y));
    rec.setFillColor(sf::Color(46, 76, 86));
    window.draw(rec);
}

void MenuDrawer::render_destsrc()
{
    sf::Text temp;
    std::string buffer;
    sf::View v = window.getView();

    temp.setFont(font);
    temp.setCharacterSize(25);
    temp.setFillColor(sf::Color::White);
    temp.setString("Depart");
    temp.setPosition(sf::Vector2f(v.getSize().x / 2 - temp.getGlobalBounds().width / 2, 100));
    temp.setStyle(sf::Text::Bold);
    window.draw(temp);
    temp.setStyle(sf::Text::Regular);
    if (source) {
        temp.setString(source->getName());
        temp.setPosition(sf::Vector2f(v.getSize().x / 2 - temp.getGlobalBounds().width / 2, 125));
        window.draw (temp);
        temp.setStyle(sf::Text::Regular);    
    }

    temp.setString("Destination");
    temp.setStyle(sf::Text::Bold);
    temp.setPosition(sf::Vector2f(v.getSize().x / 2 - temp.getGlobalBounds().width / 2, 150));
    window.draw(temp);
    temp.setStyle(sf::Text::Regular);
    if (destination) {
        temp.setString(destination->getName());
        temp.setPosition(sf::Vector2f(v.getSize().x / 2 - temp.getGlobalBounds().width / 2, 175));
        window.draw (temp);
    }
}

void MenuDrawer::render_buttons()
{
    for (int i = 0; i < 16; i++)
    {
        window.draw(linesButton[i]);
    }
    window.draw(swapMode);
}

void MenuDrawer::render_path()
{
    sf::Text temp;
    temp.setCharacterSize(25);
    temp.setColor(sf::Color::White);
    temp.setFont(font);
    temp.setPosition({10.f, 25});

    for (auto& i : pathString)
    {
        temp.move(0, temp.getGlobalBounds().height + 5);
        temp.setString(i);
        window.draw(temp);
    }
}

void MenuDrawer::render_return()
{

}

ButtonColor& MenuDrawer::getSwapMode() {return swapMode;};
