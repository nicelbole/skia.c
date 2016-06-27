struct Data
{
  size_t size;
};

Data* create_data(size_t);
Data* create_data(const void*, size_t, ReleaseProc, void*);

inline size_t get_size(Data* data)
{
  return data->size;
}

inline bool is_empty_data(Data* data)
{
  return (data->size == 0);
}
