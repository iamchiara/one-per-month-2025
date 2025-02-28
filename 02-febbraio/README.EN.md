# One per month 2025 - "Indovina numero"
>February project


*Read this in other languages: [Italiano](README.md)*

---

## The project
The creative idea of February is a game of numbers, in classical version (the user guesses what the program chooses) and reverse (the user chooses the number that the program guesses).

---

## Rules of the game
### Rules version 1 (the user guesses)
- ⚙ Set game parameters with range and number of retries available
- 🔢 Try to guess the random number that the program has chosen by being guided by the instructions of the program (too big/small)
- 🧠 It is advisable to proceed following a strategy, especially if the available attempts are few and the range is wide

### Rules version 2 (the program guesses)
- ⚙ Set game parameters with ranges and indicators
- 🔢 Choose a number (and don’t change it!)
- ✍ Respond to the program according to the proposal it makes, indicating the relation of magnitude between the proposed number and the chosen one

---

## Game parameters
### Version 1 (the user guesses)
The game parameters to set are:

- Range:
    1. 0-100 (simple)
    2. 0-1000 (medium)
    3. 0-1000000 (difficult)
    4. 0-1000000000 (very difficult)
    5. 0-18446744073709551615 (extra)
    >If the value entered is less than 1 it is assigned 1 and if it is greater than 5 it is assigned 5. After that it is reduced by 1 to be used as index

- Attempts available:
    1. Unlimited (simple)
    2. 100 (medium)
    3. 50 (difficult)
    4. 20 (very difficult)
    5. 5 (extra)
    >If the value entered is less than 1 it is assigned 1 and if it is greater than 5 it is assigned 5. After that it is reduced by 1 to be used as index

### Version 2 (the program guesses)
- Range:
    1. 0-100 (simple)
    2. 0-1000 (medium)
    3. 0-1000000 (difficult)
    4. 0-1000000000 (very difficult)
    5. 0-18446744073709551615 (extra)
    >If the value entered is less than 1 it is assigned 1 and if it is greater than 5 it is assigned 5. After that it is reduced by 1 to be used as index

- Indicators (WARNING! The first is used when the number proposed by the programme is GREATER than the number chosen, the second when it is less, and the third when the answer is correct):
    1. g - p - c
    2. > - < - =
    3. M - m - u
    >If the value entered is less than 1 it is assigned 1 and if it is greater than 3 it is assigned 3. After that it is reduced by 1 to be used as index

---

## Challenges
In the first version, where the program chooses a random number based on the set range, finding a function that was uniformly randomized even for a number the size of an unsigned long long was particularly difficult. With the bcrypt. h library, with the BCryptGenRandom function, it was the most suitable option among those I found.
In the second version, however, a problem evident from the outset was that of the maximum value of the range. In fact, always proposing (max+min)/2, if the number chosen is equal to max you never reach the number. The first solution I had adopted was to start from the attempt of the maximum value and then proceed with the following attempts, but it was redundant and useless. Instead, I expanded the range by one so that even the maximum was included.
In addition, through the library setjmp. h, once finished the game you return to main, to avoid sudden interruption of the program.

## Contributions and Feedback
This project is a personal journey, but any suggestions or feedback are welcome! If you have ideas or comments, open an issue or contact me directly.

---

## License
This project is released under the MIT license. See [LICENSE](LICENSE) for details.