#pragma once
#include <cstddef>
#include <string>

class Resource {
public:
    Resource(const char* start, const size_t len) : resource_data(start), data_len(len) {}

    const char * const &data() const { return resource_data; }
    const size_t &size() const { return data_len; }

    const char *begin() const { return resource_data; }
    const char *end() const { return resource_data + data_len; }

    std::string toString() const { return std::string(data(), size()); }

private:
    const char* resource_data;
    const size_t data_len;

};

#define LOAD_RESOURCE(RESOURCE) ([]() {                                       \
        extern const char resource_##RESOURCE[];                              \
        extern const size_t resource_##RESOURCE##_len;                        \
        return Resource(resource_##RESOURCE, resource_##RESOURCE##_len - 1);  \
        })()
