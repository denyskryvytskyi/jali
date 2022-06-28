#pragma once

static bool s_hadError = false;

static void report(int line, const std::string& where_, const std::string& message)
{
    std::cout << "[line " << line << "] Error" << where_ << ": " << message << std::endl;
    s_hadError = true;
}
static void error(int line, const std::string& message)
{
    report(line, "", message);
}
