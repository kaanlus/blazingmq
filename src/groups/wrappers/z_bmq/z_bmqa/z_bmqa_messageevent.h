#ifndef INCLUDED_Z_BMQA_MESSAGEEVENT
#define INCLUDED_Z_BMQA_MESSAGEEVENT

#if defined(__cplusplus)
extern "C" {
#endif

#include <z_bmqa_messageiterator.h>
#include <z_bmqt_messageeventtype.h>

typedef struct z_bmqa_MessageEvent z_bmqa_MessageEvent;

/**
 * @brief Deletes a bmqa::MessageEvent object and nullifies the pointer.
 *
 * This function deallocates the memory associated with a bmqa::MessageEvent object pointed to by the input parameter and sets the pointer to NULL, ensuring the object is properly destroyed and preventing memory leaks.
 * 
 * @param event_obj A pointer to a pointer to a bmqa::MessageEvent object. After deletion, this pointer will be set to NULL.
 * @return Returns 0 upon successful deletion.
 */

int z_bmqa_MessageEvent__delete(z_bmqa_MessageEvent** event_obj);

/**
 * @brief Creates a new bmqa::MessageEvent object.
 *
 * This function allocates and initializes a new bmqa::MessageEvent object, setting the input pointer to point to it. It provides a way to dynamically create event objects that can later be populated with event-specific data.
 * 
 * @param event_obj A pointer to a pointer that will be updated to point to the newly created bmqa::MessageEvent object.
 * @return Returns 0 upon successful creation of the event object.
 */

int z_bmqa_MessageEvent__create(z_bmqa_MessageEvent** event_obj);

/**
 * @brief Retrieves a message iterator for iterating over messages in a bmqa::MessageEvent object.
 *
 * This function initializes a new message iterator based on the messages contained within the specified event object. It allows for sequential access to the individual messages associated with an event.
 * 
 * @param event_obj A constant pointer to the bmqa::MessageEvent object from which to retrieve the iterator.
 * @param iterator_obj A pointer to a pointer that will be updated to point to the newly created bmqa::MessageIterator object.
 * @return Returns 0 upon successful creation of the message iterator.
 */

int z_bmqa_MessageEvent__messageIterator(
    const z_bmqa_MessageEvent* event_obj,
    z_bmqa_MessageIterator**   iterator_obj);

/**
 * @brief Retrieves the type of a bmqa::MessageEvent object.
 *
 * This function returns the event type of the specified bmqa::MessageEvent object. Event types are used to distinguish between different kinds of events that can occur in a messaging system.
 * 
 * @param event_obj A constant pointer to the bmqa::MessageEvent object whose type is to be determined.
 * @return Returns the type of the event, as a value from the z_bmqt_MessageEventType::Enum enumeration.
 */

z_bmqt_MessageEventType::Enum
z_bmqa_MessageEvent__type(const z_bmqa_MessageEvent* event_obj);

/**
 * @brief Converts a bmqa::MessageEvent object to a string representation.
 *
 * This function creates a string representation of the specified bmqa::MessageEvent object, which can include details such as event type, associated messages, and other relevant information. This is useful for logging, debugging, or displaying event information in a human-readable format.
 * 
 * @param event_obj A constant pointer to the bmqa::MessageEvent object to be converted to string.
 * @param out A pointer to a character pointer that will be updated to point to the newly allocated string representing the event. The caller is responsible for freeing this memory.
 * @return Returns 0 upon successful conversion of the event to a string.
 */

int z_bmqa_MessageEvent__toString(const z_bmqa_MessageEvent* event_obj,
                                  char**                     out);

#if defined(__cplusplus)
}
#endif

#endif
