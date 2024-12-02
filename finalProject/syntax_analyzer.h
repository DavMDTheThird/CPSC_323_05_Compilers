#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

  #include <iostream>    // For std::cout, std::endl
  #include <string>      // For std::string
  #include <vector>      // For std::vector

  #include "tokenizer.h"

class SyntaxAnalyzer
{
private:
  std::vector<Token>       tokens;
  int                      currentIndex = 0;
  std::vector<std::string> errors;

public:
  SyntaxAnalyzer( const std::vector<Token> & tokens_ ) : tokens( tokens_ ) {}

  void analyze()
  {
    if( !parseProg() )
    {
      errors.push_back( "Syntax error in program structure." );
    }
    displayErrors();
  }

private:
  Token currentToken()
  {
    if( currentIndex < tokens.size() )
    {
      return tokens[currentIndex];
    }
    return { UNKNOWN, "" };
  }

  void nextToken()
  {
    if( currentIndex < tokens.size() )
    {
      currentIndex++;
    }
  }

  bool parseProg()
  {
    if( currentToken().type != PROGRAM )
    {
      errors.push_back( "program is expected." );
      return false;
    }
    nextToken();

    if( currentToken().type != IDENTIFIER )
    {
      errors.push_back( "Identifier is expected after program." );
      return false;
    }
    nextToken();

    if( currentToken().value != ";" )
    {
      errors.push_back( "Semicolon is missing." );
      return false;
    }
    nextToken();

    if( !parseDecList() ) return false;

    if( currentToken().type != BEGIN )
    {
      errors.push_back( "begin is expected." );
      return false;
    }
    nextToken();

    if( !parseStatList() ) return false;

    if( currentToken().type != END )
    {
      errors.push_back( "end is expected." );
      return false;
    }
    nextToken();

    if( currentToken().value != "." )
    {
      errors.push_back( "Period is missing." );
      return false;
    }
    nextToken();

    return true;
  }

  bool parseDecList()
  {
    while( currentToken().type == IDENTIFIER )
    {
      if( !parseDec() ) return false;
    }
    return true;
  }

  bool parseDec()
  {
    if( currentToken().type != IDENTIFIER )
    {
      errors.push_back( "Identifier is expected in variable declaration." );
      return false;
    }
    nextToken();

    while( currentToken().value == "," )
    {
      nextToken();
      if( currentToken().type != IDENTIFIER )
      {
        errors.push_back( "Identifier is expected after comma." );
        return false;
      }
      nextToken();
    }

    if( currentToken().value != ":" )
    {
      errors.push_back( "Colon is missing in variable declaration." );
      return false;
    }
    nextToken();

    if( currentToken().type != INTEGER )
    {
      errors.push_back( "integer is expected as type." );
      return false;
    }
    nextToken();

    if( currentToken().value != ";" )
    {
      errors.push_back( "Semicolon is missing in variable declaration." );
      return false;
    }
    nextToken();

    return true;
  }

  bool parseStatList()
  {
    do {
      if( !parseStat() ) return false;
    } while( currentToken().type != END );
    return true;
  }

  bool parseStat()
  {
    if( currentToken().type == PRINT )
    {
      return parseWrite();
    }
    else if( currentToken().type == IDENTIFIER )
    {
      return parseAssign();
    }
    else
    {
      errors.push_back( "Invalid statement." );
      return false;
    }
  }

  bool parseWrite()
  {
    nextToken();
    if( currentToken().value != "(" )
    {
      errors.push_back( "Left parenthesis is missing in print statement." );
      return false;
    }
    nextToken();

    if( currentToken().type != IDENTIFIER )
    {
      errors.push_back( "Identifier is expected in print statement." );
      return false;
    }
    nextToken();

    if( currentToken().value != ")" )
    {
      errors.push_back( "Right parenthesis is missing in print statement." );
      return false;
    }
    nextToken();

    if( currentToken().value != ";" )
    {
      errors.push_back( "Semicolon is missing in print statement." );
      return false;
    }
    nextToken();

    return true;
  }

  bool parseAssign()
  {
    nextToken();
    if( currentToken().value != "=" )
    {
      errors.push_back( "Assignment operator '=' is missing." );
      return false;
    }
    nextToken();

    if( !parseExpr() )
    {
      errors.push_back( "Invalid expression in assignment." );
      return false;
    }

    if( currentToken().value != ";" )
    {
      errors.push_back( "Semicolon is missing in assignment." );
      return false;
    }
    nextToken();

    return true;
  }

  bool parseExpr()
  {
    return parseTerm();    // Simplified for this implementation
  }

  bool parseTerm()
  {
    return parseFactor();    // Simplified for this implementation
  }

  bool parseFactor()
  {
    if( currentToken().type == IDENTIFIER || currentToken().type == NUMBER )
    {
      nextToken();
      return true;
    }
    errors.push_back( "Invalid factor in expression." );
    return false;
  }

  void displayErrors()
  {
    if( errors.empty() )
    {
      std::cout << "No Error\nReady to compile\n";
    }
    else
    {
      std::cout << "This is the list of errors:\n";
      for( const std::string & error : errors )
      {
        std::cout << error << "\n";
      }
    }
  }
};

#endif
