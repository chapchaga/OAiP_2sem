#pragma once

#include <stdexcept>

class FigureException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class ValidationError : public FigureException
{
public:
    using FigureException::FigureException;
};

