AAClip* create_aa_clip()
{
  AAClip *clip = malloc(sizeof(AAClip));
  clip->bounds.setEmpty();
  clip->run_head = nullptr;
  return clip;
}

AAClip* create_aa_clip(const AAClip& src)
{
  AAClip* clip = malloc(sizeof(AAClip));
  clip->run_head = nullptr;
  *clip = src;
  return clip;
}

void delete_aa_clip(AAClip* clip)
{
  free_runs_aa_clip(clip);
}
