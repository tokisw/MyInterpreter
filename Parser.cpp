#include "Parser.h"

Parser::Parser(Lexer lexer)
    :_lexer(lexer)
{
    _currentToken = _lexer.getNextToken();
}

void Parser::shift(eTokenType type) {
    if (type == _currentToken.type) {
        _currentToken = _lexer.getNextToken();
    }
    else {
        std::cerr << "SyntaxError : unexpected token" << std::endl;
    }
}

std::unique_ptr<Node> Parser::program() {
    auto left = statement();
    if (_currentToken.type == eTokenType::END) {
        return left;
    }
    else {
        auto right = program();
        return std::make_unique<BinaryNode>(eTokenType::SEMICOLON, left, right);
    }
    return nullptr;
}

std::unique_ptr<Node> Parser::statement() {
    if (_currentToken.type == eTokenType::PRINT) {
        shift(eTokenType::PRINT);
        shift(eTokenType::LPAREN);
        auto expr = expression();
        shift(eTokenType::RPAREN);
        shift(eTokenType::SEMICOLON);
        return std::make_unique<UnaryNode>(eTokenType::PRINT, expr);
    }
    else {
        std::cerr << "SyntaxError : wrong syntax" << std::endl;
    }
    return nullptr;
}

std::unique_ptr<Node> Parser::expression() {
    auto left = term();
    
    while (_currentToken.type == eTokenType::PLUS || _currentToken.type == eTokenType::MINUS) {
        eTokenType op = _currentToken.type;
        shift(op);
        auto right = term();
        left = std::make_unique<BinaryNode>(op, left, right);
    }

    return left;
}

std::unique_ptr<Node> Parser::term() {
    auto left = factor();

    while (_currentToken.type == eTokenType::MULTIPLY|| _currentToken.type == eTokenType::DIVISION) {
        eTokenType op = _currentToken.type;
        shift(op);
        auto right = factor();
        left = std::make_unique<BinaryNode>(op, left, right);
    }

    return left;
}

std::unique_ptr<Node> Parser::factor() {
    if (_currentToken.type == eTokenType::NUMBER) {
        float num = _currentToken.value;
        shift(eTokenType::NUMBER);
        return std::make_unique<NumberNode>(num);
    }
    else if (_currentToken.type == eTokenType::LPAREN) {
        shift(eTokenType::LPAREN);
        auto expr = expression();
        shift(eTokenType::RPAREN);
        return expr;
    }
    else {
        std::cerr << "TokenError : unknown token" << std::endl;
    }
}


/*

program ::= ( statement )*

statement ::= PRINT "(" expression ")" ";"

expression ::= term ( ( "+" | "-" ) temr )*

term ::= factor ( ( "*" | "/" )  factor )*

factor ::= NUMBER
           | "(" expression ")"

*/