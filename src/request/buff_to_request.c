#include "request.h"

rq_req                 buff_to_request(char *buffer) {

  rq_req               request;
  char                 *data;
  int                  i;

  request.event = calloc(100, sizeof(char));
  for (i = 0; i < 100 && buffer[i] != '#'; i++)
    request.event[i] = buffer[i];

  request.data = calloc(100, sizeof(char));
  data = strchr(buffer, '#');
  if (data) {
    data++;
    memcpy(request.data, data, strlen(data));
    strcat(request.data, "\0");
  }
  else
    request.data = NULL;

  return (request);
}
