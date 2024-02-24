# Craft Micro SDK - Contributing

We welcome improvements and fixes to the Craft Micro SDK! Please follow the [general guidelines on how to contribute to a project](https://github.com/firstcontributions/first-contributions), and take a look at our specific guidelines below.

## Guidelines

Your contribution will have a much higher chance of being accepted if you follow these guidelines :)

1. Please follow the same styles and conventions as existing code, and follow the coding style below
2. Ensure that your code is portable - your code should work on as many dev boards as possible, and not just on one family
3. Do not introduce any external libraries or other external dependencies
4. If you are adding a new feature, please check first whether it is suitable. If it's very specialist it may not be accepted
5. Add doxygen comment blocks to classes and methods in header files (see existing comment blocks for reference)

## Code style

1. Opening curly braces on the same line
    ````
    // Good
    while (true) {
        doSomething();
    }

    // Also good
    while (true) doSomething();

    // Bad
    while (true)
    {
        doSomething();
    }
    ````
2. Pointer and reference operators to the left
    ````
    // Good
    MyObject* obj;
    AnotherObject& obj2;

    // Also good
    void doSomething(MyVal& value) { ... }

    // Bad
    MyObject *obj;
    void doSomething(MyVal &value) { ... }
    ````
