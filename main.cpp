#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory> // Required for std::unique_ptr

#include "Address.hpp"
#include "Pikachu.hpp"
#include "Pokemon.hpp" // Ensure Pokemon.hpp is included

// Constants
const int MAX_HEALTH = 300;

// Function declarations
void displayIntro();
void displayAsciiArt(int choice);
void battle(Pokemon& currentPoke); // Still takes a reference to Pokemon

int main() {
    unsigned outputCounter = 0;

    // Pokemon is now an abstract class, so we must instantiate derived classes
    // pichu must now be a Pikachu object
    Pikachu pichu_poke("Pichu"); // Changed from Pokemon pichu;
    Pikachu pikachu("Pikachu");
    Pikachu raichu("Raichu", { "Stony Wilderness", "Galar Region" });



    Address home("Route 5", "Stony Wilderness", "Galar Region", "2834");
    raichu.address(home);

    pikachu.name("Ash's Pikachu").address({"My house", "Pallet Town"});


    displayIntro();

    int playGame;
    std::cin >> playGame;

    if (playGame != 1) return 0;

    std::cout << "\nLET'S GO!\n";

    // Health variables are local to main, not directly part of Pokemon objects in this setup
    // int yourHealth = MAX_HEALTH; // These are now managed within the battle function
    // int enemyHealth = MAX_HEALTH;

    std::cout << "Choose your Pokemon:\n";
    std::cout << "1. " << pichu_poke.name() << "\n"; // Use pichu_poke
    std::cout << "2. " << pikachu.name() << "\n";
    std::cout << "3. " << raichu.name() << "\n";

    int choice;
    std::cin >> choice;

    // FIX: Use std::unique_ptr to avoid object slicing and enable polymorphism
    std::unique_ptr<Pokemon> currentPoke;
    switch (choice) {
        case 1: currentPoke = std::make_unique<Pikachu>(pichu_poke);
        std::cout << pichu_poke   << '\n' << std::endl; // Use pichu_poke

        break; // Create a new Pikachu from pichu_poke

        case 2: currentPoke = std::make_unique<Pikachu>(pikachu);
        std::cout << pikachu << '\n' << std::endl;

        break;   // Create a new Pikachu from pikachu

        case 3: currentPoke = std::make_unique<Pikachu>(raichu);
        std::cout << raichu  << '\n' << std::endl;
        break;    // Create a new Pikachu from raichu
        default:
            std::cout << "Invalid choice. Exiting.\n";
            return 1;
    }

    // Check if a valid Pokemon was chosen
    if (!currentPoke) {
        std::cout << "Failed to select a Pokemon. Exiting.\n";
        return 1;
    }

    displayAsciiArt(choice);

    std::cout << "\nCurrent Pokemon is: " << currentPoke->name() << "\n\n"; // Use -> for unique_ptr

    battle(*currentPoke); // Pass the dereferenced unique_ptr to battle

    return 0;
}

