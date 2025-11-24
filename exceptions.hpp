#pragma once

#include <stdexcept>
#include <string>

class FJAException : public std::runtime_error {
  public:
    explicit FJAException(const std::string& message)
    : std::runtime_error(message) {}
};

class ValidationError : public FJAException {
  public:
    explicit ValidationError(const std::string& message)
    : FJAException("Validation error: " + message) {}
};

class ParseError : public FJAException {
  public:
    explicit ParseError(const std::string& message)
    : FJAException("Parse error: " + message) {}
};

class SortError : public FJAException {
  public:
    explicit SortError(const std::string& message)
    : FJAException("Sort error: " + message) {}
};
