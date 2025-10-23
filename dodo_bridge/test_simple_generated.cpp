#include <string>
#include <vector>
#include <map>
#include <array>
#include <memory>
#include <iostream>

// Mock miniros types for compilation test
namespace miniros {
    struct Time { int sec, nsec; };
    struct Duration { int sec, nsec; };
    namespace message_traits {}
    namespace serialization {}
    namespace message_operations {
        template<typename T>
        struct Printer {
            template<typename Stream> 
            static void stream(Stream& s, const std::string& indent, const T& v) {}
        };
    }
}

// Mock allocator allocator traits for compilation
template<typename T>
struct std::allocator_traits {
    template<typename U>
    using rebind_alloc = std::allocator<U>;
};

#define MINIROS_DECLARE_ALLINONE_SERIALIZER

#include "generated_include/db_parsing/DodobotNotify.hxx"

int main() {
    db_parsing::DodobotNotify notify_msg;
    notify_msg.message = "Test message";
    notify_msg.level = db_parsing::DodobotNotify::WARN;
    notify_msg.timeout = 5000;
    
    std::cout << "DodobotNotify message: " << notify_msg.message << std::endl;
    std::cout << "Level: " << notify_msg.level << " (WARN=" << db_parsing::DodobotNotify::WARN << ")" << std::endl;
    std::cout << "Timeout: " << notify_msg.timeout << " ms" << std::endl;
    
    return 0;
}