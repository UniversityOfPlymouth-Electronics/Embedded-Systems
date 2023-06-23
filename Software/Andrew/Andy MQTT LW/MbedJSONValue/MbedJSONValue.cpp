#include "MbedJSONValue.h"

# include <stdlib.h>
# include <stdio.h>

// Clean up
void MbedJSONValue::clean() {
    switch (_type) {
        case TypeString:
            delete _value.asString;
            break;
        case TypeArray:
            for (int i = 0; i < index_array; i++)
                delete array[i];
            index_array = 0;
            break;
        case TypeObject:
            for (int i = 0; i < index_token; i++) {
                delete token[i];
                delete token_name[i];
            }
            index_token = 0;
            break;
        default:
            break;
    }
    _type = TypeNull;
    _type = TypeNull;
}

bool MbedJSONValue::hasMember(char * name)
{
    for(int i = 0; i < index_token; i++)
        if( !strcmp(name, (*(token_name[i])).c_str() ))
            return true;
    return false;
}


void copy(const std::string& s, std::back_insert_iterator<std::string> oi) {
    std::copy(s.begin(), s.end(), oi);
}

void serialize_str(const std::string& s, std::back_insert_iterator<std::string> oi) {
    *oi++ = '"';
    for (std::string::const_iterator i = s.begin(); i != s.end(); ++i) {
        switch (*i) {
#define MAP(val, sym) case val: copy(sym, oi); break
                MAP('"', "\\\"");
                MAP('\\', "\\\\");
                MAP('/', "\\/");
                MAP('\b', "\\b");
                MAP('\f', "\\f");
                MAP('\n', "\\n");
                MAP('\r', "\\r");
                MAP('\t', "\\t");
#undef MAP
            default:
                if ((unsigned char)*i < 0x20 || *i == 0x7f) {
                    char buf[7];
                    sprintf(buf, "\\u%04x", *i & 0xff);
                    copy(buf, buf + 6, oi);
                } else {
                    *oi++ = *i;
                }
                break;
        }
    }
    *oi++ = '"';
}

std::string MbedJSONValue::serialize(){
    std::string s;
    serialize(std::back_inserter(s));
    return s;
}

std::string MbedJSONValue::to_str(){
    switch (_type) {
        case TypeNull:
            return "null";
        case TypeBoolean:
            return _value.asBool ? "true" : "false";
        case TypeInt:    {
            char buf[10];
            sprintf(buf, "%d", _value.asInt);
            return buf;
        }
        case TypeDouble:    {
            char buf[10];
            sprintf(buf, "%f", _value.asDouble);
            return buf;
        }
        default:
            break;
    }
    return NULL;
}



void MbedJSONValue::serialize(std::back_insert_iterator<std::string> oi) {
    switch (_type) {
        case TypeString:
            serialize_str(*_value.asString, oi);
            break;
        case TypeArray: {
            *oi++ = '[';
            for (int i = 0; i < index_array; i++) {
                if (i)
                    *oi++ = ',';
                (*this)[i].serialize(oi);
            }
            *oi++ = ']';
            break;
        }
        case TypeObject: {
            *oi++ = '{';
            for (int i = 0; i < index_token; i++) {
                if (i)
                    *oi++ = ',';
                serialize_str(*(token_name[i]), oi);
                *oi++ = ':';
                (*(token[i])).serialize(oi);
            }
            *oi++ = '}';
            break;
        }
        default:
            copy(to_str(), oi);
            break;
    }
}



MbedJSONValue& MbedJSONValue::operator[](int i) {
    _type = TypeArray;
    if (i < NB_TOKEN && index_array == i ) {
#ifdef DEBUG
        printf("will add an element to the array\r\n");
#endif
        array[i] = new MbedJSONValue();
        index_array++;
        return *(array[i]);
    }
    if (i < NB_TOKEN && index_array > i)
        return *(array[i]);

    //if the user is not doing something wrong, this code is never executed!!
    return *(new MbedJSONValue());
}

MbedJSONValue& MbedJSONValue::operator[](std::string k) {
    _type = TypeObject;
    for (int i = 0; i < index_token; i++) {
#ifdef DEBUG
        printf("k: %s\r\n", k.c_str());
        printf("str: %s\r\n", token_name[i]->c_str());
#endif
        //existing token
        if (!strcmp(k.c_str(), token_name[i]->c_str())) {
#ifdef DEBUG
            printf("token found: %d\r\n", i);
#endif
            return *(token[i]);
        }
    }

    if(index_token >= NB_TOKEN)
        index_token = NB_TOKEN - 1;
    //non existing token
    token_name[index_token] = new std::string(k);
    token[index_token] = new MbedJSONValue();
    index_token++;
    return *(token[index_token - 1]);
}

MbedJSONValue& MbedJSONValue::operator[](std::string k) const
{
    for (int i = 0; i < index_token; i++) {
#ifdef DEBUG
        printf("k: %s\r\n", k.c_str());
        printf("str: %s\r\n", token_name[i]->c_str());
#endif
        if (!strcmp(k.c_str(), token_name[i]->c_str())) {
#ifdef DEBUG
            printf("token found: %d\r\n", i);
#endif
            return *(token[i]);
        }
    }
    
    //if the user is not doing something wrong, this code is never executed!!
    return *(new MbedJSONValue());
}


// Operators
MbedJSONValue& MbedJSONValue::operator=(MbedJSONValue const& rhs) {
    if (this != &rhs) {
        clean();
        _type = rhs._type;
        switch (_type) {
            case TypeBoolean:
                _value.asBool = rhs._value.asBool;
                break;
            case TypeInt:
                _value.asInt = rhs._value.asInt;
                break;
            case TypeDouble:
                _value.asDouble = rhs._value.asDouble;
                break;
            case TypeString:
                _value.asString = new std::string(*rhs._value.asString);
                break;
            case TypeArray:
                for (int i = 0; i < rhs.index_array; i++)
                    (*this)[i] = rhs[i];
            case TypeObject:
                for (int i = 0; i < rhs.index_token; i++)
                    (*this)[*(rhs.token_name[i])] = rhs[*(rhs.token_name[i])];
            default:
                break;
        }
    }
    return *this;
}


// Works for strings, arrays, and structs.
int MbedJSONValue::size() const {
    switch (_type) {
        case TypeString:
            return int(_value.asString->size());
        case TypeArray:
            return index_array;
        case TypeObject:
            return index_token;
        default:
            break;
    }
    return -1;
}

