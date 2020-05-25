#include <iostream>
#include <SFML/Graphics.hpp>
#include "Station.hpp"
#include <list>
#include <unordered_map>






class SearchBox : public sf::Transformable, public sf::Drawable
{
private:
    std::string input;
    std::string default_text;
    std::list<Station> search_matchs;
    std::unordered_map<std::string, Station>* stations; 

    sf::Font font;
    sf::Color back_color;
    sf::Color selected_color;
    sf::Color outline_color;
    sf::Color font_color;

    sf::Vector2f dimensions;
    bool has_text;
    bool is_selected;
    int hovered_choice;

public:
    enum Status {Empty, No_match, Match, Known};
    SearchBox(sf::Vector2f pos, sf::Vector2f dim);
    ~SearchBox();

    Status handleEvent(sf::Event& evt, sf::RenderWindow& window);
    Status update_match();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool getStation(Station& res);
    sf::Vector2f getDimension();

    void setDefaultText(std::string def);
    void setFont(sf::Font& font);
    void setStations(std::unordered_map<std::string, Station>& s);
    void setInput(const std::string station);
private:
};