// displayIntro and displayAsciiArt functions remain unchanged
void displayIntro() {
    std::cout << R"(
    _.----.        ____         ,'  _\   ___    ___     ____
 _,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
 \      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
  \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
    \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
     \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
      \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
       \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
        \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
         \_.-'       |__|    `-._ |              '-.|     '-.| |   |
                                 `'                            '-._|
                         PRESS START-1
    )" << std::endl;
}

void displayAsciiArt(int choice) {
    switch (choice) {
        case 1:
            std::cout << R"(
              /*’*-„
            /;;;;;;;'*„
           /;;;;;;;;;;;;*-„
         „';;;;;;;;;;;;;;;;*-„
         |;;;;;;;;;;;;;;;;;;;;;*„
        '|;;;;;;;;;;;;;;;;;;;;;;;;*-„
        |;;;;;;;;„*-„;\*-„;;;;;;;;;;*-„
      '|;;;;;;;;;|   *^'  *-„;;;;;;;;;;*-„
      |;;;;;;;;;|            *„;;;;;;;;;;*„
     '|;;;;;;;;;|               *„;;;;;;;;;*„
     |;;;;;;;;;'|                 *„;;;;;;;;;*„                                    __„„„„----^^^^******¯¯;;;;;;;;;;;;;:;;;„*
     |;;;;;;;;;|                     '„;;;;;;;;'„                           „„--^^*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:;;„'
     |;;;;;;;;;|                      '-„;;;„-'                           /;;;;;;;;;;;;;;;_„„„„„„-------„;;;;;;;;;;;;;:;;„*
     |;;;;;;;;;|                        '-„-'                           „*;;;;;;„„--^^**¯           „-^*„-^*„;;;;;;;;:;;„*
     *-„;;;;;'|                        „„-*„„„„„„„„„„„„„„„             /--;;;;^^*                  *''''¯.„-*;;;;;;;„-*
           *-„;'|                    -^*''''              ¯'''''*^-„.....„*                         .„-*;;;;;;;;;„-'
                *-„       „„                                                                      „-*;;;;;;;;;;;„-*
                    ¯-^''                                                                      .„*;;;;;;;;;;;„-*
                   „-*       „„„„„                                                           „-*;;;;;;;;:;;;„*
                „*    „- *;„*. *„;*„                       „-^***^-„                     .„-*;;;;;;;:;;„-*
              „*    „*;;;;;*---*;;;„*                    „*;*„..„*;;*-„          „„_„-*;;;;;;;;;:„-*
              |      *„;;;;;;;;;;;„*                     *„;;;''''';;;*„         *„...*^^---„„„-*
              \-^^^-„ *-„;;;;„-*             „„          '„;;;;;;;;;;;„'           „'
               '„;.;.;*„                  „„_____„„        *^-„„„„-^''     „-^**^-„„'
                '-„;.;.'„                '„;.;.;.;„'                      „-*;;;;„-*
                   *„-*                    |;.;.;.|                       „';;;;„-*
                       *-„.                 *-„„-*                        *-„_„-*
                            *^-„ .                                   .„--^*
                                „-*„';;'''*^^-„„___„„„„„„-----^^^\*\¯
                              „*   **-„;;;;;;;;;;;;;;;;;;;;;;;;„---\ .\
                             „'       \*;;„-*¯*-„„-*¯*-„;;;;/-^       \
                             /         \ *                *-„/           \-'¯'-„_
                            |            \                  /          „* |;;;;;;;¯*-„
                            |  *-„        \               /         „-*   |;;;;;;;;;;;*-„
                            \     *-„ . „*''              *-„    „-*      |;;;;;;;;;;;;;;;*-„
                              \                               ***        „-*\;;;;;;;;;;;;;;;„-*
                        .„--**   *                                  „-*-„    '*-„;;;;;;;;„--*
                   „-*„-*             *^^„*^---„„„„„---^*\*''            *-„      *-„„-^*
                 „*-*  „-^**     „„--^^*                    *^-„         ^-„*-„
                  *-„„„|„„„„„--^^*                              *-„    *-„   *-„
                                                                   **--„„„„„\-*
            )" << std::endl;
            break;
        case 2:
            std::cout << R"(
quu..__
 $$$b  `---.__
  "$""b        `--.                          ___.---uuudP
   `$$b           `.__.------.__     __.---'      $$$$"              .
     "$b          -'            `-.-'            $$$"              .'|
       ".                                       d$"             _.'  |
         `.   /                              ..."             .'     |
           `./                           ..::-'            _.'       |
            /                         .:::-'            .-'         .'
           :                          ::''\          _.'            |
          .' .-.             .-.           `.      .'               |
          : /'$$|           .@"$\           `.   .'              _.-'
         .'|$u$$|          |$$,$$|           |  <            _.-'
         | `:$$:'          :$$$$$:           `.  `.       .-'
         :                  `"--'             |    `-.     \
        :##.       ==             .###.       `.      `.    `\
        |##:                      :###:        |        >     >
        |#'     `..'`..'          `###'        x:      /     /
         \                                   xXX|     /    ./
          \                                xXXX'|    /   ./
          /`-.                                  `.  /   /
         :    `-  ...........,                   | /  .'
         |         ``:::::::'       .            |<    `.
         |             ```          |           x| \ `.:``.
         |                         .'    /'   xXX|  `:`M`M':.
         |    |                    ;    /:' xXXX'|  -'MMMMM:'
         `.  .'                   :    /:'       |-'MMMM.-'
          |  |                   .'   /'        .'MMM.-'
          `'`'                   :  ,'          |MMM<
            |                     `'            |tbap\
             \                                  :MM.-'
              \                 |              .''
               \.               `.            /
                /     .:::::::.. :           /
               |     .:::::::::::`.         /
               |   .:::------------\       /
              /   .''               >::'  /
              `',:                 :    .'
                                   `:.:'
            )" << std::endl;
            break;
        case 3:
            std::cout << R"(            _,--""`---...__
                            _.---""""`-'.   .-"""'`-.._`-._
                _,.-----.,-"         .". `-.           "---`.
             _,' _,.-..,'__          `.'  ,-`...._      ,""''`-.
           ,' ,-'     / (  .   ,-.       |    `.  `-._  .       `.
         ,',-"       /   `"    `"'       '      .    _`. \
       ,','       ,-'7--.                 `.__."|   ( ` `j
      '.:--.    ,'   |   .       |\             '    `--'
     /.     | ,'     |   |       `'            .
    '       |',".    |._,'                     `      _.--"""""-._
'.          `-..'    `.                      ,  \  ,-' _.-"""""-. `.
` `                   F  -.                 /    ,' .-'          `  `
 \ `                 j     `.              ,-.   . /               . `
    `.               |     .-`.           .  '-.  V                 . `
  `   `.      .      | .    \  \         j      \/|                  ' .
   .    `.    |`.    |-.`._/`   .        |    ,'  A                  | |
    \     `. F   \   |--`  "._  |        `-.-"   / .                 | |
     \      -'    `. |        `"'                  |                 F '
      \             `+`.                           |                / .
       \              .-`                     .    j               / ,
        \              \   `.               .'    /               ' .
         \       |`._   \    `-.._        ,'    ,'              ,'.'
          '      |   `.  `.       `<`""""'    .'             _,'.'
           `     |     `-. `._      )   `.     .          _.'_.'
            `    |        `--/     /`-._  .     `.___..--'_."
             `   |          /     /._   `""`.     `. _,.-"
              `  |         /     /   `--.....`.     `._
               ` |       ,'     /              .""""'  `.
                `'      , `-..,7                `    . `.`.
                       .       '                 `.   \  `v
                      j.  ,   /                    `.._L_.'
                      || .   /
                      `"-'__/


            )" << std::endl;
            break;
    }
}

void battle(Pokemon& currentPoke) {
    int yourHealth = MAX_HEALTH;
    int enemyHealth = MAX_HEALTH;
    int op, attackNum;

    std::cout << "A WILD CHARIZARD APPEARS! HEALTH = " << enemyHealth << " ";
    std::cout << R"(
                    ."-,.__
                    `.     `.  ,
                 .--'  .._,'"-' `.
                .    .'         `'
                `.   /          ,'
                  `  '--.   ,-"'
                   `"`   |  \
                      -. \, |
                       `--Y.'      ___.
                            \     L._, \
                  _.,        `.   <  <\                _
                ,' '           `, `.   | \            ( `
             ../, `.            `  |    .\`.           \ \_
            ,' ,..  .           _.,'    ||\l            )  '".
           , ,'   \           ,'.-.`-._,'  |           .  _._`.
         ,' /      \ \        `' ' `--/   | \          / /   ..\
       .'  /        \ .         |\__ - _ ,'` `        / /     `.`.
       |  '          ..         `-...-"  |  `-'      / /        . `.
       | /           |L__           |    |          / /          `. `.
      , /            .   .          |    |         / /             ` `
      / /          ,. ,`._ `-_       |    |  _   ,-' /               ` \
      / .           \"`_/. `-_ \_,.  ,'    +-' `-'  _,        ..,-.    \`.
      .  '         .-f    ,'   `    '.       \__.---'     _   .'   '     \ \
      ' /          `.'    l     .' /          \..      ,_|/   `.  ,'`     L`
      |'      _.-""` `.    \ _,'  `            \ `.___`.'"`-.  , |   |    | \
      ||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|
      ||  ,'          `. ;.,.---' ,'       `.   `.. `-'  .-' /_ .'    ;_   ||
      || '              V      / /           `   | `   ,'   ,' '.    !  `. ||
      ||/            _,-------7 '              . |  `-'    l         /    `||
      . |          ,' .-   ,' ||               | .-.        `.      .'     ||
      `'        ,'    `".'    |               |    `.        '. -.'       `'
             /      ,'      |               |,'    \-.._,.'/'
             .     /        .               .       \    .''
           .`.    |         `.             /         :_,'.'
             \ `...\   _     ,'-.        .'         /_.-'
              `-.__ `,  `'   .  _.>----''.  _  __  /
                   .'        /"'          |  "'   '_
                  /_|.-'\ ,".             '.'`__'-( \
                    / ,"'"\,'               `/  `-.|"


    )" << std::endl;
    std::cout << "Ready to fight?!" << std::endl;
    std::cout << "1-FIGHT!" << std::endl;
    std::cout << "2-RUN!" << std::endl;

    std::cin >> op;
    if (op != 1) return;

    while (enemyHealth > 0 && yourHealth > 0) {
        std::cout << "What attack do you want to use" << std::endl;
        std::cout << "1. THUNDERBOLT  2. DISCHARGE"<< std::endl;
        std::cout << "3. WILDCHARGE   4. THUNDER" << std::endl;
        std::cin >> attackNum;

        switch (attackNum) {
            case 1:
                std::cout << currentPoke.name() << " used THUNDERBOLT! ";
                enemyHealth = currentPoke.thunderbolt(enemyHealth);
                break;
            case 2:
                std::cout << currentPoke.name() << " used DISCHARGE! ";
                enemyHealth = currentPoke.discharge(enemyHealth);
                break;
            case 3:
                std::cout << currentPoke.name() << " used WILDCHARGE! ";
                enemyHealth = currentPoke.wildcharge(enemyHealth);
                break;
            case 4:
                std::cout << currentPoke.name() << " used THUNDER! ";
                enemyHealth = currentPoke.thunder(enemyHealth);
                break;
            default:
                std::cout << "Invalid attack." << std::endl;
                continue;
        }

        std::cout << "CHARIZARD used Flamethrower! It does 90 damage!" << std::endl;
        yourHealth -= 90;

        std::cout << "Your Health: " << yourHealth << " " << std::endl;
        std::cout << "Enemy Health: " << enemyHealth << " " << std::endl;
    }

    if (yourHealth <= 0) {
        std::cout << R"(
          _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______
         /  _____|    /   \     |   \/   | |   ____|    /  __  \  \   \  /   / |   ____||   _  \
        |  |  __     /  ^  \    |  \  /  | |  |__      |  |  |  |  \   \/   /  |  |__   |  |_)  |
        |  | |_ |   /  /_\  \   |  |\/|  | |   __|     |  |  |  |   \      /   |   __|  |      /
        |  |__| |  /  _____  \  |  |  |  | |  |____    |  `--'  |    \    /    |  |____ |  |\  \----.
         \______| /__/     \__\ |__|  |__| |_______|    \______/      \__/     |_______|| _| `._____|

        You fainted! Better luck next time!
        )" << std::endl;
    } else {
        std::cout << "CHARIZARD has fainted.\n";
        std::cout << R"(
          ____    ____  __    ______ .___________.  ______   .______     ____    ____
          \   \  /   / |  |  /      ||           | /  __  \  |   _  \    \   \  /   /
           \   \/   /  |  | |  ,----'`---|  |----`|  |  |  | |  |_)  |    \   \/   /
            \      /   |  | |  |         |  |     |  |  |  | |      /      \_    _/
             \    /    |  | |  `----.    |  |     |  `--'  | |  |\  \----.   |  |
              \__/     |__|  \______|    |__|      \______/  | _| `._____|   |__|

        )" << std::endl;
        std::cout << currentPoke.name() << " WINS!!!\n";
        std::cout << currentPoke.name() << " hops " << currentPoke.hop() << " space in joy!";
        std::cout << R"(
                                          _.|  '
                                        .'  | /
                                      ,'    |'
                                     /      /
                       _..----""---.'      /
 _.....---------...,-""                  ,'
 `-._  \                                /
     `-.+_            __           ,--. .
          `-.._     .:  ).        (`--"| \
               7    | `" |         `...'  \
               |     `--'     '+"        ,". ,""-
               |   _...        .____     | |/    '
          _.   |  .    `.  '--"   /      `./     j
         \' `-.|  '     |   `.   /        /     /
         '     `-. `---"      `-"        /     /
          \       `.                  _,'     /
           \        `                        .
            \                                j
             \                              /
              `.                           .
                +                          \
                |                           L
                |                           |
                |  _ /,                     |
                | | L)'..                   |
                | .    | `                  |
                '  \'   L                   '
                 \  \   |                  j
                  `. `__'                 /
                _,.--.---........__      /
               ---.,'---`         |   -j"
                .-'  '....__      L    |
              ""--..    _,-'       \ l||
                  ,-'  .....------. `||'
               _,'                /
             ,'                  /
            '---------+-        /
                     /         /
                   .'         /
                 .'          /
               ,'           /
             _'....----""""" )" << std::endl;
    }
}
