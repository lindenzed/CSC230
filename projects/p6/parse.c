#include "parse.h"
#include "stringval.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Prototype so we can use this function before defining it.
static Expr *parseExpr( char *tok, FILE *fp );


//////////////////////////////////////////////////////////////////////
// Input tokenization

// Current line we're parsing, starting from 1 like most editors.
static int lineCount = 1;

/** Print a syntax error message, with a line number and exit. */
static void syntaxError()
{
  fprintf( stderr, "line %d: syntax error\n", lineCount );
  exit( EXIT_FAILURE );
}

/** Helper function for parseToken.  It checks for overflow and stores
    the given character in the next element of token.
    @param ch The character to add. 
    @param token The token we're building.
    @param len Next position in token, passed by address. */
static void addToToken( char ch, char *token, int *len )
{
  // Complain if the token is too long.
  if ( *len >= MAX_TOKEN ) {
    fprintf( stderr, "line %d: token too long\n", lineCount );
    exit( EXIT_FAILURE );
  }

  // Add the given character.
  token[ *len ] = ch;
  *len += 1;
}

/** Documented in the header. */
bool parseToken( char *token, FILE *fp )
{
  int ch;

  // Skip whitespace and comments.
  while ( isspace( ch = fgetc( fp ) ) || ch == '#' ) {
    // If we hit the comment characer, skip the whole line.
    if ( ch == '#' )
      while ( ( ch = fgetc( fp ) ) != EOF && ch != '\n' )
        ;

    if ( ch == '\n' )
      lineCount++;
  }
    
  if ( ch == EOF )
    return false;

  // Record the character we've read and keep up with the token length.
  int len = 0;
  token[ len++ ] = ch;

  
  if ( isalpha( ch ) || ch == '_' ) {
    // Try to parse the token as an identifier.
    while ( isalnum( ( ch = fgetc( fp ) ) ) || ch == '_' )
      addToToken( ch, token, &len );

    // We had to read one character too far to find the end of the token.
    // put the extra character back.
    if ( ch != EOF )
      ungetc( ch, fp );
  } else if ( ch == '-' || isdigit( ch ) ) {
    // Try to parse the token as an integer value, it's a sequence of digits
    // after the initial sign or digit.
    while ( isdigit( ( ch = fgetc( fp ) ) ) )
      addToToken( ch, token, &len );
    
    // We had to read one character too far to find the end.
    // Put the extra character back.
    if ( ch != EOF )
      ungetc( ch, fp );
  } else if ( ch == '"' ) {
    // Try to parse the token as a dobule-quoted string.
    // Is the next character escaped.
    bool escape = false;

    // Keep reading until we hit the matching close quote.
    while ( ( ch = fgetc( fp ) ) != '"' || escape ) {
      // Error conditions
      if ( ch == EOF || ch == '\n' ) {
        fprintf( stderr, "line %d: invalid string literal.\n", lineCount );
        exit( EXIT_FAILURE );
      }
      
      // On a backslash, we just enable escape mode.
      if ( !escape && ch == '\\' ) {
        escape = true;
      } else {
        // Interpret escape sequences if we're in escape mode.
        if ( escape ) {
          switch ( ch ) {
          case 'n':
            ch = '\n';
            break;
          case 't':
            ch = '\t';
            break;
          case '"':
            ch = '"';
            break;
          case '\\':
            ch = '\\';
            break;
          default:
            fprintf( stderr, "line %d: Invalid escape sequence \"\\%c\"\n",
                     lineCount, ch );
            exit( EXIT_FAILURE );
          }
          escape = false;
        }

        addToToken( ch, token, &len );
      }
    }    
    // Store the closing quote.
    addToToken( '"', token, &len );
  }  else {
    // Is this a multi-character token?
    int ch2 = fgetc( fp );
    if ( ( ch == '=' && ch2 == '=' ) ||
         ( ch == '&' && ch2 == '&' ) ||
         ( ch == '|' && ch2 == '|' ) ) {
      token[ len++ ] = ch2;
    } else {
      // Put back the second token and just take a one-character token.
      if ( ch2 != EOF )
        ungetc( ch2, fp );
    }
  }
    
  token[ len++ ] = '\0';
  return token;
}

