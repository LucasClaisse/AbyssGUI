#pragma once

#include <Windows.h>
#include <cstdio>
#include <stdexcept>
#include <string>

class WindowsConsole final {
private:
    FILE *m_stdin{nullptr};
    FILE *m_stdout{nullptr};
    FILE *m_stderr{nullptr};

public:
    WindowsConsole();
    ~WindowsConsole();
};

WindowsConsole::WindowsConsole()
{
    if (!::AllocConsole())
        throw std::runtime_error{"Couldn't allocate console"};

    /*if (!::AttachConsole(GetCurrentProcessId()))
        throw std::runtime_error{std::string{"Couldn't attach console to current process ("} + std::to_string(GetLastError()) + ")"};*/

    // Todo: check freopen results
    ::freopen_s(&m_stdin, "CON", "r", stdin);
    ::freopen_s(&m_stdout, "CON", "w", stdout);
    ::freopen_s(&m_stderr, "CON", "w", stderr);
}

WindowsConsole::~WindowsConsole()
{
	::FreeConsole();

    ::fclose(m_stdin);
    ::fclose(m_stdout);
    ::fclose(m_stderr);
}
