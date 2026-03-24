inline sf::FloatRect getTextSize(const std::string& text,
                                 sf::Font* font,
                                 unsigned int size) {
    sf::Text textObj(*font, text);
    textObj.setCharacterSize(size);
    return textObj.getLocalBounds();
}