/** Called when we expect another token on the input.  This function
    parses the token and exits with an error if there isn't one.
    @param storage for the next token, with capacity for at least
    MAX_TOKEN characters.  This buffer will be modified by the parse
    function as it reads additional tokens.
    @param fp file tokens should be read from.
    @return a copy of the pointer to the tok buffer, so this function
    can be used as a parameter to other parsing calls.
*/
static char *expectToken( char *tok, FILE *fp )
{
  if ( !parseToken( tok, fp ) )
    syntaxError();
  return tok;
}

/** Called when the next token, must be a particular value,
    target.  Prints an error message and exits if it's not.
    @param target string that the next token should match.
    @param fp file tokens should be read from.
*/
static void requireToken( char const *target, FILE *fp )
{
  char tok[ MAX_TOKEN + 1 ];
  if ( strcmp( expectToken( tok, fp ), target ) != 0 )
    syntaxError();
}

/** Return true if the given string is a legal identifier name.
    @param tok token parsed from the input.
    @return true if the given token is a legal identifier name.
*/
static bool isIdentifier( char const *tok )
{
  // Make sure the first character is legal.
  if ( !isalpha( tok[ 0 ] ) && tok[ 0 ] != '_' )
    return false;

  // Then, check the rest.
  for ( int i = 1; tok[ i ]; i++ )
    if ( !isalnum( tok[ i ] ) && tok[ i ] != '_' )
      return false;

  // Make sure it's not too long
  if ( strlen( tok ) > MAX_VAR_NAME )
    return false;

  // And, make sure it doesn't match a reserved word.
  if ( strcmp( tok, "if" ) == 0 ||
       strcmp( tok, "while" ) == 0 ||
       strcmp( tok, "print" ) == 0 ||
       strcmp( tok, "cat" ) == 0 ||
       strcmp( tok, "strlen" ) == 0 ||
       strcmp( tok, "substr" ) == 0 )
    return false;

  return true;
}



/** Return true if the given string is an infix operator in our language.
    @param tok token parsed from the input.
    @return true if the given token matches one of the infix operator.
*/
static bool isInfixOperator( char const *tok )
{
  return strcmp( tok, "+" ) == 0 ||
    strcmp( tok, "-" ) == 0 ||
    strcmp( tok, "*" ) == 0 ||
    strcmp( tok, "/" ) == 0 ||
    strcmp( tok, "<" ) == 0 ||
    strcmp( tok, "==" ) == 0 ||
    strcmp( tok, "&&" ) == 0 ||
    strcmp( tok, "||" ) == 0;
}

/** Parse a building block for a larger expression, either a literal, a
    variable, or an expression inside parentheses.
    @param tok next token from the input.
    @param fp file subsequent tokens are being read from.
    @return the expression object constructed from the input.
*/
static Expr *parseTerm( char *tok, FILE *fp )
{
  if ( strcmp( tok, "(" ) == 0 ) {
    Expr *expr = parseExpr( expectToken( tok, fp ), fp );
    requireToken( ")", fp );
    return expr;
  }


  // Create a literal token for a quoted string, without the quotes.
  if (tok[ 0 ] == '\"' ) {
    char tokNoQuotes[ MAX_TOKEN - DOUBLE_CAPACITY ];//minus two becuase of quotes that arent being counted
    int i = 1;
    while ( tok [ i ] != '\"' ) {
      tokNoQuotes[ i - 1 ] = tok [ i ];
      if (tok[ i + 1 ] == '\"' && strlen( tok ) - DOUBLE_CAPACITY > i ) {
        tokNoQuotes[ i ] = '\"';
        i++;
      }
      i++;
    }
    tokNoQuotes[ i - 1 ] = '\0';

    if ( strlen ( tok ) - DOUBLE_CAPACITY != strlen( tokNoQuotes ) ) {
      //syntaxError();
    }
    return makeLiteral( makeString( tokNoQuotes ) ); 
  }
  else if ( tok[ 0 ] == '-' || isdigit( tok[ 0 ] ) ) {
    // Conver the integer to an int and wrap it in a literal token.
    int val, n;
    if ( sscanf( tok, "%d%n", &val, &n ) != 1 ||
         n != strlen( tok ) )
      syntaxError();
    return makeLiteral( makeInteger( val ) );
  } else if ( isIdentifier( tok ) ) {
    return makeVariable( tok );
  } else
    syntaxError();

  // Not reached.
  return NULL;
}

