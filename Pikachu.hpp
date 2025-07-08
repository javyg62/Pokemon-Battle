#ifndef PIKACHU_HPP
#define PIKACHU_HPP

#include "Pokemon.hpp" // Inherits from Pokemon
#include "Address.hpp" // Uses Address class
#include <string>
#include <string_view>
#include <cstddef> // For std::size_t

// Enum for Gender
enum class Gender { Boy, Girl };

// Stream operators for Gender enum
std::ostream & operator<<( std::ostream & s, const Gender & gender );
std::istream & operator>>( std::istream & s, Gender & gender );

class Pikachu : public Pokemon {
public:
    // Static member for unique ID generation
    static std::size_t next_id;

    // Constructors
    Pikachu();
    Pikachu(std::string_view name);
    Pikachu(std::string_view name, const Address & address);

    // Copy constructor (assigns new ID)
    Pikachu(const Pikachu & original);

    // Copy assignment operator
    Pikachu & operator=(const Pikachu & rhs);

    // Destructor
    ~Pikachu() override; // Mark as override

    // Queries (Getters)
    std::string name() const override; // Override base class name getter
    Gender gender() const;
    Address address() const;
    std::size_t id() const;

    // Mutators (Setters)
    Pikachu & name(std::string_view newName);
    Pikachu & address(const Address & newAddress);

    // Attack methods (override virtual functions from Pokemon)
    int thunderbolt(int health) override;
    int discharge(int health) override;
    int wildcharge(int health) override;
    int thunder(int health) override;

    // Hop method (override virtual function from Pokemon)
    int hop() const override;

private:
    Gender _gender;
    Address _address;
    std::size_t _id;
};

// Stream insertion operator for Pikachu
std::ostream & operator<<( std::ostream & s, const Pikachu & pikachu );

#endif // PIKACHU_HPP
