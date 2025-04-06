#include "Parser.h"

Parser::Parser(Lexer lexer)
    :_lexer(lexer)
{
    _currentToken = _lexer.getNextToken();
    // 一単語目のデータを得ておく
}

void Parser::shift(eTokenType type) {
    if (type == _currentToken.type) {
        _currentToken = _lexer.getNextToken();
    }
    else {
        std::cerr << "ShiftError : unexpected token" << std::endl;
        exit(-1);
        // 単語の種類が想定していたもと異なるときにこのエラーが出る
    }
}

std::unique_ptr<Node> Parser::parse() {
    return program();
}

// * の部分は再帰関数で
std::unique_ptr<Node> Parser::program() {
    auto left = statement();
    if (_currentToken.type == eTokenType::END) {
        return left;
    }
    else {
        auto right = program();
        return std::make_unique<BinaryNode>(eTokenType::SEMICOLON, std::move(left), std::move(right));
    }
    return nullptr;
}

std::unique_ptr<Node> Parser::statement() {
    if (_currentToken.type == eTokenType::PRINT) {
        shift(eTokenType::PRINT);     // print
        shift(eTokenType::LPAREN);    // (
        auto expr = expression();     // 式
        shift(eTokenType::RPAREN);    // )
        shift(eTokenType::SEMICOLON); // ;
        return std::make_unique<UnaryNode>(eTokenType::PRINT, std::move(expr));
    }
    else {
        // 今回はPRINTのみだが、関数とかも実装すればここに来る。
        std::cerr << "ParserError : wrong syntax" << std::endl;
        exit(-1);
    }
    return nullptr;
}

// expression - term - factor の流れは再帰風でいける
std::unique_ptr<Node> Parser::expression() {
    auto left = term();
    
    while (_currentToken.type == eTokenType::PLUS || _currentToken.type == eTokenType::MINUS) {
        eTokenType op = _currentToken.type;
        shift(op);
        auto right = term();
        left = std::make_unique<BinaryNode>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Node> Parser::term() {
    auto left = factor();

    while (_currentToken.type == eTokenType::MULTIPLY|| _currentToken.type == eTokenType::DIVISION) {
        eTokenType op = _currentToken.type;
        shift(op);
        auto right = factor();
        left = std::make_unique<BinaryNode>(op, std::move(left), std::move(right));
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
        shift(eTokenType::LPAREN); // (
        auto expr = expression();  // 式
        shift(eTokenType::RPAREN); // )
        return expr;
    }
    else {
        std::cerr << "ParserError : unknown token" << std::endl;
        exit(-1);
    }
    return nullptr;
}

/*

program ::= ( statement )*

statement ::= PRINT "(" expression ")" ";"

expression ::= term ( ( "+" | "-" ) temr )*

term ::= factor ( ( "*" | "/" )  factor )*

factor ::= NUMBER
           | "(" expression ")"

*/