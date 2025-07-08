#include "Pikachu.hpp"
#include <random> // For potential random gender or other uses
#include <algorithm> // For std::tolower

std::size_t Pikachu::next_id = 1;

// Default constructor: Initialize all members
Pikachu::Pikachu()
  : Pokemon("Pichu"), // Call base class constructor with a default name
    _gender(Gender::Boy), // Default gender
    _address("Unknown Street", "Unknown City", "Unknown State", "00000"), // Default address
    _id(next_id++)
{}

// Constructor with name (for Pichu in main.cpp)
Pikachu::Pikachu(std::string_view name)
  : Pokemon(name), // Call base class constructor
    _gender(Gender::Boy), // Default gender
    _address("Unknown Street", "Unknown City", "Unknown State", "00000"), // Default address
    _id(next_id++)
{}

Pikachu::Pikachu(std::string_view name, const Address & address)
  : Pokemon(name), // Call base class constructor
    _address(address),
    _gender(Gender::Boy), // Default gender, could be randomized or passed as param
    _id(next_id++)
{}

Pikachu::Pikachu(const Pikachu & original)
  : Pokemon(original), // Call base class copy constructor
    _gender(original._gender),
    _address(original._address),
    _id(next_id++) // New ID for the copy
{
    // Note: ID is not copied, a new unique ID is assigned.
    // This is an intentional design choice for this specific class.
}

Pikachu & Pikachu::operator=(const Pikachu & rhs) {
  if (this != &rhs) {
    Pokemon::operator=(rhs); // Call base class assignment operator
    _gender = rhs._gender;
    // _name = rhs._name; // This line is redundant if Pokemon::operator= handles _name
    _address = rhs._address;
    // Note: ID not copied
  }
  return *this;
}

Pikachu::~Pikachu() = default; // Use default destructor

// Override name getter from Pokemon
std::string Pikachu::name() const { return _name; }
Gender Pikachu::gender() const { return _gender; }
Address Pikachu::address() const { return _address; }
std::size_t Pikachu::id() const { return _id; }

Pikachu & Pikachu::name(std::string_view newName) {
  _name = newName;
  return *this;
}

Pikachu & Pikachu::address(const Address & newAddress) {
  _address = newAddress;
  return *this;
}

// Attack methods (now override virtual functions)
int Pikachu::thunderbolt(int health) {
    const int DAMAGE = 90; // Use constant for damage
    std::cout << _name << " used THUNDERBOLT! It deals " << DAMAGE << " damage.\n";
    return health - DAMAGE;
}
int Pikachu::discharge(int health) {
    const int DAMAGE = 70;
    std::cout << _name << " used DISCHARGE! It deals " << DAMAGE << " damage.\n";
    return health - DAMAGE;
}
int Pikachu::wildcharge(int health) {
    const int DAMAGE = 80;
    std::cout << _name << " used WILDCHARGE! It deals " << DAMAGE << " damage.\n";
    return health - DAMAGE;
}
int Pikachu::thunder(int health) {
    const int DAMAGE = 110;
    std::cout << _name << " used THUNDER! It deals " << DAMAGE << " damage.\n";
    return health - DAMAGE;
}

// Hop method implementation
int Pikachu::hop() const {
    return 3; // Example hop value
}

std::ostream & operator<<( std::ostream & s, const Gender & gender ) {
  return s << (gender == Gender::Boy ? "Boy" : "Girl");
}

std::istream & operator>>( std::istream & s, Gender & gender ) {
  std::string token;
  s >> token;
  // Convert token to lowercase for case-insensitive comparison
  std::transform(token.begin(), token.end(), token.begin(),
                 [](unsigned char c){ return std::tolower(c); });

  if (token == "boy") gender = Gender::Boy;
  else if (token == "girl") gender = Gender::Girl;
  else s.setstate(std::ios::failbit); // Set failbit if input is not "boy" or "girl"
  return s;
}

// Stream insertion operator for Pikachu
std::ostream & operator<<( std::ostream & s, const Pikachu & pikachu ) {
    s << "Name: " << pikachu.name()
      << ", ID: " << pikachu.id()
      << ", Gender: " << pikachu.gender()
      << ", Address: " << pikachu.address(); // Address operator<< is already defined
    return s;
}