/** Parse with one token worth of look-ahead, return the Expr
    object representing the next legal expression from the input.
    @param tok next token from the input, already read before
    calling this function.
    @param fp file subsequent tokens are being read from.
    @return the Expr object constructed from the input.
*/
static Expr *parseExpr( char *tok, FILE *fp )
{
  // Parse the expression, or just the left-hand operatnd of a longer
  // expression.
  Expr *left = parseTerm( tok, fp );
  
  // See if there's another oprator after this one.
  char op[ MAX_TOKEN + 1 ];
  while ( isInfixOperator( expectToken( op, fp ) ) ) {
    // Parse the right-hand operand.
    Expr *right = parseTerm( expectToken( tok, fp ), fp );

    // Create the right type of expression, based on what binary
    // operator it is.
    if ( strcmp( op, "+" ) == 0 ) {
      left = makeAdd( left, right );
    } else if ( strcmp( op, "-" ) == 0 ) {
      left = makeSub( left, right );
    } else if ( strcmp( op, "*" ) == 0 ) {
      left = makeMul( left, right );
    } else if ( strcmp( op, "/" ) == 0 ) {
      left = makeDiv( left, right );
    } else if ( strcmp( op, "<" ) == 0 ) {
      left = makeLess( left, right );
    } else if ( strcmp( op, "==" ) == 0 ) {
      left = makeEquals( left, right );
    } else if ( strcmp( op, "&&" ) == 0 ) {
        left = makeAnd( left, right );
    } else if (strcmp( op, "||" ) == 0 ) {
        left = makeOr( left, right );
    }

  }




  // To end an expression, the next token must be ;, ) or a comma.
  if ( strcmp( op, ";" ) != 0 && strcmp( op, ")" ) != 0 &&
       strcmp( op, "," ) != 0 )
    syntaxError();

  // Code that called us is going to expect to see this token.
  ungetc( op[ 0 ], fp );
  return left;
}

Stmt *parseStmt( char *tok, FILE *fp )
{
  // Handle compound statements
  if ( strcmp( tok, "{" ) == 0 ) {
    int len = 0;
    int cap = INITIAL_CAPACITY;
    Stmt **stmtList = (Stmt **) malloc( cap * sizeof( Stmt * ) );

    // Keep parsing statements until we hit the closing curly bracket.
    while ( strcmp( expectToken( tok, fp ), "}" ) != 0 ) {
      if ( len >= cap ) {
        cap *= DOUBLE_CAPACITY;
        stmtList = (Stmt **) realloc( stmtList, cap * sizeof( Stmt * ) );
      }
      stmtList[ len++ ] = parseStmt( tok, fp );
    }

    return makeCompound( len, stmtList );
  }
  if (strcmp( tok, "strlen" ) == 0 ) {
    Expr *arg = parseExpr( expectToken( tok, fp ), fp );
    requireToken( ")", fp );
    return makeStrlen( arg );
  }

  // Parse a print statement.
  else if ( strcmp( tok, "print" ) == 0 ) {
    // Parse the one argument to print, and create a print expression.
    Expr *arg = parseExpr( expectToken( tok, fp ), fp );
    requireToken( ";", fp );
    return makePrint( arg );
  } else if ( strcmp( tok, "if" ) == 0 ) {
    requireToken( "(", fp );
    Expr *cond = parseExpr( expectToken( tok, fp ), fp );
    requireToken( ")", fp );
    Stmt *body = parseStmt( expectToken( tok, fp ), fp );
    return makeIf( cond, body );
  } else if ( strcmp( tok, "while" ) == 0 ) {
    requireToken( "(", fp );
    Expr *cond = parseExpr( expectToken( tok, fp ), fp );
    requireToken( ")", fp );
    Stmt *body = parseStmt( expectToken( tok, fp ), fp );
    return makeWhile( cond, body );
  } else if ( isIdentifier( tok ) ) {
    // This must be an assignment.  Copy the variable name then parse
    // the expression being assigned to it.
    char vname[ MAX_VAR_NAME + 1 ];
    strcpy( vname, tok );
    requireToken( "=", fp );
    Expr *expr = parseExpr( expectToken( tok, fp ), fp );
    requireToken( ";", fp );
    // Make the assignment statement.
    return makeAssignment( vname, expr );
  } else
    syntaxError();

  // Never reached.
  return NULL;
}
