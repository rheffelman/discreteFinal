float weights[] = {0.333f};

float weights[] = {0.333f, 0.6f, 0.0666f, 0.0f};
float temp[4];

float32x4_t * w = (float32x4_t *) weights;
float32x4_t * t = (float32x4_t *) temp;
float32x4_t * s = (float32x4_t *) src.data;
int * d = src.gray_data;

for (long pix_num = 0; pix_num < src.width * src.height; pix_num++){
    float sum;
    *t = vmulq_f32(*w, *(s++));
    sum = vaddvq_f32(*t);
    *(d++) = int(sum * src.max_value);
}