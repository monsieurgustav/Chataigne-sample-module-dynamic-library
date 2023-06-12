# Chataigne-sample-module-dynamic-library
A sample module for Chataigne that uses a dynamic library developed in C++.

Find a regular sample module for Chataigne here: https://github.com/tommag/Sample-Chataigne-module

DLSampleProject contains a JUCE project to build the dynamic library: a .DLL, .dylib or .so file depending on the platform.

DLSampleModule is a Chataigne module using Javascript code to load the dynamic library and call its exported functions.
