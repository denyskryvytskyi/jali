# JALI - Just Another Lox Implementation
[![build](https://github.com/denyskryvytskyi/jali/actions/workflows/cmake.yml/badge.svg?branch=master)](https://github.com/denyskryvytskyi/jali/actions/workflows/cmake.yml)

C++ implementation of the Lox programming language following Bob Nystrom's book [Crafting Interpreters](http://www.craftinginterpreters.com/).

<h2> Getting started </h2>

`git clone --recursive https://github.com/kryvytskyidenys/ElvenEngine`

Firstly you need to install [cmake](https://cmake.org/) 3.10+ version (3.21+ for VS 2022 support)

To generate Visual Studio solution you can run script `configure-win-vs2022`

Or just call command from the build directory with your version of VS and platform name (architecture) like this:

`cmake -G "Visual Studio Generator 17 2022" -A x64`

To build project run this command from the root:
`cmake --build build --config <Debug/Release>`

