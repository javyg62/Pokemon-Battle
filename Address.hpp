#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <iostream>       // istream, ostream
#include <string>         // string
#include <string_view>    // string_view

#include "Address.hpp"


class Address
{
  // Befriending non-member functions gives those non-member functions access private class members
  // Insertion (write) and extraction (read) operators
  friend std::ostream & operator<<( std::ostream & outputStream, const Address & address );
  friend std::istream & operator>>( std::istream & inputStream,        Address & address );

  // Relational operators need access to private members
  friend bool operator==( const Address & lhs, const Address & rhs );
  friend bool operator< ( const Address & lhs, const Address & rhs );

  // Public interface definition
  public:
    // Constructors, destructor and copy assignment operator
    Address            ( const Address & original );       // Copy constructor
    Address & operator=( const Address & rhs );            // Copy assignment operator
    Address( std::string_view street  = {},                // Default and up to 4 argument constructor
             std::string_view city    = {},                //   the empty braces is a default constructed object
             std::string_view state   = {},                //   which in this case is the empty string
             std::string_view zipCode = {} );
   ~Address();                                             // Destructor

    // Queries
    std::string street () const;                           // Returns the current street
    std::string city   () const;                           // Returns the current city
    std::string state  () const;                           // Returns the current state
    std::string zipCode() const;                           // Returns the current zipcode


    // Mutators
    Address & street ( std::string_view newStreet );       // Updates the current street
    Address & city   ( std::string_view newCity   );       // Updates the current city
    Address & state  ( std::string_view newState  );       // Updates the current state
    Address & zipCode( std::string_view newZipCode);       // Updates the current zipcode

  // Private, implementation details not exposed to class clients
  private:
    std::string _street;
    std::string _city;
    std::string _state;
    std::string _zipcode;
};

// Address's Relational operators as non-member functions.  These are still part of the public interface
bool operator==( const Address & lhs, const Address & rhs );
bool operator!=( const Address & lhs, const Address & rhs );
bool operator< ( const Address & lhs, const Address & rhs );
bool operator<=( const Address & lhs, const Address & rhs );
bool operator> ( const Address & lhs, const Address & rhs );
bool operator>=( const Address & lhs, const Address & rhs );

#endif 
