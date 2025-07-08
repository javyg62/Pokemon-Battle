#include "Pokemon.hpp"

// Default constructor
Pokemon::Pokemon() : _name("Unnamed Pokemon") {}

// Constructor with name
Pokemon::Pokemon(std::string_view name) : _name(name) {}

// Virtual destructor implementation
Pokemon::~Pokemon() {}

// Getter for name
std::string Pokemon::name() const {
    return _name;
}

// Stream insertion operator for Pokemon
std::ostream & operator<<( std::ostream & s, const Pokemon & pokemon ) {
    return s << "Pokemon Name: " << pokemon.name();
}
