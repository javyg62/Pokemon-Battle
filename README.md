#Pokemon Battle

This project implements a simplified Pokémon-style battle game in C++, demonstrating object-oriented programming principles such as inheritance, polymorphism, and operator overloading.

**Key Features:**

*   **Pokémon Hierarchy:**
    *   **`Pokemon` (Abstract Base Class):** Defines the common interface for all Pokémon, including a name and a virtual destructor.
    *   **`Pikachu` (Derived Class):** Inherits from `Pokemon` and adds specific attributes like gender, address, and a unique ID. It also implements specific attack methods (`thunderbolt`, `discharge`, `wildcharge`, `thunder`) and a `hop` method.
*   **Address Management:**
    *   **`Address` Class:** Manages street, city, state, and zip code information. It includes:
        *   **Constructors:** Default and parameterized constructors.
        *   **Queries (Getters):** Methods to retrieve individual address components.
        *   **Mutators (Setters):** Methods to update individual address components.
        *   **Stream Operators (`<<` and `>>`):** Overloaded operators for formatted output and input of `Address` objects, including robust input validation.
        *   **Relational Operators (`<`, `==`, `!=`, `<=`, `>`, `>=`):** Overloaded operators for comparing `Address` objects based on a defined sorting precedence (state, city, zipcode, street).
*   **Game Logic (`main.cpp`):**
    *   **Pokémon Selection:** Allows the user to choose from pre-defined `Pikachu` objects (`Pichu`, `Pikachu`, `Raichu`).
    *   **Polymorphism with `std::unique_ptr`:** Uses `std::unique_ptr<Pokemon>` to manage the selected Pokémon, enabling polymorphic behavior and preventing object slicing.
    *   **Battle Simulation:**
        *   A simplified turn-based battle system against a "WILD CHARIZARD."
        *   Players choose attacks, and health points are deducted.
        *   ASCII art is used to enhance the user experience during the introduction and battle outcomes.
*   **Operator Overloading:**
    *   **Stream Insertion (`<<`):** Overloaded for `Pokemon`, `Pikachu`, `Address`, and `Gender` enums to provide custom output formatting.
    *   **Stream Extraction (`>>`):** Overloaded for `Address` and `Gender` enums to handle formatted input.
    *   **Assignment Operator (`=`):** Custom assignment operator for `Pikachu` to handle base class assignment and specific member copying (excluding ID, which is intentionally unique for copies).
*   **Design Considerations:**
    *   **Header Guards:** Implied by the use of `.hpp` files, ensuring headers are included only once.
    *   **Standard Library Usage:** Utilizes various standard library components such as `iostream`, `string`, `string_view`, `iomanip`, `array`, `vector`, `memory`, `random`, and `algorithm`.
    *   **Constants:** Use of `const` for damage values and `MAX_HEALTH`.
    *   **`std::string_view`:** Employed for function parameters to efficiently handle string data without unnecessary copying.
