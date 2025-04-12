#include "Parser.h"

Parser::Parser(Lexer lexer)
    :_lexer(lexer), _currentToken(_lexer.getNextToken()) {}

void Parser::shift(eTokenType type) {
    if (type == _currentToken.getType()) {
        _currentToken = _lexer.getNextToken();
    }
    else {
        std::cerr << "SyntaxError : unexpected token was shifted" << std::endl;
        exit(-1);
    }
}

std::unique_ptr<Node> Parser::parse() {
    return program();
}

std::unique_ptr<Node> Parser::program() {
    auto left = statement();
    if (_currentToken.getType() == eTokenType::END) {
        return left;
    }
    else {
        auto right = program();
        return std::make_unique<BinaryNode>(eTokenType::SEMICOLON, std::move(left), std::move(right));
    }
    return nullptr;
}

std::unique_ptr<Node> Parser::statement() {
    if (_currentToken.getType() == eTokenType::PRINT) {
        shift(eTokenType::PRINT);
        shift(eTokenType::LPAREN);
        auto expr = expression();
        shift(eTokenType::RPAREN);
        shift(eTokenType::SEMICOLON);
        return std::make_unique<UnaryNode>(eTokenType::PRINT, std::move(expr));
    }
    else if (_currentToken.getType() == eTokenType::VARDEF) {
        auto dec = declaration();
        shift(eTokenType::SEMICOLON);
        return dec;
    }
    else if (_currentToken.getType() == eTokenType::VARNAME) {
        auto var = std::make_unique<VariableNode>(_currentToken.getString());
        shift(eTokenType::VARNAME);
        shift(eTokenType::ASSIGN);
        auto expr = expression();
        shift(eTokenType::SEMICOLON);
        return std::make_unique<BinaryNode>(eTokenType::ASSIGN, std::move(var), std::move(expr));
    }
    else {
        std::cerr << "ParserError : wrong syntax" << std::endl;
        exit(-1);
    }
    return nullptr;
}

std::unique_ptr<Node> Parser::declaration() {
    shift(eTokenType::VARDEF);
    if (_currentToken.getType() != eTokenType::VARNAME) {
        std::cerr << "ParserErrro : not written variable_name" << std::endl;
        exit(-1);
    }
    std::string name = _currentToken.getString();
    shift(eTokenType::VARNAME);
    std::unique_ptr<Node> expr = std::make_unique<NumberNode>(0);
    std::unique_ptr<Node> var = std::make_unique<VariableNode>(name);
    if (_currentToken.getType() == eTokenType::ASSIGN) {
        shift(eTokenType::ASSIGN);
        expr = expression();
    }
    return std::make_unique<BinaryNode>(eTokenType::VARDEF, std::move(var), std::move(expr));
}

std::unique_ptr<Node> Parser::expression() {
    auto left = term();
    
    while (_currentToken.getType() == eTokenType::PLUS || _currentToken.getType() == eTokenType::MINUS) {
        eTokenType op = _currentToken.getType();
        shift(op);
        auto right = term();
        left = std::make_unique<BinaryNode>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Node> Parser::term() {
    auto left = factor();

    while (_currentToken.getType() == eTokenType::MULTIPLY || _currentToken.getType() == eTokenType::DIVISION) {
        eTokenType op = _currentToken.getType();
        shift(op);
        auto right = factor();
        left = std::make_unique<BinaryNode>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Node> Parser::factor() {
    switch (_currentToken.getType()) {
        case eTokenType::NUMBER: {
            float num = _currentToken.getNumber();
            shift(eTokenType::NUMBER);
            return std::make_unique<NumberNode>(num);
        }
        case eTokenType::LPAREN: {
            shift(eTokenType::LPAREN);
            auto expr = expression();
            shift(eTokenType::RPAREN);
            return expr;
        }
        case eTokenType::STRING: {
            std::string str = _currentToken.getString();
            shift(eTokenType::STRING);
            return std::make_unique<StringNode>(str);
        }
        case eTokenType::VARNAME: {
            std::string name = _currentToken.getString();
            shift(eTokenType::VARNAME);
            return std::make_unique<VariableNode>(name);
        }
        default:
            std::cerr << "ParserError : unknown token" << std::endl;
            exit(-1);
    }
    return nullptr;
}