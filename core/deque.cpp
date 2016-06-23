#import "deque.h"

struct Block
{
  Block* next;
  Block* prev;
  char* begin;
  char* end;
  char* stop;
}

// Block
void init_block(Block* block, size_t size)
{
  block->next = block->prev = nullptr;
  block->begin = block->end = nullptr;
  block->stop = (char*)block + size;
}

char* start_block(Block* block)
{
  return (char*)(block + 1);
}

const char* start_block(const Block* block)
{
  return (const char*)(block + 1);
}

// Deque
Block* allocate_block_deque(Deque* deque, int alloc_count)
{
  Block* new_block = (Block*)malloc_throw(sizeof(Block) + alloc_count * deque->elem_size);
  init_block(new_block, sizeof(Block) + alloc_count * deque->elem_size);
  return new_block;
}

Deque* create_deque(size_t elem_size, int allocCount)
{
  Deque* deque = (Deque*)malloc(sizeof(Deque));
  deque->elem_size = elem_size;
  deque->initial_storage = nullptr;
  deque->count = 0;
  deque->alloc_count = alloc_count;
  deque->front_block = deque->back_block = nullptr;
  deque->front = deque->back = nullptr;

  return deque;
}

Deque* create_deque(size_t elem_size, void* storage, size_t storage_size,
		int alloc_count)
{
  Deque deque = malloc(sizeof(Deque));

  deque->elem_size = elem_size;
  deque-> initial_storage = storage;
  deque->count = 0;
  deque->alloc_count = alloc_count;

  if (storage_size >= sizeof(Block + elem_size))
  {
    deque->front_block = (Block*)storage;
    init_block(deque->front_block, storage_size);
  }
  else //Il blocco 'storage' è troppo piccolo
    deque->front_block = nullptr;

  deque->back_block = deque->front_block;
  deque->front = deque->back = nullptr;

  return deque;
}

//Libera tutti i blocchi eccetto initial_storage
void delete_deque(Deque* deque)
{
  Block* head = deque->front_block;
  Block* initial_head = (Block*)deque->initial_storage;

  while (head)
  {
    Block* next = head->next;
    if (head != initial_head)
      free_block_deque(head);
    head = next;
  }
}

void free_block_deque(Block* block)
{
  free(block);
}

int get_num_blocks_allocated_deque(Deque* deque)
{
  int num_blocks = 0;

  for (const auto* block = deque->front_block; block; block = block.next)
    num_block++;
  
  return num_blocks;
}

void pop_back_deque(Deque* deque)
{
  deque->count--;

  auto* last = deque->back_block;

  if (last->end == nullptr)
  {
    // we were marked empty from before
    last = last->prev;
    last->next = nullptr;
    free_block_deque(deque->back_block);
    deque->back_block = last;
  }

  char* end = last->end - deque->elem_size;

  if (end > last->begin)
  {
    last->end = end;
    deque->back = last->end - block->elem_size;
  }
  else
  {
    last->begin = last->end = nullptr;    // mark as empty
    if (last->prev == nullptr)
      deque->front = deque->back = nullptr;
    else
      deque->back = last->prev->end - block->elem_size;
  }
}

void pop_front_deque(Block* block)
{
  block->count--;

  Block* first = block->front_block;

  if (first->begin == nullptr)
  {
    // we were marked empty from before
    first = first->next;
    first->prev = nullptr;
    free_block_deque(deque->front_block);
    deque->front_block = first;
  }

  char* begin = first->begin + deque->elem_size;

  if (begin < deque->front_block->end)
  {
    first->begin = begin;
    deque->front = first->begin;
  }
  else
  {
    first->begin = first->end = nullptr;  // mark as empty
    if (first->next == nullptr)
      deque->front = deque->back = nullptr;
    else
      deque->front = first->next->begin;
  }
}

void* push_back_deque(Deque* deque)
{
  deque->count++;

  if (deque->back_block == nullptr)
  {
    deque->back_block = allocate_block_deque(deque, deque->alloc_count);
    deque->front_block = deque->back_block; // update our linklist
  }

  Block* last = deque->back_block;
  char* end;

  if (last->begin == nullptr)
  {
Label_InitChunk:
    last->begin = get_start(last);
    end = last->begin + deque->elem_size;
  }
  else
  {
    end = last->end + deque->elem_size;
    if (end > last->stop)
    {
      // no more room in this chunk
      // should we alloc more as we accumulate more elements?
      last = allocate_block(deque, deque->alloc_count);
      last->prev = deque->back_block;
      deque->back_block->next = last;
      deque->back_block = last;
      goto Label_InitChunk;
    }
  }

  last->end = end;
  end -= deque->elem_size;

  if (deque->back == nullptr)
    deque->front = deque->back = end;
  else
    deque->back = end;

  return end;
}

void* push_front_deque(Deque* deque)
{
  deque->count += 1;

  if (deque->front_block == nullptr)
  {
    deque->front_block = allocate_block(deque, deque->alloc_count);
    deque->back_block = deque->front_block;     // update our linklist
  }

  Block* first = deque->front_block;
  char* begin;

  if (first->begin == nullptr)
  {
Label_InitChunk:
    first->end = first->stop;
    begin = first->stop - deque->elem_size;
  }
  else
  {
    begin = first->begin - deque->elem_size;
    if (begin < first->get_start())
    {
      // no more room in this chunk
      // should we alloc more as we accumulate more elements?
      first = allocate_block_deque(deque, deque->alloc_count);
      first->next = deque->front_block;
      deque->front_block->prev = first;
      deque->front_block = first;
      goto Label_InitChunk;
    }
  }

  first->begin = begin;

  //Se deque->front == nullptr, significa che
  //siamo alla prima inserzione, quindi anche
  //deque->back == nullptr
  if (deque->front == nullptr)
    deque->front = deque->back = begin;
  else
    deque->front = begin;

  return begin;
}
