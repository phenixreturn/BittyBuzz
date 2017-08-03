function (config_value value default)
    if("${${value}}" STREQUAL "")
        message(STATUS "Using default value for ${value} (-D${value}=${default})")
        set(${value} ${default} PARENT_SCOPE)
    endif()
endfunction()

if (BBZ_XTREME_MEMORY STREQUAL "ON")
    config_value(BBZHEAP_SIZE 1024)
else()
    config_value(BBZHEAP_SIZE 3072)
endif ()
config_value(BBZHEAP_ELEMS_PER_TSEG 5)
config_value(BBZSTACK_SIZE 96)
config_value(BBZVSTIG_CAP 3)
config_value(BBZNEIGHBORS_CAP 15)
config_value(BBZINMSG_QUEUE_CAP 10)
config_value(BBZOUTMSG_QUEUE_CAP 10)
config_value(RESERVED_ACTREC_MAX 24)
config_value(BBZLAMPORT_THRESHOLD 50)
config_value(BBZHEAP_GCMARK_DEPTH 8)
config_value(BBZMSG_IN_PROC_MAX 10)

# Set the XTREME memory optimization to false if it hasn't been set yet.
option(BBZ_XTREME_MEMORY "Whether to enable high memory-optimization." OFF)
option(BBZ_USE_PRIORITY_SORT "Wether to use priority sort on out-messages queue." OFF)
option(BBZ_USE_FLOAT "Wether to use float type." OFF)
option(BBZ_DISABLE_NEIGHBORS "Wether to disable usage of neighbor's data structure and messages." OFF)
option(BBZ_DISABLE_VSTIGS "Wether to disable usage of virtual stigmergies's data structure and messages." OFF)
option(BBZ_DISABLE_SWARMS "Wether to disable usage of swarms's data structure and messages." OFF)
option(BBZ_DISABLE_MESSAGES "Wether to disable usage and transfert of any kind of Buzz message." OFF)