/* session.h
 * By Ron Bowes
 * March, 2013
 */

#ifndef __SESSION_H__
#define __SESSION_H__

#include <stdint.h>

#include "buffer.h"
#include "packet.h"

typedef enum
{
  SESSION_STATE_NEW,
  SESSION_STATE_ESTABLISHED
} session_state_t;

extern NBBOOL trace_packets;

typedef struct
{
  /* Session information */
  uint16_t        id;
  session_state_t state;
  uint16_t        their_seq;
  uint16_t        my_seq;
  NBBOOL          is_closed;
  char           *name;

  int             max_packet_size;

  buffer_t       *incoming_data;
  buffer_t       *outgoing_data;

  data_callback_t *outgoing_data_callback;
  void            *outgoing_data_callback_param;
} session_t;

session_t *session_create(data_callback_t *outgoing_data_callback, void *outgoing_data_callback_param, size_t max_size);
void       session_destroy(session_t *session);

void       session_set_name(session_t *session, char *name);

void       session_recv(session_t *session, packet_t *packet);
void       session_send(session_t *session, uint8_t *data, size_t length);
void       session_close(session_t *session);

void       session_do_actions(session_t *session);

void       session_go(session_t *session);

#endif
