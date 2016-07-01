/* Costruisce la tavola del gamma: table[x] = (x/255.)^gamma */
static void make_gamma_table(uint8_t table[256], Scalar gamma)
{
  const float dx = 1 / 255.0f;
  const float g = scalar_to_float(gamma);

  float x = 0;
  for (int i = 0; i < 256; i++)
  {
    // float ee = powf(x, g) * 255;
    table[i] = TPin(float_round_2_int(powf(x, g) * 255), 0, 255);
    x += dx;
  }
}
