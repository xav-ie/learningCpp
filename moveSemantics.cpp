#include <iostream>

class String {
        public:
                String() = default;
                String(const char* string) {
                        m_Size = std::strlen(string);
                        m_Data = new char[m_Size];
                        memcpy(m_Data, string, m_Size);
                        printf("Created!\n");
                }
                String(const String& other) {
                        m_Size = other.m_Size; 
                        m_Data = new char[m_Size];
                        memcpy(m_Data, other.m_Data, m_Size);
                        printf("Copied!\n");
                }
                ~String() {
                        delete m_Data;
                }
        private:
                char* m_Data;
                std::uint32_t m_Size;
};

class Entity {
        public:
                Entity(const String& name) {
                        : m_Name(name);
                }
                ~Entity() {
                }
        private:
                String m_Name;
        
};


int main() {
        Entity entity("Xavier");
        std::cin.get();
}
