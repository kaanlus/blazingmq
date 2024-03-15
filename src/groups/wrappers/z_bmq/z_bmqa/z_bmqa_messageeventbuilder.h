#ifndef INCLUDED_Z_BMQA_MESSAGEEVENTBUILDER
#define INCLUDED_Z_BMQA_MESSAGEEVENTBUILDER
#include <z_bmqa_queueid.h>

#if defined(__cplusplus)
extern "C" {
#endif

#include <z_bmqa_message.h>
#include <z_bmqa_messageevent.h>

typedef struct z_bmqa_MessageEventBuilder z_bmqa_MessageEventBuilder;

/**
 * @brief Deletes a bmqa::MessageEventBuilder object and nullifies the pointer.
 *
 * This function deallocates the memory associated with a bmqa::MessageEventBuilder object pointed to by the input parameter and sets the pointer to NULL. This ensures the object is properly destroyed and prevents memory leaks.
 * 
 * @param builder_obj A pointer to a pointer to a bmqa::MessageEventBuilder object. After deletion, this pointer will be set to NULL.
 * @return Returns 0 upon successful deletion.
 */

int z_bmqa_MessageEventBuilder__delete(
    z_bmqa_MessageEventBuilder** builder_obj);

/**
 * @brief Creates a new bmqa::MessageEventBuilder object.
 *
 * This function allocates and initializes a new bmqa::MessageEventBuilder object, setting the input pointer to point to it. It provides a mechanism for building message event objects dynamically.
 * 
 * @param builder_obj A pointer to a pointer that will be updated to point to the newly created bmqa::MessageEventBuilder object.
 * @return Returns 0 upon successful creation of the builder object.
 */

int z_bmqa_MessageEventBuilder__create(
    z_bmqa_MessageEventBuilder** builder_obj);

/**
 * @brief Initiates the creation of a new message within the event builder.
 *
 * This function starts the process of adding a new message to the event being built, providing access to the message object for further modification. It is part of the message event construction workflow in which messages are sequentially added to an event.
 * 
 * @param builder_obj A pointer to the bmqa::MessageEventBuilder object being used to construct the event.
 * @param out_obj A pointer to a pointer that will be updated to point to the newly initiated bmqa::Message object for further modifications.
 * @return Returns 0 upon successful initiation of a new message.
 */

int z_bmqa_MessageEventBuilder__startMessage(
    z_bmqa_MessageEventBuilder* builder_obj,
    z_bmqa_Message**            out_obj);

/**
 * @brief Finalizes the current message and associates it with a queue ID.
 *
 * This function completes the preparation of the current message being constructed and associates it with the specified queue ID. It marks the message as ready to be included in the message event being built.
 * 
 * @param builder_obj A pointer to the bmqa::MessageEventBuilder object.
 * @param queueId A constant pointer to a z_bmqa_QueueId identifying the queue associated with the message.
 * @return Returns 0 upon successful packing of the message, or a non-zero error code if the operation fails.
 */

int z_bmqa_MessageEventBuilder__packMessage(
    z_bmqa_MessageEventBuilder* builder_obj,
    const z_bmqa_QueueId*       queueId);

/**
 * @brief Resets the state of the bmqa::MessageEventBuilder object.
 *
 * This function clears the current state of the event builder, removing any messages that have been added so far. It allows the builder to be reused for constructing a new message event from scratch.
 * 
 * @param builder_obj A pointer to the bmqa::MessageEventBuilder object to be reset.
 * @return Returns 0 upon successful reset of the builder.
 */

int z_bmqa_MessageEventBuilder__reset(z_bmqa_MessageEventBuilder* builder_obj);

/**
 * @brief Retrieves the current message event being constructed.
 *
 * This function provides access to the message event that is currently being built by the event builder. It allows for inspection or further manipulation of the event before finalization.
 * 
 * @param builder_obj A pointer to the bmqa::MessageEventBuilder object.
 * @param event_obj A pointer to a pointer that will be updated to point to the current bmqa::MessageEvent object being constructed.
 * @return Returns 0 upon successful retrieval of the message event.
 */

int z_bmqa_MessageEventBuilder__messageEvent(
    z_bmqa_MessageEventBuilder* builder_obj,
    const z_bmqa_MessageEvent** event_obj);

/**
 * @brief Retrieves the current message being edited in the event builder.
 *
 * This function provides access to the message currently being constructed or edited within the event builder. It allows for further modifications to the message before it is finalized and added to the event.
 * 
 * @param builder_obj A pointer to the bmqa::MessageEventBuilder object.
 * @param message_obj A pointer to a pointer that will be updated to point to the current bmqa::Message object being constructed or edited.
 * @return Returns 0 upon successful retrieval of the current message.
 */

int z_bmqa_MessageEventBuilder__currentMessage(
    z_bmqa_MessageEventBuilder* builder_obj,
    z_bmqa_Message**            message_obj);

/**
 * @brief Returns the number of messages currently included in the event being built.
 *
 * This function counts the messages that have been added to the message event currently under construction. It provides a way to query the number of messages that are part of the event, which can be useful for validation, logging, or conditional logic based on the size of the event.
 * 
 * @param builder_obj A constant pointer to the bmqa::MessageEventBuilder object being queried.
 * @return Returns the number of messages that have been added to the current message event.
 */

int z_bmqa_MessageEventBuilder__messageCount(
    const z_bmqa_MessageEventBuilder* builder_obj);

/**
 * @brief Returns the total size of the message event being built, in bytes.
 *
 * This function calculates the total size of the message event currently under construction, including all messages that have been added. This size can be useful for understanding the bandwidth requirements for transmitting the event or for storage considerations.
 * 
 * @param builder_obj A constant pointer to the bmqa::MessageEventBuilder object being queried.
 * @return Returns the total size of the message event, in bytes.
 */

int z_bmqa_MessageEventBuilder__messageEventSize(
    const z_bmqa_MessageEventBuilder* builder_obj);

#if defined(__cplusplus)
}
#endif

#endif