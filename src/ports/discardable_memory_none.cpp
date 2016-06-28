#import "discardable_memory.h"

DiscardableMemory* create_discardable_memory(size_t bytes)
{
  return create_gdmp(get_global_discardable_memory_pool(), bytes);
}
