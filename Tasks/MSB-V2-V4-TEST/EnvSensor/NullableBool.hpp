#ifndef _NULLABLE_BOOL_H_
#define _NULLABLE_BOOL_H_

class NullableBool
{
    bool _val;
    bool _isDefined = false;
    public:
    typedef enum {U, FALSE, TRUE} BoolValue_t;
    
    operator double() {
        return 1.0;
    }

    operator BoolValue_t()
    {
        if (_isDefined) {
            return _val ? TRUE : FALSE;
        } else {
            return U;
        }
    }

    operator bool() {
        return _val;
    }

    void operator = (bool newValue) {
        _val = newValue;
        _isDefined = true;
    }
};

#endif