#ifndef _LAVY_VALUE_TYPE_
#define _LAVY_VALUE_TYPE_

template<typename T>
class LazyValueType
{
private:
    T _value;
    bool _isDefined = false;
public:

    operator bool() {
        return _isDefined;
    }

    T value() {
        return _value;
    }

    void operator = (T newVal)
    {
        _value = newVal;
        _isDefined = true;
    }
};

#endif