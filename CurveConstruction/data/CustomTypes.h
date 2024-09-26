#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include <string>
#include <map>
#include<unordered_map>
#include <variant>
#include <stdexcept>

#include "Enums.h"

using namespace std;


// Define your custom types
using VariantType = std::variant<std::string, int, double>;
using UnorderedDictionary = std::unordered_map<std::string, VariantType>;
using Dictionary = std::map<std::string, VariantType>;
using DictionaryOfVectors = std::map<std::string, std::vector<VariantType>>;
using VectorOfDictionaries = std::vector<Dictionary>;


template<typename T>
T getValueFromVariant(const std::variant<std::string, int, double>& variantValue) {
    if constexpr (std::is_same_v<T, std::string>) {
        if (std::holds_alternative<std::string>(variantValue)) {
            return std::get<std::string>(variantValue);
        }
        throw std::bad_variant_access();
    }
    else if constexpr (std::is_same_v<T, double>) {
        if (std::holds_alternative<double>(variantValue)) {
            return std::get<double>(variantValue);
        }
        throw std::bad_variant_access();
    }
    else if constexpr (std::is_same_v<T, int>) {
        if (std::holds_alternative<int>(variantValue)) {
            return std::get<int>(variantValue);
        }
        throw std::bad_variant_access();
    }
    else {
        throw std::invalid_argument("Variant type to be cast cannot be recognised!");
    }
}

#endif // CUSTOM_TYPES_H