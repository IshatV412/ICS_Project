# Tic Tac Toe Bot with C--

- Course : Introduction to Computer Science
- Submitted by Parrva Shah (B24CS1053), Ishat Varshney (B24ME1034), Veer Shah (B24CM1054), Ishita Tyagi (B24CI1017)

## Introduction

### Objective
- Designing a custom language named C-- with pseudo-code syntax
- Implementing a tic tac toe game where users play against a bot

### Key Features
- C-- lexer, parser and interpreter
- A Tic Tac Toe bot using minimax
- Key features of language include pseudo-code like syntax (syntax is well explained in readme file), having datatypes of complex data structures like linkedlists and dictionaries, hassle-free memory management and easy to learn

## Implementation

### 2.1 C-- Lexer, Parser and Interpreter 
- Custom Datatypes : Creating custom datatypes like string , dictionary, linkedlist and even for the usual datatypes like integer, character as well
- Tokenization : Handled by lexer which breaks the entire code into tokens of keywords (like `create`) , datatypes (like `string`), operators (like `==`), identifiers, strings and numbers and returns them to the parser.
- Grammar Rules : Handled by the parser which gets the tokens from the lexer and defines the grammar rules for statements (like `var_dec`, `assign`,etc.) for our language. 
- AST : The Abstract Syntax Tree is created by the parser which is then sent to the interpreter for execution where each node represents a specific operation or statement in the program.


### 2.2 Tic Tac Toe Bot
- Minimax is a recursive decision-making algorithm used in two-player games like Tic-Tac-Toe. It simulates all possible moves, alternating between:

  1. Maximizing player (usually the AI), who tries to get the highest score.

  2. Minimizing player (usually the human), who tries to reduce the AI's score.

- The minimax function implemented in our code only searches one move ahead.
- It only maximizes the AI input and doesn'tfocus on minimizing user input



## Demonstration 



