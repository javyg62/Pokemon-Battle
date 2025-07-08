#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>
#include <string_view>
#include <iostream> // For operator<<

class Pokemon {
public:
    // Constructors
    Pokemon();
    Pokemon(std::string_view name);

    // Virtual destructor for proper polymorphic cleanup
    virtual ~Pokemon();

    // Getter for name
    virtual std::string name() const;

    // Virtual attack methods (pure virtual to make Pokemon an abstract base class)
    virtual int thunderbolt(int health) = 0;
    virtual int discharge(int health) = 0;
    virtual int wildcharge(int health) = 0;
    virtual int thunder(int health) = 0;

    // Virtual hop method
    virtual int hop() const = 0;

protected:
    std::string _name; // Protected to allow derived classes direct access if needed, or keep private and use setters
};

// Stream insertion operator for Pokemon (non-member function)
std::ostream & operator<<( std::ostream & s, const Pokemon & pokemon );

#endif // POKEMON_HPP
