#include <iostream>

int GetValue() {
        return 9;
}

// returns a reference to an int
int& GetOtherValue() {
        static int value = 10;
        return value;
}

void SetValue(int value) {}

void SetOtherValue(int& value) {}

void SetAnotherValue(const int& value) {}

void PrintName(std::string& name) {
        std::cout << name << std::endl;
}

void PrintOtherName(std::string&& name) {
        std::cout << name << std::endl;
}

// function (1)
// void test(const std::string& name) {} 
// function (2)
void test(std::string& name){}
// function (3)
void test(std::string&& name){}
// (3) will always be chosen when an rvalue is used with test()
// regardless of the existens of (1) or (2)
// basically, you are giving up this rvalue to the function, 
// or just creating and assigning an rvalue at the time you 
// call the function


int main() {
        // i is an lvalue; 10 is an r value
        int i = 10;
        // you can't assign something to an rvalue
        // 10 = 23234; 👿
        // this is because rvalues do not have a location until 
        // they are assigned to an lvalue
        
        // you are also allowed to assign lvalues to other lvalues
        int a = i;
        // lvalues can also be assigned to the result of a function
        // GetValue() is actually and rvalue
        int b = GetValue();
        // this is valid because it is really just returning a 
        // reference to an lvalue
        GetOtherValue() = 10;
        

        int j = 10;
        // you can pass lvalues into functions
        SetValue(j);
        // or rvalues!
        SetValue(10);

        // this function takes in only lvalues because it wants a 
        // reference to something passed into it
        SetOtherValue(j);
        // ❗️ You *cannot* take an lvalue reference from an rvalue ❗️
        // SetOtherValue(10); not valid
        
        // you also can't get an lvalue reference from an rvalue in general
        // int& c = 10; not valid
        // BUT, const got sum special up its sleeve 👀
        const int& d = 10; // it is really just syntactic sugar
                           // the compiler creates a temporary variable
                           // and then assigns its reference to d
        
        // the earlier concept can apply to functions as well
        // even though SetAnotherValue wants a reference to an int,
        // with "const", the compiler will create temporary variable for
        // us and pass in its reference!
        // notice how we can now pass in rvalue in function that wants a 
        // reference to an lvalue!
        SetAnotherValue(10);
        
        std::string firstName = "Xavier";
        std::string lastName = "Ruiz";
        // believe it or not "firstName+lastName" is actually an rvalue
        // the compiler will construct a temporary string there and put it 
        // in its place
        std::string fullName = firstName+lastName;
        
        // because fullName is an lvalue, this call will work fine
        PrintName(fullName);
        // this next call will not work because what you are trying to 
        // pass is an rvalue
        // PrintString(firstName + lastName);

        // so far we have seen functions that only accept lvalues,
        // functions that accept lvalues and rvalues, and functions
        // that accept rvalues
        // PrintOtherName() is a function that only accepts rvalues
        // this means the next call now works:
        PrintOtherName(firstName + lastName);
        // but this one does not:
        // PrintOtherName(fullName);
        // but we can at least work around that, too
        PrintOtherName(std::string *fullName);

        return 0;
}
