#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


// Define TokenType enum
enum TokenType {
  PROGRAM,
  VAR,
  BEGIN,
  END,
  INTEGER,
  PRINT,
  IDENTIFIER,
  NUMBER,
  OPERATOR,
  SYMBOL,
  UNKNOWN
};

// Define Token struct
struct Token
{
  TokenType   type;
  std::string value;
};

// Define Tokenizer class
class Tokenizer
{
private:
  std::vector<Token> tokens;
  std::string        fileName;

public:
  Tokenizer( std::string fileName_ ) : fileName( fileName_ ) {}

  std::vector<Token> tokenize()
  {
    std::ifstream fileIn( fileName );
    if( !fileIn )
    {
      std::cerr << "Unable to open file\n";
      return {};
    }

    std::string word;
    while( fileIn >> word )
    {
      tokens.push_back( classifyToken( word ) );
    }

    fileIn.close();
    return tokens;
  }

private:
  Token classifyToken( const std::string & word )
  {
    if( word == "program" ) return { PROGRAM, word };
    if( word == "var" ) return { VAR, word };
    if( word == "begin" ) return { BEGIN, word };
    if( word == "end" ) return { END, word };
    if( word == "integer" ) return { INTEGER, word };
    if( word == "print" ) return { PRINT, word };
    if( isIdentifier( word ) ) return { IDENTIFIER, word };
    if( isNumber( word ) ) return { NUMBER, word };
    if( isSymbol( word ) ) return { SYMBOL, word };
    if( isOperator( word ) ) return { OPERATOR, word };
    return { UNKNOWN, word };
  }

  bool isIdentifier( const std::string & word )
  {
    if( !std::isalpha( word[0] ) ) return false;
    for( char c : word )
    {
      if( !std::isalnum( c ) ) return false;
    }
    return true;
  }

  bool isNumber( const std::string & word )
  {
    for( char c : word )
    {
      if( !std::isdigit( c ) ) return false;
    }
    return true;
  }

  bool isSymbol( const std::string & word )
  {
    return ( word == ";" || word == "," || word == "." || word == "(" || word == ")" );
  }

  bool isOperator( const std::string & word )
  {
    return ( word == "+" || word == "-" || word == "*" || word == "/" );
  }
};

#endif    // TOKENIZER_H
