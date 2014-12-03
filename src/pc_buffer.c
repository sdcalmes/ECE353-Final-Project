#include "pc_buffer.h"

void pc_buffer_init(PC_Buffer *buffer, char* array, uint16_t buffer_size)
{
   buffer->array = array;
   buffer->BUFFER_SIZE = buffer_size;
   buffer->produce_count = 0;
   buffer->consume_count = 0;
}

void pc_buffer_add(PC_Buffer *buffer, char data)
{
  buffer->array[buffer->produce_count % buffer->BUFFER_SIZE] = data;
  buffer->produce_count++;
}

void pc_buffer_remove(PC_Buffer *buffer, char *data)
{
  *data = buffer->array[buffer->consume_count % buffer->BUFFER_SIZE];
  buffer->consume_count++;
}

bool pc_buffer_empty(PC_Buffer *buffer)
{
  if(buffer->produce_count == buffer->consume_count)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool pc_buffer_full(PC_Buffer *buffer)
{
  if( (buffer->produce_count - buffer->consume_count) == buffer->BUFFER_SIZE)
  {
    return true;
  }
  else
  {
    return false;
  }
}
