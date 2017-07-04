/**
 * @file bbzmsg.h
 * @brief Definition of message types between robots.
 */

#ifndef BBZMSG_H
#define BBZMSG_H

#include "bbzinclude.h"
#include "bbzringbuf.h"

#ifndef BBZ_XTREME_MEMORY
#include <netinet/in.h>
#else
ALWAYS_INLINE uint16_t htons(uint16_t x) {return x;};
ALWAYS_INLINE uint16_t ntohs(uint16_t x) {return x;};
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Broadcast message data
 */
typedef struct {
    bbzmsg_payload_type_t type;
    bbzrobot_id_t rid;
    uint16_t topic; /**< @brief The topic of the broadcast. @note A string ID */
    bbzheap_idx_t value; /**< @brief The broadcasted value. */
} bbzmsg_broadcast_t;

/**
 * @brief Swarm message data
 */
typedef struct {
    bbzmsg_payload_type_t type;
    bbzrobot_id_t rid;
    bbzlamport_t lamport;
    bbzswarmlist_t swarms;
} bbzmsg_swarm_t;

/**
 * @brief Virtual stigmergy message data
 */
typedef struct {
    bbzmsg_payload_type_t type;
    bbzrobot_id_t rid;
    uint8_t lamport;
    uint16_t key;
    bbzheap_idx_t data;
} bbzmsg_vstig_t;

/**
 * @brief Generic message data
 */
typedef union {
    uint8_t type;
    bbzmsg_broadcast_t bc;
    bbzmsg_swarm_t sw;
    bbzmsg_vstig_t vs;
} bbzmsg_t;

/**
 * @brief Data of a message.
 */
typedef bbzringbuf_t bbzmsg_payload_t;

/**
 * @brief Serializes a 8-bit unsigned integer.
 * @details The data is appended to the given buffer.
 * @param[in,out] rb The buffer where the serialized data is appended.
 * @param[in] data The data to serialize.
 */
void bbzmsg_serialize_u8(bbzringbuf_t *rb,
                         uint8_t data);

/**
 * @brief Deserializes a 8-bit unsigned integer.
 * @details The data is read from the given buffer starting at the given
 * position.
 * @param[out] data The deserialized data of the element.
 * @param[in] rb The buffer where the serialized data is stored.
 * @param[in] pos The position at which the data starts.
 */
int16_t bbzmsg_deserialize_u8(uint8_t *data,
                              const bbzringbuf_t *rb,
                              uint16_t pos);

/**
 * @brief Serializes a 16-bit unsigned integer.
 * @details The data is appended to the given buffer.
 * @param[in,out] rb The buffer where the serialized data is appended.
 * @param[in] data The data to serialize.
 */
void bbzmsg_serialize_u16(bbzringbuf_t *rb,
                          uint16_t data);

/**
 * @brief Deserializes a 16-bit unsigned integer.
 * @details The data is read from the given buffer starting at the given
 * position.
 * @param[out] data The deserialized data of the element.
 * @param[in] rb The buffer where the serialized data is stored.
 * @param[in] pos The position at which the data starts.
 */
int16_t bbzmsg_deserialize_u16(uint16_t *data,
                               const bbzringbuf_t *rb,
                               uint16_t pos);

/**
 * @brief Serializes a BittyBuzz's object.
 * @details The data is appended to the given buffer.
 * @param[in,out] rb The buffer where the serialized data is appended.
 * @param[in] obj The object to serialize.
 */
void bbzmsg_serialize_obj(bbzringbuf_t *rb, bbzobj_t *obj);

/**
 * @brief Serializes a BittyBuzz's object.
 * @details The data is read from the given buffer starting at the given
 * position.
 * @param[out] data The deserialized data of the element.
 * @param[in] rb The buffer where the serialized data is stored.
 * @param[in] pos The position at which the data starts.
 */
int16_t bbzmsg_deserialize_obj(bbzobj_t *data, bbzringbuf_t *rb, uint16_t pos);

// +=-=-=-=-=-=-=-=-=-=-=-=-=-=+
// | Message utility functions |
// +=-=-=-=-=-=-=-=-=-=-=-=-=-=+

/**
 * @brief Applies a sorting algorithm to the given ring buffer.
 * @note It currently uses quicksort, but it could change in the futur.
 *       It also modifies the unused space at the end of the ring buffer.
 * @param[in,out] rb The ring buffer which we want to sort.
 */
void bbzmsg_sort_priority(bbzringbuf_t* rb);

/*
 * Uncomment this line if the sorting algorithm above needs
 * to be called when an element is removed from the ring buffer.
 */
//#define BBZMSG_POP_NEEDS_SORT

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !BBZMSG_H