#include <SearchBox.hpp>



SearchBox::SearchBox(sf::Vector2f pos, sf::Vector2f dim)
{
    sf::Transformable::setPosition(pos);
    dimensions = dim;
    font_color = sf::Color::Black;
    back_color = sf::Color(46, 192, 249);
    selected_color = sf::Color(186, 39, 74);
    outline_color = sf::Color::Black;
    is_selected = false;
    has_text = false;
    default_text = "Type text here...";
    stations = nullptr;
    hovered_choice = 0;
}

SearchBox::~SearchBox()
{

}

SearchBox::Status SearchBox::handleEvent(sf::Event& evt, sf::RenderWindow& window)
{
    if (search_matchs.size() > 0 && is_selected)
    {
        sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (pos.y > dimensions.y + getPosition().y && pos.x >= getPosition().x && pos.x <= getPosition().x + dimensions.x)
        {
            hovered_choice = (pos.y - getPosition().y) / dimensions.y - 1;
            if (hovered_choice > search_matchs.size())
                hovered_choice = search_matchs.size();
        }
    }
    else 
        hovered_choice = 0;
    if (evt.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f temp = getPosition();
        sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (search_matchs.size() > 0 && is_selected && pos.y > dimensions.y + getPosition().y  && pos.y < getPosition().y + ((search_matchs.size() + 1) * dimensions.y)\
            && pos.x >= getPosition().x && pos.x <= getPosition().x + dimensions.x)
        {
            input = std::next(search_matchs.begin(), hovered_choice)->getName();
            is_selected = false;
            return update_match();
        }
        if ((pos.x >= temp.x && pos.x <= temp.x + dimensions.x) &&  (pos.y >= temp.y && pos.y <= temp.y + dimensions.y))
            is_selected = true;
        else
            is_selected = false;
    }
    else if (evt.type == sf::Event::TextEntered && is_selected)
    {
        if (evt.text.unicode == 13)
        {
            if (search_matchs.size() > 0)
            {
                input = search_matchs.front().getName();
            }
        }
        else if (evt.text.unicode == 8)
        {
            if (input.size() > 0)
            {
                input.pop_back();
                has_text = input.size() > 0;
            }
        }
        else if (evt.text.unicode < 128)
        {
            input += evt.text.unicode;
            has_text = true;
        }
        return update_match();
    }
    return (search_matchs.size() > 0) ? Match : Empty;
}

bool check_if_match(const std::string a, const std::string b)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    }
    return true;
}

SearchBox::Status SearchBox::update_match()
{
    search_matchs.clear();
    if (has_text == false)
        return Empty;
    for (auto& i : *stations)
    {
        std::string temp = i.second.getName();
        if (check_if_match(input, temp))
            search_matchs.push_front(i.second);
    }
    if (search_matchs.size() == 1 && input == search_matchs.front().getName())
    {
        return Known;
    }
    else if (search_matchs.size() > 0)
        return Match;
    return No_match;
}

void SearchBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rec;
    sf::Text text;

    rec.setPosition(getPosition());
    rec.setSize(dimensions);
    rec.setFillColor(back_color);
    text.setFillColor(font_color);
    text.setCharacterSize(15);
    text.setFont(font);
    if (has_text == false && !is_selected)
        text.setString(default_text);
    else
        text.setString(input);
    text.setPosition(getPosition().x + dimensions.x / 2 - text.getGlobalBounds().width / 2,\
                         getPosition().y + dimensions.y / 2 -  + text.getGlobalBounds().height / 2);
    target.draw(rec);
    target.draw(text);
    if (has_text && is_selected)
    {
        auto temp = search_matchs.begin();
        rec.setOutlineThickness(0);
        for (size_t i = 0; i < (5 < search_matchs.size() ? 5 : search_matchs.size()); i++)
        {
            rec.move(0, dimensions.y);
            if (i == hovered_choice)
            {
                rec.setFillColor(sf::Color::White);
            }
            else
                rec.setFillColor(back_color);
            text.setString(temp->getName());
            text.setPosition(getPosition().x + dimensions.x / 2 - text.getGlobalBounds().width / 2,\
                            getPosition().y + dimensions.y * (1.f/2.f + i + 1) -  + text.getGlobalBounds().height / 2);
            target.draw(rec);
            target.draw(text);
            temp++;
        }
    }
    rec.setPosition(getPosition());
    rec.setFillColor(sf::Color(0, 0, 0, 0));
    rec.setOutlineColor(outline_color);
    rec.setOutlineThickness(2);
    if (is_selected && search_matchs.size())
        rec.setSize(sf::Vector2f(dimensions.x, dimensions.y * std::min((search_matchs.size() + 1), 6UL)));
    else
        rec.setSize(sf::Vector2f(dimensions.x, dimensions.y));
    target.draw(rec);
}

bool SearchBox::getStation(Station& res)
{
    if (search_matchs.size() > 0)
    {
        input = search_matchs.front().getName();
        res = search_matchs.front();
        return true;
    }
    return false;
}

sf::Vector2f SearchBox::getDimension()
{
    return dimensions;
}

void SearchBox::setDefaultText(std::string def)
{
    default_text = def;
}

void SearchBox::setFont(sf::Font& font)
{
    this->font =font;
}

void SearchBox::setStations(std::unordered_map<std::string, Station>& s)
{
    stations = std::addressof(s);
}

void SearchBox::setInput(const std::string station)
{
    input = station;
    if (station == "")
        has_text = false;
    else
    {
        has_text = true;
        update_match();
    }
}