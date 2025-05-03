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

std::shared_ptr<Node> Parser::parse() {
    return program();
}

std::shared_ptr<Node> Parser::program() {
    auto left = statement();
    if (_currentToken.getType() == eTokenType::END) {
        return left;
    }
    else {
        auto right = program();
        return std::make_shared<BinaryNode>(eTokenType::SEMICOLON, left, right);
    }
    return nullptr;
}

std::shared_ptr<Node> Parser::statement() {
    if (_currentToken.getType() == eTokenType::PRINT) {
        shift(eTokenType::PRINT);
        shift(eTokenType::LPAREN);
        auto expr = expression();
        shift(eTokenType::RPAREN);
        shift(eTokenType::SEMICOLON);
        return std::make_shared<UnaryNode>(eTokenType::PRINT, expr);
    }
    else if (_currentToken.getType() == eTokenType::VARDEF) {
        auto dec = declaration();
        shift(eTokenType::SEMICOLON);
        return dec;
    }
    else if (_currentToken.getType() == eTokenType::FUNCDEF) {
        auto def = declaration();
        return def;
    }
    else if (_currentToken.getType() == eTokenType::SYMBOL) {
        auto sym = std::make_shared<SymbolNode>(_currentToken.getString());
        shift(eTokenType::SYMBOL);
        if (_currentToken.getType() == eTokenType::ASSIGN) {
            shift(eTokenType::ASSIGN);
            auto expr = expression();
            shift(eTokenType::SEMICOLON);
            return std::make_shared<BinaryNode>(eTokenType::ASSIGN, sym, expr);
        }
        else if (_currentToken.getType() == eTokenType::LPAREN) {
            auto call = call_func(sym);
            shift(eTokenType::SEMICOLON);
            return call;
        }
    }
    else if (_currentToken.getType() == eTokenType::LBRACE) {
        return compound();
    }
    else {
        std::cerr << "ParserError : wrong syntax" << std::endl;
        exit(-1);
    }
    return nullptr;
}

std::shared_ptr<Node> Parser::compound() {
    shift(eTokenType::LBRACE);

    std::shared_ptr<Node> left = statement();
    while (_currentToken.getType() != eTokenType::RBRACE) {
        auto right = statement();
        left = std::make_shared<BinaryNode>(eTokenType::SEMICOLON, left, right);
    }

    shift(eTokenType::RBRACE);
    return left;
}

std::shared_ptr<Node> Parser::declaration() {
    if (_currentToken.getType() == eTokenType::VARDEF) {
        shift(eTokenType::VARDEF);
        if (_currentToken.getType() != eTokenType::SYMBOL) {
            std::cerr << "ParserError : not written variable_name" << std::endl;
            exit(-1);
        }
        std::string name = _currentToken.getString();
        shift(eTokenType::SYMBOL);
        std::shared_ptr<Node> expr = std::make_shared<NumberNode>(0);
        std::shared_ptr<Node> var = std::make_shared<SymbolNode>(name);
        if (_currentToken.getType() == eTokenType::ASSIGN) {
            shift(eTokenType::ASSIGN);
            expr = expression();
        }
        return std::make_shared<BinaryNode>(eTokenType::VARDEF, var, expr);
    }
    else if (_currentToken.getType() == eTokenType::FUNCDEF) {
        shift(eTokenType::FUNCDEF);
        std::shared_ptr<Node> name = std::make_shared<SymbolNode>(_currentToken.getString());
        shift(eTokenType::SYMBOL);
        shift(eTokenType::LPAREN);
        std::shared_ptr<Node> arguments = nullptr;

        if (_currentToken.getType() == eTokenType::SYMBOL) {
            arguments = std::make_shared<SymbolNode>(_currentToken.getString());
            shift(eTokenType::SYMBOL);
                while (_currentToken.getType() == eTokenType::COMMA) { 
                    shift(eTokenType::COMMA);
                    auto arg = std::make_shared<SymbolNode>(_currentToken.getString());
                    arguments = std::make_shared<BinaryNode>(eTokenType::COMMA, arguments, arg);
                    shift(eTokenType::SYMBOL);
                }
        }
        shift(eTokenType::RPAREN);
        auto program = compound();
        return std::make_shared<TernaryNode>(eTokenType::FUNCDEF, name, arguments, program);
    }
    return nullptr;
}

std::shared_ptr<Node> Parser::call_func(std::shared_ptr<Node> symbol_name) {
    shift(eTokenType::LPAREN);

    std::shared_ptr<Node> arg = nullptr;

    if (_currentToken.getType() != eTokenType::RPAREN) {
        arg = expression();

        while (_currentToken.getType() == eTokenType::COMMA) {
            shift(eTokenType::COMMA);
            auto expr = expression();
            arg = std::make_shared<BinaryNode>(eTokenType::COMMA, arg, expr);
        }
    }
    shift(eTokenType::RPAREN);
    auto call = std::make_shared<BinaryNode>(eTokenType::FUNC, symbol_name, arg);
    return call;
}

std::shared_ptr<Node> Parser::expression() {
    auto left = term();
    
    while (_currentToken.getType() == eTokenType::PLUS || _currentToken.getType() == eTokenType::MINUS) {
        eTokenType op = _currentToken.getType();
        shift(op);
        auto right = term();
        left = std::make_shared<BinaryNode>(op, left, right);
    }

    return left;
}

std::shared_ptr<Node> Parser::term() {
    auto left = factor();

    while (_currentToken.getType() == eTokenType::MULTIPLY || _currentToken.getType() == eTokenType::DIVISION) {
        eTokenType op = _currentToken.getType();
        shift(op);
        auto right = factor();
        left = std::make_shared<BinaryNode>(op, left, right);
    }

    return left;
}

std::shared_ptr<Node> Parser::factor() {
    switch (_currentToken.getType()) {
        case eTokenType::NUMBER: {
            float num = _currentToken.getNumber();
            shift(eTokenType::NUMBER);
            return std::make_shared<NumberNode>(num);
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
            return std::make_shared<StringNode>(str);
        }
        case eTokenType::SYMBOL: {
            auto sym = std::make_shared<SymbolNode>(_currentToken.getString());
            shift(eTokenType::SYMBOL);
            if (_currentToken.getType() == eTokenType::LPAREN) {
                return call_func(sym);
            }
            else {
                return sym;
            }
        }
        default:
            std::cerr << "ParserError : unknown token" << std::endl;
            exit(-1);
    }
    return nullptr;
}