#ifndef __CANBEENABLED__
#define __CANBEENABLED__
#include <iostream>

class CanBeEnabled {
    private:
        static uint32_t count;
    protected:
        bool _enabled = false;
    public:
        
        CanBeEnabled(bool en = true)
        {
            std::cout << "CanBeEnabled Constructor: call number->" << ++count << std::endl;
            _enabled = en;
        }

        bool isEnabled() {
            return _enabled;
        }
};

#endif