#include <iostream>
#include <string>            // string,  string::compare()
#include <string_view>
#include <iomanip>           // quoted()
#include <array>

#include "Address.hpp"       // Notice how the standard library header files are in angle brackets, but our header files are in
                             // double quotes.  That's intentional!  You need to do that too!






/***********************************************************************************************************************************
** Constructors, destructor and assignment operators
***********************************************************************************************************************************/
Address::Address( std::string_view street,         // Default and up to 4 argument constructor;
                  std::string_view city,
                  std::string_view state,
                  std::string_view zipCode )
  : _street ( street  ),                           // constructor member initialization
    _city   ( city    ),
    _state  ( state   ),
    _zipcode( zipCode )
{}                                                 // note the body of the constructor is empty


// After reviewing the class requirements along with allocated resources (none), the compiler synthesized default version of these
// functions are exactly what is needed
Address::Address            ( const Address & original ) = default;  // Copy constructor
Address & Address::operator=( const Address & rhs      ) = default;  // Copy assignment operator
Address::~Address()                                      = default;  // Destructor






/***********************************************************************************************************************************
** Queries
***********************************************************************************************************************************/
// Returns the current street
std::string Address::street() const
{ return _street; }


// Returns the current city
std::string Address::city() const
{ return _city; }


// Returns the current state
std::string Address::state() const
{ return _state; }


// Returns the current zipcode
std::string Address::zipCode() const
{ return _zipcode; }






/***********************************************************************************************************************************
** Mutators
***********************************************************************************************************************************/
// Updates the current street
Address & Address::street( std::string_view newStreet )
{
  _street = newStreet;
  return *this;
}


// Updates the current city
Address & Address::city( std::string_view newCity )
{
  _city = newCity;
  return *this;
}


// Updates the current state
Address & Address::state( std::string_view newState )
{
  _state = newState;
  return *this;
}


// Updates the current zipcode
Address & Address::zipCode( std::string_view newZipCode )
{
  _zipcode = newZipCode;
  return *this;
}






/***********************************************************************************************************************************
** Insertion (write) and extraction (read) symmetrical operators
**   Format:    {"street with numbers", "city", "state", "zipcode"}
***********************************************************************************************************************************/
std::ostream & operator<<( std::ostream & outputStream, const Address & address )
{
  outputStream << '{'
               << std::quoted( address._street  ) << ", "
               << std::quoted( address._city    ) << ", "
               << std::quoted( address._state   ) << ", "
               << std::quoted( address._zipcode ) << '}';
  return outputStream;
}


std::istream & operator>>( std::istream & inputStream, Address & address )
{
  // Best Practice:  Change the user's address object only after you are certain all data has been read in and validated.  In other
  //                 words, the user's data should not be changed if an error is encountered anywhere in the extraction process.
  Address workingTempAddress;
  std::array<char, 5> delimitors = {'\0'};

  // Assumes std::skipws
  inputStream >> delimitors[0]                                                 // expected {
              >> std::quoted( workingTempAddress._street  ) >> delimitors[1]   // expected "street with numbers",
              >> std::quoted( workingTempAddress._city    ) >> delimitors[2]   // expected "city",
              >> std::quoted( workingTempAddress._state   ) >> delimitors[3]   // expected "state",
              >> std::quoted( workingTempAddress._zipcode ) >> delimitors[4];  // expected "zipcode" }

  if(    inputStream            // tests the state of the input stream, false is returned if an error occurred
      && delimitors[0] == '{'
      && delimitors[1] == ','
      && delimitors[2] == ','
      && delimitors[3] == ','
      && delimitors[4] == '}')
  {
    // data has been read in successfully and content validated, so now we can change the user's parameter
    address = workingTempAddress;           // Note:  calls Address's copy assignment operator
  }
  else inputStream.setstate( std::ios_base::failbit );


  return inputStream;                       // The caller tests the stream's state to determine success, much like we did a few lines ago
}






/***********************************************************************************************************************************
** Relational Operators
***********************************************************************************************************************************/
// Must define at least one of these, so let's pick operator< (the typical choice) and define all the others in terms of operator<

bool operator<( const Address & lhs, const Address & rhs )
{
  // Desired precedence, sort by:
  //  o) state,   then
  //  o) city,    then
  //  o) zipcode, then
  //  o) street

  if( lhs._state   != rhs._state   ) return lhs._state   < rhs._state;    // if states   are different you have your answer, otherwise if they're the same then
  if( lhs._city    != rhs._city    ) return lhs._city    < rhs._city;     // if cities   are different you have your answer, otherwise if they're the same then
  if( lhs._zipcode != rhs._zipcode ) return lhs._zipcode < rhs._zipcode;  // if zipcodes are different you have your answer, otherwise if they're the same then
  else                               return lhs._street  < rhs._street;   // you have your answer
}


// delegate these to operator<
bool operator!=( const Address & lhs, const Address & rhs )   { return !( lhs == rhs ); }
bool operator<=( const Address & lhs, const Address & rhs )   { return !( rhs <  lhs ); }
bool operator> ( const Address & lhs, const Address & rhs )   { return  ( rhs <  lhs ); }
bool operator>=( const Address & lhs, const Address & rhs )   { return !( lhs <  rhs ); }
bool operator==( const Address & lhs, const Address & rhs )
{
  if constexpr( (true) )    // pick one of these implementations, but not both
  {
    // Has the advantage of always getting it right.  The logic within operator< can sometime be very complicated, and you don't
    // want to duplicate that here.  This also guarantees that the same logic is applied to all the relational operators.  The
    // downside is that two calls to operator< must be made essentially doubling the time it takes to compute the answer.
    // call can be expensive.
    return !( lhs < rhs ) && !( rhs < lhs );
  }
  else
  {
    // compute the answer directly.  In this case all 4 attributes must be equal for the Addresses to be equal.  Use short circuit
    // boolean algebra and avoid redundant checks.  For example, Avoid code that looks like this:
    //   if ( x == y)  return true; else return false;
    // Just return the results of the expression, like this:
    //   return x == y;
    //
    // Has the advantage of efficiency (avoids two calls to operator <), but has the disadvantage of potentially calculating a
    // different answer that operator< would have.  Extra care by the implementors and maintainers must be taken to ensure operator<
    // and operator== are in perfect harmony and don't diverge over time.
    //
    // Note the short-circuit boolean algebra.  False and anything is false, so as soon as we find attributes that don't match we
    // have our answer and stop looking.
    return lhs._state   == rhs._state
        && lhs._city    == rhs._city
        && lhs._zipcode == rhs._zipcode
        && lhs._street  == rhs._street;
  }
}
