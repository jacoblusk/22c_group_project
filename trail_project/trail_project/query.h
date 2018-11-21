#ifndef QUERY_H
#define QUERY_H

namespace query {
  template <typename T>
  struct Splice {
    size_t length;
    T *data;
  };

  class Token {
    size_t m_index;
    Splice<char> m_splice;

  public:
    enum TokenType {
      Identifier,
      Keyword,
      Separator,
      Operator,
      Literal
    };

    virtual Token::TokenType get_token_type(void) = 0;
  };

  class IdenitiferToken : Token {
  public:
    Token::TokenType get_token_type(void) {
      return Token::Identifier;
    }
  };

  class SeparatorToken : Token {
  public:
    Token::TokenType get_token_type(void) {
      return Token::Separator;
    }
  };

  class OperatorToken : Token {
  public:
    Token::TokenType get_token_type(void) {
      return Token::Operator;
    }
  };

  class Operator {
  public:
    enum OperatorType {
      Binary,
      Unary
    };

    virtual Operator::OperatorType get_operator_type(void) = 0;
  };

  class BinaryOperator : Operator {
    enum BinaryOperatorType {
      Algebraic,
      Logical
    };
  };

  class UnaryOperator {

  };

  class LiteralToken : Token {
  public:
    Token::TokenType get_token_type(void) {
      return Token::Identifier;
    }
  };

  class Literal {
  public:
    enum LiteralType {
      String,
      Float,
      Integer
    };

    virtual Literal::LiteralType get_literal_type(void) = 0;
  };

  class Lexer {
  public:

  };
}

#endif