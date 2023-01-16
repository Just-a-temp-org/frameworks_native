/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace android {

template <typename T>
inline std::string constToString(const T& v) {
    return std::to_string(v);
}

template <>
inline std::string constToString(const bool& value) {
    return value ? "true" : "false";
}

template <>
inline std::string constToString(const std::vector<bool>::reference& value) {
    return value ? "true" : "false";
}

inline std::string constToString(const std::string& s) {
    return s;
}

/**
 * Convert an optional type to string.
 */
template <typename T>
inline std::string toString(const std::optional<T>& optional,
                            std::string (*toString)(const T&) = constToString) {
    return optional ? toString(*optional) : "<not set>";
}

/**
 * Convert a set of integral types to string.
 */
template <typename T>
std::string dumpSet(const std::set<T>& v, std::string (*toString)(const T&) = constToString) {
    std::string out;
    for (const T& entry : v) {
        out += out.empty() ? "{" : ", ";
        out += toString(entry);
    }
    return out.empty() ? "{}" : (out + "}");
}

/**
 * Convert a map to string. Both keys and values of the map should be integral type.
 */
template <typename K, typename V>
std::string dumpMap(const std::map<K, V>& map, std::string (*keyToString)(const K&) = constToString,
                    std::string (*valueToString)(const V&) = constToString) {
    std::string out;
    for (const auto& [k, v] : map) {
        if (!out.empty()) {
            out += "\n";
        }
        out += keyToString(k) + ":" + valueToString(v);
    }
    return out;
}

/**
 * Convert a vector to a string. The values of the vector should be of a type supported by
 * constToString.
 */
template <typename T>
std::string dumpVector(std::vector<T> values) {
    std::string dump = constToString(values[0]);
    for (size_t i = 1; i < values.size(); i++) {
        dump += ", " + constToString(values[i]);
    }
    return dump;
}

const char* toString(bool value);

/**
 * Add "prefix" to the beginning of each line in the provided string
 * "str".
 * The string 'str' is typically multi-line.
 * The most common use case for this function is to add some padding
 * when dumping state.
 */
std::string addLinePrefix(std::string str, const std::string& prefix);

} // namespace android
