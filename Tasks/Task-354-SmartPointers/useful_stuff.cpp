#include "useful_stuff.hpp"

uint32_t print_memory_info() { 
    // Grab the heap statistics
    mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);
    std::cout << "Heap size: " << heap_stats.current_size << " / " << heap_stats.reserved_size << " bytes" << std::endl;
    return heap_stats.current_size;
}